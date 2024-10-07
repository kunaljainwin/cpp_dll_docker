#include <iostream>
#include <thread>
#include <chrono>
#include<vector>

using namespace std;

extern vector<int*>exVecData;

void extIncrementAll()
{

}
class Main {
    private:
    string app_name;
public:
    Main()
    {
        app_name="";
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
        for(auto i=0;i<exVecData.size();i++)
        {
            cout <<*(exVecData[i])<<", ";

        }
        cout << ']'<<endl;
    }
    void incrementExternData()
    {
        extIncrementAll();
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
