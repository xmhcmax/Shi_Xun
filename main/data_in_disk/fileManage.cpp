#include"data_in_disk.h"
using namespace std;
//文件管理的内容我想的是，可以检测到一级文件的数量，我这里假定是10个以及文件就会往上合成为一个二级文件，把10个的内容相加
//但是不是单纯叠加，是把10个文件的一类的列都归为一个列，

//得到数据文件的level,int类型
int getFileLevel(string filePath){
    string fileLevel_s;
    int fileLevel_i;
    fileLevel_s=filePath.substr(0,filePath.size()-5);
    fileLevel_s.erase(0,fileLevel_s.size()-1);
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

//生成目前应该filePath的函数，level是级数，int 类型
string getFilePath(int level){
//思路是根据传入的level来拼接成一个完整的目录路径(带“\\”)
    string path="D:\\dataFile\\";
    string Level=to_string(level);
    path.append(Level);
    path.append("\\");
    return path;
}

//生成fileName的函数,这里的filePath是级目录，不是数据文件根目录
string getFileName(string filePath){
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
            //检查是不是index文件
            if(name.erase(0,3)!=".index"){
                //不是index文件,则
                nameLevel=fileInfo1.name;
                nameNumber=fileInfo1.name;
                nameEnd=fileInfo1.name;
                //单独取出级号
                nameLevel.resize(2);
                //去除".db"后缀
                nameNumber.resize(name.size()-3);
                //单独取出后缀
                nameEnd.erase(0,name.size());
                //去除级号
                nameNumber.erase(0,2);
                //**现在的nameNumber就只代表文件号**//
                //cout<<nameNumber<<endl;
            }
        }
        //while运行完毕之后，nameNumber就是最后一个文件的文件号，文件号+1就可以生成新的文件了
        int number=stoi(nameNumber);
        number++;
        nameNumber=to_string(number);
        name.append(nameLevel);
        name.append(nameNumber);
        name.append(nameEnd);
        //此时name是一个新的数据文件名（带后缀）
        return name;
    }
}

//检查该级目录是不是满了的函数,这里的filePath是级目录，不是数据文件根目录
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

//将同一级目录下的所有数据文件转移到下一级目录的一个新数据文件中,这里的filePath是级目录，不是数据文件根目录
bool upgradeFile(string filePath){
    string thePath=filePath;
    string oldPath=filePath;
    string newPath;
    string fileLevel;
    //更改级目录到下一级,装入newPath
    thePath.resize(thePath.size()-1);
    newPath=thePath;
    filePath.erase(0,thePath.size());
    int level=stoi(filePath);
    //判断是不是已经到了最高一级目录
    if(level=9){
        cout<<"Error!This folder is the biggest one!"<<endl;
        return false;
    }
    //level还有用，用来计算这一级目录下的文件内将包含多少条数据，级别1就是10^1,级别2就是10^2条
    level++;//目前的level是新的目录的级数
    fileLevel=to_string(level);
    newPath.append(fileLevel);
    //生成新的文件名，拼接成完整文件路径
    string fileName=getFileName(newPath);
    string newFilePath=newPath;
    newFilePath.append("\\");
    newFilePath.append(fileName);
    
    //打开最新级别的新文件
    ofstream fout_new;
    //以二进制、追加方式写入新文件
    fout_new.open(newFilePath,ios::binary|ios::app);
    
    //将读取的内容放到以下数组里
    time_t timeStamp[10^(level-1)];
    int temp[10^(level-1)];
    bool deleted[10^(level-1)];
    //oldFilePath用来存放当前的旧数据文件路径
    string oldFilePath=oldPath;
    oldFilePath.append("\\");
    //oldFilePath_save用来存档当前级的目录路径
    string oldFilePath_save1=oldFilePath;
    string oldFilePath_save2;
    
    string fileLevel;//fileLevel是文件级数
    string fileNumber;//fileNumber是文件号
    fileLevel=to_string(level-1);
    fileLevel.append(".");
    const char* oldFilePath_char;
    //循环，将每一个oldPath下的文件内容都移动到新文件中
    for(int i=0;i<3;i++){
        //i=0代表移动的数据是timeStamp
        //i=1代表移动的数据是temp
        //i=2代表移动的数据是deleted
        for(int j=0;j<=9;j++){
            //重置目录路径
            oldFilePath=oldFilePath_save1;
            //组合新的旧文件路径
            fileNumber=to_string(j);//fileNumber是文件号
            fileNumber.append(".db");
            oldFilePath.append(fileLevel);
            oldFilePath.append(fileNumber);//现在的oldFilePath就是旧的文件的完整路径了
            //这里转变一下数据类型，方便后面的remove();
            oldFilePath_save2=oldFilePath;
            oldFilePath_char=oldFilePath_save2.c_str();

            //打开旧文件
            ifstream fin_old;
            fin_old.open(oldFilePath,ios::binary);
            switch (i)
            {
            case 0:
                {
                    fin_old.read((char*)timeStamp,sizeof(timeStamp));
                    fout_new.write((char*)timeStamp,sizeof(timeStamp));
                    fin_old.close();
                    break;
                }
            case 1:
                {
                    fin_old.read((char*)temp,sizeof(temp));
                    fout_new.write((char*)temp,sizeof(temp));
                    fin_old.close();
                    break;
                }
            case 2:
                {
                    fin_old.read((char*)deleted,sizeof(deleted));
                    fout_new.write((char*)deleted,sizeof(deleted));
                    fin_old.close();
                    //在最后一个数据移动完毕之后，删除该旧数据文件，避免出现冗余
                    remove(oldFilePath.c_str());
                    break;
                }    
            }
        }
    }
    fout_new.close();
    //两个for都循环完了，就已经完成了数据的转录了接下来要生成索引和删除旧索引了
    //此时oldFilePath是上一级的最后一个文件路径，我们要开始删除之前的索引了
    string oldIndexPath=oldFilePath;
    //旧文件去除"文件号.db"
    oldIndexPath.resize(oldIndexPath.size()-4);
    //存个备份
    string oldIndexPath_save=oldIndexPath;
    //倒序删掉索引，正序也可以
    for(int i=9;i>=0;i++){
        oldIndexPath=oldIndexPath_save;
        oldIndexPath.append(to_string(i));
        oldIndexPath.append(".index");
        remove(oldIndexPath.c_str());
    }
    //删完了，不能没有索引吧，给新文件创建一个
    //创建新索引
    makeIndex(newFilePath);
    // ofstream fout_index;  
    // fout_index.open(newIndexPath,ios::binary|ios::app);
    
    // int pos0=0;
    // int pos1=sizeof(timeStamp);
    // int pos2=sizeof(temp);
    // fout_index.write((char*)&pos0,sizeof(int)); 
    // fout_index.write((char*)&pos1,sizeof(int));
    // fout_index.write((char*)&pos2,sizeof(int));
    // fout_index.close();
    return true;
}