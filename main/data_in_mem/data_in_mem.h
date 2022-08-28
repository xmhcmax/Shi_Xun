#undef UNICODE

#include<iostream>
#include<fstream>
#include<time.h>
#include<io.h>
#include<direct.h>
#include<windows.h>
using namespace std;



//dataStruct.cpp--------------------------------------------------------------------
//数据节点结构体
struct dataPiece
{
    time_t timestamp;//时间戳
    int temp;//温度数据
    bool deleted=false;//是否已经被删除
};

//memSave.cpp-----------------------------------------------------------------------
//链表节点结构
struct memNode
{
    memNode* next;
    dataPiece* data;
};

//链表头结点结构体
struct headNode
{
    int nodeCount;
    memNode* last;
    memNode* next;
};

//初始化链表头
bool initMemList(headNode* nodeHead);

//接收数据函数--未完成
//dataPiece* catchData();

//存入链表的函数
bool saveNode(headNode headNode,dataPiece* dataSource);

//dataRecognizing.cpp---------------------------------------------------------------
//进行原始数据分割--未完成
dataPiece* recognizing(dataPiece* dataSource);
