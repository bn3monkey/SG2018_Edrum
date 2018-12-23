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
        pCM = nullptr;
        std::cout << "ERROR : SERVER_LIST ALLOCATION FAIL!" << std::endl;
        return false;
    }
    if(!list_server->initialize())
    {
        delete pCM;
        pCM = nullptr;
        std::cout << "ERROR : SERVER_LIST INITIALIZATION FAIL!" << std::endl;
        return false;
    }

    list_local = new LocalList();
    if(!list_local)
    {
        delete pCM;
        pCM = nullptr;
        delete list_server;
        list_server = nullptr;
        std::cout << "ERROR : LOCAL_LIST ALLOCATION FAIL!" << std::endl;
        return false;
    }
    if(!list_local->initialize(local_path))
    {
        delete pCM;
        pCM = nullptr;
        delete list_server;
        list_server = nullptr;
        std::cout << "ERROR : LOCAL_LIST INITIALIZATION FAIL!" << std::endl;
        return false;
    }

    list_my = new MyList(*pCM);
    if(!list_my)
    {
        delete pCM;
        pCM = nullptr;
        delete list_server;
        list_server = nullptr;
        delete list_local;
        list_local = nullptr;
        std::cout << "ERROR : MY_LIST ALLOCATION FAIL!" << std::endl;
        return false;
    }
    if(!list_my->initialize(my_path))
    {
        delete pCM;
        pCM = nullptr;
        delete list_server;
        list_server = nullptr;
        delete list_local;
        list_local = nullptr;
        std::cout << "ERROR : MY_LIST INITIALIZATION FAIL!" << std::endl;
        return false;
    }
    return true;
}

void ResourceManager::destroy()
{
    if(list_server != nullptr)
    {
        delete list_server;
        list_server = nullptr;
    }
    std::cout << "SERVER_LIST DEALLOCATION" << std::endl;
    if(list_local != nullptr)
    {
        delete list_local;
        list_local = nullptr;
    }
    std::cout << "LOCAL_LIST DEALLOCATION" << std::endl;
    if(list_my != nullptr)
    {
        delete list_my;
        list_my = nullptr;
    }
    std::cout << "MY_LIST DEALLOCATION" << std::endl;
    if(pCM != nullptr)
    {
        delete pCM;
        pCM = nullptr;
    }
    std::cout << "COMMUNICATION MODULE DEALLOCATION" << std::endl;
}
