#include"..\\main\\data_in_disk_forN\\data_in_disk_forN.h"
using namespace std;
struct tests
{
    int a=0;
    tests* next;
};


void change(tests** test){
    (*test)=(*test)->next;
    int a=0;
}

int main(){
    tests* test1=new tests;
    tests* test2=new tests;
    test1->next=test2;
    change(&test1);
    return 0;
}