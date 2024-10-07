#include <iostream>
#include<vector>
using namespace std;

vector<int*>data; 

extern "C"
{
#define API_FUNC __attribute__((visibility("default")))
    API_FUNC bool InitializeDLL(int Size);
    API_FUNC void GetNum(int Index);
}


/* DLL Definitions [S] */
API_FUNC bool InitializeDLL(int Size)//formal prameter
{
    for(auto i=0;i<data.size();i++)
    {
        delete data[i];

    }

    data.resize(Size);
    cout << "DLL initialized" << endl;
    
    cout << "Data : [";
    for(auto i=0;i<Size;i++)
    {
        // std::unique_ptr<int> ptrNum = std::make_unique<int>();
        int * ptrNum=new int(i*2);//multiple of 2
        data[i]=ptrNum;
        if(i==Size-1)
            break;
            
        cout <<*ptrNum<<", ";

    }
    cout << ']'<<endl;
    return 0;
}

API_FUNC void incrementAll(int x)
{
    for(auto &ptrNum:data)
    {
        *ptrNum+=x;
    }
    cout<<"incremented each by "<<x<<endl;

}
/* DLL Definitions [E] */


/* internal tests */
int main ()
{
    InitializeDLL(5);
    return 0;
}