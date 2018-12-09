#ifndef __MY_LIST__
#define __MY_LIST__

#include "LocalList.hpp"

class MyList : public LocalList
{
public:
	MyList()
	{
		path = "./mylist/";
	}
	~MyList() {}
	/*
	// 현재 List를 초기화한다.
	bool initialize();
	// Page를 update한다. 
	bool updatePage(int page_num);
	// 현재 Page에 해당하는 SongData를 가져온다.
	SongData* getSong(int song_num);
	// 현재 Page에 해당하는 SongData를 삭제한다.
	bool remove(int song_num);
	*/

	// 현재 Page에 해당하는 SongData를 추가한다.
	bool insert(int local_id, std::string name, std::string artist, std::string ID, int drum_amount, const std::vector<NoteData> notelist);
	// 현재 Page에 해당하는 SongData를 업로드한다.
	bool upload(int song_num);
	// 현재 Page에 해당하는 SongData를 삭제한다.
	bool upload_cancel(int song_num);

};

#endif
