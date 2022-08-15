#include"data_in_disk_forN.h"
using namespace std;

//得到索引文件的level,int类型
int getIndexLevel(string indexPath){
    string indexLevel_s;
    int indexLevel_i;
    indexLevel_s=indexPath.substr(0,indexPath.size()-8);
    indexLevel_s.erase(0,indexLevel_s.size()-1);
    indexLevel_i=stoi(indexLevel_s);
    return indexLevel_i;
}

//得到索引文件的number,int类型
int getIndexNumber(string indexPath){
    string indexNumber_s;
    int indexNumber_i;
    indexNumber_s=indexPath.substr(0,indexPath.size()-6);
    indexNumber_s.erase(0,indexNumber_s.size()-1);
    indexNumber_i=stoi(indexNumber_s);
    return indexNumber_i;
}

//给对应的文件路径，创建该文件的index
bool makeIndex(string filePath,string sequence){
    string indexName=filePath;
    string fileName=filePath;
    string indexPath=filePath.substr(0,filePath.size()-6);
    fileName.resize(fileName.size()-3);
    fileName.erase(0,fileName.size()-3);
    indexName.erase(0,indexName.size()-6);
    indexName.resize(3);
    indexName.append(".index");
    indexPath.append(indexName);
    ofstream fout;
    fout.open(indexPath,ios::binary|ios::app);
    //先写入sequence
    fout.write(sequence.c_str(),sizeof(sequence));
    //再写入文件名(不带后缀)
    fout.write(fileName.c_str(),sizeof(fileName));
    ifstream fin;
    fin.open(filePath,ios::binary);
    if(!fin.is_open()){
        cout<<"No file!!"<<endl;
        return false;
    }
    //写入首时间戳
    time_t timeStamp;
    fin.read((char*)&timeStamp,sizeof(time_t));
    fout.write((char*)&timeStamp,sizeof(time_t));
    //写入尾时间戳
    fin.seekg(sizeof(time_t)*((10^getFileLevel(filePath))-1),ios::beg);
    fin.read((char*)&timeStamp,sizeof(time_t));
    fout.write((char*)&timeStamp,sizeof(time_t));
    fin.close();
    //开始根据索引写入数据偏移
    int sequenceNum;
    //略过10^level个时间戳数据
    int pos=sizeof(time_t)*(10^getFileLevel(filePath));
    for(int i=1;i<=sequence.size();i++){
        sequenceNum=stoi(departSequence(sequence,i));
        switch (sequenceNum)
        {
        case 1:
            //是int类型数据
            fout.write((char*)&pos,sizeof(int));
            pos+=sizeof(int)*(10^getFileLevel(filePath));
            break;
        case 2:
            //是char类型数据
            fout.write((char*)&pos,sizeof(int));
            pos+=sizeof(char)*(10^getFileLevel(filePath));
            break;
        case 3:
            //是bool类型数据
            fout.write((char*)&pos,sizeof(int));
            pos+=sizeof(bool)*(10^getFileLevel(filePath));
            break;
        case 4:
            //是float类型数据
            fout.write((char*)&pos,sizeof(int));
            pos+=sizeof(float)*(10^getFileLevel(filePath));
            break;
        case 5:
            //是double类型数据
            fout.write((char*)&pos,sizeof(int));
            pos+=sizeof(double)*(10^getFileLevel(filePath));
            break;
        default:
            break;
        }
    }
    fout.close();
    return true;
}