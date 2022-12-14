#include"data_in_mem_forN.h"

using namespace std;
//这个文件定义了行链表的节点和节点中包含的联合，以及节点的组织函数

static string SOURCEPATH="D:\\dataFile\\source.db";
//static mem_data_head** HEADPOINTER;//一行数据的指针，用来接收传感器构成的

// //定义了存储数据的最小单位--联合
// union mem_data_union
// {
//     time_t timeStamp;
//     int intData;
//     char charData;
//     bool boolData;
//     float floatData;
//     double doubleData;
// };

// //定义了行链表的结点结构，包含next的指针和指向联合的指针
// struct mem_data_node
// {
//     string sequence;
//     mem_data_union* data;
//     mem_data_node* next;
// };

// //定义了行链表头结点，其中有指向行链表第一个和最后一个结点的node指针，
// //指向上一个、下一个头结点和最后一个头结点的previous、next、last指针，还包含该链表中节点数量信息
// struct mem_data_head
// {
//     string sequence;
//     int nodeNum=0,headNum=0;
//     mem_data_node* firstNode;
//     mem_data_node* lastNode;
//     mem_data_head* previous;
//     mem_data_head* next;
//     mem_data_head* last;

// };

// //用来给出HEADPOINTER指针的函数
// mem_data_head** getHEADPOINTER(){
//     return HEADPOINTER;
// }

//初始化行链表,返回一个已经分配内存，并且其他全部初始化为空或者0的行链表头指针
mem_data_head* initColChain(){
    mem_data_head* chainHead=new mem_data_head;
    chainHead->sequence="";
    chainHead->firstNode=NULL;
    chainHead->lastNode=NULL;
    chainHead->previous=NULL;
    chainHead->next=NULL;
    chainHead->last=NULL;
    chainHead->nodeNum=0;
    chainHead->headNum=0;
    return chainHead;
}

// //获取第一个数据--时间戳进入第一个node，并且加入链表
// bool getTimeStampInChain(mem_data_head* chainHead,mem_data_node* node){
//     //说明只有一个头结点，那就操作这个头结点
//     if(chainHead->last==NULL){
//         time_t timeStamp;
//         fin.read((char*)timeStamp,sizeof(time_t));
//         node->data->timeStamp=timeStamp;
//         fin.close();
//         chainHead->firstNode=node;
//         chainHead->lastNode=node;
//         //添加了时间戳数据在这一行链表，表明这一行链表真实存在了，所以HeadNum++
//         chainHead->headNum++;
//         //时间戳是一个数据，所以nodeNum++
//         chainHead->nodeNum++;
//         return true;
//     }
//     //不止他一个，就到最后一个头结点
//     else{
//         mem_data_head* pointer=chainHead->last;
//         time_t timeStamp;
//         fin.read((char*)timeStamp,sizeof(time_t));
//         node->data->timeStamp=timeStamp;
//         fin.close();
//         pointer->firstNode=node;
//         pointer->lastNode=node;
//         //添加了时间戳数据在这一行链表，表明这一行链表真实存在了，所以HeadNum++
//         chainHead->headNum++;
//         //时间戳是一个数据，所以nodeNum++
//         chainHead->nodeNum++;
//         return true;
//     }
// }

// //获取一个数据到node中
// bool getOneData(mem_data_node* node,string sequenceNum,int* off){
//     int sequenceNum_i=stoi(sequenceNum);
//     ifstream fin;
//     fin.open(SOURCEPATH,ios::binary);
//     if(!fin.is_open()){
//         cout<<"源文件打开失败！"<<endl;
//         return false;
//     }
//     //进行偏移
//     fin.seekg(*off,ios::beg);
//     switch (sequenceNum_i)
//     {
//     case 1:
//         //读出一个int类型
//         int intData;
//         fin.read((char*)&intData,sizeof(int));
//         *off+=sizeof(int);
//         node->data->intData=intData;
//         break;
//     case 2:
//         //读出一个char类型
//         char charData;
//         fin.read((char*)&charData,sizeof(char));
//         *off+=sizeof(char);
//         node->data->charData=charData;
//         break;
//     case 3:
//         //读出一个bool类型
//         bool boolData;
//         fin.read((char*)&boolData,sizeof(bool));
//         *off+=sizeof(bool);
//         node->data->boolData=boolData;
//         break;
//     case 4:
//         //读出一个float类型
//         float floatData;
//         fin.read((char*)&floatData,sizeof(float));
//         *off+=sizeof(float);
//         node->data->floatData=floatData;
//         break;
//     case 5:
//         //读出一个double类型
//         double doubleData;
//         fin.read((char*)&doubleData,sizeof(double));
//         *off+=sizeof(double);
//         node->data->doubleData=doubleData;
//         break;
//     }
//     fin.close();
//     return true;
// }

