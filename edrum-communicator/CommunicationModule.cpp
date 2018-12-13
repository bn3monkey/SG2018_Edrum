#include "CommunicationModule.hpp"
#include <cstring>
#include <iostream>

bool CommunicationModule::initialize(std::string _server_url)
{
    this->server_url = _server_url;
    //Py_SetProgramName((char *)"CommunicationModule");
    Py_Initialize();
    
    if(!Py_IsInitialized())
    {
        std::cerr << "ERROR : Embedded python initialization fail!" << std::endl;
        return false;
    }
    
    char* test = (char *)"";
    PySys_SetArgv(1, &test);
    pyFile = PyImport_ImportModule("scripts.CommunicationModule");
    if(!pyFile)
    {
        std::cerr << "ERROR : Embedded python module load fail!" << std::endl;
        return false;
    }
    
    initialized = true;
    return true;
}
void CommunicationModule::destroy()
{
    Py_XDECREF(pyFile);
    Py_Finalize();
}

bool CommunicationModule::login(const std::string& id, const std::string& password)
{
    if(!initialized)
    {
         std::cerr << "ERROR : Communication Module is not initialized" << std::endl;
         return false;
    }
    return true;
}
bool CommunicationModule::signup(const std::string& id, const std::string& password)
{
    if(!initialized)
    {
         std::cerr << "ERROR : Communication Module is not initialized" << std::endl;
         return false;
    }
    return true;
}
bool CommunicationModule::upload(const std::string& path, const SongData& e)
{
    if(!initialized)
    {
         std::cerr << "ERROR : Communication Module is not initialized" << std::endl;
         return false;
    }
    
    std::string upload_url = server_url + "songs/";
    std::string upload_filename = path + ((SongData &)e).get_filename();

    PyObject* pyFunc = PyObject_GetAttrString(pyFile, "upload");
    if(!pyFunc)
    {
        std::cerr << "ERROR : Embedded python function name(upload) load fail!" << std::endl;
        return false;
    }

    PyObject* py_upload = 
        PyObject_CallFunction(pyFunc,"sssss",
            (char *)(upload_url.c_str()),
            e.name,
            e.artist,
            e.ID,
            (char *)(upload_filename.c_str())
        );
    
    if(!py_upload)
    {
        std::cerr << "ERROR : Embedded python function(upload) load fail!" << std::endl;
        Py_XDECREF(pyFunc);
        return false;
    }

    bool success = false;
    //get return value of python function
    if(!PyObject_IsTrue(py_upload))
    {
        success = true;
    }
    Py_XDECREF(pyFunc);
    Py_XDECREF(py_upload);
    return success;            
}
bool CommunicationModule::uploadCancel(const std::string& path, const SongData& e)
{
    if(!initialized)
    {
         std::cerr << "ERROR : Communication Module is not initialized" << std::endl;
         return false;
    }
    return true;
}
bool CommunicationModule::download(const std::string& path, SongData& e)
{
    if(!initialized)
    {
         std::cerr << "ERROR : Communication Module is not initialized" << std::endl;
         return false;
    }
    return true;
}
bool CommunicationModule::updatePage(const int page_size, const int page_num, std::vector<SongData>& songlist)
{
    if(!initialized)
    {
         std::cerr << "ERROR : Communication Module is not initialized" << std::endl;
         return false;
    }
    return true;
}