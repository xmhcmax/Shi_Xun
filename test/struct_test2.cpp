#include"..\\main\\data_in_disk_forN\\data_in_disk_forN.h"
using namespace std;


struct testStruct
{
    time_t timeStamp;
    char a;
    int b;
    char c;
};


int main(){
    testStruct test;
    cout<<sizeof(test)<<endl;
    cout<<offsetof(testStruct,timeStamp)<<" "<<offsetof(testStruct,a)<<" "<<offsetof(testStruct,b)<<" "<<offsetof(testStruct,c)<<endl;
    return 0;
}