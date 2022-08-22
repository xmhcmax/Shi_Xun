#include"..\\main\\data_in_disk_forN\\data_in_disk_forN.h"
using namespace std;

string departSequence(string sequence,int sequenceNum){
    sequence.erase(0,sequenceNum-1);
    sequence.resize(1);
    return sequence;
}

//测试用char[]来接收用户输入，然后给string赋值后对比---对比结果相等返回0，不相等返回1
int main(){
    // char* chars;
    // char charss[100];
    // string str1,str2="str2";
    // cin.get(charss,20);
    // //cin>>charss;
    // //chars=&charss;st
    // str1=charss;
    // cout<<sizeof(str1)<<"   "<<sizeof(str2)<<endl;
    // cout<<str2.compare(str1)<<endl;
    // cout<<str1<<endl;

    // char chars[10];
    // string str;
    // cin.get(chars,10);
    // str=chars;

    // cout<<str.compare("0")<<endl;
    // cout<<chars<<str<<endl;
    // cout<<str<<endl;


//测试dataSource的getClientRequest函数
    // char chars[10];
    // char sequence[20];
    // int sequenceNum=0;
    // string str;
    // string strInt="int";
    // string strChar="char";
    // string strBool="bool";
    // string strFloat="float";
    // string strDouble="double";
    // while(1){
    //     cout<<"如果要退出，请输入0。"<<endl;
    //     cout<<"请输入您需要的数据类型(小写)："<<endl;
    //     cin>>chars;
    //     str=chars;
    //     if(!str.compare("0")){
    //         break;
    //     }
    //     if(!str.compare(strInt)){
    //         sequence[sequenceNum++]='1';
    //         continue;
    //     }
    //     else if(!str.compare(strChar)){
    //         sequence[sequenceNum++]='2';
    //         continue;
    //     }
    //     else if(!str.compare(strBool)){
    //         sequence[sequenceNum++]='3';
    //         continue;
    //     }
    //     else if(!str.compare(strFloat)){
    //         sequence[sequenceNum++]='4';
    //         continue;
    //     }
    //     else if(!str.compare(strDouble)){
    //         sequence[sequenceNum++]='5';
    //         continue;
    //     }
    //     else{
    //         cout<<"Please use the correct type"<<endl;
    //     }
    // }
    // str=sequence;
    // cout<<str<<"\n"<<endl;
    // cout<<sequence<<endl;
    
    
    //测试departSequence函数
    // string i=departSequence("012345",3);
    // cout<<departSequence("012345",3)<<endl;

    return 0;
}
