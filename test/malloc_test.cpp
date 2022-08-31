#include"..\\main\\data_in_disk_forN\\data_in_disk_forN.h"
#include<io.h>
using namespace std;

union unionTest
{
    int Idata;
    char Cdata;
};


struct test
{
    unionTest* dataUnion;
    test* next;
};

//在函数内定义，然后再函数内进行内存申请--赋值的地方出现错误
// void mallocTest1(test** head){
//     *head=new test;
//     (*head)->next=NULL;
//     (*head)->dataUnion->Cdata='2';
// }

//使用在函数内用new的方法分配内存，并且在函数内进行定义--可以使用，（但是会多一个指针，与main函数共同指向同一个内存）<-有误
test* mallocTest2(){
    test* HeadTest=new test;
    HeadTest->next=NULL;
    HeadTest->dataUnion=new unionTest;
    HeadTest->dataUnion->Cdata='2';
    return HeadTest;
}

int main(){
    //test* headTest;
    //mallocTest1(&headTest);
    test* headTest=mallocTest2();
    cout<<headTest->dataUnion->Cdata<<endl;
    return 0;
}