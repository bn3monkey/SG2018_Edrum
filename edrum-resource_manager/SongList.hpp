#ifndef __SONG_LIST__
#define __SONG_LIST__
#include "SongData.hpp"
class SongList
{
protected:
	// ���� SongList.cpp �ȿ�
	const static int page_size = 5;
	// ���� �����ְ� �ִ� page
	int current_page;
	// ���� �����ְ� �ִ� page�� �� ���
	SongData songs[page_size];
	// ���� �����ְ� �ִ� page�� �� �� ��ȿ�� ����� ����
	int song_len;
	// ���� list�� ���ϵ��� ����� directory
	std::string path;
	
public:
	SongList() {}
	virtual ~SongList() {}
	// ���� List�� �ʱ�ȭ�Ѵ�.
	virtual bool initialize(std::string path) = 0;
	// Page�� update�Ѵ�. 
	virtual bool updatePage(int page_num) = 0;
	// ���� Page�� �ش��ϴ� SongData�� �����´�.
	SongData* getSong(int song_num) { return &songs[song_num]; }

	// ������� ����, ���� �������� �� �����͵��� ���� �����ش�.
	void print();
};

#endif
