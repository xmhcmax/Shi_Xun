#include"D:\apps\VS code\Programs\C++ program\shixun\data_transit\data_transit.h"
using namespace std;

//createFile.cpp---------------------------------------------------------------------------------
//把memery中的10条数据转换为第一层文件,顺便产生索引
bool makeFile(dataList datalist[],string fileName,string filePath);

//fileManage.cpp---------------------------------------------------------------------------------
//得到数据文件的level,int类型
int getFileLevel(string filePath);

//得到数据文件的number,int类型
int getFileNumber(string filePath);

//生成目前应该filePath的函数，level是级数，int 类型
string getFilePath(int level);

//生成fileName的函数,这里的filePath是级目录，不是数据文件根目录
string getFileName(string filePath);

//检查每一级文件是不是满了的函数,这里的filePath是级目录，不是数据文件根目录
bool is_fileFull(string filePath);

//将同一级目录下的所有数据文件转移到下一级目录的一个新数据文件中,这里的filePath是级目录，不是数据文件根目录
bool upgradeFile(string filePath);

//createFolder.cpp--------------------------------------------------------------------------------
//初始化目录文件（就是在用户使用的时候创建好整个目录结构）
string initFolder();

//indexManage.cpp---------------------------------------------------------------------------------
//得到索引文件的level,int类型
int getIndexLevel(string indexPath);

//得到索引文件的number,int类型
int getIndexNumber(string indexPath);

//创建索引,filePath是文件目录，不是级目录、数据文件根目录
bool makeIndex(string filePath);

//search.cpp--------------------------------------------------------------------------------------
//更换到下一个目录的函数,返回下一个目录的路径（带"\\"）
string changeFolder(string lastIndexPath);

//更换到下一个索引的函数,返回下一个索引的路径
string getNextFilePath(string lastIndexPath);

//对比首时间戳1,true代表timeStamp_start大,false代表timeStamp_start≤time
bool is_timeStamp_start_bigger(time_t time,string indexPath);

//对比首时间戳2,true代表timeStamp_start小,false代表timeStamp_start≥time
bool is_timeStamp_start_smaller(time_t time,string indexPath);

//对比尾时间戳1，true代表timeStamp_end大，false代表timeStamp_end≤time
bool is_timeStamp_end_bigger(time_t time,string indexPath);

//对比尾时间戳2，true代表timeStamp_end小，false代表timeStamp_end≥time
bool is_timeStamp_end_smaller(time_t time,string indexPath);
