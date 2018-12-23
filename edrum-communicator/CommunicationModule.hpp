#ifndef __COMMUNICATION_MODULE__
#define __COMMUNICATION_MODULE__

#include <Python.h>
#include "../edrum-resource_manager/SongData.hpp"
#include <vector>
#include <string>
class CommunicationModule
{
    bool initialized;
    std::string server_url;
    std::string current_id;
    PyObject* pyFile;
public:
    CommunicationModule()
    {
        initialized = false;
    }
    ~CommunicationModule() {}

    bool initialize(std::string _server_url = "http://106.10.34.243/");
    bool isinitialized() {return initialized;}
    void destroy();

    bool login(const std::string& id, const std::string& password);
    bool signup(const std::string& id, const std::string& password);
    
    // if error occured, return -1
    // return the number of whole pages
    int getAllpage(const int page_size);
    // upload SongData and get data file and server_id from server
     bool upload(const std::string& path, SongData& e);
     // cancel to uplaod SongData using server_id in SongData
     // and remove server_id in SongData
    bool uploadCancel(SongData& e);
    bool download(const std::string& path, SongData& e);
    //page_num starts 0
    bool updatePage(const int page_size, const int page_num, std::vector<SongData>& songlist);
};

#endif