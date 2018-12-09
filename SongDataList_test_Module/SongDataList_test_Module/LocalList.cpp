#include "LocalList.hpp"
#include <algorithm>
#include <dirent.h>
/*
#include <filesystem>
namespace fs = std::experimental::filesystem::v1;
*/

#define MIN(a,b) ((a)<(b)?(a):(b))
// 현재 List를 초기화한다.
bool LocalList::initialize()
{
	// 운영체제의 파일시스템에 맞게 파일들을 읽어온다.
	/*
	for (auto & p : fs::directory_iterator(path))
	{
		SongData song;
		song.pre_read(path, p.path().filename().generic_string());
		all_songs.push_back(song);
	}
	*/
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

	//파일 이름에 맞게 sorting한다
	std::sort(all_songs.begin(), all_songs.end());

	//맨 처음 페이지를 업데이트한다
	updatePage(0);

	return true;
}
// Page를 update한다. 
bool LocalList::updatePage(int page_num)
{
	int start = this->get_allsongnum(page_num, 0);	
	
	// 수정으로 인해 가져오고자 하는 범위가 초과되었을 경우
	printf("all_song_size : %d\n", all_songs.size());
	if ((int)all_songs.size() <= start)
	{
		page_num = all_songs.size() / page_size;
	}

	//가져오고자 할 페이지를 저장한다.
	this->current_page = page_num;
	// 가져올 페이지의 맨 끝에 있는 곡의 인덱스를 정한다.
	start = this->get_allsongnum(this->current_page, 0);
	int end = MIN( this->get_allsongnum(this->current_page, page_size - 1) , (int)all_songs.size() -1 );

	// 현재 곡 리스트를 초기화한다.
	for (int i = 0; i < page_size; i++)
		songs[i].clear();

	// 전체 곡 리스트에서 현재 곡 리스트로 필요한 값들을 복사한다.
	song_len = 0;
	for (int i = start; i <= end; i++)
	{
		songs[song_len++] = all_songs[i];
	}

	return true;
}
// 현재 Page에 해당하는 SongData를 가져온다.
SongData* LocalList::getSong(int song_num)
{
	return &songs[song_num];
}
// 현재 Page에 해당하는 SongData를 삭제한다.
bool LocalList::remove(int song_num)
{
	//1. 현재 List에서 삭제한다.
	if (song_num >= song_len)
	{
		std::cerr << "ERROR : LocalList remove (index error : " << song_num << ", " << page_size << ")" << std::endl;
		return false;
	}
	if (!songs[song_num].remove(path))
	{
		std::cerr << "ERROR : LocalList remove " << std::endl;
		return false;
	}
	songs[song_num].clear();

	//2. 전체 List에서 삭제한다.
	size_t whole_songnum = this->get_allsongnum(this->current_page, song_num);
	if (whole_songnum >= all_songs.size())
	{
		std::cerr << "ERROR : LocalList remove (all_index error : " << whole_songnum << ", " << all_songs.size() << ")" << std::endl;
		return false;
	}
	all_songs.erase(all_songs.begin() + whole_songnum);

	//3. 현재 Page를 재업데이트한다.
	updatePage(current_page);

	return true;
}
