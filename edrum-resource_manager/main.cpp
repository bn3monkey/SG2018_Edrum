#include "ResourceManager.hpp"
#include <memory>
int main()
{
    std::shared_ptr<ResourceManager> pRM = std::make_shared<ResourceManager>();
    pRM->initialize();
   
    ServerList* pServer = pRM->getServerlist();
    pServer->initialize();
    pServer->updatePage(0);
    
    LocalList* pLocal = pRM->getLocallist();
    pLocal->initialize();
    pLocal->updatePage(0);

    MyList* pMy = pRM->getMylist();
    pMy->initialize();
    pMy->updatePage(0);

    return 0;
}