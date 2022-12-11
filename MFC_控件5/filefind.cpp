#include<afxwin.h>
#include<iostream>

using namespace std;

void Find(CString path)
{
	CString strPath = path;   
	strPath += "/*.*";   //"d:/mycode/*.*"

	CFileFind find;  //�ļ����������
	BOOL canFind=find.FindFile(strPath);  //�Ƿ���Կ�������
	while (canFind)
	{
		//�ҵ���ǰ�ļ������ļ���Ϣ���浽find����ĳ�Ա������
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