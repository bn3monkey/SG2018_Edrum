#include "ResourceManager.hpp"

bool ResourceManager::initialize()
    {
        list_server = new ServerList();
        if(!list_server)
        {
            std::cout << "ERROR : SERVER_LIST INITIALIZATION FAIL!" << std::endl;
            return false;
        }

        list_local = new LocalList();
        if(!list_local)
        {
            delete list_server;
            std::cout << "ERROR : LOCAL_LIST INITIALIZATION FAIL!" << std::endl;
            return false;
        }

        list_my = new MyList();
        if(!list_my)
        {
            delete list_server;
            delete list_local;
            std::cout << "ERROR : MY_LIST INITIALIZATION FAIL!" << std::endl;
            return false;
        }
    }