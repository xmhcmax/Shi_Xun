#include"data_in_disk.h"
using namespace std;
//这里是进行一级文件的创建，还有一级索引，一级文件的内容就是memery里的内容

/*这些不用了
    //存放在文件中的数据
    // struct metaInfo
    // {
    //     //数据起始位置
    //     int dataStart;
    //     //数据长度
    //     int dataLen;
    //     //索引区起始索引
    //     int indexStart;
    //     //索引区长度
    //     int indexLen;
    // };

    //元素定位
    // struct position
    // {
    //     // 起始索引
    //     int Start;
    //     // 长度
    //     int Len;
    //     // Key是否已经被删除
    //     bool deleted;
    // };

    //文件的存储结构
    // struct fileTable
    // {
    //     //文件句柄
    //     FILE* f;
    //     //数据
    //     metaInfo data;
    //     //索引
    //     position index[];
    // };
*/

//把memery中的10条数据转换为第一级文件,顺便产生索引
bool makeFile(dataList datalist[],string fileName,string filePath){
    //拼凑完整文件路径
    string path;
    string insert="\\";
    path.append(filePath);
    path.append(insert);
    path.append(fileName);
    //创建文件，存入文件
    ofstream fout;
    fout.open(path,ios::binary|ios::app);
    //判断文件是否打开了
    if(!fout.is_open()){
        cout<<"Error!No file is opened!"<<endl;
        return false;
    }
    //转移mem内容到数组方便写入
    time_t timestamp[10];
    int temp[10];
    bool deleted[10];
    //第一层循环遍历每一类元素
    for(int i=0;i<3;i++){
        //第二层循环遍历每一类元素的每一个(共10个)
        for(int j;j<10;j++){
            timestamp[j]=datalist->value->data->timestamp;
            temp[j]=datalist->value->data->temp;
            deleted[j]=datalist->value->data->deleted;
        }
    }
    //写入文件
    fout.write((char*)timestamp,sizeof(time_t)*10);
    fout.write((char*)temp,sizeof(int)*10);
    fout.write((char*)deleted,sizeof(bool)*10);
    fout.close();

    
    //创建一级索引文件
    makeIndex(path);
    // string fileName_new;
    // //拼接函数append
    // fileName_new.append(fileName);
    // //去除.db,以便加入后缀.index
    // fileName_new.resize(fileName_new.size()- 3);
    // fileName_new.append(".index");
    // ofstream iout;
    // iout.open(fileName_new,ios::binary|ios::app);
    // if(!iout.is_open())
    //     return false;
    // int pos0=0;
    // int pos1=(sizeof(time_t)*10);
    // int pos2=(sizeof(time_t)*10)+(sizeof(int)*10);
    // iout.write((char*)&pos0,sizeof(int));
    // iout.write((char*)&pos1,sizeof(int));
    // iout.write((char*)&pos2,sizeof(int));
    // fout.close();
    return true;
}