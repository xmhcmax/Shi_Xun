#ifndef DATA_TRANSIT_FORN
#define DATA_TRANSIT_FORN

#include"..\\data_in_mem_forN\\data_in_mem_forN.h"
using namespace std;

//rowChain.cpp=-----------------------------------------------------------------
//用来放数组的联合,可以用来容纳任意数据类型10条
union transit_data_union
{
    time_t timeData[10];
    int intData[10];
    char charData[10];
    bool boolData[10];
    float floatData[10];
    double doubleData[10];
};

//用来存放联合的单链表
struct transit_data_chain
{
    string sequence;
    int dataNum;
    transit_data_union* data;
    transit_data_chain* next;
    transit_data_chain* last;
};

//初始化列链表,返回一个链表头指针，可以用来创建一个链表
transit_data_chain* initRowChain(mem_data_head* colChain);

//根据sequence往链表中行列转换数据,dataToTransit是分离出来的十条链表的第一个头指针
bool colTOrow(mem_data_head** dataToTransit,transit_data_chain** rowChain);

#endif