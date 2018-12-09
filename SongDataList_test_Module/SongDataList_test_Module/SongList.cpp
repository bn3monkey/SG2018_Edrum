#include "SongList.hpp"

using namespace std;
void SongList::print()
{
	std::cout << "current_page : " << current_page << std::endl;

	for (int i = 0; i < page_size; i++)
	{
		std::cout << "------(" << i << ")------" << std::endl;
		std::cout << "server_id :" << songs[i].server_id << std::endl;
		std::cout << "local_id :" << songs[i].local_id << std::endl;
		std::cout << "name :" << songs[i].name << std::endl;
		std::cout << "artist :" << songs[i].artist << std::endl;
		std::cout << "date :" << songs[i].date << std::endl;
		std::cout << "ID :" << songs[i].ID << std::endl;
		std::cout << "---------------" << std::endl;
	}
}