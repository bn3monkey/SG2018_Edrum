#include <Python.h>
#include <string>

using namespace std;

void import_SendFile(char *s_name,char *s_artist,char *c_id,char *f_name){
    PyObject *send_obj = PyImport_ImportModule("send");

    if(send_obj){
        PyObject *send_file = PyObject_GetAttrString(send_obj,"sendFile");

        if(send_file){

            PyObject *res = PyObject_CallFunction(send_file,"ssss",s_name,s_artist,c_id,f_name);
            
            if(res){
                Py_XDECREF(res);
            }
            Py_XDECREF(send_file);
        }
        Py_XDECREF(send_obj);
    }
}

void SysPath(){
    PyRun_SimpleString("import sys\nprint sys.path\nprint\n");
}

int main(int argc, char **argv){
    Py_SetProgramName(argv[0]);
    Py_Initialize();

    char *s_name = "luv";
    char *s_artist = "apink";
    char *c_id = "thkim";
    char *f_name = "luv.txt";

    if(Py_IsInitialized()){
        PySys_SetArgv(argc,argv);
        SysPath();
        import_SendFile(s_name,s_artist,c_id,f_name);
        Py_Finalize();
    }

    return 0;
}