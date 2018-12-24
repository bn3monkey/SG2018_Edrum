#include "../edrum-hardware/Hardware_IO/Hardware_IO.hpp"
#include "../edrum-resource_manager/ResourceManager.hpp"
#include <memory>
#include <thread>
#include <chrono>

unsigned long long int elapsed = 0;
std::vector<NoteData> Notelist;
std::mutex Notelist_mutex;
std::vector<string> printed;
std::mutex printed_mutex;
int timer_toggle;
void ClearScreen()
{
    std::cout << std::string( 100, '\n' );
}
void timer()
{
    while(timer_toggle)
    {
        elapsed++;
        unsigned long long int note_time = Notelist.front().time;
        note_time - elapsed;
        if(note_time < elapsed)
        {
            Notelist_mutex.lock();
            Notelist.erase(Notelist.begin());
            Notelist_mutex.unlock();
        }
        ClearScreen();
        std::cout << "note_ time : " << note_time << std::endl;
        printed_mutex.lock();
        for(size_t i=0;i<printed.size();i++)
        {
            std::cout << printed[i] << std::endl;
        }
        printed_mutex.unlock();
        std::this_thread::sleep_for (std::chrono::milliseconds(1));
    }
}
int main()
{
	Hardware_IO::initialize();
	std::shared_ptr<ResourceManager> pRM = std::make_shared<ResourceManager>();
    pRM->initialize();
   
    pLocalList->updatePage(0);
    pLocalList->print();

    std::cout << "What do you want to play?" << std::endl;
    int number;
    std::cin >> number;

    SongData* song = pLocalList->getSong(number); 
    song->read(Notelist);

    std::function<void()> container;
    container = []() {
		std::unique_lock<std::mutex> lk(m);
		lk.unlock();
		cv.notify_all();
		printf("End!\n");
	};
	Hardware_IO::registCallback(container, np_ok);

    container;
    container = []() {
        Notelist_mutex.lock();
        unsigned long long int note_time = Notelist.front().time;
        Notelist_mutex.unlock();
        unsigned long long int time_gap = note_time - elapsed;
        if(time_gap <= 500)
        {
            if(time_gap > 400)
            {
                std::cout << "Miss" << std::endl;
            }
            else if(time_gap > 300)
            {
                std::cout << "bad" << std::endl;
            }
            else if(time_gap > 200)
            {
                std::cout << "soso" << std::endl;
            }
            else if(time_gap > 100)
            {
                std::cout << "good" << std::endl;
            }
            else if(time_gap > 0)
            {
                std::cout << "very good" << std::endl;
            }
        }
    };
    Hardware_IO::registerCallback(container, np_drum1);

	elapsed = 0;
    timer_toggle = 1;
    std::thread timer_thread = std::thread(timer);
	
	std::unique_lock<std::mutex> lk(m);
	cv.wait(lk);

    timer_toggle = 0;
    std::thread timer_thread.join();

	Hardware_IO::destroy();
}
