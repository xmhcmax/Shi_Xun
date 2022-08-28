#include"..\\main\\data_in_disk_forN\\data_in_disk_forN.h"
using namespace std;


// //测试能不能完成dataFile的创建
// string initFolder(){
//     //根目录位置
//     string rootFolderPath="D:\\dataFile";
//     //查看是不是已经有了根目录
//     if (access(rootFolderPath.c_str(), 0)!=0){
//         //没有文件，则创建
//         //cout<<"No usable folder!Creating..."<<endl;
//         mkdir(rootFolderPath.c_str());
//         //cout<<"Done"<<endl;
//     }
//         //如果已经有了根目录则不创建
//         //进入根目录，依次检查是不是每级文件都存在
//         string folderPath=rootFolderPath;
//         folderPath.append("\\");
//         string folderPath_save=folderPath;
//         //循环，查看每一级文件
//         for (int i = 1; i <= 9; i++){
//             folderPath=folderPath_save;
//             folderPath.append(to_string(i));
//             //查看是不是已经有了i级目录
//             if (access(folderPath.c_str(), 0)!=0){
//             //没有文件，则创建
//             //cout<<"the childFolder："+i<<" is missing.Creating..."<<endl;
//             mkdir(folderPath.c_str());
//             //cout<<"Done"<<endl;
//             }
//         }
    
//     cout<<"Initialization done！The folder is at: D:\\dataFile"<<endl;
//     return rootFolderPath;
// }

// int main(){
//     string str=initFolder();
//     cout<<str<<endl;
//     return 0;
// }