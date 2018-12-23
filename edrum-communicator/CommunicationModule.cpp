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
    
    PyRun_SimpleString(
        "import sys\n" 
        "sys.path.append('.')\n"
        "sys.path.append('../edrum-communicator/')\n"
        "print(sys.path)\n"
    );
    
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
    std::string login_url = server_url + "login/";

    PyObject *pyFunc = PyObject_GetAttrString(pyFile, "login_sharedrum");
    if(!pyFunc){
        std::cerr << "ERROR : Embedded python function name(login_sharedrum) load fail!" << std::endl;
        return false;
    }

    PyObject *py_login = 
        PyObject_CallFunction(pyFunc,"sss",
            (char*)(login_url.c_str()),
            (char*)(id.c_str()),
            (char*)(password.c_str())
        );

    if(!py_login){
        std::cerr << "ERROR : Embedded python function(login_sharedrum) load fail!" << std::endl;
        Py_XDECREF(pyFunc);
        return false;
    }

    bool success = false;
    if(PyObject_IsTrue(py_login)){
        success = true;
    }

    Py_XDECREF(pyFunc);
    Py_XDECREF(py_login);

    return success;
}

bool CommunicationModule::signup(const std::string& id, const std::string& password)
{
    if(!initialized)
    {
         std::cerr << "ERROR : Communication Module is not initialized" << std::endl;
         return false;
    }
    /* need to add */
    std::string signup_url = server_url + "signup/";
    
    PyObject *pyFunc = PyObject_GetAttrString(pyFile, "signup_sharedrum");
    if(!pyFunc){
         std::cerr << "ERROR : Embedded python function name(signup_sharedrum) load fail!" << std::endl;
        return false;
    }

    PyObject *py_signup = 
        PyObject_CallFunction(pyFunc,"sss",
            (char*)(signup_url.c_str()),
            (char*)(id.c_str()),
            (char*)(password.c_str())
        );

    if(!py_signup){
        std::cerr << "ERROR : Embedded python function(signup_sharedrum) load fail!" << std::endl;
        Py_XDECREF(pyFunc);
        return false;
    }

    bool success = false;
    if(PyObject_IsTrue(py_signup)){
        success = true;
    }

    Py_XDECREF(pyFunc);
    Py_XDECREF(py_signup);
    return success;
}

