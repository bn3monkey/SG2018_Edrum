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
	// ���� List�� �ʱ�ȭ�Ѵ�.
	bool initialize(std::string path = "./local/");
	// Page�� update�Ѵ�. 
	bool updatePage(int page_num);
	// ���� Page�� �ش��ϴ� SongData�� �����´�.
	//SongData* getSong(int song_num);
	// ���� Page�� �ش��ϴ� SongData�� �����Ѵ�.
	bool remove(int song_num);
};

#endif
