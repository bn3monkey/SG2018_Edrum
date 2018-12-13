#ifndef __LOCAL_LIST__
#define __LOCAL_LIST__

#include "SongList.hpp"
#include <vector>

class LocalList : public SongList
{
protected:
	std::vector<SongData> all_songs;
	inline int get_allsongnum(int page_num, int song_num)
	{
		return page_num * page_size + song_num;
	}

public:
	LocalList()
	{
	}
	~LocalList()
	{
		all_songs.clear();
	}
	// initialize list 
	bool initialize(const std::string& path = "./local/");
	// update page by page_num  
	bool updatePage(int page_num);
	// get song which matches song_num in current page
	//SongData* getSong(int song_num);
	// remove song which matches song_num in current page
	bool remove(int song_num);
};

#endif
