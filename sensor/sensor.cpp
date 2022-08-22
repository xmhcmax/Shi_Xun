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

void initdataStruct(mem_data_struct *p){
    p->timeStamp = time(NULL);
    p->intData = 270;
    p->charData = 2;
    p->boolData = true;
    p->floatData = 22.7;
    p->doubleData = 36.00;
}

//类似getOneData，但从结构体中直接取数据----------------------------------服务于insert，用于解析结构体成员
void getADataToColNode(mem_data_node* node,string sequenceNum,mem_data_struct* dataInput,int* off){
    int sequenceNum_i=stoi(sequenceNum);
    switch (sequenceNum_i)
    {
    case 0:
        //读出一个时间戳数据
        //time_t timeStamp;
        (node->data->timeStamp)=*(time_t *)((unsigned char *)dataInput+*off);
        *off+=sizeof(time_t);
        break;
    case 1:
        //读出一个int类型
        node->data->intData=*(int *)((unsigned char *)dataInput+*off);
        *off+=sizeof(int);
        break;
    case 2:
        //读出一个char类型
        node->data->charData=*(char *)((unsigned char *)dataInput+*off);
        *off+=sizeof(char);
        break;
    case 3:
        //读出一个bool类型
        node->data->boolData=*(bool *)((unsigned char *)dataInput+*off);
        *off+=sizeof(bool);
        break;
    case 4:
        //读出一个float类型
        node->data->floatData=*(float *)((unsigned char *)dataInput+*off);
        *off+=sizeof(float);
        break;
    case 5:
        //读出一个double类型
        node->data->doubleData=*(double *)((unsigned char *)dataInput+*off);
        *off+=sizeof(double);
        break;
    }
}

//将数据插入缓存行数据，成为一行链表
void insert(mem_data_struct* inputData,mem_data_head* chainHead){
    //需要首先定位到最后一个头结点
    mem_data_struct* data = inputData;
    int off=sizeof(string);
    string sequence=inputData->sequence;
    string sequenceNum;
    if(chainHead->last==NULL){
        //说明传入的就是唯一的头结点
        for(int i=0;i<=sequence.size();i++){
            mem_data_node* node=new mem_data_node;
            mem_data_union* Union=new mem_data_union;
            node->data=Union;
            //sequence_i=stoi(departSequence(sequence,i));
            //getOneData(node,departSequence(sequence,i),&off);
            //需要一个类似getdata的函数，获取结构体中某个数据类型的数据
            
            //这里判断是不是第一个数据
            if(i==0){
                //是第一个数据的输入，是timeStamp,插入
                sequenceNum="0";
                getADataToColNode(node,sequenceNum,data,&off);
                chainHead->firstNode=node;
                chainHead->lastNode=node;
                chainHead->nodeNum++;
                continue;
            }
            getADataToColNode(node,departSequence(sequence,i),data,&off);
            chainHead->lastNode->next=node;
            chainHead->lastNode=node;
            chainHead->nodeNum++;
        }
    }
    else{
        mem_data_head* pointer=chainHead->last;
        for(int i=0;i<=sequence.size();i++){
        mem_data_node* node=new mem_data_node;
        mem_data_union* Union=new mem_data_union;
        node->data=Union;
        //sequence_i=stoi(departSequence(sequence,i));
        //getOneData(node,departSequence(sequence,i),&off);
        //需要一个类似getdata的函数，获取结构体中某个数据类型的数据

        //这里判断是不是第一个数据
        if(i==0){
            //是第一个数据的输入，是timeStamp,插入
            sequenceNum="0";
            getADataToColNode(node,sequenceNum,data,&off);
            pointer->firstNode=node;
            pointer->lastNode=node;
            pointer->nodeNum++;
            continue;
        }
        getADataToColNode(node,departSequence(sequence,i),data,&off);
        pointer->lastNode->next=node;
        pointer->lastNode=node;
        pointer->nodeNum++;
        }
    }
    //函数结束了，说明一帧数据，即一行链表添加完成，所以headNum+1;
    chainHead->headNum++;
}

//模拟传感器产生数据-----------------------------服务于boostDataToStruct
void sensor(mem_data_struct* dataSource){
        dataSource->timeStamp = time(NULL);
        dataSource->intData = (dataSource->intData-250+5)%50 + 250;
        dataSource->charData = (dataSource->charData+1)%16;
        dataSource->boolData = !(dataSource->boolData);
        dataSource->floatData = (dataSource->floatData-20+0.1)-(5*floor((dataSource->floatData-20+0.1)/5)) + 20;
        dataSource->doubleData = (dataSource->doubleData-35+0.01)-(2*floor((dataSource->doubleData-35+0.01)/2)) +35;
}

//生成数据，向结构体进行输入
void boostDataToStruct(mem_data_struct* dataSource){
    sensor(dataSource);
}

//为缓存的行链表增加新的一个头并返回指向它的指针，其实就是colChain.cpp中的addHead
void addOneHead(mem_data_head* chainHead){
    addHead(chainHead);
}

//将一帧数据传出,传出的一行的头指针是colChain中的HEADPOINTER
bool pushOneCol(mem_data_head* chainHead){
    if(chainHead->headNum<=1){
        //小于最小输出标准，不进行push
        return false;
    }
    //否则，进行push
    mem_data_head* chainHead_save=chainHead;
    mem_data_head** ColToBePush=getHEADPOINTER();
    *ColToBePush=chainHead;
    //让chainHead指针指向下一个头，然后因为移出了一行，所以headNum-1
    chainHead=chainHead->next;
    chainHead->headNum=chainHead_save->headNum--;
    //_save指向的还是之前的头，我们把headNum清零
    chainHead_save->headNum=0;
    return true;
}

int main(){
    int* data_request=NULL;
    //创建一帧数据的结构体
    mem_data_struct* dataSource=new mem_data_struct;
    initdataStruct(dataSource);
    //创建一个缓存传感器数据的行链表
    mem_data_head* chainHead=initColChain();
    while(1){
        data_request=getDATA_REQUEST();
        if(*data_request==1){
            //说明需要进行一次数据push
            pushOneCol(chainHead);
            //置0
            *data_request=0;
            continue;
        }
        //先产生一帧数据，放入结构体
        boostDataToStruct(dataSource);
        //为缓存行链表添加数据
        insert(dataSource,chainHead);
        //为缓存行链表添加新头,只是增加一个空头
        addOneHead(chainHead);
        Sleep(1000);
    }
    return 0;
}