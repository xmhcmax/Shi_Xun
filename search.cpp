#undef UNICODE

#include"D:\apps\VS code\Programs\C++ program\shixun\data_in_disk_forN\data_in_disk_forN.h"
#include<iostream>
#include<fstream>
#include<time.h>
#include<io.h>
#include<direct.h>
#include<windows.h>
using namespace std;

//string ROOTFOLDERPATH="D:\\dataFile";
//这里是查找功能的初步实现
//查找的思路是：因为查找功能是按照时间戳来进行的，即用户输入时间戳范围，我们输出这个时间戳范围内的数据
//当然这个用户还要输入是否是查询一整行的信息，所以可能需要做一个重载或者直接写到一个函数里
//原要求如下：
/*
    // a. 读模式下能够指定传感器时间范围进行检索；查询指定传感器两个时间戳之间的数据？
    // b. 读模式下能够指定时间间隔进行检索；是云端2次检索数据的时间间隔吗？
    // c. 读模式下能够检索帧数据中的某一个字段，并组合 a，b；
    // d. 读模式下能够检索整帧数据，并组合 a，b；
    // e. 读模式输入为最终的数据文件或目录结构，输出为满足检索条件的数据。
*/
//我的查找逻辑：
    //1.先定位到最高级别的非满目录，并且从文件号最低的文件开始。这样能保证从最旧的数据找起
    //2.先找的是索引，不是文件，找到索引拿出首时间戳和尾时间戳和用户的范围对比，会出现3种情况
    //      2.1.第一种情况是范围下限≥该数据文件首时间戳＜尾时间戳，范围上限该数据≤文件尾时间戳：就取出范围需要的数据
    //      2.2.第二种情况是范围下限≥该数据文件首时间戳＜尾时间戳，范围上限＞该数据文件尾时间戳：先把这个文件范围内的全拿了，
    //          然后往后进下一个数据文件索引，对比范围上限和尾时间戳
    //              2.2.1.若范围上限≤尾时间戳，则取出该文件从头到上限时间戳的数据，加上上一个文件的数据
    //              2.2.2.若范围上限大于尾时间戳，则取出整个文件的数据，然后重复2.2.1和2.2.2
    //      2.3.第三种情况是范围下限＞该数据文件首时间戳同时＞尾时间戳，则跳过该文件，前往下一个数据文件索引，重复2.1、2.2和2.3
    //这些情况，除了第一种，其他的是除了跨文件，还可能跨目录，所以要有一个类似缺页的思想，在数据目录名到达该级别最高时，
    //下一个文件进行路径的迭代保持

//更换到上一个目录的函数,返回上一个目录的路径（带"\\"）--暂时没有用到
string changeToLastFolder(string lastIndexPath){
    string newFolderPath=lastIndexPath;
    string level_s=newFolderPath;
    newFolderPath.resize(newFolderPath.size()-11);
    level_s.resize(level_s.size()-10);
    int level_i=stoi(level_s.erase(0,level_s.size()-1));
    newFolderPath.append(to_string(--level_i));
    newFolderPath.append("\\");
    return newFolderPath;
}

