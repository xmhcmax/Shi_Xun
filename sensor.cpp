#include"data_in_disk_forN\\data_in_disk_forN.h"
using namespace std;
struct mem_data_struct
    {
        time_t timeStamp;
        int intData;
        char charData;
        bool boolData;
        float floatData;
        double doubleData;
    };

    void initdataStruct(mem_data_struct *p){
        p->timeStamp = time(NULL);
        p->intData = 270;
        p->charData = 2;
        p->boolData = true;
        p->floatData = 22.7;
        p->doubleData = 36.00;
    }

//模拟传感器产生数据
void sensor(){
    struct mem_data_struct inputdata1;
    struct mem_data_struct *inputdata2;
    inputdata2 = &inputdata1;
    initdataStruct(inputdata2);
    //定义行链表头，为insert做准备
    mem_data_head* m_d_h = initColChain();
    for(;;){
        inputdata2->timeStamp = time(NULL);
        inputdata2->intData = (inputdata2->intData-250+5)%50 + 250;
        inputdata2->charData = (inputdata2->charData+1)%16;
        inputdata2->boolData = !(inputdata2->boolData);
        inputdata2->floatData = (inputdata2->floatData-20+0.1)-(5*floor((inputdata2->floatData-20+0.1)/5)) + 20;
        inputdata2->doubleData = (inputdata2->doubleData-35+0.01)-(2*floor((inputdata2->doubleData-35+0.01)/2)) +35;
        insert(inputdata2,m_d_h,getSequence());
        Sleep(500);
    }

}

//类似getOneData，但从结构体中直接取数据
void getAData(mem_data_node* node,string sequenceNum,mem_data_struct* off){
    int sequenceNum_i=stoi(sequenceNum);
    switch (sequenceNum_i)
    {
    case 1:
        //读出一个int类型
        int intData;
        intData = (int)&off;
        off+=sizeof(int);
        node->data->intData=intData;
        break;
    case 2:
        //读出一个char类型
        char charData;
        charData = (char)&off;
        off+=sizeof(char);
        node->data->charData=charData;
        break;
    case 3:
        //读出一个bool类型
        bool boolData;
        boolData = (bool)&off;
        off+=sizeof(bool);
        node->data->boolData=boolData;
        break;
    case 4:
        //读出一个float类型
        float floatData;
        float* floatDataP;
        floatDataP = (float*)&off;
        floatData=*floatDataP;
        off+=sizeof(float);
        node->data->floatData=floatData;
        break;
    case 5:
        //读出一个double类型
        double doubleData;
        double* doubleDataP;
        doubleDataP = (double*)&off;
        doubleData=*doubleDataP;
        off+=sizeof(double);
        node->data->doubleData=doubleData;
        break;
    }
}


//将数据插入内存中的行链表
void insert(mem_data_struct* inputData,mem_data_head* chainHead,string sequence){
    //需要首先定位到最后一个头结点
    if(chainHead->last==NULL){
        for(int i=1;i<=sequence.size();i++){
        mem_data_node* node=new mem_data_node;
        mem_data_union* Union=new mem_data_union;
        node->data=Union;
        //sequence_i=stoi(departSequence(sequence,i));
        //getOneData(node,departSequence(sequence,i),&off);
        //需要一个类似getdata的函数，获取结构体中某个数据类型的数据
        mem_data_struct* off = inputData;
        getAData(node,departSequence(sequence,i),off);
        chainHead->lastNode->next=node;
        chainHead->lastNode=node;
        chainHead->nodeNum++;
    }
    }
    else{
        mem_data_head* pointer=chainHead->last;
        for(int i=1;i<=sequence.size();i++){
        mem_data_node* node=new mem_data_node;
        mem_data_union* Union=new mem_data_union;
        node->data=Union;
        //sequence_i=stoi(departSequence(sequence,i));
        //getOneData(node,departSequence(sequence,i),&off);
        //需要一个类似getdata的函数，获取结构体中某个数据类型的数据
        mem_data_struct* off = inputData;
        getAData(node,departSequence(sequence,i),off);
        pointer->lastNode->next=node;
        pointer->lastNode=node;
        pointer->nodeNum++;
        }
    }
    //为下一个结构体创建链表头
    addHead(chainHead);
    
    
}

