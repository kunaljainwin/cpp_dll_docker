#include <iostream>
#include <thread>
#include <chrono>
#include<vector>
#include<dlfcn.h>
using namespace std;

typedef bool (*InitializeDLL)(int);
typedef void (*IncrementAll)(int);

vector<int*> *exVecData;

class Main {
    private:
    string app_name;
    void * dllHandle;
public:
    Main()
    {
        void* handle = dlopen("./libmylibrary.so", RTLD_LAZY);
        if (!handle) {
            std::cerr << "Error loading shared library: " << dlerror() << std::endl;
            // return 1;
        }
        dllHandle=handle;
        app_name="";


        InitializeDLL initializeDLL = (InitializeDLL) dlsym(handle, "InitializeDLL");
        const char* dlsym_error = dlerror();
        if (dlsym_error) {
            std::cerr << "Error locating `InitializeDLL` function: " << dlsym_error << std::endl;
            dlclose(handle);
        }

        initializeDLL(5);
        exVecData= (vector<int*> *)dlsym(handle,"data");
        dlsym_error = dlerror();
        if(dlsym_error)
        {
            std::cerr << "Error locating `data` function: " << dlsym_error << std::endl;
            dlclose(handle);
        }
    }
    string GetAppName(){
        return app_name;
    }
    void InputAppName()
    {
        string s;
        cin>>s;
        app_name=s;
    }
    void printExternData()
    {
        cout << "Data : [";

        int n=5;
        for(auto i=0;i<n;i++)// main.cpp:34:23: warning: comparison of integer expressions of different signedness: 'int' and 'std::vector<int*>::size_type' {aka 'long unsigned int'} [-Wsign-compare]
        {
            cout <<*((*exVecData)[i])<<", ";

        }
        cout << ']'<<endl;
    }
    void incrementExternData()
    {
        IncrementAll incrementAll = (IncrementAll) dlsym(dllHandle, "IncrementAll");
        const char* dlsym_error = dlerror();
        if (dlsym_error) {
            std::cerr << "Error locating `IncrementAll` function: " << dlsym_error << std::endl;
            dlclose(dllHandle);
        }
        incrementAll(1);

    }
};

int main() {

    Main *main=new Main();
    main->InputAppName();
    cout<<"App name : "<<main->GetAppName()<<endl;

    while(true)
    {
        cout<<"0 : INCREMENT \n 1 : CONTINUE \n";
        int nINPUT=-1;
        cin>>nINPUT;
        switch (nINPUT)
        {
        case 0:
        {
            main->incrementExternData();
            break;
        }
        case 1 :
        {
            main->printExternData();
            break;
        }
        default:
            return 0;
            break;
        }
    }
    return 0;
}
