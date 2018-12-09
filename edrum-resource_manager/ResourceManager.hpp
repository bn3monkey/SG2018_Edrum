#ifndef __RESOURCE_MANAGER__
#define __RESOURCE_MANAGER__

#include "ServerList.hpp"
#include "LocalList.hpp"
#include "MyList.hpp"

class ResourceManager
{
    ServerList* list_server;
    LocalList* list_local;
    MyList* list_my;
public:
    ResourceManager()
    {
        list_server = nullptr;
        list_local = nullptr;
        list_my = nullptr;
    }
    ~ResourceManager()
    {
        if(list_server != nullptr)
            delete list_server;
        if(list_local != nullptr)
            delete list_local;
        if(list_my != nullptr)
            delete list_my;
    }

    bool initialize();
    inline ServerList* getServerlist() {return list_server;}
    inline LocalList* getLocallist() {return list_local;}
    inline MyList* getMylist() {return list_my;}
};

#endif