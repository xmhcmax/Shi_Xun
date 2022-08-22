#include"data_in_disk_forN\\data_in_disk_forN.h"
using namespace std;

int main(){
    cout<< "hello,world"<<endl;
    //为用户创建目录
    initFolder();
    //初始化行表
    mem_data_head* head;
    head=initColChain();
    return 0;
}