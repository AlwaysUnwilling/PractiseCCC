#include<afxwin.h>
#include<iostream>

using namespace std;

void Find(CString path)
{
	CString strPath = path;   
	strPath += "/*.*";   //"d:/mycode/*.*"

	CFileFind find;  //文件搜索类对象
	BOOL canFind=find.FindFile(strPath);  //是否可以开启查找
	while (canFind)
	{
		//找到当前文件，将文件信息保存到find对象的成员变量中
		canFind=find.FindNextFile();

		CString filename=find.GetFileName();
		CString filepath = find.GetFilePath();
		if (find.IsDirectory())
		{
			cout << "[" << filename << "]" << endl;
			if(!find.IsDots())
				Find(filepath);
		}
		else
		{
			cout << filename << endl;
		}
	}

	find.Close();
}
int main(int argc, TCHAR* argv[], TCHAR* envp[])
{

	Find("d:/mycode");
	return 0;
}