//更换到下一个索引的函数，如果没有下一个可以查找的索引，那么就返回"";
string getNextIndexPath(string oldIndexPath){
    string newIndexPath=oldIndexPath;
    string level_s,number_s;
    int level_i,number_i;
    //首先检查oldIndexPath所在的目录是不是最低级的目录,如果是则不能再换新目录
    //拿到number
    number_s=newIndexPath;
    number_s.resize(number_s.size()-6);
    number_s.erase(0,number_s.size()-1);
    number_i=stoi(number_s);
    //拿到level
    level_s=newIndexPath;
    level_s.resize(level_s.size()-8);
    level_s.erase(level_s.size()-1);
    level_i=stoi(level_s);
    //查看级号
    if(level_i==1){
        //说明是最低级目录
        return "";
    }
    //不是最低级目录，那么再查看上一个索引文件是不是本级的最后一个文件
    if(number_i==9){
        //说明是最后一个文件，需要转移到更低级目录的第一个索引文件
        newIndexPath=ROOTFOLDERPATH;
        newIndexPath.append("\\");
        newIndexPath.append(to_string(--level_i));
        newIndexPath.append("\\");
        newIndexPath.append(level_s);
        newIndexPath.append(".0.index");
        return newIndexPath;
    }
    //不是最低级的目录，也不是本级最后一个文件，那么返回本级目录的下一个文件
    //先检查这一级还有没有下一个索引
    newIndexPath.resize(newIndexPath.size()-7);
    newIndexPath.append(to_string(++number_i));
    newIndexPath.append(".index");
    ifstream check;
    check.open(newIndexPath,ios::binary);
    if(check.is_open()){
        //打开了说明有这个文件
        check.close();
        return newIndexPath;
    }
    //没有这个文件，那么还是要前往低级目录的第一个
    newIndexPath=ROOTFOLDERPATH;
    newIndexPath.append("\\");
    newIndexPath.append(to_string(--level_i));
    newIndexPath.append("\\");
    newIndexPath.append(level_s);
    newIndexPath.append(".0.index");
    return newIndexPath;
}

//更换到下一个索引的函数,返回下一个索引的路径,用于在索引时间戳对比中转移当前索引文件--太拉了，不要了，用上面那个
// string getNextFilePath(string lastIndexPath){
//     string indexPath;
//     string indexNumber;
//     string lastIndexPath_save=lastIndexPath;
//     int number;
//     //去除“.index”
//     lastIndexPath.resize(lastIndexPath.size()-6);
//     indexPath=lastIndexPath;
//     //新路径去除文件号
//     indexPath.resize(indexPath.size()-1);
//     //旧路径保留上一个文件号
//     indexNumber=lastIndexPath.erase(0,lastIndexPath.size()-1);
//     number=stoi(indexNumber);
//     if(number==9){
//         //说明已经到索引的最后一个了，该换到上一级目录了，也就是级数-1级
//         string newFolderPath=changeToLastFolder(lastIndexPath_save);
//         if(newFolderPath==lastIndexPath_save){
//             //没有进行索引文件切换，说明这一级已经是最后一级了
//         }
//         //得到上一个的级号,lastIndexPaht_save没有改变
//         string indexLevel=lastIndexPath_save.substr(0,lastIndexPath_save.size()-8);
//         int level_s=stoi(indexLevel.erase(0,indexLevel.size()-1));
//         number=0;
//         indexLevel=to_string(--level_s);
//         indexNumber=to_string(number);
//         //路径去除“级号.”
//         indexPath.resize(indexPath.size()-2);
//         //拼接新的索引路径
//         indexPath.append(indexLevel);
//         indexPath.append(".");
//         indexPath.append(indexNumber);
//         indexPath.append(".index");
//         return indexPath;
//     }
//     else{
//         //上一个索引号不是9就不用直接换目录，但是要查看该级目录还有没有下一个索引
//         //计算下一个索引文件的索引号
//         indexNumber=to_string(++number);
//         //拼接完整
//         indexPath.append(indexNumber);
//         indexPath.append(".index");
//         ifstream check;
//         check.open(indexNumber);
//         //存在索引，check.is_open()返回true，不存在返回false
//         if(check.is_open()){
//             //存在则return路径
//             check.close();
//             return indexPath;
//         }
//         else{
//             check.close();
//             //不存在则跳转到上一级目录
//             string newFolderPath=changeToLastFolder(lastIndexPath_save);
//             //得到旧的级号
//             string indexLevel=lastIndexPath_save.substr(0,lastIndexPath_save.size()-8);
//             int level_s=stoi(indexLevel.erase(0,indexLevel.size()-1));
//             number=0;
//             indexLevel=to_string(--level_s);
//             indexNumber=to_string(number);
//             //路径去除“级号.”
//             indexPath.resize(indexPath.size()-2);
//             //拼接新的索引路径
//             indexPath.append(indexLevel);
//             indexPath.append(".");
//             indexPath.append(indexNumber);
//             indexPath.append(".index");
//             return indexPath;
//         }
//     }
// }

