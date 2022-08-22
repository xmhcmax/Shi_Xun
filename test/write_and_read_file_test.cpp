#include"..\\main\\data_in_disk_forN\\data_in_disk_forN.h"
using namespace std;
//这个文件用来测试关于文件读写的一些操作

bool writeInt(ofstream& fout,int intData){
    fout.write((char*)&intData,sizeof(int));
    return true;
}


int main(){
//带偏移量单个读写
/*    
    int a=1;
    int c=sizeof(a);
    ofstream fin;
    //以追加的方式写入文件
    //fin.open("test.db",ios::binary|ios::app);
    //以覆盖的方式写入文件
    fin.open("test.db",ios::binary);
    fin.write((char*)&a,sizeof(int));
    fin.write((char*)&c,sizeof(int));
    fin.close();
    
    int b=0;
    ifstream fout1;
    ifstream fout2;
    fout1.open("test.db",ios::in|ios::binary);
    fout2.open("test.db",ios::in|ios::binary);
    //从文件头开始，偏移sizeof(int)位置开始读入
    fout1.seekg(sizeof(int),ios::beg);
    fout2.seekg(0,ios::beg);
    //从偏移4读入
    fout1.read((char*)&b,sizeof(int));
    //从偏移0读入，覆盖偏移4读入
    fout2.read((char*)&b,sizeof(int));
    fout1.close();
    fout2.close();
    
    cout<<b<<endl;
    return 0;
*/

//不带偏移量以数组形式读写
/*
    int a[10]={1,2,3,4,5,6,7,8,9,10};
    ofstream fout;
    fout.open("test2.db",ios::binary);
    fout.write((char*)a,sizeof(int)*10);
    fout.close();


    int b[10];
    ifstream fin;
    fin.open("test2.db",ios::binary);
    fin.read((char*)b,sizeof(int)*10);
    fin.close();
    for(int i=0;i<10;i++){
        cout<<b[i]<<endl;
    }
    return 0;
*/

//使用sizeof作为输入-----出现错误，不能使用sizeof作为输入
/*
    ofstream fout;
    fout.open("test3.db",ios::binary);
    fout.write((char*)(sizeof(bool)*10),sizeof((sizeof(bool)*10)));
    fout.close();

    int b;
    ifstream fin;
    fin.open("test3.db",ios::binary);
    fin.read((char*)&b,sizeof((sizeof(bool)*10)));
    fin.close();

    cout<<b<<endl;
    return 0;
*/

// //看看会不会自己创建文件夹出来---是不会的
//     int a=1;
//     ofstream fout1;
//     ofstream fout2;
//     fout1.open("D:\\apps\\VS code\\Programs\\C++ program\\shixun\\data\\testFile\\test4.db",ios::binary);
//     fout1.write((char*)&a,sizeof(int));
//     fout1.close();
//     // fout2.open("test4.db",ios::binary);
//     // fout2.write((char*)&a,sizeof(int));
//     // fout2.close();
// }

// //看看能不能用绝对路径创建文件---可以
//     int a=1;
//     ofstream fout1;
//     ofstream fout2;
//     fout1.open("D:\\apps\\VS code\\Programs\\C++ program\\shixun\\data_transit\\test4.db",ios::binary);
//     fout1.write((char*)&a,sizeof(int));
//     fout1.close();

// //看看能不能用str来存入和接收--输入可以，接收用char数组来接收，转换成str
//     string str1="1.2";
//     ofstream fout;
//     fout.open("test.index",ios::binary);
//     fout.write(str1.c_str(),sizeof(str1));
//     fout.close();

//     string str2;
//     ifstream fin;
//     char* p;//=str2.data();
//     fin.open("test.index",ios::binary);
//     cout<<fin.is_open()<<endl;
//     char a[10];
//     fin.read((char*)a,sizeof(a));
//     fin.close();
//     str2=a;
//     cout<<str2<<endl;
    
//带偏移量读取多个字符   
    // string a="1.23";
    // ofstream fin;
    // //以追加的方式写入文件
    // //fin.open("test.db",ios::binary|ios::app);
    // //以覆盖的方式写入文件
    // fin.open("test.db",ios::binary);
    // fin.write(a.c_str(),sizeof(int));
    // fin.close();
    // cout<<a.size()<<endl;

    // char b[4];
    // ifstream fout;
    // fout.open("test.db",ios::in|ios::binary);
    // //从文件头开始，偏移1位置开始读入
    // fout.seekg(1,ios::beg);
    // fout.read((char*)b,3);
    // fout.close();
    // a=b;
    // cout<<a<<endl;
    // cout<<a.size()<<endl;

    //测试函数
    // ofstream fout;
    // fout.open("test.txt",ios::app|ios::binary);
    // int i[2]={1,2};
    // cout<<i[0]<<i[1]<<endl;

    // writeInt(fout,i[1]);
    // fout.close();

    // ifstream fin;
    // fin.open("test.txt",ios::binary);
    // int j;
    // fin.read((char*)&j,sizeof(int));
    // fin.close();

    // cout<<j<<endl;

    //测试写入2个str，y读出来会不会串--没有串起来
    // ofstream fout;
    // string str1="1.0";
    // string str2="1.1";
    // string str3="1.2";
    // fout.open("test.txt",ios::app);
    // fout.write(str1.c_str(),sizeof(string));
    // fout.write(str2.c_str(),sizeof(string));
    // fout.write(str3.c_str(),sizeof(string));
    // fout.close();

    // char char1[10];
    // char char2[10];
    // ifstream fin;
    // fin.open("test.txt");
    // fin.read((char*)char1,sizeof(char1));
    // fin.seekg(sizeof(str3),ios::beg);
    // fin.read((char*)char2,sizeof(char2));
    // fin.close();
    // string str4=char2;
    // cout<<char1<<endl;
    // cout<<str4<<endl;

    //测试最后一个读出来会不会是""
//     ofstream fout;
//     string str1="1.0";
//     string str2="1.1";
//     string str3="1.2";
//     fout.open("test.txt",ios::app);
//     fout.write(str1.c_str(),sizeof(string));
//     fout.write(str2.c_str(),sizeof(string));
//     fout.write(str3.c_str(),sizeof(string));
//     fout.close();

//     int num=0;
//     int pos=0;
//     string strout;
//     char char1[4];
    
//     ifstream fin;
//     fin.open("test.txt");
//     do{
//         fin.seekg(pos,ios::beg);
//         fin.read((char*)char1,sizeof(char1));
//         strout=char1;
//         char1[0]={0};
//         cout<<strout<<endl;
//         pos+=sizeof(string);
//         num++;
//     }
//    while(strout!="");
//     fin.close();
//     cout<<num<<endl;
    
    //测试从文件尾部开始读取
    ofstream fout;
    string str1="1.0";
    string str2="1.1";
    string str3="1.2";
    fout.open("test.txt",ios::app|ios::binary);
    fout.write(str1.c_str(),sizeof(string));
    fout.write(str2.c_str(),sizeof(string));
    fout.write(str3.c_str(),sizeof(string));
    fout.close();

    char chars[10];
    string str;
    ifstream fin;
    fin.open("test.txt",ios::binary);
    fin.seekg(-sizeof(string),ios::end);
    fin.read((char*)chars,sizeof(chars));
    fin.close();
    str=chars;
    cout<<str<<endl;

    
    return 0;
}