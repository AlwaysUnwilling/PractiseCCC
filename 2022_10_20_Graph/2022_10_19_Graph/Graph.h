#pragma once
#include<iostream>
#include<vector>
#include<map>
#include<assert.h>
#include<exception>

namespace matrix
{
	template<typename V, class W, W MAX_W = INT_MAX, bool Direction=false>       //V--����   W--Ȩֵ
	class Graph
	{
	public:
		//ͼ�Ĵ�����1��IO���룻2��ͼ�ṹ��ϵд���ļ������ļ��ж�ȡ��3���ֶ���ӱ�
		Graph(const V* a,size_t n)
		{
			_vertexs.reserve(n);
			for (size_t i = 0; i < n; ++i)
			{
				_vertexs.push_back(a[i]);
				_indexMap[a[i]] = i;
			}
			_matrix.resize(n);
			for (size_t i = 0; i < _matrix.size(); ++i)
			{
				_matrix[i].resize(n,MAX_W);
			}
		}
		size_t GetVertexsIndex(const V& v)
		{
			auto it = _indexMap.find(v);
			if (it != _indexMap.end())
			{
				return it->second;
			}
			else
			{
				//assert(false);
				throw std::invalid_argument("���㲻���ڣ�");
				return -1;
			}
		}
		void AddEdge(const V& src, const V& dst, const W& w)
		{
			size_t srci = GetVertexsIndex(src);
			size_t dsti = GetVertexsIndex(dst);

			_matrix[srci][dsti] = w;
			if (Direction==false)                 //����ͼ  �����㻥�����Ȩֵ
			{
				_matrix[dsti][srci] = w;
			}
		}
		void Print()
		{
			//����
			for (size_t i = 0; i < _vertexs.size(); ++i)
			{
				std::cout << "[" << i << "]" << "->" << _vertexs[i] << std::endl;
			}
			std::cout << std::endl;

			//�±�
			std::cout << "  ";
			for (size_t i = 0; i < _vertexs.size(); ++i)
			{
				std::cout << i << " ";
			}
			std::cout << std::endl;
			//����
			for (size_t i = 0; i < _matrix.size(); ++i)
			{
				std::cout << i << " ";  //�����±�
				for (size_t j = 0; j < _matrix[i].size(); ++j)
				{
					if (_matrix[i][j] == MAX_W)
					{
						std::cout << "*" << " ";
					}
					else
					{
						std::cout << _matrix[i][j] << " ";
					}
				}
				std::cout << std::endl;
			}
			std::cout << std::endl;
		}
	private:
		std::vector<V> _vertexs;  //���㼯��
		std::map<V, size_t> _indexMap;  //����ӳ����±��ϵ
		std::vector<std::vector<W>> _matrix; //�ڽӾ���
	};

	void TestGraph1()
	{
		Graph<char, int, INT_MAX, true> g("0123", 4);
		g.AddEdge('0', '1', 1);
		g.AddEdge('0', '3', 4);
		g.AddEdge('1', '3', 2);
		g.AddEdge('1', '2', 9);
		g.AddEdge('2', '3', 8);
		g.AddEdge('2', '1', 5);
		g.AddEdge('2', '0', 3);
		g.AddEdge('3', '2', 6);

		g.Print();
	}
}