//为了满足时间戳对比的＞、＜，≥，≤对比要求，所以有了以下4个函数
//对比首时间戳1,true代表timeStamp_start大,false代表timeStamp_start≤time
bool is_timeStamp_start_bigger(time_t time,string indexPath){
    time_t timeStamp_start;
    ifstream fin_index;
    fin_index.open(indexPath,ios::binary);
    //偏移值，sequence大小时sizeof(string),文件名大小是sizeof(string)
    int off=sizeof(string)*2;
    fin_index.seekg(off,ios::beg);
    fin_index.read((char*)&timeStamp_start,sizeof(int));
    fin_index.close();
    if(timeStamp_start>time){
        return true;
    }
    else
        return false;
}

//对比首时间戳2,true代表timeStamp_start小,false代表timeStamp_start≥time
bool is_timeStamp_start_smaller(time_t time,string indexPath){
    time_t timeStamp_start;
    ifstream fin_index;
    fin_index.open(indexPath,ios::binary);
    //偏移值，sequence大小时sizeof(string),文件名大小是sizeof(string)
    int off=sizeof(string)*2;
    fin_index.seekg(off,ios::beg);
    fin_index.read((char*)&timeStamp_start,sizeof(int));
    fin_index.close();
    if(timeStamp_start<time){
        return true;
    }
    else
        return false;
}

//对比尾时间戳1，true代表timeStamp_end大，false代表timeStamp_end≤time
bool is_timeStamp_end_bigger(time_t time,string indexPath){
    time_t timeStamp_end;
    ifstream fin_index;
    fin_index.open(indexPath,ios::binary);
    //偏移值，sequence大小时sizeof(string),文件名大小是sizeof(string)，timeStamp_start大小是sizeof(time_t)
    int off=(sizeof(string)*2)+sizeof(time_t);
    fin_index.seekg(off,ios::beg);
    fin_index.read((char*)&timeStamp_end,sizeof(int));
    fin_index.close();
    if(timeStamp_end>time){
        return true;
    }
    else
        return false;
}

//对比尾时间戳2，true代表timeStamp_end小，false代表timeStamp_end≥time
bool is_timeStamp_end_smaller(time_t time,string indexPath){
    time_t timeStamp_end;
    ifstream fin_index;
    fin_index.open(indexPath,ios::binary);
    //偏移值，sequence大小时sizeof(string),文件名大小是sizeof(string)，timeStamp_start大小是sizeof(time_t)
    int off=(sizeof(string)*2)+sizeof(time_t);
    fin_index.seekg(off,ios::beg);
    fin_index.read((char*)&timeStamp_end,sizeof(int));
    fin_index.close();
    if(timeStamp_end<time){
        return true;
    }
    else
        return false;
}

//定位到最大目录的最小文件的函数,没有可供查找的文件返回""
string getLowestIndex(){
    string indexPath=ROOTFOLDERPATH;
    int fileNum=0;
    for(int i=3;3>0;i--){
        string path=ROOTFOLDERPATH;
        path.append("\\");
        path.append(to_string(i));
        path.append("\\");
        intptr_t handle;
        _finddata_t fileInfo;
        handle=_findfirst(path.c_str(),&fileInfo);
        _findnext(handle,&fileInfo);
        while(!_findnext(handle,&fileInfo)){
            //有文件则fileNum++
            fileNum++;
        }
        if(fileNum!=0){
            //说明有文件，则进入该目录的最小文件中
            indexPath=path;
            indexPath.append("\\");
            indexPath.append(to_string(i));
            indexPath.append(".0.index");
            return indexPath;
        }
        else{
            //没有文件，关闭文件夹句柄,进入下一轮循环，查找低一级文件
            _findclose(handle);
            if(i==1){
                //在最低级目录下也没文件，查找失败
                return "";
            }
        }
    }
    

}

