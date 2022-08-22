#include"D:\apps\VS code\Programs\C++ program\shixun\data_in_mem\data_in_mem.h"
using namespace std;
//dataList.cpp--------------------------------------------------------------
//用于存放单个数据的联合
union dataUnion
{
    time_t timestamp;//时间戳
    int temp;//温度数据
    bool deleted=false;//是否已经被删除
};

//dataList之后的数据节点
struct dataAtom
{
    dataUnion* data;
    dataAtom* next;
};

//数据表的结构体
struct dataList
{
    int seriesNum;//该项列表编号
    string dataName;//该项列表所持有的数据名字
    int dataCount=0;//该项列表所持有的数据量
    dataAtom* value;//具体存储的数据
};

//初始化datalist
dataList* initDatalist(dataList datalist[]);


//dataDepart.cpp-----------------------------------------------------------------
//用于将memery中的链表数据拆分成单个数据的dataAtom,并存放到相应的list中
bool dataDepart(headNode* nodeHead,dataList datalist[]);