#include <Python.h>
#include <cstring>

using namespace std;

bool upload(char *s_name,char *s_artist,char *c_id,char *f_name);
bool download_note(int s_id);
void SysPath();

int main(int argc, char **argv){
    Py_SetProgramName(argv[0]);
    Py_Initialize();
    bool flag = false;

    char s_name[51] = {'\0'}; // name of song
    char s_artist[51] = {'\0'}; // name of artist
    char c_id[21] = {'\0'}; // creator of this note file
    char *f_name; // filename

    strcpy(s_name,"luv");
    strcpy(s_artist,"apink_2");
    strcpy(c_id,"taehoon");
    f_name = (char*)"synctest.txt";

    if(Py_IsInitialized()){
        PySys_SetArgv(argc,argv);
        SysPath();
        
        flag = upload(s_name,s_artist,c_id,f_name);
        if(flag){
            printf("Successfully transmitted\n");
        }
        else{
            printf("Fail\n");
        }
        
        //flag = download_note(5);
        if(flag){
            printf("Successful\n");
        }
        else{
            printf("Fail\n");
        }
        Py_Finalize();
    }

    return 0;
}

void SysPath(){
    printf("sys.path:");
    PyRun_SimpleString("import sys\nprint sys.path\nprint\n");
}

bool upload(char *s_name,char *s_artist,char *c_id,char *f_name){
    PyObject *send_obj = PyImport_ImportModule("scripts.send");
    bool success = false;

    if(send_obj){
        PyObject *send_file = PyObject_GetAttrString(send_obj,"sendFile");

        if(send_file){
            PyObject *res = PyObject_CallFunction(send_file,"ssss",s_name,s_artist,c_id,f_name);

            if(res){
                if(PyObject_IsTrue(res) == 1){
                    success = true;
                }
                Py_XDECREF(res);
            }
            Py_XDECREF(send_file);
        }
        Py_XDECREF(send_obj);
    }

    return success;
}

bool download_note(int s_id){
    PyObject *down_obj = PyImport_ImportModule("scripts.send");
    bool success = false;

    if(down_obj){
        PyObject *down_file = PyObject_GetAttrString(down_obj,"downloadFile");

        if(down_file){
            PyObject *res = PyObject_CallFunction(down_file,"i",s_id);

            if(res){
                 if(PyObject_IsTrue(res) == 1){
                    success = true;
                }
                Py_XDECREF(res);
            }
            Py_XDECREF(down_file);
        }
        Py_XDECREF(down_obj);
    }

    return success;
}