//获取包含所需数据的文件名,timeHigh是时间上限，timeLow是时间下限，表示一个范围
bool locateFile(time_t timeLow,time_t timeHigh){
    //生成一个record文件记录所经过的fileName
    string fileName;
    char fileNameChar[10];
    ofstream fout;
    fout.open("D\\dataFile\\record.txt",ios::binary|ios::app);
    fout.close();
    //定位到最大级的目录的最小号索引
    string indexPath=getLowestIndex();
    time_t timeStamp_start,timeStamp_end;
    int timeStamp_start_off=sizeof(string)*2;
    int timeStamp_end_off=timeStamp_start_off+sizeof(time_t);
    if(indexPath==""){
        //说明没有文件可供查找
    }
    //定位到查找下限所在的文件
    while(1){
        //timeLow<timeStamp_start,查询范围出错了
        if(is_timeStamp_start_bigger(timeLow,indexPath)&!(!(is_timeStamp_start_bigger(timeLow,indexPath))&!(is_timeStamp_end_smaller(timeLow,indexPath)))){
            return false;
        }
        //timeLow>timeStamp_end
        else if(is_timeStamp_end_smaller(timeLow,indexPath)&!(!(is_timeStamp_end_bigger(timeLow,indexPath))&!(is_timeStamp_end_smaller(timeLow,indexPath)))){
            //更换到下一个index文件继续循环
            indexPath=getNextIndexPath(indexPath);
            if(indexPath==""){
                //说明没有下一个index文件了，没有想要的数据，查找失败
                return false;
            }
        }
        //timeLow>=timeStamp_start且timeLow<=timeStart_end
        else if(!(is_timeStamp_start_bigger(timeLow,indexPath))&!(is_timeStamp_end_smaller(timeLow,indexPath))){
            //就是这个文件，记录下它的名字到record文件
            ifstream fin;
            fin.open(indexPath,ios::binary);
            fin.read((char*)fileNameChar,sizeof(fileNameChar));
            fileName=fileNameChar;
            fout.write(fileName.c_str(),sizeof(string));
            fin.close();
            //跳出循环，进行时间上限的匹配
            break;
        }
    }
    
    //定位时间下限在的文件
    //此时的indexPath是timeLow所在的索引路径
    //先查看时间上限是不是在目前的indexPath
    if(!is_timeStamp_end_smaller(timeHigh,indexPath)){
            //时间上限就在当前indexPath，并且此时该文件名已经被存入record，所以直接return
        return true;
    }
    //此时就确定时间上限不在当前索引，前往下一个索引
    indexPath=getNextIndexPath(indexPath);
    while(1){
        //timeStamp_end>timeHigh
        if(is_timeStamp_end_bigger(timeHigh,indexPath)){
            //最后的记录在当前文件中，记录下当前文件,结束
            ifstream fin;
            fin.open(indexPath,ios::binary);
            fin.read((char*)fileNameChar,sizeof(fileNameChar));
            fileName=fileNameChar;
            fout.write(fileName.c_str(),sizeof(string));
            fin.close();
            return true;
        }
        //timeStamp_end<=timeHigh
        else{
            //还没找完，写入该文件名，
            ifstream fin;
            fin.open(indexPath,ios::binary);
            fin.read((char*)fileNameChar,sizeof(fileNameChar));
            fileName=fileNameChar;
            fout.write(fileName.c_str(),sizeof(string));
            fin.close();
            //然后继续前往下一个index
            indexPath=getNextIndexPath(indexPath);
            if(indexPath==""){
                //说明没有下一个index文件了，时间范围有误，查找失败
                return false;
            }
        }
    }
}

