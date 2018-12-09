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
		path = "./local/";
	}
	// 현재 List를 초기화한다.
	bool initialize();
	// Page를 update한다. 
	bool updatePage(int page_num);
	// 현재 Page에 해당하는 SongData를 가져온다.
	SongData* getSong(int song_num);
	// 현재 Page에 해당하는 SongData를 삭제한다.
	bool remove(int song_num);
};

#endif