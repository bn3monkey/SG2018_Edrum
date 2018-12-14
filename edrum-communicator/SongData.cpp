#include "SongData.hpp"
#include <string.h>

const int SongData::metadata_size = sizeof(server_id) + sizeof(local_id) +
sizeof(name) + sizeof(artist) + sizeof(date) + sizeof(ID) +
sizeof(drum_amount) + sizeof(note_amount);

SongData::SongData(const SongData& e)
{
	this->server_id = e.server_id;
	this->local_id = e.local_id;
	memcpy(this->name, e.name, sizeof(name));
	memcpy(this->artist, e.artist, sizeof(artist));
	memcpy(this->date, e.date, sizeof(date));
	memcpy(this->ID, e.ID, sizeof(ID));
	this->drum_amount = e.drum_amount;
	this->note_amount = e.note_amount;
	this->current_note = 0;
	this->filename = e.filename;
}
SongData& SongData::operator=(const SongData& e)
{
	this->server_id = e.server_id;
	this->local_id = e.local_id;
	memcpy(this->name, e.name, sizeof(name));
	memcpy(this->artist, e.artist, sizeof(artist));
	memcpy(this->date, e.date, sizeof(date));
	memcpy(this->ID, e.ID, sizeof(ID));
	this->drum_amount = e.drum_amount;
	this->note_amount = e.note_amount;
	this->current_note = 0;
	this->filename = e.filename;
	return *this;
}

bool SongData::read_header()
{
	//1. go to file
	song.seekg(0, song.beg);

	//2. read metadata stream
	char buffer[metadata_size + 1];
	song.read(buffer, metadata_size);
	if (!song.good())
	{
		std::cerr << "ERROR : read_header [" << this->filename  << "]" << std::endl;
		return false;
	}

	// set metadata
	int step = 0;
	memcpy((char *)(&server_id), buffer + step, sizeof(server_id));
	step += sizeof(server_id);
	memcpy((char *)(&local_id), buffer + step, sizeof(local_id));
	step += sizeof(local_id);
	memcpy(name, buffer + step, sizeof(name));
	step += sizeof(name);
	memcpy(artist, buffer + step, sizeof(artist));
	step += sizeof(artist);
	memcpy(date, buffer + step, sizeof(date));
	step += sizeof(date);
	memcpy(ID, buffer + step, sizeof(ID));
	step += sizeof(ID);
	memcpy((char *)&drum_amount, buffer + step, sizeof(drum_amount));
	step += sizeof(drum_amount);
	memcpy((char *)&note_amount, buffer + step, sizeof(note_amount));
	step += sizeof(note_amount);

	// intialize metadata
	this->current_note = 0;

	return true;
}

bool SongData::write_header()
{
	//1. go to file first
	song.seekp(0, song.beg);

	//2. move metadata to buffer
	char buffer[metadata_size + 1];
	memset(buffer, 0, metadata_size + 1);
	
	int step = 0;
	memcpy(buffer + step, (char *)&server_id, sizeof(server_id));
	step += sizeof(server_id);
	memcpy(buffer + step, (char *)&local_id, sizeof(local_id));
	step += sizeof(local_id);
	memcpy(buffer + step, name, sizeof(name));
	step += sizeof(name);
	memcpy(buffer + step, artist, sizeof(artist));
	step += sizeof(artist);
	memcpy(buffer + step, date, sizeof(date));
	step += sizeof(date);
	memcpy(buffer + step, ID, sizeof(ID));
	step += sizeof(ID);
	memcpy(buffer + step, (char *)&drum_amount, sizeof(drum_amount));
	step += sizeof(drum_amount);
	memcpy(buffer + step, (char *)&note_amount, sizeof(note_amount));
	step += sizeof(note_amount);

	//3. write buffer to file
	song.write(buffer, metadata_size);
	if (!song.good())
	{
		std::cerr << "ERROR : write_header [" << this->filename << "]" << std::endl;
		return false;
	}

	// intialize metadata
	this->current_note = 0;
	return true;
}

bool SongData::read_note(NoteData& note)
{
	// go to current note in file
	song.seekg(metadata_size + this->current_note * sizeof(NoteData), song.beg);
	// read note
	song.read((char *)(&note), sizeof(note));
	if (!song.good())
	{
		std::cerr << "ERROR : read_note (" << this->current_note << ") [" << this->filename << "]" << std::endl;
		return false;
	}
	// go to next current note
	++this->current_note;
	return true;
}

bool SongData::write_note(const NoteData& note)
{
	// go to current note in file
	song.seekp(metadata_size + this->current_note * sizeof(NoteData), song.beg);
	// write note
	song.write((char *)(&note), sizeof(note));
	if (!song.good())
	{
		std::cerr << "ERROR : write_note (" << this->current_note << ") [" << this->filename << "]" << std::endl;
		return false;
	}
	// go to next note
	++this->current_note;
	return true;
}

