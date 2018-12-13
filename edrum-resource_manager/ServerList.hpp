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
	// ���� List�� �ʱ�ȭ�Ѵ�.
	bool initialize(const std::string& path="");
	// Page�� update�Ѵ�. 
	bool updatePage(int page_num);
	// ���� Page�� �ش��ϴ� SongData�� �����´�.
	//SongData* getSong(int song_num);
	
	// Server ��Ͽ� �ִ� ���� �ٿ�ε� �޴´�.
	bool download(int page_num);
	// Server ��Ͽ� �ִ� ���� �ٿ�ε带 ����Ѵ�.
	bool download_cancel(int page_num);
};

#endif
