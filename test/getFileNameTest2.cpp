#include"..\\main\\data_in_disk_forN\\data_in_disk_forN.h"
using namespace std;
 
int main(void)
{
	intptr_t Handle;
	struct _finddata_t FileInfo;
	string p;
	string path = "D:\\apps\\VS code\\Programs\\C++ program\\shixun\\data_in_mem";
	if ((Handle = _findfirst(p.assign(path).append("\\*").c_str(), &FileInfo)) == -1)
		printf("没有找到匹配的项目\n");
	else
	{
		printf("%s\n", FileInfo.name);
		while (_findnext(Handle, &FileInfo) == 0)
			printf("%s\n", FileInfo.name);
		_findclose(Handle);
	}
	return 0;
}