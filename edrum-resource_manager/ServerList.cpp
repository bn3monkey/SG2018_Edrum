#include "ServerList.hpp"


bool ServerList::initialize(const std::string& path)
{
	this->path = path;
	if(!pCM->isinitialized())
	{
		std::cerr << "ERROR : ServerList -> Communication Module not initialized!" << std::endl;
		return false;
	}
	return true;
}

bool ServerList::updatePage(int page_num)
{
	std::vector<SongData> temp_list;
	if(!pCM->updatePage(page_size, page_num, temp_list))
	{
		std::cerr << "ERROR : ServerList update Page error!" << std::endl;
		return false;
	}
	for(int i=0;i<page_size;i++)
	{
		songs[i] = temp_list[i];
		songs[i].set_filename();
	}
	this->current_page = page_num;
	return true;
}
int ServerList::getMaxpage()
{
	return pCM->getAllpage(page_size);
}
bool ServerList::download(int song_num)
{
	if (song_num >= song_len || song_num < 0)
	{
		std::cerr << "ERROR : ServerList download (index error : " << song_num << ", " << page_size << ")" << std::endl;
		return false;
	}
	if(existSong(song_num))
	{
		std::cerr << "ERROR : Already downloaded!" << std::endl;
		return false;
	}
	if(!pCM->download(path, songs[song_num]))
	{
		std::cerr << "ERROR : ServerList download error!" << std::endl;
		return false;
	}
	return true;
}

bool ServerList::downloadCancel(int song_num)
{
	//1. check if song_num is validates
	if (song_num >= song_len || song_num < 0)
	{
		std::cerr << "ERROR : ServerList download_cancel (index error : " << song_num << ", " << page_size << ")" << std::endl;
		return false;
	}
	if(!existSong(song_num))
	{
		std::cerr << "ERROR : there is no downloaded song!" << std::endl;
		return false;
	}
	// 2. remove song data
	if (!songs[song_num].remove(path))
	{
		std::cerr << "ERROR : ServerList download_cancel " << std::endl;
		return false;
	}
	return true;
}