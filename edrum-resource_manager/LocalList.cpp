#include "LocalList.hpp"
#include <algorithm>
#include <dirent.h>
/*
#include <filesystem>
namespace fs = std::experimental::filesystem::v1;
*/

#define MIN(a,b) ((a)<(b)?(a):(b))
// ���� List�� �ʱ�ȭ�Ѵ�.
bool LocalList::initialize(std::string path)
{
	// �ü���� ���Ͻý��ۿ� �°� ���ϵ��� �о�´�.
	/*
	for (auto & p : fs::directory_iterator(path))
	{
		SongData song;
		song.pre_read(path, p.path().filename().generic_string());
		all_songs.push_back(song);
	}
	*/
	this->path = path;
	
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

	//���� �̸��� �°� sorting�Ѵ�
	std::sort(all_songs.begin(), all_songs.end());

	//�� ó�� �������� ������Ʈ�Ѵ�
	updatePage(0);

	return true;
}
// Page�� update�Ѵ�. 
bool LocalList::updatePage(int page_num)
{
	int start = this->get_allsongnum(page_num, 0);	
	
	// �������� ���� ���������� �ϴ� ������ �ʰ��Ǿ��� ���
	printf("all_song_size : %d\n", all_songs.size());
	if ((int)all_songs.size() <= start)
	{
		page_num = all_songs.size() / page_size;
	}

	//���������� �� �������� �����Ѵ�.
	this->current_page = page_num;
	// ������ �������� �� ���� �ִ� ���� �ε����� ���Ѵ�.
	start = this->get_allsongnum(this->current_page, 0);
	int end = MIN( this->get_allsongnum(this->current_page, page_size - 1) , (int)all_songs.size() -1 );

	// ���� �� ����Ʈ�� �ʱ�ȭ�Ѵ�.
	for (int i = 0; i < page_size; i++)
		songs[i].clear();

	// ��ü �� ����Ʈ���� ���� �� ����Ʈ�� �ʿ��� ������ �����Ѵ�.
	song_len = 0;
	for (int i = start; i <= end; i++)
	{
		songs[song_len++] = all_songs[i];
	}

	return true;
}

// ���� Page�� �ش��ϴ� SongData�� �����Ѵ�.
bool LocalList::remove(int song_num)
{
	//1. ���� List���� �����Ѵ�.
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

	//2. ��ü List���� �����Ѵ�.
	size_t whole_songnum = this->get_allsongnum(this->current_page, song_num);
	if (whole_songnum >= all_songs.size())
	{
		std::cerr << "ERROR : LocalList remove (all_index error : " << whole_songnum << ", " << all_songs.size() << ")" << std::endl;
		return false;
	}
	all_songs.erase(all_songs.begin() + whole_songnum);

	//3. ���� Page�� �������Ʈ�Ѵ�.
	updatePage(current_page);

	return true;
}
