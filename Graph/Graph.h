#pragma once

#include<iostream>
#include<vector>
#include<queue>
#include<string>
#include<map>
#include<stdio.h>
#include<stdlib.h>

//�ڽӾ���(matrix)��ʾ������vector���涥��vector<char>,�þ��󣨶�ά���飩����ߣ�vector<verctor<W>> edge;
// 
// ����--�����ҵ���������֮��ıߣ��ʺϱ߱Ƚ϶��ͼ
// ���ƣ�Ҫ����һ���������ӳ�ȥ�ıߵ�Ч����O(N)
//    A  B  C  D
// A  0  1  0  1
// B  1  0  1  0
// C  0  1  0  1
// D  1  0  1  0
namespace Matrix
{
	template<class V,class W,bool Direction=false>       //V--�������ͣ�W--Ȩֵ(����֮��Ĺ�ϵ)
	class Graph
	{
	private:
		std::map<std::string, int> _vIndexMap;  //���涥���Ӧ���±��ӳ���ϵ
		std::vector<V> _vertexs;  //���㼯��
		std::vector<std::vector<W>> _matrix; //�洢�߼��ϵľ���
	private:
		void _DFS(size_t srcIndex, std::vector<bool>& vBool)
		{
			std::cout << _vertexs[srcIndex] << "->";
			vBool[srcIndex] = true;
			for (size_t i = 0; i < _vertexs.size(); ++i)
			{
				if (vBool[i] == false && _matrix[srcIndex][i] != W())
				{
					_DFS(i, vBool);
				}
			}
		}
	public:
		Graph(const V* vertexs, size_t n) //n--�����С(����ĸ���)
		{
			_vertexs.reserve(n);
			for (size_t i = 0; i < n; ++i)
			{
				_vertexs.push_back(vertexs[i]);
				_vIndexMap[vertexs[i]] = i;
			}
			_matrix.resize(n);   //�����󿪿ռ䣬����������ÿ��һά���鿪�ռ�  
			for (auto& e : _matrix)
			{
				e.resize(n);
			}
		}
		size_t GetVertexIndex(const V& v)
		{
			auto ret = _vIndexMap.find(v);
			if (ret != _vIndexMap.end())
			{
				return ret->second;
			}
			else
			{
				throw std::invalid_argument("�Ƿ�����");
				return -1;
			}
		}
		void AddEdge(const V& src, const V& dst,const W& w)
		{
			size_t srcIndex = GetVertexIndex(src);
			size_t dstIndex = GetVertexIndex(dst);
			_matrix[srcIndex][dstIndex] = w;
			if (Direction == false)              //����ͼ;����ͼֻ�����src->dst��Ȩֵ,dst->src��Ȩֵ�������
			{
				_matrix[dstIndex][srcIndex] = w;
			}
		}
		//������ȱ���
		void BFS(const V& src)
		{
			size_t srcIndex = GetVertexIndex(src);
			std::queue<int> q;
			std::vector<bool> vBool;
			vBool.resize(_vertexs.size(), false);
			q.push(srcIndex);
			vBool[srcIndex] = true;
			size_t dfriend = 1;
			while (!q.empty())
			{
				size_t qSize = q.size();
				printf("%s��%d�Ⱥ��ѣ�", _vertexs[srcIndex].c_str(), dfriend);
				while (qSize--)
				{
					size_t front = q.front();
					q.pop();
					for (size_t i = 0; i < _vertexs.size(); ++i)
					{
						if (vBool[i] == false && _matrix[front][i] != W())
						{
							std::cout << _vertexs[i] << " ";
							vBool[i] = true;
							q.push(i);
						}
					}	
				}
				std::cout << std::endl;
				dfriend++;
			}
		}
		//������ȱ���
		void DFS(const V& src)
		{
			size_t srcIndex = GetVertexIndex(src);
			std::vector<bool> vBool;
			vBool.resize(_vertexs.size(), false);
			_DFS(srcIndex, vBool);
			std::cout << std::endl;;
		}
	};

	void TestGraph()
	{
		std::string a[] = { "����","����","����","����","����"};
		Graph<std::string, int> g1(a,sizeof(a)/sizeof(std::string));
		g1.AddEdge("����","����",100);
		g1.AddEdge("����","����",200);
		g1.AddEdge("����","����",30);
		g1.AddEdge("����","����",30);
		std::cout << "������ȱ�����";
		g1.BFS("����");
		std::cout << std::endl;
		std::cout << "������ȱ�����";
		g1.DFS("����");
	}
}

//�ڽӱ��ʾ����ʹ��vector���涥��,ʹ����������ÿ��������ͨ�Ķ��㣬���ƹ�ϣͰ��һ���������ı�����ʽ�ṹ���ں���
// ���ƣ���һ��������������ı�Ч�ʺܸߣ����ƣ��ʺϱ߱Ƚ��٣��Ƚ�ϡ���ͼ---ȷ�����������Ƿ�������ʱ�临�Ӷ���O(N)
// �ܽ᣺�������ṹ�ǻ����ġ�

namespace LinkTable
{
	template<class W>
	struct LinkEdge    //�����д洢����������أ�Ȩֵ��������±�͹�ϵ��Ȩֵ��
	{
		int _srcIndex;
		int _dstIndex;
		W _w;
		LinkEdge<W>* _next;
		LinkEdge(const W& w):_srcIndex(-1),_dstIndex(-1),_next(nullptr),_w(w)
		{}
	};
	template<class V, class W, bool Direction = false>       //V--�������ͣ�W--Ȩֵ(����֮��Ĺ�ϵ)
	class Graph
	{
		typedef LinkEdge<W> Edge;
	private:
		std::map<std::string, int> _vIndexMap;  //���涥���Ӧ���±��ӳ���ϵ
		std::vector<V> _vertexs;  //���㼯��
		std::vector<Edge*> _linkTable;  //�߼��ϵ��ڽӱ�
	public:
		Graph(const V* vertexs, size_t n) //n--�����С(����ĸ���)
		{
			_vertexs.reserve(n);
			for (size_t i = 0; i < n; ++i)
			{
				_vertexs.push_back(vertexs[i]);
				_vIndexMap[vertexs[i]] = i;
			}
			_linkTable.resize(n, nullptr);
		}
		size_t GetVertexIndex(const V& v)
		{
			auto ret = _vIndexMap.find(v);
			if (ret != _vIndexMap.end())
			{
				return ret->second;
			}
			else
			{
				throw std::invalid_argument("�Ƿ�����");
				return -1;
			}
		}
		void AddEdge(const V& src, const V& dst, const W& w)
		{
			size_t srcIndex = GetVertexIndex(src);
			size_t dstIndex = GetVertexIndex(dst);
			Edge* st_e = new Edge(w);
			st_e->_srcIndex = srcIndex;
			st_e->_dstIndex = dstIndex;
			st_e->_next = _linkTable[srcIndex];
			_linkTable[srcIndex] = st_e;
			if (Direction == false)
			{
				Edge* ds_e = new Edge(w);
				ds_e->_srcIndex = dstIndex;
				ds_e->_dstIndex = srcIndex;
				ds_e->_next = _linkTable[dstIndex];
				_linkTable[dstIndex] = ds_e;
			}
		}
	};

	void TestGraph()
	{
		std::string a[] = { "����","����","����","����" };
		Graph<std::string, int> g1(a, 4);
		g1.AddEdge("����", "����", 100);
		g1.AddEdge("����", "����", 200);
		g1.AddEdge("����", "����", 30);
	}
}