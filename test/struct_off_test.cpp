#include"..\\main\\data_in_disk_forN\\data_in_disk_forN.h"
using namespace std;

struct testStruct
{
    time_t timeStamp=time(NULL);
    int a=1;
    char b='1';
    bool c=true;
    bool d=true;
    bool h=true;
    float e=1.21;
    float i=1.22;
    double f=1.24;
    int g=0;
};

struct getStruct
{
    time_t timeStamp;
    int a;
    char b;
    bool c;
    bool d;
    bool h;
    float e;
    float i;
    double f;
    int g=0;
};

void testFunc(testStruct* test,getStruct* get,int* off){
    get->timeStamp=*(time_t *)((unsigned char *)test+*off);
    *off+=sizeof(time_t);
    get->a= *(int *)((unsigned char *)test+*off);
    *off+=sizeof(int);
    get->b=*(time_t *)((unsigned char *)test+*off);
    *off+=sizeof(char);
    get->c=*(bool *)((unsigned char *)test+*off);
    //off=offsetof(testStruct,d);
    *off+=sizeof(bool);
    get->d=*(bool *)((unsigned char *)test+*off);
    //off=offsetof(testStruct,h);
    *off+=sizeof(bool);
    get->h=*(bool *)((unsigned char *)test+*off);
    //off=offsetof(testStruct,e);
    *off+=sizeof(bool);
    get->e=*(float *)((unsigned char *)test+*off);
    //off=offsetof(testStruct,i);
    *off+=sizeof(float);
    get->i=*(float *)((unsigned char *)test+*off);
    //off=offsetof(testStruct,f);
    *off+=sizeof(float);
    get->f=*(double *)((unsigned char *)test+*off);
    //off=offsetof(testStruct,g);
    *off+=sizeof(double);
    cout<<sizeof(bool)<<endl;
}

int main(){
    testStruct* test=new testStruct;
    getStruct* get=new getStruct;
    int off=0;
    testFunc(test,get,&off);
    return 0;
}


// struct Test
// {
// int b;
// int a;
// char ch;

// };
// int main()
// {
// Test mytest;
// mytest.a = 111;
// mytest.b = 222;
// mytest.ch = 'A';
// int a = *(int *)((unsigned char *)&mytest + sizeof(int));
// cout << a << endl;//a=222,this value is related to the order of declaration
// char ch = *(char *)((unsigned char *)&mytest + sizeof(int)*2);
// cout << ch << endl;//ch='A'
// cout << "--------------------" << endl;
// int *b = (int *)((unsigned char *)&mytest);
// cout << *b << endl;
// int *ap = (int *)(b + 1);
// cout << *ap << endl;
// char *cp = (char *)(ap + 1);
// cout << *cp << endl;

// system("pause");
// return 0;

// }