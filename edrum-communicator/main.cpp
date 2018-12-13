#include "CommunicationModule.hpp"

int main()
{
    CommunicationModule* pCM = new CommunicationModule();
    pCM->initialize();

    //1. making SongData
    int local_id = 234;
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
	if (song1.pre_write("./local/", local_id, name, artist, ID, drum_amount, notes.size()) == false)
		return false;
	song1.write(notes);

    pCM->upload("./local/", song1);

    pCM->destroy();
    delete pCM;

    return 0;
}