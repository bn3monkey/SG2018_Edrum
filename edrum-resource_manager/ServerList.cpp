#include "ServerList.hpp"

// 현재 List를 초기화한다.
bool ServerList::initialize()
{
	return true;
}
// Page를 update한다. 
bool ServerList::updatePage(int page_num)
{
	return true;
}
// Server 목록에 있는 곡을 다운로드 받는다.
bool ServerList::download(int page_num)
{
	return true;
}
// Server 목록에 있는 곡의 다운로드를 취소한다.
bool ServerList::download_cancel(int page_num)
{
	return true;
}