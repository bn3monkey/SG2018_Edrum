#ifndef __SONG_DATA__
#define __SONG_DATA__
#include <fstream>
#include <cstdio>
#include <string>
#include <vector>
#include <iostream>
#include <string.h>
#include "../../edrum-hardware/Hardware_IO/NoteData.hpp"

class SongData
{
	// 곡에 쓰이는 드럼 개수
	int drum_amount;
	// 현재 곡에서 참조하고 있는 노트
	int current_note;
	// 곡에 쓰이는 노트 개수
	int note_amount;
	
	// 실제 곡 데이터를 가지고 있는 곡 데이터 파일.
	std::fstream song;
	
	//파일이 있는 path명이다.
	//파일명은 만든사람ID_곡이름_작곡가.sdd 로 정의한다.
	std::string filename;
	inline void set_filename() 
	{
		filename = std::string(ID) + "_" + std::string(name) + "_" + std::string(artist) + ".sdd";
	};

	// 곡으로부터 메타데이터를 읽어온다.
	bool read_header();
	// 현재 메타데이터를 DataFIle에 쓴다.
	bool write_header();

	// 파일로부터 NoteData 하나를 읽어온다.
	bool read_note(NoteData& note);
	// 파일로부터 NoteData 하나를 쓴다.
	bool write_note(const NoteData& note);

	//파일을 연다.
	bool open(std::string path, std::string filename);
	// 파일을 만든다.
	bool create(std::string path, std::string filename);
	// 파일을 닫는다.
	void  close();
		
public:

	//server에서 쓰이는 id
	int server_id; //4byte
	 // local에서 부여되는 id
	int local_id; //4byte
	// 곡 이름
	char name[51]; //51byte
	// 작곡가
	char artist[51];
	// 날짜 정보의 표현
	char date[16];
	// 곡을 제작한 사람의 ID
	char ID[21];

	const static int metadata_size;

	

	SongData()
	{
		this->clear();		
	}

	//복사 생성자
	SongData(const SongData& e);
	SongData& operator=(const SongData& e);
	bool operator<(const SongData &e) {
		return (strcmp(this->name, e.name) < 0);
	}
	bool operator>(const SongData &e) {
		return (strcmp(this->name, e.name) > 0);
	}

	// SongData 내부에 있는 파일명을 가져온다.
	inline std::string& get_filename()
	{
		return filename;
	}
	/* filename에 해당하는 파일을 읽어 메타데이터를 구성한다. */
	/* 파일이 없으면 false를 리턴한다. */
	bool pre_read(std::string path, std::string filename);
	/* filename에 해당하는 파일을 읽어 메타데이터를 받아온 뒤,
	Note 정보들을 list에 넣는다 */
	bool read(std::vector<NoteData>& notelist);
	
	/* MetaData를 구성한다.*/
	bool pre_write(std::string path, int local_id, std::string name, std::string artist, std::string ID, int drum_amount, int note_amount);
	/* 현재 있는 MetaData를 바탕으로 파일을 쓴다 */
	bool write(const std::vector<NoteData>& notelist);

	/* 현재 객체에서 참조하고 있는 파일 이름으로 된 곡 데이터 파일이 존재하는지 확인한다. */
	bool exist(std::string path);
	// 미리 곡 데이터 파일을 만드는 패러미터들을 집어넣어 해당하는 곡 데이터 파일이 존재하는지 확인한다.
	bool exist(std::string path, std::string name, std::string artist, std::string ID);

	/* 현재 객체에서 참조하고 있는 파일 이름으로 된 곡 파일을 삭제한다. */
	bool remove(std::string path);
	// 현재 객체 내부에 있는 모든 변수를 초기값으로 초기화한다.
	void clear();
};

#endif
