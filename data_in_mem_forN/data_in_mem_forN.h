#undef UNICODE

#include<iostream>
#include<fstream>
#include<time.h>
#include<io.h>
#include<direct.h>
#include<windows.h>
using namespace std;

string SOURCEPATH="D:\\dataFile\\source.db";
string SEQUENCE;
//extern char SEQUENCE[10];
//extern string SEQUENCE;

//colChain.cpp------------------------------------------------
//定义了存储数据的最小单位--联合
union mem_data_union
{
    time_t timeStamp;
    int intData;
    char charData;
    bool boolData;
    float floatData;
    double doubleData;
};

//定义了行链表的结点结构，包含next的指针和指向联合的指针
struct mem_data_node
{
    mem_data_union* data;
    mem_data_node* next;
};

//定义了行链表头结点，其中有指向行链表第一个和最后一个结点的node指针，
//指向上一个、下一个头结点和最后一个头结点的previous、next、last指针，还包含该链表中节点数量信息
struct mem_data_head
{
    string sequence;
    int nodeNum=0,headNum=0;
    mem_data_node* firstNode;
    mem_data_node* lastNode;
    mem_data_head* previous;
    mem_data_head* next;
    mem_data_head* last;
};

//初始化行链表,返回一个已经分配内存，并且其他全部初始化为空或者0的行链表头指针
mem_data_head* initColChain();

//获取第一个数据--时间戳进入第一个node，并且加入链表
bool getTimeStampInChain(mem_data_head* chainHead,mem_data_node* node);

//获取一个数据到node中
bool getOneData(mem_data_node* node,string sequenceNum,int* off);

//添加node进入链表
bool addNode(string sequence,mem_data_head* chainHead);

//添加新的一行的头
bool addHead(mem_data_head* chainHead);

//dataSource.cpp-----------------------------------------------
//识别用户的输入，来判断用户需要的数据类型和数量
string getClientRequest();

//进行sequence的任意位置的数据读取,要获取第几位,sequenceNum就几
string departSequence(string sequence,int sequenceNum);

//得到SEQUENCE
string getSequence();
