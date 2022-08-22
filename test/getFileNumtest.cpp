#include"..\\main\\data_in_disk_forN\\data_in_disk_forN.h"
#include<io.h>
using namespace std;

int getFileNum(string path) {   //需要用到<io.h>头文件
    _finddata_t fileinfo;
    intptr_t handle=_findfirst(path.c_str(),&fileinfo) ;
    int fileNum=0;
    if(handle==-1)
        return 0;
    while(!_findnext(handle,&fileinfo))
        fileNum++;
    _findclose(handle);
    cout<<fileNum<<endl;
    return fileNum;
}

int main(){
    int fileNum;

    intptr_t Handle;
    _finddata_t fileInfo;
    string path="D:\\dataFile\\1";
    string p;
    Handle=_findfirst(p.assign(path).append("\\*").c_str(),&fileInfo);
    _findnext(Handle,&fileInfo);
    while(!_findnext(Handle,&fileInfo)){
        fileNum++;
    }
    cout<<fileNum<<endl;
    return 0;
    //string path="D:\\dataFile\\1";
    //getFileNum(path);
}