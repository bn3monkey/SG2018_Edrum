#ifndef __SERVER_LIST__
#define __SERVER_LIST__

#include "SongList.hpp"
#include "../edrum-communicator/CommunicationModule.hpp"
#include <vector>

class ServerList : public SongList
{
protected:
	CommunicationModule* pCM;

public:
	ServerList(CommunicationModule& _pCM)
	{
		path = "./local/";
		pCM = &_pCM;
	}
	~ServerList() {}
	// initialize list
	bool initialize(const std::string& path="./local/");
	// update page by page_num 
	bool updatePage(int page_num);
	// get song which matehs song_num in current page
	//SongData* getSong(int song_num);
	int getMaxpage();

	// download data file by using metadata in song data 
	bool download(int song_num);
	// cancel data file by using metadata in song data 
	bool downloadCancel(int song_num);
};

#endif
