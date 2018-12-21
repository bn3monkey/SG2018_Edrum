#include "CommunicationModule.hpp"
#include <iostream>
CommunicationModule* pCM;
SongData makeSong(int local_id, std::string name, std::string artist, std::string ID)
{
    SongData song1;
    std::vector<NoteData> notes;
    int drum_amount = 1;

    for (int i = 0; i < 10; i++)
	{
		NoteData note(1 + 500 * i, 1, 200);
		notes.push_back(note);
	}

    if (song1.pre_write("./mylist/", local_id, name, artist, ID, drum_amount, notes.size()) == true)
    {
	    song1.write(notes);
    }
    return song1;
}
int upload_test(int local_id, std::string name, std::string artist, std::string ID)
{
     SongData e;
     e = makeSong(local_id, name, artist, ID);
     pCM->upload("./mylist/", e);
     std::cout << "e.server_id : " << e.server_id << std::endl;
     pCM->uploadCancel(e);
     return 1;
}
int uploadCancel_test(int server_id)
{
     SongData e;
     e.server_id = server_id;
     pCM->uploadCancel(e);
     return 1;
}
int Download_test(int server_id)
{
    SongData song2;
    song2.server_id = server_id;
    pCM->download("./local/", song2);
    printf("Song Name : %s\name", song2.name);
    return 1;
}

void login_test()
{
    bool result;
    std::string id;
    std::string password;
    do
    {
        std::cout << "-----Login-----" << std::endl;
        std::cout << "Enter your id" << std::endl;
        std::cin >> id;
        if(!id.compare("."))
        {
            std::cout << "OUT!!" << std::endl;
            return;
        }
        std::cout << "Enter your password" << std::endl;
        std::cin >> password;
        if(!password.compare("."))
        {
            std::cout << "OUT!!" << std::endl;
            return;
        }
        result = pCM->login(id, password);
        if(result)
        {
            std::cout << "Login Success!" << std::endl;
        }
        else
        {
            std::cout << "Login Fail!" << std::endl;
        }
    } while(!result);
}
void signup_test()
{
    bool result;
    std::string id, password;
    do
    {
        std::cout << "-----Sign up-----" << std::endl;
        std::cout << "Enter your id" << std::endl;
        std::cin >> id;
        if(!id.compare("."))
        {
            std::cout << "OUT!!" << std::endl;
            return;
        }
        std::cout << "Enter your password" << std::endl;
        std::cin >> password;
        if(!password.compare("."))
        {
            std::cout << "OUT!!" << std::endl;
            return;
        }

        result = pCM->signup(id, password);
        if(result)
        {
            std::cout << "Success!" << std::endl;
        }
        else
        {
            std::cout << "Redundant ID!" << std::endl;
        }

    } while(!result);
}

int main()
{
    pCM = new CommunicationModule();
    if(!pCM->initialize())
    {
        std::cout << "Not initialized" << std::endl;
        return false;
    }
    signup_test();
    login_test();
    //1. making SongData
    
    /*
    upload_test(0, "Mirror", "Guckkasten", "bn3monkey");
    upload_test(1, "Violet Wand", "Guckkasten", "bn3monkey");
    upload_test(2, "Maze", "Guckkasten", "bn3monkey");
    upload_test(3, "Faust", "Guckkasten", "bn3monkey");
    upload_test(4, "Rafflesia", "Guckkasten", "bn3monkey");
    upload_test(5, "Vitriol", "Guckkasten", "bn3monkey");
    upload_test(6, "Gavial", "Guckkasten", "bn3monkey");
    upload_test(7, "Limbo", "Guckkasten", "bn3monkey");
    upload_test(8, "Mandrake", "Guckkasten", "bn3monkey");
    upload_test(9, "Sink Hole", "Guckkasten", "bn3monkey");
    upload_test(10, "Tail", "Guckkasten", "bn3monkey");
    upload_test(11, "Toddle", "Guckkasten", "bn3monkey");
    upload_test(12, "Tail(Acoustic)", "Guckkasten", "bn3monkey");
    

    for(int i=0;i<10;i++)
        Download_test(i);

    std::vector<SongData> SongList;
    pCM->updatePage(5, 0, SongList);
    for(int i=0;i<(int)SongList.size();i++)
    {
        SongList[i].print();
    }
    pCM->updatePage(5, 1, SongList);
    for(int i=0;i<(int)SongList.size();i++)
    {
        SongList[i].print();
    }

    pCM->updatePage(5, 4, SongList);
    for(int i=0;i<(int)SongList.size();i++)
    {
        SongList[i].print();
    }
    pCM->updatePage(5, 5, SongList);
    for(int i=0;i<(int)SongList.size();i++)
    {
        SongList[i].print();
    }

    pCM->updatePage(5, 6, SongList);
    for(int i=0;i<(int)SongList.size();i++)
    {
        SongList[i].print();
    }
 
    std::cout << pCM->getAllpage(5) << std::endl;
*/

    pCM->destroy();
    delete pCM;

    return 0;
}