// //添加node进入链表,一个函数将一行的数据全部加入
// bool addNode(string sequence,mem_data_head* chainHead){
//     int sequence_i;
//     int off=sizeof(time_t);
//     //需要首先定位到最后一个头结点
//     if(chainHead->last==NULL){
//         for(int i=1;i<=sequence.size();i++){
//         mem_data_node* node=new mem_data_node;
//         mem_data_union* Union=new mem_data_union;
//         node->data=Union;
//         //sequence_i=stoi(departSequence(sequence,i));
//         getOneData(node,departSequence(sequence,i),&off);
//         chainHead->lastNode->next=node;
//         chainHead->lastNode=node;
//         chainHead->nodeNum++;
//     }
//     }
//     else{
//         mem_data_head* pointer=chainHead->last;
//         for(int i=1;i<=sequence.size();i++){
//         mem_data_node* node=new mem_data_node;
//         mem_data_union* Union=new mem_data_union;
//         node->data=Union;
//         //sequence_i=stoi(departSequence(sequence,i));
//         getOneData(node,departSequence(sequence,i),&off);
//         pointer->lastNode->next=node;
//         pointer->lastNode=node;
//         pointer->nodeNum++;
//         }
//     }
//     return true;
// }

//添加新的一行的头
bool addHead(mem_data_head* chainHead){
    mem_data_head* nextChainHead=initColChain();
    if(chainHead->next==NULL){
        chainHead->next=nextChainHead;
        chainHead->last=nextChainHead;
    }
    else{
        chainHead->last->next=nextChainHead;
        chainHead->last=nextChainHead;
    }
    return true;
}


// //拿到一帧数据，以一条链的形式体现
// bool getOneCol(mem_data_head* chainHead){
//     // setDATA_REQUEST();
//     if(chainHead->next=NULL){
//         //说明内存中还没有一帧数据
//         chainHead->firstNode=(*HEADPOINTER)->firstNode;
//         chainHead->headNum++;
//         addHead(chainHead);
//         return true;
//     }
//     else{
//         //说明内存中已经有1帧及以上的数据了，直接添加到最后的空头里头就好
//         chainHead->last->firstNode=(*HEADPOINTER)->firstNode;
//         chainHead->headNum++;
//         addHead(chainHead);
//         return true;
//     }
//     delete(HEADPOINTER);
// }

//查看内存里够不够10条数据了
bool ifTenDataYet(mem_data_head* chainHead_mem){
    if(chainHead_mem->headNum>10){
        return true;
    }
    else return false;
}

//把成链的头以10个一组分离出来，进行接下来的行列转换
bool get10Cols(mem_data_head** chainHead,mem_data_head** dataToTransit){
    if(!ifTenDataYet((*chainHead))){
        return false;
    }
    (*dataToTransit)=(*chainHead);
    mem_data_head* chainHead_save=(*chainHead);
    mem_data_head* lastHead;
    //定位到第10个
    for(int i=0;i<9;i++){
        (*dataToTransit)=(*dataToTransit)->next;
    }
    lastHead=(*dataToTransit);
    //原链表头指针指向第11个头结点
    (*chainHead)=(*dataToTransit)->next;
    //断开链接
    (*dataToTransit)->next=NULL;
    //分离链表头指针指向原链表第一个头
    (*dataToTransit)=chainHead_save;
    //修改last指针
    (*chainHead)->last=(*dataToTransit)->last;
    (*dataToTransit)->last=lastHead;
    //继承sequence
    (*chainHead)->sequence=(*dataToTransit)->sequence;
    //修改headNum数据
    (*chainHead)->headNum=(*dataToTransit)->headNum-10;
    //(*chainHead)->last=(*chainHead)->next;
    (*dataToTransit)->headNum=10;
    return true;
    }

