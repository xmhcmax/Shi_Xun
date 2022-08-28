#include"data_in_mem_forN.h"

using namespace std;
//这个文件用于向用户了解用户需要的数据类型和数量，方便我们后续进行构建行链表

static string SEQUENCE;

//识别用户的输入，来判断用户需要的数据类型和数量
string getClientRequest(){//int，char，bool，int---1231
    char chars[10];
    char sequence[20];
    int sequenceNum=0;
    string str;
    string strInt="int";
    string strChar="char";
    string strBool="bool";
    string strFloat="float";
    string strDouble="double";
    while(1){
        cout<<"第一个数据已经默认为时间戳，如果要退出，请输入0";
        cout<<"请输入其他您需要的数据类型(小写)："<<endl;
        cin>>chars;
        str=chars;
        if(!str.compare("0")){
            break;
        }
        if(!str.compare(strInt)){
            sequence[sequenceNum++]='1';
            continue;
        }
        else if(!str.compare(strChar)){
            sequence[sequenceNum++]='2';
            continue;
        }
        else if(!str.compare(strBool)){
            sequence[sequenceNum++]='3';
            continue;
        }
        else if(!str.compare(strFloat)){
            sequence[sequenceNum++]='4';
            continue;
        }
        else if(!str.compare(strDouble)){
            sequence[sequenceNum++]='5';
            continue;
        }
        else{
            cout<<"Please use the correct type"<<endl;
        }
    }
    str=sequence;
    cout<<"接收完成！"<<endl;
    SEQUENCE=str;
    return str;
}

//进行sequence的任意位置的数据读取,要获取第几位,sequenceNum就几
string departSequence(string sequence,int sequenceNum){
    sequence.erase(0,sequenceNum-1);
    sequence.resize(1);
    return sequence;
}

//得到SEQUENCE
string getSequence(){
    return SEQUENCE;
}

