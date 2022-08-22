#include"D:\apps\VS code\Programs\C++ program\shixun\data_in_disk\data_in_disk.h"
using namespace std;
//这个文件用来测试关于string的一些操作

int main(){
//关于怎么去删除文件后缀的探索
    string str1="test.db";
    string str2=".index";
    string str3;
    str3.append(str1);
    string str4=str3.substr(0,str3.size()-3);
    cout<<str4<<endl;
    //str3.resize(str3.size()-3);
    // str3.pop_back();
    // str3.pop_back();
    // str3.pop_back();
    //str3.erase(str3.size(),3);
    str4.erase(0,2);
    str4.append(str2);

    cout<<str4<<endl;

//测试从文件路径中读出来的是一个"\"还是"\\"----是"\"
    // string filePath="D:\\apps\\VS code\\Programs\\C++ program\\shixun\\data_in_disk\\1";
    // cout<<filePath<<endl;
    // filePath.resize(filePath.size()-2);
    // cout<<filePath<<endl;
    return 0;
}


