#include"data_in_disk_forN.h"
using namespace std;

//将行列转换完成的数据，转存到一级文件中
bool makeLevelOneFile(transit_data_chain* chainToWrite){
    string filePath=ROOTFOLDERPATH;
    string fileName=makeFileName(filePath.append("\\1"));
    filePath.append("\\");
    //得到完整文件路径
    filePath.append(fileName);
    ofstream fout;
    //以二进制、追加方式写入文件
    fout.open(filePath,ios::binary|ios::app);
    if(!fout.is_open()){
        cout<<"No file!!"<<endl;
        return false;
    }
    
    //开始转移数据
    string sequence=chainToWrite->sequence;
    
    transit_data_chain* pointer=chainToWrite->next;
    //循环每个有数据的节点，包括时间戳节点
    //这里的level应该是1
    int level=getFileLevel(filePath);
    for(int i=0;i<=sequence.size();i++){
        
        if(i==0){
            //写时间戳进去
            for(int j=0;j<(10^level);j++){
                fout.write((char*)pointer->data->timeData[j],sizeof(time_t));
            }
            //写完结点之后这个节点就可以delete了
            pointer=pointer->next;
            delete(chainToWrite->next);
            chainToWrite->next=pointer;
        }
        else{
            //不是第一个数据，就要根据序列写入
            //拿到（时间戳之后的）第i个数据的序列，判断类型
            int sequenceNum=stoi(departSequence(sequence,i));
            switch (sequenceNum)
            {
            case 1:
                //写入int数据
                for(int j=0;j<(10^level);j++){
                writeInt(fout,pointer->data->intData[j]);
                fout.write((char*)&pointer->data->intData[j],sizeof(int));
                }
                break;
            case 2:
                //写入char数据
                for(int j=0;j<(10^level);j++){
                writeChar(fout,pointer->data->charData[j]);
                //fout.write((char*)&pointer->data->charData[j],sizeof(char));
                }
                break;
            case 3:
                //写入bool数据
                for(int j=0;j<(10^level);j++){
                writeBool(fout,pointer->data->boolData[j]);
                //fout.write((char*)&pointer->data->boolData[j],sizeof(bool));
                }
                break;
            case 4:
                //写入float数据
                for(int j=0;j<(10^level);j++){
                writeFloat(fout,pointer->data->floatData[j]);
                //fout.write((char*)&pointer->data->floatData[j],sizeof(float));
                }
                break;
            case 5:
                //写入double数据
                for(int j=0;j<(10^level);j++){
                writeDouble(fout,pointer->data->doubleData[j]);
                //fout.write((char*)&pointer->data->doubleData[j],sizeof(double));
                }
                break;
            }
            //每次写完一个结点之后这个节点就可以delete了
            pointer=pointer->next;
            delete(chainToWrite->next);
            chainToWrite->next=pointer;
        }
        //都写完了，现在删除chainToWrite
        delete(chainToWrite);
    }
    fout.close();
    //文件写入完了，现在来创建index
    makeIndex(filePath,sequence);
}