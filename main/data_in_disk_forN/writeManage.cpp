#include"data_in_disk_forN.h"
using namespace std;

//写入time_h类型
bool writeTime(ofstream& fout,time_t timeData){
    fout.write((char*)&timeData,sizeof(time_t));
    return true;
}

//写入int类型
bool writeInt(ofstream& fout,int intData){
    fout.write((char*)&intData,sizeof(int));
    return true;
}

//写入char类型
bool writeChar(ofstream& fout,char charData){
    fout.write((char*)&charData,sizeof(char));
    return true;
}

//写入bool类型
bool writeBool(ofstream& fout,bool boolData){
    fout.write((char*)&boolData,sizeof(bool));
    return true;
}

//写入float类型
bool writeFloat(ofstream& fout,bool floatData){
    fout.write((char*)&floatData,sizeof(float));
    return true;
}

//写入double类型
bool writeDouble(ofstream& fout,bool doubleData){
    fout.write((char*)&doubleData,sizeof(double));
    return true;
}

//写一个数据进入打开的的文件
// bool writeOneData(int sequenceNum,ofstream& fout){
//     switch (sequenceNum)
//     {
//     case 1:
//         //写入int数据
//         writeInt(fout,);
//         break;
    
//     default:
//         break;
//     }
// }