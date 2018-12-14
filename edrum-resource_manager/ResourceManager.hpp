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
	    destroy();
    }

    bool initialize(const std::string& local_path = "./local/", const std::string& my_path = "./mylist/");
    void destroy();
    inline ServerList* getServerlist() {return list_server;}
    inline LocalList* getLocallist() {return list_local;}
    inline MyList* getMylist() {return list_my;}
};

#endif
