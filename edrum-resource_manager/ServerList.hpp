#ifndef __SERVER_LIST__
#define __SERVER_LIST__

#include "SongList.hpp"
#include <vector>

class ServerList : public SongList
{
protected:
	std::vector<SongData> all_songs;
	inline int get_allsongnum(int page_num, int song_num)
	{
		return page_num * page_size + song_num;
	}

public:
	ServerList()
	{
	}
	~ServerList() {}
	// initialize list
	bool initialize(const std::string& path="");
	// update page by page_num 
	bool updatePage(int page_num);
	// get song which matehs song_num in current page
	//SongData* getSong(int song_num);
	int getMaxpage();

	// download data file by using metadata in song data 
	bool download(int page_num);
	// cancel data file by using metadata in song data 
	bool download_cancel(int page_num);
};

#endif
