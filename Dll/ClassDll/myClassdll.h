#pragma once
#include"pch.h"
/*
��̬���з�װ��
1����������ǰ����_declspec(dllexport)���� eg.            //һ��ʹ���������������Ƽ�ʹ��ģ�鶨���ļ�.def����������(��Ȼ����),��Ϊ��
	class _declspec(dllexport)CMath					//һ�����ǵ�����̬���е��࣬��ʵ��������еĳ�Ա��������Ե�ַ����ȥ���ڶ�̬���з�װ���࣬
	{												//��ʵ���Ǹ�����(��int��double���޲��),�����ǲ����е�ַ�ġ�
		...
	};
2��ͨ��ʹ��Ԥ���뿪���л���ĵ��뵼������ eg.
	#ifdef DLLCLASS_EXPORT            //��������DLLCLASS_EXPORT ��÷���.cpp��
	#define EXT_CLASS _declspec(dllexport) //DLL
	#else
	#define EXT_CLASS _declspec(dllimport) //ʹ����
	#endif

	class EXT_CLASS CMath
	{
		...
	};
*/

//�ڶ�̬���з�װ�࣬һ����Ҫ.h�ļ���������������ʹ�ö�̬������޷�֪����̬���з�װ�������������ò�����Ա����

#ifdef DLLCLASS_EXPORT
#define EXT_CLASS _declspec(dllexport) //DLL
#else
#define EXT_CLASS _declspec(dllimport) //ʹ����
#endif


// template<class T>
// class  EXT_CLASS CMath       //�������������յ���ȥ������ĳ�Ա�����ĵ�ַ��
// {									//_declspec(dllexport)��������̬�� _declspec(dllimport)��ʹ�ö�̬��ʱ������
// public:
// 	T Add(T x, T y);
// 	T Sub(T x, T y);
/*};*/

class  EXT_CLASS CMath       //�������������յ���ȥ������ĳ�Ա�����ĵ�ַ��
{									//_declspec(dllexport)��������̬�� _declspec(dllimport)��ʹ�ö�̬��ʱ������
public:
	int Add(int x, int y);
	int Sub(int x, int y);
};