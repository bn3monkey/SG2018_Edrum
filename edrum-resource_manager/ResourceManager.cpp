#include "ResourceManager.hpp"

bool ResourceManager::initialize(const std::string& local_path, const std::string& my_path )
{
    pCM = new CommunicationModule();
    if(!pCM)
    {
        std::cout << "ERROR : CommunicationModule ALLOCATION FAIL!" << std::endl;
        return false;
    }
    if(!pCM->initialize())
    {
        std::cout << "ERROR : CommunicationModule INITIALIZATION FAIL!" << std::endl;
        return false;
    }
    
    list_server = new ServerList(*pCM);
    if(!list_server)
    {
        delete pCM;
        std::cout << "ERROR : SERVER_LIST ALLOCATION FAIL!" << std::endl;
        return false;
    }
    if(!list_server->initialize())
    {
        delete pCM;
        std::cout << "ERROR : SERVER_LIST INITIALIZATION FAIL!" << std::endl;
        return false;
    }

    list_local = new LocalList();
    if(!list_local)
    {
        delete pCM;
        delete list_server;
        std::cout << "ERROR : LOCAL_LIST ALLOCATION FAIL!" << std::endl;
        return false;
    }
    if(!list_local->initialize(local_path))
    {
        delete pCM;
        delete list_server;
        std::cout << "ERROR : LOCAL_LIST INITIALIZATION FAIL!" << std::endl;
        return false;
    }

    list_my = new MyList(*pCM);
    if(!list_my)
    {
        delete pCM;
        delete list_server;
        delete list_local;
        std::cout << "ERROR : MY_LIST ALLOCATION FAIL!" << std::endl;
        return false;
    }
    if(!list_my->initialize(my_path))
    {
        delete pCM;
        delete list_server;
        delete list_local;
        std::cout << "ERROR : MY_LIST INITIALIZATION FAIL!" << std::endl;
        return false;
    }
    return true;
}

void ResourceManager::destroy()
{
    if(list_server != nullptr)
        delete list_server;
    if(list_local != nullptr)
        delete list_local;
    if(list_my != nullptr)
        delete list_my;
    if(pCM != nullptr)
        delete pCM;
}