//计算出定位到第一个对应的位置的数据前面需要多少偏移
int* getOffsite(string filePath,int dataPos,string sequence,int* off){
    int level_i=getFileLevel(filePath);
    off[0]={(int)(sizeof(time_t)*10^level_i)};
    off[1]={(int)(sizeof(time_t)*10^level_i)};
    off[2]={0};
    int sequenceNum_i;
    int count=1;
    string sequenceNum_s;
    //看看前面都有哪些东西
    for(count;count<=dataPos;count++){
        sequenceNum_i=stoi(sequenceNum_s=departSequence(sequence,count));
        switch (sequenceNum_i)
        {
        case 1:
            //int类型数据
            if(count==dataPos){
                off[1]+=sizeof(int)*(10^level_i);
                off[2]=sizeof(int);
                break;
            }
            off[0]+=sizeof(int)*(10^level_i);
            off[1]=off[0];
            break;
        case 2:
            //char类型数据
            if(count==dataPos){
                off[1]+=sizeof(char)*(10^level_i);
                off[2]=sizeof(char);
                break;
            }
            off[0]+=sizeof(char)*(10^level_i);
            off[1]=off[0];
            break;
        case 3:
            //bool类型数据
            if(count==dataPos){
                off[1]+=sizeof(bool)*(10^level_i);
                off[2]=sizeof(bool);
                break;
            }
            off[0]+=sizeof(bool)*(10^level_i);
            off[1]=off[0];
            break;
        case 4:
            //float类型数据
            if(count==dataPos){
                off[1]+=sizeof(float)*(10^level_i);
                off[2]=sizeof(float);
                break;
            }
            off[0]+=sizeof(float)*(10^level_i);
            off[1]=off[0];
            break;
        case 5:
            //double类型数据
            if(count==dataPos){
                off[1]+=sizeof(double)*(10^level_i);
                off[2]=sizeof(double);
                break;
            }
            off[0]+=sizeof(double)*(10^level_i);
            off[1]=off[0];
            break;
        }
    }
    return off;
}

