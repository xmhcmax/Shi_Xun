#include"D:\apps\VS code\Programs\C++ program\shixun\data_in_disk\data_in_disk.h"
using namespace std;

void test(string str){
    cout<<str<<endl;
}

int main(){
    //试试能不能输入一个string 来作为函数参数--可以
    string str;
    cout<<"please send in str"<<endl;
    cin>>str;
    test(str);
    return 0;    
}