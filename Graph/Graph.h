#pragma once

#include<iostream>
#include<vector>
#include<queue>
#include<string>
#include<map>
#include<stdio.h>
#include<stdlib.h>

//邻接矩阵(matrix)表示法：用vector保存顶点vector<char>,用矩阵（二维数组）保存边：vector<verctor<W>> edge;
// 
// 优势--快速找到俩个顶点之间的边；适合边比较多的图
// 劣势：要查找一个顶点连接出去的边的效率是O(N)
//    A  B  C  D
// A  0  1  0  1
// B  1  0  1  0
// C  0  1  0  1
// D  1  0  1  0
namespace Matrix
{
	template<class V,class W,bool Direction=false>       //V--顶点类型；W--权值(顶点之间的关系)
	class Graph
	{
	private:
		std::map<std::string, int> _vIndexMap;  //保存顶点对应的下标的映射关系
		std::vector<V> _vertexs;  //顶点集合
		std::vector<std::vector<W>> _matrix; //存储边集合的矩阵
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
		Graph(const V* vertexs, size_t n) //n--数组大小(顶点的个数)
		{
			_vertexs.reserve(n);
			for (size_t i = 0; i < n; ++i)
			{
				_vertexs.push_back(vertexs[i]);
				_vIndexMap[vertexs[i]] = i;
			}
			_matrix.resize(n);   //给矩阵开空间，并给矩阵中每个一维数组开空间  
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
				throw std::invalid_argument("非法顶点");
				return -1;
			}
		}
		void AddEdge(const V& src, const V& dst,const W& w)
		{
			size_t srcIndex = GetVertexIndex(src);
			size_t dstIndex = GetVertexIndex(dst);
			_matrix[srcIndex][dstIndex] = w;
			if (Direction == false)              //无向图;有向图只能添加src->dst的权值,dst->src的权值不能添加
			{
				_matrix[dstIndex][srcIndex] = w;
			}
		}
		//广度优先遍历
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
				printf("%s的%d度好友：", _vertexs[srcIndex].c_str(), dfriend);
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
		//深度优先遍历
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
		std::string a[] = { "张三","李四","王五","赵六","周七"};
		Graph<std::string, int> g1(a,sizeof(a)/sizeof(std::string));
		g1.AddEdge("张三","李四",100);
		g1.AddEdge("张三","王五",200);
		g1.AddEdge("王五","赵六",30);
		g1.AddEdge("王五","周七",30);
		std::cout << "深度优先遍历：";
		g1.BFS("张三");
		std::cout << std::endl;
		std::cout << "广度优先遍历：";
		g1.DFS("张三");
	}
}

//邻接表表示法：使用vector保存顶点,使用链表保存与每个顶点连通的顶点，类似哈希桶把一个点相连的边用链式结构挂在后面
// 优势：找一个顶点相连顶点的边效率很高；劣势：适合边比较少，比较稀疏的图---确认俩个顶点是否相连的时间复杂度是O(N)
// 总结：这俩个结构是互补的。

namespace LinkTable
{
	template<class W>
	struct LinkEdge    //链表中存储的是俩个相关（权值）顶点的下标和关系（权值）
	{
		int _srcIndex;
		int _dstIndex;
		W _w;
		LinkEdge<W>* _next;
		LinkEdge(const W& w):_srcIndex(-1),_dstIndex(-1),_next(nullptr),_w(w)
		{}
	};
	template<class V, class W, bool Direction = false>       //V--顶点类型；W--权值(顶点之间的关系)
	class Graph
	{
		typedef LinkEdge<W> Edge;
	private:
		std::map<std::string, int> _vIndexMap;  //保存顶点对应的下标的映射关系
		std::vector<V> _vertexs;  //顶点集合
		std::vector<Edge*> _linkTable;  //边集合的邻接表
	public:
		Graph(const V* vertexs, size_t n) //n--数组大小(顶点的个数)
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
				throw std::invalid_argument("非法顶点");
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
		std::string a[] = { "张三","李四","王五","赵六" };
		Graph<std::string, int> g1(a, 4);
		g1.AddEdge("张三", "李四", 100);
		g1.AddEdge("张三", "王五", 200);
		g1.AddEdge("王五", "赵六", 30);
	}
}