#include"data_transit_forN.h"
using namespace std;
//该文件用于定义行列转换中列数据结构

// //用来放数组的联合,可以用来容纳任意数据类型10条
// union transit_data_union
// {
//     time_t timeData[10];
//     int intData[10];
//     char charData[10];
//     bool boolData[10];
//     float floatData[10];
//     double doubleData[10];
// };

// //用来存放联合的单链表
// struct transit_data_chain
// {
//     string sequence;
//     int dataNum;
//     transit_data_union* data;
//     transit_data_chain* next;
//     transit_data_chain* last;
// };

//初始化列链表,返回一个链表头指针，可以用来创建一个链表
transit_data_chain* initRowChain(){
    string sequence=getSequence();
    transit_data_chain* chainHead=new transit_data_chain;
    transit_data_chain* pointer=chainHead;
    chainHead->sequence=sequence;
    chainHead->data=NULL;
    chainHead->next=NULL;
    chainHead->last=NULL;
    chainHead->dataNum=sequence.size()+1;
    //创建长度为sequence长度+2的链表，因为还有时间戳数据,并且第一个结点（头）不保存数据
    for(int i=0;i<=sequence.size();i++){
        //先创建链表结点
        transit_data_chain* chainNode=new transit_data_chain;
        //再创建结点内联合
        transit_data_union* nodeUnion=new transit_data_union;
        //添加联合
        chainNode->data=nodeUnion;
        //加入头结点,先修改next指针
        pointer->next=chainNode;
        pointer=pointer->next;
    }
    // //最后修改last指针
    // chainHead->last=pointer;
    // //pointer指回chainHead
    // pointer=chainHead;
    return chainHead;
}

//根据sequence往链表中行列转换数据,dataToTransit是分离出来的十条链表的第一个头指针
bool colTOrow(mem_data_head* dataToTransit,transit_data_chain* rowChain){
    string sequence=rowChain->sequence;
    int sequenceNum;
    mem_data_head* colChainHeadPointer=dataToTransit;
    mem_data_head* saveHead;
    mem_data_node* colChainNodePointer=colChainHeadPointer->firstNode;
    //mem_data_node* saveNode;
    transit_data_chain* rowChainNodePointer=rowChain->next;
    //先转移一种类型，从上往下移动,转移第一节点中的内容，然后将第一节点指向下一个节点
    for(int i=0;i<=sequence.size();i++){
    //外循环，循环row链表结点  

        for(int j=0;j<10;j++){
        //内循环，循环dataToTransit链表
            //判断转移的数据类型
            if(i==0){
            //转移数据
            rowChainNodePointer->data->timeData[j]=colChainNodePointer->data->timeStamp;
            }
            else{
                sequenceNum=stoi(departSequence(sequence,i+1));
                switch (sequenceNum)
                {
                case 1:
                    //添加int类型
                    rowChainNodePointer->data->intData[j]=colChainNodePointer->data->intData;
                    break;
                case 2:
                    //添加char类型
                    rowChainNodePointer->data->charData[j]=colChainNodePointer->data->charData;
                    break;
                case 3:
                    //添加bool类型
                    rowChainNodePointer->data->boolData[j]=colChainNodePointer->data->boolData;
                    break;
                case 4:
                    //添加float类型
                    rowChainNodePointer->data->floatData[j]=colChainNodePointer->data->floatData;
                    break;
                case 5:
                    //添加double类型
                    rowChainNodePointer->data->doubleData[j]=colChainNodePointer->data->doubleData;
                    break;
                }
            }
            //最后一个数据转移完成，需要进行内存释放
            if(i==sequence.size()){
                saveHead=colChainHeadPointer;
                colChainHeadPointer=colChainHeadPointer->next;
                delete(saveHead->firstNode);
                delete(saveHead);
                colChainNodePointer=colChainHeadPointer->firstNode;
            }
            //不是最后一个就往后指
            else{
                colChainHeadPointer=colChainHeadPointer->next;
                colChainNodePointer=colChainHeadPointer->firstNode;
            }
        }
        rowChainNodePointer=rowChainNodePointer->next;
    }
}




