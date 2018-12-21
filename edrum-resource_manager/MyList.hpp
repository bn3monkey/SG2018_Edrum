#ifndef __MY_LIST__
#define __MY_LIST__

#include "LocalList.hpp"
#include "../edrum-communicator/CommunicationModule.hpp"

class MyList : public LocalList
{
	CommunicationModule* pCM;
public:
	MyList(CommunicationModule& _pCM)
	{
		path = "./mylist/";
		pCM = &_pCM;
	}
	~MyList() {}
	
	// initialize list
	bool initialize(const std::string& path = "./mylist/");
	/*
	// update page by page_num 
	bool updatePage(int page_num);
	// get song which matches song_num in current page
	SongData* getSong(int song_num);
	// remove song which matches song_num in current page
	bool remove(int song_num);
	// get amount of pages
	int getMaxpage();
	*/

	// insert song from meta data
	bool insert(int local_id, std::string name, std::string artist, std::string ID, int drum_amount, const std::vector<NoteData> notelist);
	// upload data file by using metadata in song data 
	bool upload(int song_num);
	// cancel data file by using metadata in song data 
	bool uploadCancel(int song_num);

};

#endif
