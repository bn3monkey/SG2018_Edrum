#ifndef __SONG_DATA__
#define __SONG_DATA__
#include <fstream>
#include <string>
#include <vector>
#include <iostream>

#include "../../edrum-hardware/Hardware_IO/NoteData.hpp"

class SongData
{
	// 곡에 쓰이는 드럼 개수
	int drum_amount;
	// 현재 곡에서 참조하고 있는 노트
	int current_note;
	// 곡에 쓰이는 노트 개수
	int note_amount;
	
	std::fstream song;
	
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
	bool open(std::string filename);
	// 파일을 만든다.
	bool create(std::string filename);
	// 파일을 닫는다.
	void  close();

	//내부에 있는 모든 변수를 초기값으로 초기화한다.
	void clear();

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

	// SongData 내부에 있는 파일명을 가져온다.
	inline std::string& get_filename()
	{
		return filename;
	}

	/* filename에 해당하는 파일을 읽어 메타데이터를 구성한다. */
	/* 파일이 없으면 false를 리턴한다. */
	bool pre_read(char* filename);
	/* filename에 해당하는 파일을 읽어 메타데이터를 받아온 뒤,
	Note 정보들을 list에 넣는다 */
	bool read(std::vector<NoteData>& notelist);
	
	/* MetaData를 구성한다.*/
	bool pre_write(int local_id, std::string name, std::string artist, std::string ID, int drum_amount, int note_amount);
	/* 현재 있는 MetaData를 바탕으로 파일을 쓴다 */
	bool write(const std::vector<NoteData>& notelist);
};

#endif