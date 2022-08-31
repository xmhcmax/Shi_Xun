#include"data_in_mem.h"
using namespace std;
//这里是在内存中存储dataPiece节点的存储结构，dataPiece属于memNode，选择用链表按时间序列存储
//之所以是时间序列，是因为数据来就是已经按时间排好了序的，就不用再做处理
//链表是放在内存中的数据结构，把dataPiece放入memNode插入到headNode链表的最后

//链表节点结构体
//  struct memNode
// {
//     memNode * next;
//     dataPiece * data;
// };

//链表头结点结构体
// struct headNode
// {
//     int nodeCount;
//     memNode* last;
//     memNode* next;
// };

//初始化链表头
bool initMemList(headNode* nodeHead){
    nodeHead->nodeCount=0;
    nodeHead->last=NULL;
    nodeHead->next=NULL;
    return true;
}

//接收数据函数--未完成--已废弃
// dataPiece* catchData(){
//     dataPiece* data=(dataPiece*)malloc(sizeof(dataPiece));
//     if(data==NULL)
//     return NULL;
//     data->temp=0;
//     data->deleted=false;
//     data->timestamp=0;
//     return data;
// }

//存入链表的函数-未完成
bool saveNode(headNode headNode,dataPiece* dataSource){
    dataPiece* data=new dataPiece;
    data->deleted=dataSource->deleted;
    data->temp=dataSource->temp;
    data->timestamp=dataSource->timestamp;
    
    memNode* newNode=new memNode;
    newNode->data->deleted=data->deleted;
    newNode->data->temp=data->temp;
    newNode->data->timestamp=data->timestamp;
    if(headNode.nodeCount=0){
        headNode.next=newNode;
        headNode.last=newNode;
        headNode.nodeCount++;
        return true;
    }
    else{
        headNode.last->next=newNode;
        headNode.last=newNode;
        headNode.nodeCount++;
        return true;
    }
}