int CommunicationModule::getAllpage(const int page_size)
{
     if(!initialized)
    {
         std::cerr << "ERROR : Communication Module is not initialized" << std::endl;
         return -1;
    }
    
    std::string getallpage_url = server_url + "songs/";
    
    PyObject* pyFunc = PyObject_GetAttrString(pyFile, "getAllpage");
    if(!pyFunc)
    {
        std::cerr << "ERROR : Embedded python function name(getAllpage) load fail!" << std::endl;
        return false;
    }

    PyObject* py_getallpage = 
        PyObject_CallFunction(pyFunc,"si",
            (char *)(getallpage_url.c_str()),
            page_size
        );
    
    if(!py_getallpage)
    {
        std::cerr << "ERROR : Embedded python function(getAllpage) load fail!" << std::endl;
        Py_XDECREF(pyFunc);
        return -1;
    }

    int result = PyInt_AsLong(py_getallpage);
    Py_XDECREF(pyFunc);
    Py_XDECREF(py_getallpage);
    return result;    
}
bool CommunicationModule::upload(const std::string& path, SongData& e)
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

    PyObject* key_flag = PyString_FromString("flag");    
    PyObject* item_flag = PyObject_GetItem(py_upload, key_flag);
    
    bool success = false;
    if(PyObject_IsTrue(item_flag))
    {
        success = true;

        PyObject* key_server_id = PyString_FromString("server_id");
        PyObject* item_server_id = PyObject_GetItem(py_upload, key_server_id);

        e.server_id = PyInt_AsLong(item_server_id);

        Py_XDECREF(key_server_id);
        Py_XDECREF(item_server_id);
    }

    Py_XDECREF(key_flag);
    Py_XDECREF(item_flag);
    
    Py_XDECREF(pyFunc);
    Py_XDECREF(py_upload);
    return success;            
}
bool CommunicationModule::uploadCancel(SongData& e)
{
    if(!initialized)
    {
         std::cerr << "ERROR : Communication Module is not initialized" << std::endl;
         return false;
    }

    std::string uploadcancel_url = server_url + "songs/";
    

    PyObject* pyFunc = PyObject_GetAttrString(pyFile, "upload_cancel");
    if(!pyFunc)
    {
        std::cerr << "ERROR : Embedded python function name(upload_cancel) load fail!" << std::endl;
        return false;
    }

    PyObject* py_upload_cancel = 
        PyObject_CallFunction(pyFunc,"si",
            (char *)(uploadcancel_url.c_str()),
            e.server_id
        );
    
    if(!py_upload_cancel)
    {
        std::cerr << "ERROR : Embedded python function(upload_cancel) load fail!" << std::endl;
        Py_XDECREF(pyFunc);
        return false;
    }

    bool success = false;
    //get return value of python function
    if(PyObject_IsTrue(py_upload_cancel))
    {
        e.server_id = 0;
        success = true;
    }
    Py_XDECREF(pyFunc);
    Py_XDECREF(py_upload_cancel);
    return success;
}
bool CommunicationModule::download(const std::string& path, SongData& e)
{
    if(!initialized)
    {
         std::cerr << "ERROR : Communication Module is not initialized" << std::endl;
         return false;
    }

    PyObject* pyFunc = PyObject_GetAttrString(pyFile, "download");
    if(!pyFunc)
    {
        std::cerr << "ERROR : Embedded python function name(download) load fail!" << std::endl;
        return false;
    }

    std::string download_url = server_url + "songs/";
    std::string download_path = path;
    PyObject* py_download = 
        PyObject_CallFunction(pyFunc,"ssi",
            (char *)(download_url.c_str()),
            (char *)(download_path.c_str()),
            e.server_id
        );
    
    if(!py_download)
    {
        std::cerr << "ERROR : Embedded python function(download) load fail!" << std::endl;
        Py_XDECREF(pyFunc);
        return false;
    }

    PyObject* key_flag = PyString_FromString("flag");
    PyObject* key_server_id = PyString_FromString("server_id");
    PyObject* key_name = PyString_FromString("name");
    PyObject* key_artist = PyString_FromString("artist");
    PyObject* key_date = PyString_FromString("date");
    PyObject* key_ID = PyString_FromString("ID");
        
    PyObject* item_flag = PyObject_GetItem(py_download, key_flag);
    PyObject* item_server_id = PyObject_GetItem(py_download, key_server_id);
    PyObject* item_name = PyObject_GetItem(py_download, key_name);
    PyObject* item_artist = PyObject_GetItem(py_download, key_artist);
    PyObject* item_date = PyObject_GetItem(py_download, key_date);
    PyObject* item_ID = PyObject_GetItem(py_download, key_ID);
    
    bool success = false;
    if(PyObject_IsTrue(item_flag))
    {
        success = true;
        e.server_id = PyInt_AsLong(item_server_id);
        //std::cout << e.server_id << std::endl;
        memcpy(e.name, PyString_AsString(item_name), sizeof(e.name));
        //std::cout << e.name << std::endl;
        memcpy(e.artist, PyString_AsString(item_artist), sizeof(e.artist));
        //std::cout << e.artist << std::endl;
        memcpy(e.date, PyString_AsString(item_date), sizeof(e.date));
        //std::cout << e.date << std::endl;
        memcpy(e.ID, PyString_AsString(item_ID), sizeof(e.ID));
        //std::cout << e.ID << std::endl;
    }

    Py_XDECREF(key_flag);
    Py_XDECREF(key_server_id);
    Py_XDECREF(key_name);
    Py_XDECREF(key_artist);
    Py_XDECREF(key_date);
    Py_XDECREF(key_ID);
    
    Py_XDECREF(item_flag);
    Py_XDECREF(item_server_id);
    Py_XDECREF(item_name);
    Py_XDECREF(item_artist);
    Py_XDECREF(item_date);
    Py_XDECREF(item_ID);
    
    Py_XDECREF(pyFunc);
    Py_XDECREF(py_download);
    return success; 
}
bool CommunicationModule::updatePage(const int page_size, const int page_num, std::vector<SongData>& songlist)
{
    if(!initialized)
    {
         std::cerr << "ERROR : Communication Module is not initialized" << std::endl;
         return false;
    }

    PyObject* pyFunc = PyObject_GetAttrString(pyFile, "download_meta");
    if(!pyFunc)
    {
        std::cerr << "ERROR : Embedded python function name(download_meta) load fail!" << std::endl;
        return false;
    }

    std::string download_url = server_url + "songs/";
    songlist.clear();

    for(int i=0 ; i < page_size ; i++)
    { 
        PyObject* py_download_meta = 
        PyObject_CallFunction(pyFunc,"sii",
            (char *)(download_url.c_str()),
            page_num+1,
            i
        );
    
        if(!py_download_meta)
        {
            std::cerr << "ERROR : Embedded python function(updatePage) load fail!" << std::endl;
            Py_XDECREF(pyFunc);
            return false;
        }

        PyObject* key_flag = PyString_FromString("flag");
        PyObject* item_flag = PyObject_GetItem(py_download_meta, key_flag);

        if(!PyObject_IsTrue(item_flag))
        {
            Py_XDECREF(key_flag);
            Py_XDECREF(item_flag);
            std::cerr << "ERROR : There is no page!(updatePage)" << std::endl;
            return false;
        }
        Py_XDECREF(key_flag);
        Py_XDECREF(item_flag);

        PyObject* key_server_id = PyString_FromString("server_id");
        PyObject* key_name = PyString_FromString("name");
        PyObject* key_artist = PyString_FromString("artist");
        PyObject* key_date = PyString_FromString("date");
        PyObject* key_ID = PyString_FromString("ID");
        
        PyObject* item_server_id = PyObject_GetItem(py_download_meta, key_server_id);
        PyObject* item_name = PyObject_GetItem(py_download_meta, key_name);
        PyObject* item_artist = PyObject_GetItem(py_download_meta, key_artist);
        PyObject* item_date = PyObject_GetItem(py_download_meta, key_date);
        PyObject* item_ID = PyObject_GetItem(py_download_meta, key_ID);
    
        SongData e;
        e.server_id = PyInt_AsLong(item_server_id);
        //std::cout << e.server_id << std::endl;
        memcpy(e.name, PyString_AsString(item_name), sizeof(e.name));
        //std::cout << e.name << std::endl;
        memcpy(e.artist, PyString_AsString(item_artist), sizeof(e.artist));
        //std::cout << e.artist << std::endl;
        memcpy(e.date, PyString_AsString(item_date), sizeof(e.date));
        //std::cout << e.date << std::endl;
        memcpy(e.ID, PyString_AsString(item_ID), sizeof(e.ID));
        //std::cout << e.ID << std::endl;
        songlist.push_back(e);
    

        Py_XDECREF(key_server_id);
        Py_XDECREF(key_name);
        Py_XDECREF(key_artist);
        Py_XDECREF(key_date);
        Py_XDECREF(key_ID);
    
        Py_XDECREF(item_server_id);
        Py_XDECREF(item_name);
        Py_XDECREF(item_artist);
        Py_XDECREF(item_date);
        Py_XDECREF(item_ID);

        Py_XDECREF(py_download_meta);
    }

    Py_XDECREF(pyFunc);
    return true;

}