#ifndef __SONG_LIST__
#define __SONG_LIST__
#include "SongData.hpp"
class SongList
{
protected:
	// 값은 SongList.cpp 안에
	const static int page_size = 5;
	// 현재 보여주고 있는 page
	int current_page;
	// 현재 보여주고 있는 page의 곡 목록
	SongData songs[page_size];
	// 현재 보여주고 있는 page의 곡 중 유효한 곡들의 개수
	int song_len;
	// 현재 list의 파일들이 저장된 directory
	std::string path;
	
public:
	// 현재 List를 초기화한다.
	virtual bool initialize() = 0;
	// Page를 update한다. 
	virtual bool updatePage(int page_num) = 0;
	// 현재 Page에 해당하는 SongData를 가져온다.
	SongData* getSong(int song_num) { return &songs[song_num]; }

	// 디버깅을 위해, 현재 페이지의 곡 데이터들을 전부 보여준다.
	void print();
};

#endif