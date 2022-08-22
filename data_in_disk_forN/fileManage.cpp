#include"data_in_disk_forN.h"
using namespace std;

static string ROOTFOLDERPATH = "D:\\dataFile";

//向外输出ROOTFOLDERPATH
string getRootFolderPath(){
    return ROOTFOLDERPATH;
}

//检查该级目录是不是满了的函数,这里的filePath是级目录，不带"\\"，不是数据文件根目录
bool is_fileFull(string filePath){
    //首先读取已经有了的该级文件
    intptr_t Handle;
    _finddata_t fileInfo;
    string path=filePath;
    string p;
    Handle=_findfirst(p.assign(path).append("\\*").c_str(),&fileInfo);
    //printf("%s\n", fileInfo.name);
    //cout<<fileInfo.name<<endl;
    _findnext(Handle, &fileInfo);
    //为什么前两次读取不要呢？因为。。。我无法解释为什么会输出两个点
    string Vname="";//暂时取出的name放入Vname
    string name="";//确定是数据文件后放入name变量
    while (_findnext(Handle, &fileInfo) == 0){
			Vname=fileInfo.name;
            //去除级号和文件号，判断是不是index文件
            if(Vname.erase(0,3)!=".index"){
                //不是index文件
                //因为Vname变量已经改变了，所以重新读取一下name
                name=fileInfo.name;
                //去除".db"后缀
                name.resize(name.size()-3);
                //去除级号（前缀）
                name.erase(0,2);
                //**现在的name就只代表文件号**//
                //cout<<name<<endl;
            }
    }
    //while运行完毕之后，name就是最后一个文件的文件号，对比文件号和9，就可以知道现在该级文件有没有10个了
    //如果没有文件，就不会经历while，那么name=""，依然不为"9"，所以无影响
    if(name!="9")
        return false;
    else 
        return true;
}

//得到数据文件的level,int类型,这里的filePath可以是当前文件的级目录路径(不带"\\")，也可以是随便一个数据文件的路径
int getFileLevel(string filePath){
    string fileLevel_s=filePath;
    int fileLevel_i;
    filePath.erase(0,filePath.size()-3);
    if(filePath==".db"){
        //说明是数据文件
        fileLevel_s=filePath;
        fileLevel_s.resize(fileLevel_s.size()-5);
        fileLevel_s.erase(0,fileLevel_s.size()-1);
    }
    else{
        //说明是级目录文件
        fileLevel_s=filePath;
        fileLevel_s.erase(0,fileLevel_s.size()-1);
    }
    //fileLevel_s=filePath.substr(0,filePath.size()-5);
    //fileLevel_s.erase(0,fileLevel_s.size()-1);
    fileLevel_i=stoi(fileLevel_s);
    return fileLevel_i;
}

//得到数据文件的number,int类型
int getFileNumber(string filePath){
    string fileNumber_s;
    int fileNumber_i;
    fileNumber_s=filePath.substr(0,filePath.size()-3);
    fileNumber_s.erase(0,fileNumber_s.size()-1);
    fileNumber_i=stoi(fileNumber_s);
    return fileNumber_i;
}

//生成fileName的函数,这里的filePath是级目录，不是数据文件根目录
string makeFileName(string filePath){
    //使用这个函数之前最好使用一下is_fileFull()函数来确定是不是已经到10个数据文件了
    //首先读取已有的目录下文件名字
    intptr_t Handle1;
    intptr_t Handle2;
    _finddata_t fileInfo1;
    _finddata_t fileInfo2;
    string path=filePath;
    string p1;
    string p2;
    //.assign()是用来赋值的，就是把path的值赋给了P//.c_str()是用来将string转换成const char* 类型的
    Handle1=_findfirst(p1.assign(path).append("\\*").c_str(),&fileInfo1);
    Handle1=_findfirst(p2.assign(path).append("\\*").c_str(),&fileInfo2);
    //printf("%s\n", fileInfo.name);
    //cout<<fileInfo.name<<endl;
    _findnext(Handle1, &fileInfo1);
    _findnext(Handle2, &fileInfo2);
    //为什么前两次读取的文件名不要呢？因为。。。我无法解释为什么会是"."
    string name;
    string nameLevel;
    string nameNumber;
    string nameEnd;
    //判断目录下有没有文件
    if(_findnext(Handle2, &fileInfo2) != 0){
        //在没有文件的情况下,需要filePath名字的的级号了，生成的fileName肯定是"级号.0.db"
        nameNumber=".0";
        nameEnd=".db";
        string path1=filePath;
        //path1是去除了文件夹级号的剩余路径
        path1.resize(filePath.size()-1);
        name=filePath.erase(0,path1.size());
        //拼接成完整fileName
        name.append(nameNumber);
        name.append(nameEnd);
        return name;
    }
    else{
        //在文件夹有文件的情况下
        while (_findnext(Handle1, &fileInfo1) == 0){
            name=fileInfo1.name;
            //查看是不是index文件
            if(name.erase(0,3)!=".index"){
                //不是就保存这次文件名
                name=fileInfo1.name;
                continue;
            }
            else{
                //是就直接continue;
            }
        }
        //while完成后，name保存的一定是最后一个file的名字
        //处理文件名
        nameLevel=name;
        nameNumber=name;
        nameEnd=name;
        //保留"级号."
        nameLevel.resize(2);
        //保留 "文件号"
        nameNumber.resize(3);
        nameNumber.erase(0,2);

        int number=stoi(nameNumber);
        number++;
        nameNumber=to_string(number);
        name.append(nameLevel);
        name.append(nameNumber);
        name.append(".db");
        //此时name是一个新的数据文件名（带后缀）
        return name;
    }
}

