#include "ServerList.hpp"


bool ServerList::initialize(const std::string& path)
{
	return true;
}

bool ServerList::updatePage(int page_num)
{
	return true;
}
int ServerList::getMaxpage()
{
	return 1;
}
bool ServerList::download(int page_num)
{
	return true;
}

bool ServerList::download_cancel(int page_num)
{
	return true;
}