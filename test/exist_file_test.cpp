#include"D:\apps\VS code\Programs\C++ program\shixun\data_in_disk\data_in_disk.h"
using namespace std;

int main(){
    //测试如何判断文件存在否---用ifstream，就不会自动创建
    ifstream fin;
    string test="test.txt";
    fin.open(test);
    //if(!fin.is_open())
    cout<<fin.is_open()<< endl;
    return 0;
}