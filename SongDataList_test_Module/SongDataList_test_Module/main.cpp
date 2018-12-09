#include "SongData.hpp"
int main()
{
	int local_id = 1;
	std::string name = "Mirror";
	std::string artist = "Guckkasten";
	std::string ID = "bn3monkey";
	std::vector<NoteData> notes;
	int drum_amount = 1;

	for (int i = 0; i < 10; i++)
	{
		NoteData note(1 + 500 * i, 1, 200);
		notes.push_back(note);
	}

	SongData song1;
	if (song1.pre_write(local_id, name, artist, ID, drum_amount, notes.size()) == false)
		return false;
	song1.write(notes);

	name.clear();
	artist.clear();
	ID.clear();
	notes.clear();
	local_id = 0;
	drum_amount = 0;

	std::string filename = song1.get_filename();
	song1.pre_read((char *)filename.c_str());
	song1.read(notes);

	for (size_t i = 0; i < notes.size(); i++)
		std::cout << "(time : " << notes[i].time << " drum : " << notes[i].drum << " power : " << notes[i].power << ")" << std::endl;

	return 0;
}