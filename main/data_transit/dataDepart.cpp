#include"data_transit.h"
using namespace std;
//这里是再一次对数据进行了分割处理，看起来有点多于，但是这里是进行行列转换的前夕
//之前分割了数据之后是放到了结构体中，是行形式存储的，这里转换成dataList，变成了列存储

//用于将memery中的链表数据拆分成单个数据的dataAtom,并存放到相应的list中
bool dataDepart(headNode* nodeHead,dataList datalist[]){
    memNode* p=new memNode;
    if(nodeHead->nodeCount>0)
        p=nodeHead->next;
    dataList Lhead[3];
    dataAtom* Ltail[3];
    Lhead[0]=datalist[0];
    Lhead[1]=datalist[1];
    Lhead[2]=datalist[2];
    Ltail[0]=datalist[0].value;
    Ltail[1]=datalist[1].value;
    Ltail[2]=datalist[2].value;
    //第一层循环遍历mem中的数据链表
    for(int i=0;i<(nodeHead->nodeCount);i++){
        //第二层循环把链表节点的数据分别存入union中
        for(int i=0;i<3;i++){
            if(i=0){
                dataUnion* data=new dataUnion;
                dataAtom* value=new dataAtom;
                data->timestamp=p->data->timestamp;
                value->data=data;
                Ltail[i]=value;
                Ltail[i]=Ltail[i]->next;
                Lhead[i].dataCount++;
            }
            else if(i=1){
                dataUnion* data=new dataUnion;
                dataAtom* value=new dataAtom;
                data->temp=p->data->temp;
                value->data=data;
                Ltail[i]=value;
                Ltail[i]=Ltail[i]->next;
                Lhead[i].dataCount++;
            }
            else if(i=2){
                dataUnion* data=new dataUnion;
                dataAtom* value=new dataAtom;
                data->deleted=p->data->deleted;
                value->data=data;
                Ltail[i]=value;
                Ltail[i]=Ltail[i]->next;
                Lhead[i].dataCount++;
            }
        }
    }
}