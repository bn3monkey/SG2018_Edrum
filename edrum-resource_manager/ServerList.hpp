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
		path = "./local/";
	}
	~ServerList() {}
	// 현재 List를 초기화한다.
	bool initialize();
	// Page를 update한다. 
	bool updatePage(int page_num);
	// 현재 Page에 해당하는 SongData를 가져온다.
	//SongData* getSong(int song_num);
	
	// Server 목록에 있는 곡을 다운로드 받는다.
	bool download(int page_num);
	// Server 목록에 있는 곡의 다운로드를 취소한다.
	bool download_cancel(int page_num);
};

#endif
