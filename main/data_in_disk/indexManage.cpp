#include"data_in_disk.h"
using namespace std;
//关于索引的一些处理放在了这里

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

//创建索引,filePath是文件目录，不是级目录、数据文件根目录
bool makeIndex(string filePath){
    string indexPath=filePath;
    //去除".db"后缀
    indexPath.resize(filePath.size()-3);
    //单独取出文件名字，后来使用
    string fileName=indexPath;
    fileName.erase(0,fileName.size()-3);
    //单独取出级号，后来使用
    string level_s=fileName;
    int level_i;
    level_s.resize(2);
    level_i=stoi(level_s);
    //增加".index"前缀
    indexPath.append(".index");
    //创建索引文件
    ofstream fout_index;
    //追加方式写入
    fout_index.open(indexPath,ios::binary|ios::app);
    //读取首时间、尾时间，首温度、尾温度，首删除、尾删除
    time_t timeStamp_start,timeStamp_end;
    int temp_start,temp_end;
    bool deleted_start,deleted_end;
    ifstream fin_file;
    fin_file.open(filePath,ios::binary);
    //根据级号来推断文件所包含的数据
    int pos0=0;//首timeStamp偏移量
    int pos1=sizeof(time_t)*(10^level_i);//首temp偏移量
    int pos2=(sizeof(time_t)*(10^level_i))+(sizeof(int)*(10^level_i));//首deleted偏移量
    //首时间戳
    fin_file.read((char*)timeStamp_start,sizeof(time_t));
    //尾时间戳
    fin_file.seekg((sizeof(time_t))*((10^level_i)-1),ios::beg);
    fin_file.read((char*)timeStamp_end,sizeof(time_t));
    //首温度
    fin_file.seekg(pos1,ios::beg);
    fin_file.read((char*)temp_start,sizeof(int));
    //尾温度
    fin_file.seekg(pos1+(sizeof(int))*((10^level_i)-1),ios::beg);
    fin_file.read((char*)temp_end,sizeof(int));
    //首删除
    fin_file.seekg(pos2,ios::beg);
    fin_file.read((char*)deleted_start,sizeof(bool));
    //尾删除
    fin_file.seekg(pos2+(sizeof(bool))*((10^level_i)-1),ios::beg);
    fin_file.read((char*)deleted_end,sizeof(bool));
    fin_file.close();
    //开始写索引，索引结构参见"一些图示"目录下的word文档
    //文件名
    fout_index.write(fileName.c_str(),sizeof(fileName));
    //时间戳偏移量
    fout_index.write((char*)pos0,sizeof(int));
    //首时间戳
    fout_index.write((char*)timeStamp_start,sizeof(time_t));
    //尾时间戳
    fout_index.write((char*)timeStamp_end,sizeof(time_t));
    //温度偏移量
    fout_index.write((char*)pos1,sizeof(int));
    //首温度
    fout_index.write((char*)temp_start,sizeof(int));
    //尾温度
    fout_index.write((char*)temp_end,sizeof(int));
    //删除偏移量
    fout_index.write((char*)pos2,sizeof(int));
    //首删除
    fout_index.write((char*)deleted_start,sizeof(bool));
    //尾删除
    fout_index.write((char*)deleted_end,sizeof(bool));
    fout_index.close();
    return true;
}
