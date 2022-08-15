//#undef UNICODE;
#include"D:\apps\VS code\Programs\C++ program\shixun\data_in_disk\data_in_disk.h"
#include <WinBase.h>
#include <assert.h>
using namespace std;
//这里是对内存映射的一些测试


int main(){
    string file_name = "D:\\apps\\VS code\\Programs\\C++ program\\shixun\\test\\mappingTest.txt";
    const char* file_name_c = "D:\\apps\\VS code\\Programs\\C++ program\\shixun\\test\\mappingTest.txt";
	const DWORD mmf_size = 512 * 1024;
	DWORD error_code;
 
	//创建文件
	HANDLE mmHandle =
		CreateFile(file_name.c_str(),
        GENERIC_READ | GENERIC_WRITE,
        FILE_SHARE_READ | FILE_SHARE_WRITE,
        NULL,
        OPEN_EXISTING,//OPEN_ALWAYS
        FILE_FLAG_SEQUENTIAL_SCAN,
        NULL);
 
	if (mmHandle == INVALID_HANDLE_VALUE) {
		error_code = GetLastError();
		cout << "创建失败:" << error_code << endl;
	}

    return 0;
}