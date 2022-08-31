#include"sensor.h"
using namespace std;

//static int DATA_REQUEST=0;

// struct mem_data_struct
//     {
//         string sequence="12345";
//         time_t timeStamp;
//         int intData;
//         char charData;
//         bool boolData;
//         float floatData;
//         double doubleData;
//     };

// //用来向外界表示我们是否需要新的数据
// int* getDATA_REQUEST(){
//     return &DATA_REQUEST;
// }

// //改变DATA_REQUEST的值，来向传感器发出数据请求-----------------服务于
// void setDATA_REQUEST(int status){
//     if(status==1){
//         DATA_REQUEST=1;
//     }
//     else if(status==0){
//         DATA_REQUEST=0;
//     }
// }

void initdataStruct(mem_data_struct *p){
    p->timeStamp = time(NULL);
    p->intData = 270;
    p->charData = '@';
    p->boolData = true;
    p->floatData = 22.7;
    p->doubleData = 36.00;
}

//类似getOneData，但从结构体中直接取数据----------------------------------服务于addOnecol，用于解析结构体成员
void getADataToColNode(mem_data_node* node,string sequenceNum,mem_data_struct* dataInput,int* off){
    //string sequence=dataInput->sequence;
    node->sequence=dataInput->sequence;
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

//在看了《结构体内成员对齐原则》之后，我觉得有必要写一个对sequence进行解析来调整off的函数
int setOff(string sequence,int number,int off){
    //首先，off已经在getAdataToColNode里头进行了偏移，此时是最后一个读出了的数据的末尾，但是没有进行对齐
    //本函数的作用就是用来对齐

    int offset=off;
    //先分离出下一个数据的类型
    int sequenceNum_i=stoi(departSequence(sequence,number));
    //因为我们整个结构体，最大的数据类型所占字节数是8，所以我们的结构体的大小一是8的倍数
    //并且任何一个数据到来的时候，会把前面的内存对齐为自己类型所占字节数的整数倍，这样我们就有了对齐方案
    switch (sequenceNum_i)
    {
    case 1:
        //这是一个int数据，前面的偏移要是4的倍数
        while ((offset%4)!=0)
        {
            //说明现在的偏移不是4的倍数,一直加到是4的整数倍
            offset++;
        }
        break;
    case 2:
        //这是一个char数据，前面的偏移要是1的倍数
        while ((offset%1)!=0)
        {
            //说明现在的偏移不是1的倍数,一直加到是1的整数倍
            offset++;
        }
        break;
    case 3:
        //这是一个bool数据，前面的偏移要是1的倍数
        while ((offset%1)!=0)
        {
            //说明现在的偏移不是1的倍数,一直加到是1的整数倍
            offset++;
        }
        break;
    case 4:
        //这是一个float数据，前面的偏移要是1的倍数
        while ((offset%4)!=0)
        {
            //说明现在的偏移不是4的倍数,一直加到是4的整数倍
            offset++;
        }
        break;
    case 5:
        //这是一个double数据，前面的偏移要是8的倍数
        while ((offset%8)!=0)
        {
            //说明现在的偏移不是8的倍数,一直加到是8的整数倍
            offset++;
        }
        break;
    }
    return offset;
}

//将数据插入缓存行数据，成为一行链表
void addOneCol(mem_data_struct* inputData,mem_data_head* chainHead_cache){
    //需要首先定位到最后一个头结点
    mem_data_struct* data = inputData;
    int off=sizeof(string);
    string sequence=inputData->sequence;
    string sequenceNum;
    if(chainHead_cache->last==NULL){
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
                chainHead_cache->firstNode=node;
                chainHead_cache->lastNode=node;
                chainHead_cache->nodeNum++;
                //调整off的数值--已经更改，并且在getADataToColNode中已经对齐，不需要更改
                //off+=8;
                continue;
            }
            getADataToColNode(node,departSequence(sequence,i),data,&off);
            chainHead_cache->lastNode->next=node;
            chainHead_cache->lastNode=node;
            chainHead_cache->nodeNum++;
            //调整off的数值
            if(i<sequence.size()){
                off=setOff(sequence,i+1,off);
            }
        }
        chainHead_cache->lastNode->next=NULL;
        addHead(chainHead_cache);
    }
    else{
        mem_data_head* pointer=chainHead_cache->last;
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
                //调整off的数值
                //off+=8;
                continue;
            }
            getADataToColNode(node,departSequence(sequence,i),data,&off);
            pointer->lastNode->next=node;
            pointer->lastNode=node;
            pointer->nodeNum++;
            //调整off的数值
            if(i<sequence.size()){
                off=setOff(sequence,i+1,off);
            }
        }
        chainHead_cache->lastNode->next=NULL;
        addHead(chainHead_cache);
    }
    //函数结束了，说明一帧数据，即一行链表添加完成，所以headNum+1;
    chainHead_cache->sequence=chainHead_cache->firstNode->sequence;
    chainHead_cache->headNum++;
}

