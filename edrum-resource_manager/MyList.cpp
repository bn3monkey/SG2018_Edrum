	#include "MyList.hpp"

bool MyList::initialize(const std::string& path)
{
	if(!pCM->isinitialized())
	{
		std::cerr << "ERROR : ServerList -> Communication Module not initialized!" << std::endl;
		return false;
	}
	return LocalList::initialize(path);
}

bool MyList::insert(int local_id, std::string name, std::string artist, std::string ID , int drum_amount, const std::vector<NoteData> notelist)
{
	//1. check song if it exists
	SongData song;
	if (song.exist(path, name, artist, ID))
	{
		std::cerr << "ERROR : there is already file which has same name." << std::endl;
		return false;
	}
	//2. write songdata
	if (!song.pre_write(this->path, local_id, name, artist, ID, drum_amount, (int)notelist.size()))
	{
		std::cerr << "ERROR : mylist insert" << std::endl;
		return false;
	}
	if (!song.write(notelist) )
	{
		std::cerr << "ERROR : mylist insert" << std::endl;
		return false;
	}
	//3. push song to all_songs
	all_songs.push_back(song);

	//4. update page
	if (!updatePage(current_page))
	{
		std::cerr << "ERROR : mylist insert" << std::endl;
		return false;
	}
	return true;
}
bool MyList::upload(int song_num)
{
	if (song_num >= song_len || song_num < 0)
	{
		std::cerr << "ERROR : MyList upload (index error : " << song_num << ", " << page_size << ")" << std::endl;
		return false;
	}
	if(!pCM->upload(path, songs[song_num]))
	{
		std::cerr << "ERROR : MyList upload error!" << std::endl;
		return false;
	}
	return true;
}
bool MyList::uploadCancel(int song_num)
{
	if (song_num >= song_len || song_num < 0)
	{
		std::cerr << "ERROR : MyList upload cancel (index error : " << song_num << ", " << page_size << ")" << std::endl;
		return false;
	}
	if(!pCM->uploadCancel(songs[song_num]))
	{
		std::cerr << "ERROR : MyList upload cancel error!" << std::endl;
		return false;
	}
	return true;
}
