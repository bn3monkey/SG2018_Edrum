#include "ResourceManager.hpp"
#include <memory>
int main()
{
    std::shared_ptr<ResourceManager> pRM = std::make_shared<ResourceManager>();
    pRM->initialize();
   
    ServerList* pServer = pRM->getServerlist();
    pServer->initialize();
    pServer->updatePage(0);
    pServer->print();
    
    LocalList* pLocal = pRM->getLocallist();
    pLocal->initialize();
    pLocal->updatePage(0);
    pLocal->print();

    MyList* pMy = pRM->getMylist();
    pMy->initialize();
    pMy->updatePage(0);
    pMy->print();

    return 0;
}
