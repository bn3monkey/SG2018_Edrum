//#include "../edrum-hardware/Hardware_IO/Hardware_IO.hpp"
#include "../edrum-resource_manager/ResourceManager.hpp"
#include <memory>
int main()
{
	//Hardware_IO::initialize();
	std::shared_ptr<ResourceManager> pRM = std::make_shared<ResourceManager>();
    pRM->initialize();
   
    ServerList* pServer = pRM->getServerlist();
    pServer->updatePage(0);
    pServer->updatePage(1);
    pServer->print();
    pServer->download(3);

    std::cout << "All page : " << pServer->getMaxpage() << std::endl;
    //pServer->downloadCancel(3);
    //pServer->download(3);
    
    /*
    LocalList* pLocal = pRM->getLocallist();
    pLocal->updatePage(0);
    pLocal->print();
    */

    MyList* pMy = pRM->getMylist();
    pMy->updatePage(0);
    pMy->print();
    pMy->upload(3);
    //pMy->uploadCancel(3);   

	//Hardware_IO::destroy();
}
