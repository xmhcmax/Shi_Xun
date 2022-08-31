#include"search.h"
using namespace std;

int main(){
    cout<<"Hello,welcome to the DataBase."<<endl;
    cout<<"You can search your data here."<<endl;
    time_t timeLow=1661923165;//1661921074--1661923194
    time_t timeHigh=1661923194;
    string dataKind="12345";
    // cout<<"As your data struct,you can input the data-serial-number in your sequence for certain data"<<endl;
    // cout<<"please input the lowest time limit you want to search:";
    // cin>>timeLow;
    // cout<<""<<endl;
    // cout<<"please input the highest time limit you want to search:";
    // cin>>timeHigh;
    // cout<<""<<endl;
    // cout<<"please input the data-serial-number of the data you want to search:";
    // cin>>dataKind;
    // cout<<""<<endl;
    searchData(timeLow,timeHigh,dataKind);
    return 0;
}