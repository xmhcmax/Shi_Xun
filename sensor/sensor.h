#include"..\\main\\data_in_disk_forN\\data_in_disk_forN.h"
using namespace std;

struct mem_data_struct
    {
        string sequence="12345";
        time_t timeStamp;
        int intData;
        char charData;
        bool boolData;
        float floatData;
        double doubleData;
    };

// //用来向外界表示我们是否需要新的数据
// int* getDATA_REQUEST();

// //改变DATA_REQUEST的值，来向传感器发出数据请求-----------------服务于
// void setDATA_REQUEST();

void initdataStruct(mem_data_struct *p);

//类似getOneData，但从结构体中直接取数据----------------------------------服务于insert，用于解析结构体成员
void getADataToColNode(mem_data_node* node,string sequenceNum,mem_data_struct* dataInput,int* off);

//在看了《结构体内成员对齐原则》之后，我觉得有必要写一个对sequence进行解析来调整off的函数
int setOff(string sequence,int number,int off);

//将数据插入缓存行数据，成为一行链表
void addOneCol(mem_data_struct* inputData,mem_data_head* chainHead);

//模拟传感器产生数据-----------------------------服务于boostDataToStruct
void sensor(mem_data_struct* dataSource);

//生成数据，向结构体进行输入
void boostDataToStruct(mem_data_struct* dataSource);

//为缓存的行链表增加新的一个头并返回指向它的指针，其实就是colChain.cpp中的addHead
void addOneHead(mem_data_head* chainHead);

//将一帧数据传出,传出的一行的头指针是colChain中的HEADPOINTER
bool pushOneCol(mem_data_head** chainHead_cache,mem_data_head** chainHead_mem);

//生成一帧数据，并往内存中插入一帧数据
bool insert(mem_data_struct* dataSource,mem_data_head** chainHead_cache,mem_data_head** chainHead_mem);

