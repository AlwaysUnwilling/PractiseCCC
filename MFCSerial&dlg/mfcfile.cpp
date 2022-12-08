#include<afxwin.h>
#include<iostream>


using namespace std;

class CMyDoc :public CDocument
{
	DECLARE_SERIAL(CMyDoc)
public:
	CMyDoc(int age = 0, float score = 0.0, CString name = "")
		:m_age(age),m_score(score),m_name(name)
	{}

	virtual void Serialize(CArchive& ar)
	{
		if (ar.IsStoring())
		{
			ar << m_age << m_score << m_name;
		}
		else
		{
			ar >> m_age >> m_score >> m_name;
		}
	}

	int m_age;
	float m_score;
	CString m_name;
};
IMPLEMENT_SERIAL(CMyDoc,CDocument,1)


void File()
{
	CFile file;
	file.Open("D:/MyCode/EdoyunProject/MFCFile1/file.txt", CFile::modeCreate | CFile::modeReadWrite);
	char str[] = "hello file";
	file.Write(str, strlen(str));
	file.SeekToBegin();
	char buf[256] = { 0 };
	long nLen=file.Read(buf, 255);

	cout << buf << " " << nLen << endl;
	file.Close();
}
//序列化-存储、写
void Store()
{
	CFile file;
	file.Open("D:/MyCode/EdoyunProject/MFCFile1/serial.txt", CFile::modeCreate | CFile::modeReadWrite);
	CArchive ar(&file,CArchive::store,4096); //归档类对象,维护缓冲区

	long age = 18;
	ar << age;
	float score = 88.5;
	ar << score;
	CString name = "zhangsan";
	ar << name;
	ar.Close();
	file.Close();
}
//反序列化--加载、读
void Load()
{
	CFile file;
	file.Open("D:/MyCode/EdoyunProject/MFCFile1/serial.txt", CFile::modeRead);
	CArchive ar(&file, CArchive::load, 4096);
	long age;
	ar >> age;
	float score;
	ar >> score;
	CString name;
	ar >> name;

	cout << age << " " << score << " " <<name<< endl;
}
void StoreClass()
{
	CFile file;
	file.Open("D:/MyCode/EdoyunProject/MFCFile1/serialClass.txt", CFile::modeCreate | CFile::modeReadWrite);
	CArchive ar(&file, CArchive::store, 4096);
	CMyDoc data(18, 88.5, "zhangsan");
	ar << &data;
	ar.Close();
	file.Close();
}
void LoadClass()
{
	CFile file;
	file.Open("D:/MyCode/EdoyunProject/MFCFile1/serialClass.txt", CFile::modeRead);
	CArchive ar(&file, CArchive::load, 4096);
	CMyDoc* cmdoc=NULL;
	//CMyDoc cmdoc;    //err
	ar >> cmdoc;
	cout << cmdoc->m_age << " " << cmdoc->m_score << " " << cmdoc->m_name << endl;
}
int main()
{
	File();
	//serial
	Store();
	Load();
	StoreClass();
	LoadClass();
	return 0;
}