//模拟传感器产生数据-----------------------------服务于boostDataToStruct
void sensor(mem_data_struct* dataSource){
        dataSource->timeStamp = time(NULL);
        dataSource->intData = (dataSource->intData-250+5)%50 + 250;
        dataSource->charData = (char)((dataSource->charData+1));
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
bool pushOneCol(mem_data_head** chainHead_cache,mem_data_head** chainHead_mem){
    if((*chainHead_cache)->headNum<1){
        //小于最小输出标准，不进行push
        return false;
    }
    //否则，进行push
    mem_data_head* chainHead_cache_save=(*chainHead_cache);
    mem_data_head* ColToBePush=(*chainHead_cache);
    //让chainHead_cache指针指向下一个头，然后因为移出了一行，所以headNum-1
    (*chainHead_cache)->next->sequence=(*chainHead_cache)->sequence;
    (*chainHead_cache)=(*chainHead_cache)->next;
    (*chainHead_cache)->headNum=((chainHead_cache_save)->headNum)-1;
    //_save指向的还是之前的头，我们把headNum置1
    (chainHead_cache_save)->headNum=1;
    if((*chainHead_mem)->next==NULL){
        //说明内存中还没有一帧数据
        (*chainHead_mem)->firstNode=ColToBePush->firstNode;
        (*chainHead_mem)->lastNode=ColToBePush->lastNode;
        (*chainHead_mem)->headNum++;
        addHead((*chainHead_mem));
        (*chainHead_mem)->sequence=ColToBePush->sequence;
        (*chainHead_mem)->nodeNum=ColToBePush->nodeNum;
        return true;
    }
    else{
        //说明内存中已经有1帧及以上的数据了，直接添加到最后的空头里头就好
        (*chainHead_mem)->last->firstNode=ColToBePush->firstNode;
        (*chainHead_mem)->last->lastNode=ColToBePush->lastNode;
        (*chainHead_mem)->headNum++;
        (*chainHead_mem)->sequence=ColToBePush->sequence;
        (*chainHead_mem)->nodeNum=ColToBePush->nodeNum;
        addHead((*chainHead_mem));
        return true;
    }
}

//生成一帧数据，并往内存中插入一帧数据
bool insert(mem_data_struct* dataSource,mem_data_head** chainHead_cache,mem_data_head** chainHead_mem){
    //mem_data_head* chainHead_cache=new mem_data_head;
    //先产生一帧数据，放入结构体
    boostDataToStruct(dataSource);
    //为缓存行链表添加数据
    addOneCol(dataSource,(*chainHead_cache));
    // //为缓存行链表添加新头,只是增加一个空头
    // addOneHead(chainHead_cache);
    //将缓存中的一行转换到内存中
    pushOneCol(chainHead_cache,chainHead_mem);
    return true;
}   