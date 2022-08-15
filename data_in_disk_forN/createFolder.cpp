#include"data_in_disk_forN.h"
using namespace std;
//考虑到不是如果让用户自己来创建一个目录文件，会有点烦，所以这里就直接写一个函数来在最开始的时候就初始化一个完整的目录出来

//初始化目录文件（就是在用户使用的时候创建好整个目录结构）
string initFolder(){
    //根目录位置
    string rootFolderPath="D:\\dataFile";
    //查看是不是已经有了根目录
    if (access(rootFolderPath.c_str(), 0)!=0){
        //没有文件，则创建
        //cout<<"No usable folder!Creating..."<<endl;
        mkdir(rootFolderPath.c_str());
        //cout<<"Done"<<endl;
    }
        //如果已经有了根目录则不创建
        //进入根目录，依次检查是不是每级文件都存在
        string folderPath=rootFolderPath;
        folderPath.append("\\");
        string folderPath_save=folderPath;
        //循环，查看每一级文件
        for (int i = 1; i <= 3; i++){
            folderPath=folderPath_save;
            folderPath.append(to_string(i));
            //查看是不是已经有了i级目录
            if (access(folderPath.c_str(), 0)!=0){
            //没有文件，则创建
            //cout<<"the childFolder："+i<<" is missing.Creating..."<<endl;
            mkdir(folderPath.c_str());
            //cout<<"Done"<<endl;
            }
        }
    
    cout<<"Initialization done！The folder is at: D:\\dataFile"<<endl;
    return rootFolderPath;
}
