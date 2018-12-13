#include "ServerList.hpp"

// ���� List�� �ʱ�ȭ�Ѵ�.
bool ServerList::initialize(std::string path)
{
	return true;
}
// Page�� update�Ѵ�. 
bool ServerList::updatePage(int page_num)
{
	return true;
}
// Server ��Ͽ� �ִ� ���� �ٿ�ε� �޴´�.
bool ServerList::download(int page_num)
{
	return true;
}
// Server ��Ͽ� �ִ� ���� �ٿ�ε带 ����Ѵ�.
bool ServerList::download_cancel(int page_num)
{
	return true;
}