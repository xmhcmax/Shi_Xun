#include"..\\main\\data_in_disk_forN\\data_in_disk_forN.h"
using namespace std;


int main(){
    //首先读取已有的目录下文件名字
    intptr_t Handle;
    //intptr_t Handle2;
    _finddata_t fileInfo;
    //_finddata_t fileInfo2;
    string path="D:\\dataFile";
    string p;
    //string p2;
    //.assign()是用来赋值的，就是把path的值赋给了P//.c_str()是用来将string转换成const char* 类型的
    Handle=_findfirst(p.assign(path).append("\\*").c_str(),&fileInfo);
    for(int i=0;i<=4;i++){
        _findnext(Handle,&fileInfo);
    }
    if(fileInfo.size==64)
        cout<<"1"<<endl;
    Sleep(1);
    return 0;
}