bool SongData::open(std::string path, std::string filename)
{
	song.open(path + filename, std::ios::in | std::ios::binary);
	if (!song.is_open())
	{
		std::cerr << "ERROR : open [" << filename << "]" << std::endl;
		return false;
	}
	this->filename = filename;
	return true;
}
bool SongData::create(std::string path, std::string filename)
{
	song.open(path + filename, std::ios::out | std::ios::binary);
	if (!song.is_open())
	{
		std::cerr << "ERROR : create [" << filename << "]" << std::endl;
		return false;
	}
	this->filename = filename;
	return true;
} 

void  SongData::close()
{
	song.close();
}


bool SongData::pre_read(std::string path, std::string filename)
{
	if (!open(path, filename))
	{
		std::cerr << "ERROR : pre_read [" << path + filename << "]" << std::endl;
		return false;
	}
	if (!read_header())
	{
		std::cerr << "ERROR : pre_read [" << path + filename << "]" << std::endl;
		return false;
	}
	return true;
}

bool SongData::read(std::vector<NoteData>& notelist)
{
	if (!song.is_open())
	{
		std::cerr << "ERROR : read (file is not open) [" << filename << "]" << std::endl;
		return false;
	}
	while (this->current_note < this->note_amount)
	{
		NoteData temp;
		if (!this->read_note(temp))
		{
			std::cerr << "ERROR : read [" << filename << "]" << std::endl;
		}
		notelist.push_back(temp);
	}
	this->close();
	return true;
}

#define MIN(a,b) (a<b?a:b)
bool SongData::pre_write(std::string path, int local_id, std::string name, std::string artist, std::string ID, int drum_amount, int note_amount)
{
	this->local_id = local_id;
	memcpy(this->name, name.c_str(), MIN(name.size(), sizeof(this->name)));
	memcpy(this->artist, artist.c_str(), MIN(artist.size(), sizeof(this->artist)));
	memcpy(this->ID, ID.c_str(), MIN(ID.size(), sizeof(this->ID)));
	this->drum_amount = drum_amount;
	this->note_amount = note_amount;
	set_filename();

	if (!create(path, get_filename()))
	{
		std::cerr << "ERROR : pre_write [" << filename << "]" << std::endl;
		return false;
	}
	if (!write_header())
	{
		std::cerr << "ERROR : pre_write [" << filename << "]" << std::endl;
		return false;
	}
	return true;
}

bool SongData::write(const std::vector<NoteData>& notelist)
{
	if (!song.is_open())
	{
		std::cerr << "ERROR : write (file is not open) [" << filename << "]" << std::endl;
		return false;
	}
	while (this->current_note < this->note_amount)
	{
		NoteData temp = notelist[this->current_note];
		if (!this->write_note(temp))
		{
			std::cerr << "ERROR : write [" << filename << "]" << std::endl;
		}
	}
	this->close();
	return true;
}
bool SongData::exist(std::string path)
{
	song.open(path + this->filename, std::ios::in | std::ios::binary);
	if (song.is_open())
	{
		song.close();
		return true;
	}
	return false;
}
bool SongData::exist(std::string path, std::string name, std::string artist, std::string ID)
{
	memcpy(this->name, name.c_str(), MIN(name.size(), sizeof(this->name)));
	memcpy(this->artist, artist.c_str(), MIN(artist.size(), sizeof(this->artist)));
	memcpy(this->ID, ID.c_str(), MIN(ID.size(), sizeof(this->ID)));
	set_filename();
	return this->exist(path);
}
bool SongData::remove(std::string path)
{
	if (song.is_open())
	{
		song.close();
	}
	if (std::remove((path + this->filename).c_str()))
	{
		std::cerr << "ERROR : remove [" << filename << "]" << std::endl;
		return false;
	}
	return true;
}
void SongData::clear()
{
	this->filename = "";
	this->server_id = 0;
	this->local_id = 0;
	memset(this->name, 0, 51);
	memset(this->artist, 0, 51);
	memset(this->date, 0, 16);
	memset(this->ID, 0, 21);
	current_note = 0;
}
void SongData::print()
{
	std::cout << "----------------------------" << std::endl;
	std::cout << "server_id :" << this->server_id << std::endl;
	std::cout << "local_id :" << this->local_id << std::endl;
	std::cout << "name :" << this->name << std::endl;
	std::cout << "artist :" << this->artist << std::endl;
	std::cout << "date :" << this->date << std::endl;
	std::cout << "ID :" << this->ID << std::endl;
	std::cout << "----------------------------" << std::endl;
}