#include"..\\main\\data_in_disk_forN\\data_in_disk_forN.h"
using namespace std;

int main(){
    char c='1';
    char d;
    int num;
    c=(char)((c+2));
    cout<<c<<endl;

    ifstream fin;
    fin.open("D:\\dataFile\\2\\2.0.db",ios::binary);
    fin.seekg(sizeof(time_t)*100+sizeof(int)*100+sizeof(char)*12,ios::beg);
    fin.read((char*)&d,sizeof(char));
    fin.close();

    cout<<d<<endl;
    
    return 0;
}