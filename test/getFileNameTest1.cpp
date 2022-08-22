#include"..\\main\\data_in_disk_forN\\data_in_disk_forN.h"
using namespace std;

int main(){
    intptr_t Handle;
    _finddata_t fileInfo;
    string path="D:\\apps\\VS code\\Programs\\C++ program\\shixun\\data_in_mem";
    string p;
    Handle=_findfirst(p.assign(path).append("\\*").c_str(),&fileInfo);
    //cout<<fileInfo.name<<endl;
    //printf("%s\n", fileInfo.name);
    //cout<<fileInfo.name<<endl;
    _findnext(Handle, &fileInfo);
    //cout<<fileInfo.name<<endl;
    //为什么前两次读取不要呢？因为。。。我无法解释为什么会输出两个点
    string name;
    while (_findnext(Handle, &fileInfo) == 0){
			name=fileInfo.name;
            //去除".db"后缀
            name.resize(name.size()-4);
            //取出前4个字符
            name.erase(0,4);
            cout<<name<<endl;
    }
    return 0;

}