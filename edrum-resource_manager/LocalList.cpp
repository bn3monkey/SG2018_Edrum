#include "LocalList.hpp"
#include <algorithm>
#include <dirent.h>
/*
#include <filesystem>
namespace fs = std::experimental::filesystem::v1;
*/

#define MIN(a,b) ((a)<(b)?(a):(b))
bool LocalList::initialize(const std::string& path)
{
	/*
	for (auto & p : fs::directory_iterator(path))
	{
		SongData song;
		song.pre_read(path, p.path().filename().generic_string());
		all_songs.push_back(song);
	}
	*/
	//1. set path
	this->path = path;

	//2. read all .sdd file in path and push it to all_songs
	DIR *dp;
	struct dirent *dirp;
	if((dp = opendir(path.c_str())) == NULL)
	{
		std::cerr << "ERROR : Locallist intialization : No path (" << path << ")" << std::endl;
		return false;
	}
	while ((dirp = readdir(dp)) != NULL)
	{
		if ( strncmp( dirp->d_name + strlen(dirp->d_name) - 4 , ".sdd", 4) )
			continue;
		SongData song;
		std::cout << std::string(dirp->d_name) << std::endl;
		song.pre_read(path, std::string(dirp->d_name));
		all_songs.push_back(song);
	}
	closedir(dp);

	// sort all_songs
	std::sort(all_songs.begin(), all_songs.end());

	// update page
	updatePage(0);

	return true;
} 
bool LocalList::updatePage(int page_num)
{
	int start = this->get_allsongnum(page_num, 0);	
	
	// check if page_num validates
	printf("all_song_size : %d\n", all_songs.size());
	if ((int)all_songs.size() <= start)
	{
		page_num = all_songs.size() / page_size;
	}

	// make page_num validates
	this->current_page = page_num;
	// get start and end
	start = this->get_allsongnum(this->current_page, 0);
	int end = MIN( this->get_allsongnum(this->current_page, page_size - 1) , (int)all_songs.size() -1 );

	// clear current song list
	for (int i = 0; i < page_size; i++)
		songs[i].clear();

	// set song list from all songs
	song_len = 0;
	for (int i = start; i <= end; i++)
	{
		songs[song_len++] = all_songs[i];
	}

	return true;
}

bool LocalList::remove(int song_num)
{
	//1. check if song_num is validates
	if (song_num >= song_len || song_num < 0)
	{
		std::cerr << "ERROR : LocalList remove (index error : " << song_num << ", " << page_size << ")" << std::endl;
		return false;
	}
	// 2. remove song data
	if (!songs[song_num].remove(path))
	{
		std::cerr << "ERROR : LocalList remove " << std::endl;
		return false;
	}
	// 3. remove song data from list
	songs[song_num].clear();

	// 4. remove song data from all_songs
	size_t whole_songnum = this->get_allsongnum(this->current_page, song_num);
	if (whole_songnum >= all_songs.size())
	{
		std::cerr << "ERROR : LocalList remove (all_index error : " << whole_songnum << ", " << all_songs.size() << ")" << std::endl;
		return false;
	}
	all_songs.erase(all_songs.begin() + whole_songnum);

	//5. update page
	updatePage(current_page);

	return true;
}
int LocalList::getMaxpage()
{
	int size = (int)all_songs.size();
	int quotient = size / this->page_size;
	int remain = size - (quotient * this->page_size);
	return remain ? quotient + 1 : quotient;
}