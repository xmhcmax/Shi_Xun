#include"data_transit.h"
using namespace std;
//这里没啥东西，定义了一些数据结构，在头文件里也有
//这里的初始化dataList是将dataList的内容全部清除了



//用于存放单个数据的联合
// union dataUnion
// {
//     time_t timestamp;//时间戳
//     int temp;//温度数据
//     bool deleted=false;//是否已经被删除
// };

//dataList之后的数据节点
// struct dataAtom
// {
//     dataUnion* data;
//     dataAtom* next;
// };

// //数据表的结构体
// struct dataList
// {
//     int seriesNum;//该项列表编号
//     string dataName;//该项列表所持有的数据名字
//     int dataCount=0;//该项列表所持有的数据量
//     dataAtom* value;//具体存储的数据
// };

//初始化datalist
dataList* initDatalist(dataList datalist[]){
    for(int i = 0 ; i < (sizeof(datalist)/sizeof(dataList)) ; i++){
        datalist[i].seriesNum=i;
        datalist[i].value=NULL;
        datalist[i].dataCount=0;
        datalist[i].dataName="";
    }
    return datalist;
}

