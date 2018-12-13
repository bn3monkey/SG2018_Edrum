#ifndef __COMMUNICATION_MODULE__
#define __COMMUNICATION_MODULE__

#include <Python.h>
#include "SongData.hpp"
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
    void destroy();

    bool login(const std::string& id, const std::string& password);
    bool signup(const std::string& id, const std::string& password);
    bool upload(const std::string& path, const SongData& e);
    bool uploadCancel(const std::string& path, const SongData& e);
    bool download(const std::string& path, SongData& e);
    bool updatePage(const int page_size, const int page_num, std::vector<SongData>& songlist);
};

#endif