//输入时间范围和需要第种数据，输出满足需求的数据//int char bool int
bool searchCertainData(time_t timeLow,time_t timeHigh,int dataPos){
    string recordPath="D:\\dataFile\\record.txt";
    string fileName;
    string filePath;
    string indexPath;
    time_t timeStamp;

    int intData;
    char charData;
    bool boolData;
    float floatData;
    double doubleData;

    int sequenceNum_i;
    int level_i;
    int number_i;
    char fileNameChar[10];
    //将所有满足查询条件的文件名转入record文件
    bool is_valid=locateFile(timeLow,timeHigh);
    if(!is_valid){
        cout<<"The search range is not valid!!"<<endl;
        remove(recordPath.c_str());
        return false;
    }
    //查询范围合法
    ifstream fin;
    fin.open(recordPath,ios::binary);
    fin.read((char*)fileNameChar,sizeof(fileNameChar));
    fin.close();
    fileName=fileNameChar;
    string fileName_save=fileName;
    level_i=stoi(fileName.substr(0,1));
    filePath=ROOTFOLDERPATH;
    filePath.append("\\");
    filePath.append(to_string(level_i));
    filePath.append(fileName_save);
    //打个小差，把sequence取出来
    indexPath.assign(filePath).append(".index");
    string sequence;
    char sequenceChar[20];
    ifstream fin_index;
    fin_index.open(indexPath,ios::binary);
    fin_index.read((char*)sequenceChar,sizeof(sequenceChar));
    fin_index.close();
    sequence=sequenceChar;
    //小差开完了，继续
    filePath.append(".db");
    //先在第一个文件中寻找匹配的时间戳
    ifstream fin_file;
    fin_file.open(filePath,ios::binary);
    //不读到对的不退缩！！
    level_i=getFileLevel(filePath);
    int pos_low=0;
    for(int i=0;i<10^level_i;i++){
        fin_file.seekg(pos_low,ios::beg);
        fin_file.read((char*)timeStamp,sizeof(time_t));
        if(timeStamp!=timeLow){
            //不对劲，更新pos_low，继续走
            pos_low+=sizeof(time_t);
        }
        //对劲了！！
        //此时的pos_low就是时间下限的时间戳偏移
    }
    fin_file.close();
    int posNum_low=(pos_low/sizeof(time_t));
    //输出需要的对应的数据
    
    int offsite1[3];
    getOffsite(filePath,dataPos,sequence,offsite1);
    int startPos1=offsite1[0]+offsite1[2]*posNum_low;
    int endPos1=offsite1[1];
    ifstream fin1;
    fin1.open(filePath,ios::binary);
    for(startPos1;startPos1<endPos1;startPos1+=offsite1[2]){
        fin1.seekg(startPos1,ios::beg);
        sequenceNum_i=stoi(departSequence(sequence,dataPos));
        switch (sequenceNum_i)
        {
        case 1:
            //读取int类型
            fin.read((char*)&intData,offsite1[2]);
            cout<<intData<<endl;
            break;
        case 2:
            //读取char类型
            fin.read((char*)&charData,offsite1[2]);
            cout<<intData<<endl;
            break;
        case 3:
            //读取bool类型
            fin.read((char*)&boolData,offsite1[2]);
            cout<<intData<<endl;
            break;
        case 4:
            //读取float类型
            fin.read((char*)&floatData,offsite1[2]);
            cout<<intData<<endl;
            break;
        case 5:
            //读取double类型
            fin.read((char*)&doubleData,offsite1[2]);
            cout<<intData<<endl;
            break;
        }
    }
    fin1.close();
    //这个for完了之后pos_low就是时间下限的时间戳偏移了

    //咱们再把最后一个文件的名字读出来
    string lastFileName;
    //只能靠这种卑鄙的办法初始化fileNChar了，不然一直卡在最后一个文件的名字
    fileNameChar[0]={0};
    ifstream fin_record2;
    fin_record2.open(recordPath,ios::binary);
    fin_record2.seekg(-sizeof(string),ios::end);
    fin_record2.read((char*)fileNameChar,sizeof(fileNameChar));
    fin_record2.close();
    lastFileName=fileNameChar;
    lastFileName.append(".db");
    //根据用户的需求输出数据了
    //接下来往中间的文件定位
    int count=0;
    int off=sizeof(string);
    int pos=0;
    string middleFileName=fileName;
    ifstream fin_record;
    fin_record.open(recordPath,ios::binary);
    while(1){
        //只能靠这种卑鄙的办法初始化fileNChar了，不然一直卡在最后一个文件的名字，循环就出不来了
        fileNameChar[0]={0};
        fin_record.seekg(off,ios::beg);
        fin_record.read((char*)fileNameChar,sizeof(fileNameChar));
        fileName=fileNameChar;
        filePath=fileName;
        filePath.append(".db");
        if(fileName==lastFileName){
            //说明这个文件已经是最后一个文件了，中间文件没有或者中间文件已经输出完毕了，就可以跳出了
            break;
        }
        else{
            //不是最后一个文件,把需要的的数据全部输出出去
            //把对应的数据从头到尾输出
            int offsite2[3];
            getOffsite(filePath,dataPos,sequence,offsite2);
            int startPos2=offsite2[0];
            int endPos2=offsite2[1];
            ifstream fin2;
            fin2.open(filePath,ios::binary);
            for(startPos2;startPos2<endPos2;startPos2+=offsite2[2]){
                fin2.seekg(startPos2,ios::beg);
                sequenceNum_i=stoi(departSequence(sequence,dataPos));
                switch (sequenceNum_i)
                {
                case 1:
                    //读取int类型
                    fin.read((char*)&intData,offsite2[2]);
                    cout<<intData<<endl;
                    break;
                case 2:
                    //读取char类型
                    fin.read((char*)&charData,offsite2[2]);
                    cout<<intData<<endl;
                    break;
                case 3:
                    //读取bool类型
                    fin.read((char*)&boolData,offsite2[2]);
                    cout<<intData<<endl;
                    break;
                case 4:
                    //读取float类型
                    fin.read((char*)&floatData,offsite2[2]);
                    cout<<intData<<endl;
                    break;
                case 5:
                    //读取double类型
                    fin.read((char*)&doubleData,offsite2[2]);
                    cout<<intData<<endl;
                    break;
                }
            }
            fin2.close();
            //输出完后更新off，然后就没有这个中间文件的事情了，进行下一轮循环
            off+=sizeof(string);
        }
    }
    
    //while结束后，off就是最后一个文件的off，fileName是最后一个文件的name
    //输出最后一个文件的数据
    fileName_save=fileName;
    level_i=stoi(fileName.substr(0,1));
    filePath=ROOTFOLDERPATH;
    filePath.append("\\");
    filePath.append(to_string(level_i));
    filePath.append(fileName_save);
    filePath.append(".db");
    //找到时间上限对应的时间戳
    ifstream fin_file2;
    fin_file2.open(fileName,ios::binary);
    int pos_high=0;
    //最多遍历全部时间戳一遍
    for(int i=0;i<10^level_i;i++){
        fin_file2.seekg(pos_high,ios::beg);
        fin_file2.read((char*)&timeStamp,sizeof(time_t));
        if(timeStamp!=timeHigh){
            //说明这个不是需要的最后一个时间戳
            //更新pos_high
            pos_high+=sizeof(time_t);
        }
        //对劲，不进if就说明pos_high是时间上限的时间戳偏移
    }
    fin_file2.close();
    int posNum_high=(pos_high/sizeof(time_t));
    //输出数据
    int offsite3[3];
    getOffsite(filePath,dataPos,sequence,offsite3);
    int startPos3=offsite3[0];
    int endPos3=offsite3[0]+offsite3[2]*(posNum_high+1);
    ifstream fin3;
    fin3.open(filePath,ios::binary);
    for(startPos3;startPos3<endPos3;startPos3+=offsite3[2]){
        fin3.seekg(startPos3,ios::beg);
        sequenceNum_i=stoi(departSequence(sequence,dataPos));
        switch (sequenceNum_i)
        {
        case 1:
            //读取int类型
            fin.read((char*)&intData,offsite3[2]);
            cout<<intData<<endl;
            break;
        case 2:
            //读取char类型
            fin.read((char*)&charData,offsite3[2]);
            cout<<intData<<endl;
            break;
        case 3:
            //读取bool类型
            fin.read((char*)&boolData,offsite3[2]);
            cout<<intData<<endl;
            break;
        case 4:
            //读取float类型
            fin.read((char*)&floatData,offsite3[2]);
            cout<<intData<<endl;
            break;
        case 5:
            //读取double类型
            fin.read((char*)&doubleData,offsite3[2]);
            cout<<intData<<endl;
            break;
        }
    }
    fin3.close();
    remove(recordPath.c_str());
    return true;
}

