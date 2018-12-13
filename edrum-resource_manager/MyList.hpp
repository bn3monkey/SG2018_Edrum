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
	
	// ���� List�� �ʱ�ȭ�Ѵ�.
	bool initialize(const std::string& path = "./mylist/");
	/*
	// Page�� update�Ѵ�. 
	bool updatePage(int page_num);
	// ���� Page�� �ش��ϴ� SongData�� �����´�.
	SongData* getSong(int song_num);
	// ���� Page�� �ش��ϴ� SongData�� �����Ѵ�.
	bool remove(int song_num);
	*/

	// ���� Page�� �ش��ϴ� SongData�� �߰��Ѵ�.
	bool insert(int local_id, std::string name, std::string artist, std::string ID, int drum_amount, const std::vector<NoteData> notelist);
	// ���� Page�� �ش��ϴ� SongData�� ���ε��Ѵ�.
	bool upload(int song_num);
	// ���� Page�� �ش��ϴ� SongData�� �����Ѵ�.
	bool upload_cancel(int song_num);

};

#endif
