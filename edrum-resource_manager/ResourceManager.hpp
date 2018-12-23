#ifndef __RESOURCE_MANAGER__
#define __RESOURCE_MANAGER__

#include "ServerList.hpp"
#include "LocalList.hpp"
#include "MyList.hpp"

class ResourceManager
{
    CommunicationModule* pCM;
    ServerList* list_server;
    LocalList* list_local;
    MyList* list_my;


public:
    ResourceManager()
    {
        pCM = nullptr;
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
<<<<<<< HEAD
    inline ServerList* getServerlist() {return list_server;}
    inline LocalList* getLocallist() {return list_local;}
=======
    inline LocalList* getLocallist() {return list_local;}
    inline ServerList* getServerlist() {return list_server;}
>>>>>>> 3b4bda4a21b670190fd4dc07ecd6e056e662f734
    inline MyList* getMylist() {return list_my;}
    inline CommunicationModule* getCM() {return pCM;}
};

#endif
