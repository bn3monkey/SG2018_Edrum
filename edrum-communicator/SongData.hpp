#ifndef __SONG_DATA__
#define __SONG_DATA__
#include <fstream>
#include <cstdio>
#include <string>
#include <vector>
#include <iostream>
#include <string.h>
#include "NoteData.hpp"

class SongData
{
	// amount of drum
	int drum_amount;
	// the index of current note in note queue
	int current_note;
	// amount of note in note queue
	int note_amount;
	
	// fstream of song data file
	std::fstream song;
	
	//filename defines  "ID_SongName_Artist.sdd"
	std::string filename;
	// set filename from object
	inline void set_filename() 
	{
		filename = std::string(ID) + "_" + std::string(name) + "_" + std::string(artist) + ".sdd";
	};

	// read data file from metadata
	bool read_header();
	// write metadata to data_file
	bool write_header();

	// read one note from object
	bool read_note(NoteData& note);
	// write one note to object
	bool write_note(const NoteData& note);

	// open file
	bool open(std::string path, std::string filename);
	// create file
	bool create(std::string path, std::string filename);
	// close file.
	void  close();
		
public:

	// id used by server
	int server_id; //4byte
	// id used by local
	int local_id; //4byte
	// song name
	char name[51]; //51byte
	// song artist
	char artist[51];
	// date made by server
	char date[16];
	// uploader ID
	char ID[21];
	// metadata size
	const static int metadata_size;

	SongData()
	{
		this->clear();		
	}

	// copy constructor
	SongData(const SongData& e);
	SongData& operator=(const SongData& e);
	bool operator<(const SongData &e) {
		return (strcmp(this->name, e.name) < 0);
	}
	bool operator>(const SongData &e) {
		return (strcmp(this->name, e.name) > 0);
	}
	// get file name from song data
	inline std::string& get_filename()
	{
		return filename;
	}
	
	// read file from path and filename and make meta data in object
	// return false if there is no file.
	bool pre_read(std::string path, std::string filename);
	
	// if you first call pre_read, make notelist from data file.
	bool read(std::vector<NoteData>& notelist);
	
	// wrtie file using metadata from parameter
	bool pre_write(std::string path, int local_id, std::string name, std::string artist, std::string ID, int drum_amount, int note_amount);
	// write notelist by using metadata and note list
	bool write(const std::vector<NoteData>& notelist);

	// check file which its name same path exists  
	bool exist(std::string path);
	// check file which exists
	bool exist(std::string path, std::string name, std::string artist, std::string ID);

	// remove file which its name same path exists
	bool remove(std::string path);
	// clear object
	void clear();
};

#endif
