#ifndef __SONG_LIST__
#define __SONG_LIST__
#include "SongData.hpp"
class SongList
{
protected:
	const static int page_size = 5;

	int current_page;
	SongData songs[page_size];
	// length of songs
	int song_len;
	// path of list
	std::string path;
	
public:
	SongList() {}
	virtual ~SongList() {}
	// initialize list
	virtual bool initialize(const std::string& path) = 0;
	// update page by page_num 
	virtual bool updatePage(int page_num) = 0;
	// get song which matches song_num in current page
	SongData* getSong(int song_num) { return &songs[song_num]; }
	// get amount of page_size
	virtual int getMaxpage() = 0;

	// print page
	void print();
};

#endif
