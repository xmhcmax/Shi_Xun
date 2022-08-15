#include"D:\apps\VS code\Programs\C++ program\shixun\data_transit_forN\data_transit_forN.h"
using namespace std;

string ROOTFOLDERPATH="D:\\dataFile";

//createFolder.cpp------------------------------------------------------------
//初始化目录文件（就是在用户使用的时候创建好整个目录结构）
string initFolder();


//transDataToLevelOne.cpp-----------------------------------------------------
//将行列转换完成的数据，转存到一级文件中
bool makeLevelOneFile(transit_data_chain* chainToWrite);


//fileManage.cpp--------------------------------------------------------------
//检查该级目录是不是满了的函数,这里的filePath是级目录，不带"\\"，不是数据文件根目录
bool is_fileFull(string filePath);

//得到数据文件的level,int类型
int getFileLevel(string filePath);

//得到数据文件的number,int类型
int getFileNumber(string filePath);

//生成fileName的函数,这里的filePath是级目录，不是数据文件根目录
string makeFileName(string filePath);

//面对一个级目录已经满了的情况，就需要进行升级,这里的filePath可以是当前文件的级目录路径(不带"\\")，也可以是随便一个数据文件的路径
bool upgradeFile(string filePath);


//writeManage.cpp-------------------------------------------------------------
//写入time_h类型
bool writeTime(ofstream& fout,time_t timeData);

//写入int类型
bool writeInt(ofstream& fout,int intData);

//写入char类型
bool writeChar(ofstream& fout,char charData);

//写入bool类型
bool writeBool(ofstream& fout,bool boolData);

//写入float类型
bool writeFloat(ofstream& fout,bool floatData);

//写入double类型
bool writeDouble(ofstream& fout,bool doubleData);

//indexManage.cpp-------------------------------------------------------------
//得到索引文件的level,int类型
int getIndexLevel(string indexPath);

//得到索引文件的number,int类型
int getIndexNumber(string indexPath);

//给对应的文件路径，创建该文件的index
bool makeIndex(string filePath,string sequence);