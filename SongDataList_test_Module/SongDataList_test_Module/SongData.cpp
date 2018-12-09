#include "SongData.hpp"
#include <string.h>

const int SongData::metadata_size = sizeof(server_id) + sizeof(local_id) +
sizeof(name) + sizeof(artist) + sizeof(date) + sizeof(ID) +
sizeof(drum_amount) + sizeof(note_amount);

// 곡으로부터 메타데이터를 읽어온다.
bool SongData::read_header()
{
	song.seekg(0, song.beg);

	char buffer[metadata_size + 1];
	song.read(buffer, metadata_size);
	if (!song.good())
	{
		std::cerr << "ERROR : read_header [" << this->filename  << "]" << std::endl;
		return false;
	}

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

	this->current_note = 0;

	return true;
}
// 현재 메타데이터를 DataFIle에 쓴다.
bool SongData::write_header()
{
	song.seekp(0, song.beg);

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

	song.write(buffer, metadata_size);
	if (!song.good())
	{
		std::cerr << "ERROR : write_header [" << this->filename << "]" << std::endl;
		return false;
	}

	this->current_note = 0;
	return true;
}
// 파일로부터 NoteData 하나를 읽어온다.
bool SongData::read_note(NoteData& note)
{
	song.seekg(metadata_size + this->current_note * sizeof(NoteData), song.beg);
	song.read((char *)(&note), sizeof(note));
	if (!song.good())
	{
		std::cerr << "ERROR : read_note (" << this->current_note << ") [" << this->filename << "]" << std::endl;
		return false;
	}
	++this->current_note;
	return true;
}
// 파일로부터 NoteData 하나를 쓴다.
bool SongData::write_note(const NoteData& note)
{
	song.seekp(metadata_size + this->current_note * sizeof(NoteData), song.beg);
	song.write((char *)(&note), sizeof(note));
	if (!song.good())
	{
		std::cerr << "ERROR : write_note (" << this->current_note << ") [" << this->filename << "]" << std::endl;
		return false;
	}
	++this->current_note;
	return true;
}
//파일을 연다.
bool SongData::open(std::string filename)
{
	song.open(filename, std::ios::in | std::ios::binary);
	if (!song.is_open())
	{
		std::cerr << "ERROR : open [" << filename << "]" << std::endl;
		return false;
	}
	filename = this->filename;
	return true;
}
bool SongData::create(std::string filename)
{
	song.open(filename, std::ios::out | std::ios::binary);
	if (!song.is_open())
	{
		std::cerr << "ERROR : create [" << filename << "]" << std::endl;
		return false;
	}
	filename = this->filename;
	return true;
} 
// 파일을 닫는다.
void  SongData::close()
{
	song.close();
}

/* filename에 해당하는 파일을 읽어 메타데이터를 구성한다. */
/* 파일이 없으면 false를 리턴한다. */
bool SongData::pre_read(char* filename)
{
	if (!open(filename))
	{
		std::cerr << "ERROR : pre_read [" << filename << "]" << std::endl;
		return false;
	}
	if (!read_header())
	{
		std::cerr << "ERROR : pre_read [" << filename << "]" << std::endl;
		return false;
	}
	return true;
}
/* filename에 해당하는 파일을 읽어 메타데이터를 받아온 뒤,
Note 정보들을 list에 넣는다 */
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

/* MetaData를 구성한다.*/
#define MIN(a,b) (a<b?a:b)
bool SongData::pre_write(int local_id, std::string name, std::string artist, std::string ID, int drum_amount, int note_amount)
{
	this->local_id = local_id;
	memcpy(this->name, name.c_str(), MIN(name.size(), sizeof(this->name)));
	memcpy(this->artist, artist.c_str(), MIN(artist.size(), sizeof(this->artist)));
	memcpy(this->ID, ID.c_str(), MIN(ID.size(), sizeof(this->ID)));
	this->drum_amount = drum_amount;
	this->note_amount = note_amount;
	set_filename();

	if (!create(get_filename()))
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
/* 현재 있는 MetaData를 바탕으로 파일을 쓴다 */
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
bool SongData::exist()
{
	song.open(this->filename, std::ios::in | std::ios::binary);
	if (song.is_open())
	{
		song.close();
		return true;
	}
	return false;
}
bool SongData::remove()
{
	// 해당 파일이 열려있으면 닫는다.
	if (song.is_open())
		song.close();
	if (std::remove(this->filename.c_str()))
		return false;
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
