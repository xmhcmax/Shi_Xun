#undef UNICODE

#include"..\\main\\data_in_disk_forN\\data_in_disk_forN.h"
#include<iostream>
#include<fstream>
#include<time.h>
#include<io.h>
#include<direct.h>
#include<windows.h>
using namespace std;

//读取record.db文件的大小，来确定有几个文件入选，不然容易产生读取错误
int checkRecordSize();

//更换到上一个目录的函数,返回上一个目录的路径（带"\\"）--暂时没有用到
string changeToLastFolder(string lastIndexPath);

//更换到下一个索引的函数，如果没有下一个可以查找的索引，那么就返回"";
string getNextIndexPath(string oldIndexPath);

//看首时间戳是否与time相等
bool is_timeStamp_start_same(time_t time,string indexPath);

//对比首时间戳1,true代表timeStamp_start大,false代表timeStamp_start≤time
bool is_timeStamp_start_bigger(time_t time,string indexPath);

//对比首时间戳2,true代表timeStamp_start小,false代表timeStamp_start≥time
bool is_timeStamp_start_smaller(time_t time,string indexPath);

//查看尾时间戳是否与time一致
bool is_timeStamp_end_same(time_t time,string indexPath);

//对比尾时间戳1，true代表timeStamp_end大，false代表timeStamp_end≤time
bool is_timeStamp_end_bigger(time_t time,string indexPath);

//对比尾时间戳2，true代表timeStamp_end小，false代表timeStamp_end≥time
bool is_timeStamp_end_smaller(time_t time,string indexPath);

//定位到最大目录的最小文件的函数,没有可供查找的文件返回""
string getLowestIndex();

//获取包含所需数据的文件名,timeHigh是时间上限，timeLow是时间下限，表示一个范围
bool locateFile(time_t timeLow,time_t timeHigh);

//计算出定位到第一个对应的位置的数据前面需要多少偏移
int* getOffset(string filePath,int dataPos,string sequence,int* off);

//输入时间范围和需要第种数据，输出满足需求的数据
bool searchCertainData(time_t timeLow,time_t timeHigh,int dataPos);

//用来服务下一个函数的，给一个字符串和需要第几位，返回该位
string departString(string str,int number);

//用户调用的函数，输入时间范围和需要的第几种数据
bool searchData(time_t timeLow,time_t timeHigh,string dataKind);