//面对一个级目录已经满了的情况，就需要进行升级,这里的filePath可以是当前文件的级目录路径(不带"\\")，也可以是随便一个数据文件的路径
bool upgradeFile(string filePath){
    string path=filePath;
    string oldIndexPath=ROOTFOLDERPATH;
    string newFolderPath=ROOTFOLDERPATH;
    string oldFilePath;
    string newFilePath;
    string newFileName;
    char sequenceChar[20];
    string sequence;
    int sequenceNum;
    //string rootPath=ROOTFOLDERPATH;
    string level_s;
    string number_s;
    int level_i=getFileLevel(path);
    int number_i;
    //rootPath.append("\\");
    //level+1是下一个的文件夹级号
    level_s=to_string(level_i++);
    oldIndexPath.append("\\");
    oldIndexPath.append(level_s);
    level_s=to_string(level_i);
    newFolderPath.append("\\");
    newFolderPath.append(level_s);
    //查看下一级是不是最高级文件
    if(level_i!=3){
        //不是最高级文件
        //查看是不是已经满了
        if(is_fileFull(newFolderPath)){
            //满了
            //递归，先完成下一个文件的升级
            upgradeFile(newFolderPath);
        }
    }
    //是最高级目录(不用升级了)，或者非最高级但未满目录(可以放下这次升级的的文件)，就不用递归了
    //这个时候就要根据sequence来读取了,读取上一级的文件号最低的文件的索引，找出sequence
    oldIndexPath.append(".0.index");
    //拿到sequence
    ifstream fin_index;
    fin_index.open(oldIndexPath,ios::binary);
    fin_index.read((char*)sequenceChar,sizeof(sequence));
    sequence=sequenceChar;
    //fin_index.close();
    //开始转数据
    //遍历每个文件，从文件号最小的开始
    oldFilePath=oldIndexPath.substr(0,oldIndexPath.size()-8);
    //生成下一级文件的合适路径
    newFileName=makeFileName(newFilePath);
    newFilePath.append("\\");
    newFilePath.append(newFileName);
    //打开新文件
    ofstream fout;
    fout.open(newFileName,ios::binary|ios::app);
    //定义好数据容器
    int pos=sizeof(string)*2+sizeof(time_t)*2;
    int off;
    time_t timeData[10^(level_i-1)];
    int intData[10^(level_i-1)];
    char charData[10^(level_i-1)];
    bool boolData[10^(level_i-1)];
    float floatData[10^(level_i-1)];
    double doubleData[10^(level_i-1)];
    //每次大循环转移一种数据
    for(int i=0;i<=sequence.size();i++){
        //每次小循环转移一个文件的一种数据
        for(int j=0;j<10;j++){
            //拿到第j个文件的路径
            number_i=j;
            number_s=to_string(number_i);
            oldFilePath=newFolderPath.substr(0,newFolderPath.size()-1);
            oldFilePath.append(to_string(level_i-1));
            oldFilePath.append("\\");
            oldFilePath.append(level_s);
            oldFilePath.append(".");
            oldFilePath.append(number_s);
            oldFilePath.append(".db");
            ifstream fin_file;
            fin_file.open(oldFilePath,ios::binary);
            if(i==0){
                //转移时间戳数据
                fin_file.read((char*)timeData,sizeof(time_t)*(10*(level_i-1)));
                fout.write((char*)timeData,sizeof(time_t)*(10*(level_i-1)));
                fin_file.close();
                //pos+=sizeof(time_t)*(10*(level_i-1));
                continue;
            }
            else{
                //根据索引转移数据
                sequenceNum=stoi(departSequence(sequence,i));
                //因为所有同级文件的索引除了文件名不一样，其他的都一样，所以就不更换索引的文件了
                switch (sequenceNum)
                {
                case 1:
                    //转移int数据
                    //从索引中找到数据的偏移
                    fin_index.seekg(pos,ios::beg);
                    fin_index.read((char*)&off,ios::binary);
                    //根据偏移找到数据
                    fin_file.seekg(off,ios::beg);
                    fin_file.read((char*)intData,sizeof(int)*(10*(level_i-1)));
                    //写入数据
                    fout.write((char*)intData,sizeof(int)*(10*(level_i-1)));
                    fin_file.close();
                    if(i==sequence.size()){
                        //说明是最后一个数据了，移动完了就要删除文件了
                        remove(oldFilePath.c_str());
                    }
                    break;
                case 2:
                    //转移char数据
                    //从索引中找到数据的偏移
                    fin_index.seekg(pos,ios::beg);
                    fin_index.read((char*)&off,ios::binary);
                    //根据偏移找到数据
                    fin_file.seekg(off,ios::beg);
                    fin_file.read((char*)charData,sizeof(char)*(10*(level_i-1)));
                    //写入数据
                    fout.write((char*)charData,sizeof(char)*(10*(level_i-1)));
                    fin_file.close();
                    if(i==sequence.size()){
                        //说明是最后一个数据了，移动完了就要删除文件了
                        remove(oldFilePath.c_str());
                    }
                    break;
                case 3:
                    //转移bool数据
                    //从索引中找到数据的偏移
                    fin_index.seekg(pos,ios::beg);
                    fin_index.read((char*)&off,ios::binary);
                    //根据偏移找到数据
                    fin_file.seekg(off,ios::beg);
                    fin_file.read((char*)boolData,sizeof(bool)*(10*(level_i-1)));
                    //写入数据
                    fout.write((char*)boolData,sizeof(bool)*(10*(level_i-1)));
                    fin_file.close();
                    if(i==sequence.size()){
                        //说明是最后一个数据了，移动完了就要删除文件了
                        remove(oldFilePath.c_str());
                    }
                    break;
                case 4:
                    //转移float数据
                    //从索引中找到数据的偏移
                    fin_index.seekg(pos,ios::beg);
                    fin_index.read((char*)&off,ios::binary);
                    //根据偏移找到数据
                    fin_file.seekg(off,ios::beg);
                    fin_file.read((char*)floatData,sizeof(float)*(10*(level_i-1)));
                    //写入数据
                    fout.write((char*)floatData,sizeof(float)*(10*(level_i-1)));
                    fin_file.close();
                    if(i==sequence.size()){
                        //说明是最后一个数据了，移动完了就要删除文件了
                        remove(oldFilePath.c_str());
                    }
                    break;
                case 5:
                    //转移double数据
                    //从索引中找到数据的偏移
                    fin_index.seekg(pos,ios::beg);
                    fin_index.read((char*)&off,ios::binary);
                    //根据偏移找到数据
                    fin_file.seekg(off,ios::beg);
                    fin_file.read((char*)doubleData,sizeof(double)*(10*(level_i-1)));
                    //写入数据
                    fout.write((char*)doubleData,sizeof(double)*(10*(level_i-1)));
                    fin_file.close();
                    if(i==sequence.size()){
                        //说明是最后一个数据了，移动完了就要删除文件了
                        remove(oldFilePath.c_str());
                    }
                    break;
                }
            }
        }
        //更新下一个数据的索引的偏移
        pos+=sizeof(int);
    }
    //两个for都进行完毕了，该关闭新文件和旧文件索引，并且开始写索引、删除索引了
    fin_index.close();
    fout.close();
    //生成索引
    makeIndex(newFilePath,sequence);
    //删除旧索引
    for(int j=0;j<10;j++){
            //拿到第j个文件的路径
            number_i=j;
            number_s=to_string(number_i);
            //此时的oldFilePath是上一级最后一个数据文件的Path
            oldIndexPath=oldFilePath;
            oldIndexPath.resize(oldIndexPath.size()-4);
            oldIndexPath.append(number_s);
            oldIndexPath.append(".index");
            remove(oldIndexPath.c_str());
    }
    //完成升级
    return true;
}