//用来服务下一个函数的，给一个字符串和需要第几位，返回该位
string departString(string str,int number){
    str.resize(str.size()-(str.size()-number));
    str.erase(0,str.size()-1);
    return str;
}

//用户调用的函数，输入时间范围和需要的第几种数据
bool searchData(time_t timeLow,time_t timeHigh,string dataKind){
    int kind[dataKind.size()];
    for(int i=0;i<dataKind.size();i++){
        kind[i]=stoi(departString(dataKind,i+1));
    }
    
    for(int j=0;j<dataKind.size();j++){
        cout<<"Here comes the "<<j+1<<" data"<<endl;
        if(!searchCertainData(timeLow,timeHigh,kind[j])){
            return false;
        }
            //cout<<"The time range is not valid!!";
    }
    return true;
}



int main(){
    cout<<"Hello,welcome to the DataBase."<<endl;
    cout<<"You can search your data here."<<endl;
    time_t timeLow;
    time_t timeHigh;
    string dataKind;

    cout<<"As your data struct,you can input the data-serial-number in your sequence for certain data"<<endl;
    cout<<"please input the lowest time limit you want to search:";
    cin>>timeLow;
    cout<<""<<endl;
    cout<<"please input the highest time limit you want to search:";
    cin>>timeHigh;
    cout<<""<<endl;
    cout<<"please input the data-serial-number of the data you want to search:";
    cin>>dataKind;
    cout<<""<<endl;
    searchData(timeLow,timeHigh,dataKind);
    return 0;

}