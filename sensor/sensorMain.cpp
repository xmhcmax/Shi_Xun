#include"sensor.h"
using namespace std;

int main(){
    //为用户建立目录
    initFolder();
    //创建一帧数据的结构体
    mem_data_struct* dataSource=new mem_data_struct;
    initdataStruct(dataSource);
    //创建一个缓存传感器数据的行链表
    mem_data_head* chainHead_cache=initColChain();
    //创建一个内存数据的行链表
    mem_data_head* colChain=initColChain();
    //创建用于指向即将转换的数据头的指针
    mem_data_head* dataToTransit;
    //用于指定文件路径的一个变量
    string filePath;
    while(1){
        //插入一帧数据进入内存
        insert(dataSource,&chainHead_cache,&colChain);
        //检查内存中的数据
        if(get10Cols(&colChain,&dataToTransit)){
            //可以进行行列转换存文件了
            transit_data_chain* rowChain=initRowChain(colChain);
            //10帧数据的行列转换
            colTOrow(&dataToTransit,&rowChain);
            //列存数据转一级文件,其中包含了进行一级upgrade、递归upgrade
            makeLevelOneFile(&rowChain);
            //初始化结构体
            initdataStruct(dataSource);
        }
        Sleep(1000);
    }
    return 0;
}