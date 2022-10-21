#pragma once
#include<iostream>
#include<vector>
#include<map>
#include<assert.h>
#include<exception>
#include<queue>


namespace matrix
{
	template<typename V, class W, W MAX_W = INT_MAX, bool Direction=false>       //V--定点   W--权值
	class Graph
	{
	public:
		//图的创建：1、IO输入；2、图结构关系写到文件，从文件中读取；3、手动添加边
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
				throw std::invalid_argument("顶点不存在！");
				return -1;
			}
		}
		void AddEdge(const V& src, const V& dst, const W& w)
		{
			size_t srci = GetVertexsIndex(src);
			size_t dsti = GetVertexsIndex(dst);

			_matrix[srci][dsti] = w;
			if (Direction==false)                 //无向图  俩顶点互相添加权值
			{
				_matrix[dsti][srci] = w;
			}
		}
		void Print()
		{
			//顶点
			for (size_t i = 0; i < _vertexs.size(); ++i)
			{
				std::cout << "[" << i << "]" << "->" << _vertexs[i] << std::endl;
			}
			std::cout << std::endl;

			//下标
			std::cout << "  ";
			for (size_t i = 0; i < _vertexs.size(); ++i)
			{
				std::cout << i << " ";
			}
			std::cout << std::endl;
			//矩阵
			for (size_t i = 0; i < _matrix.size(); ++i)
			{
				std::cout << i << " ";  //纵向下标
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
		void BFS(const V& src)
		{
			size_t srci = GetVertexsIndex(src);
			std::queue<size_t> q;
			std::vector<bool> _visited(_vertexs.size(), false);
			q.push(srci);
			_visited[srci] = true;
			while (!q.empty())
			{
				size_t levelSize = q.size();
				for (size_t i = 0; i < levelSize; ++i)
				{
					size_t front = q.front();
					q.pop();
					std::cout << _vertexs[front] << " ";
					for (size_t j = 0; j < _matrix[front].size(); ++j)
					{
						if (_matrix[front][j] != MAX_W && !_visited[j])
						{
							q.push(j);
							_visited[j] = true;
						}
					}
					std::cout << std::endl;
				}
			}
		}
		void _DFS(size_t srci, std::vector<bool>& visited)
		{
			std::cout << "[ " << _vertexs[srci] << ":" << srci << "] ";
			visited[srci] = true;
			for (size_t i = 0; i < _vertexs.size(); ++i)
			{
				if (!visited[i] && _matrix[srci][i] != MAX_W)
				{
					_DFS(i, visited);
				}
			}
		}
		void DFS(const V& src)
		{
			size_t srci = GetVertexsIndex(src);
			std::vector<bool> visited(_vertexs.size());
			_DFS(srci, visited);
		}
	private:
		std::vector<V> _vertexs;  //顶点集合
		std::map<V, size_t> _indexMap;  //顶点映射的下标关系
		std::vector<std::vector<W>> _matrix; //邻接矩阵
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
	void TestGraphBDFS()
	{
		std::string a[] = { "张三","李四","王五","赵六" };
		Graph<std::string, int> g1(a, 4);
		g1.AddEdge("张三", "李四", 100);
		g1.AddEdge("张三", "王五", 200);
		g1.AddEdge("王五", "赵六", 30);
		//g1.Print();
		g1.BFS("张三");
		g1.DFS("张三");
	}
}

namespace link_table
{
	template<class W>
	struct Edge
	{
		//size_t _srci;
		size_t _dsti;    //目标点的下标
		Edge<W>* _next;
		W _w;          //权值
		Edge(const size_t dsti,const W& w)
			:_dsti(dsti),
			_w(w),
			_next(nullptr)
		{}
	};
	template<typename V, class W, bool Direction = false>       //V--定点   W--权值
	class Graph
	{
		typedef Edge<W> Edge;
	public:
		//图的创建：1、IO输入；2、图结构关系写到文件，从文件中读取；3、手动添加边
		Graph(const V* a, size_t n)
		{
			_vertexs.reserve(n);
			for (size_t i = 0; i < n; ++i)
			{
				_vertexs.push_back(a[i]);
				_indexMap[a[i]] = i;
			}

			_tables.resize(n,nullptr);
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
				throw std::invalid_argument("顶点不存在！");
				return -1;
			}
		}
		void AddEdge(const V& src, const V& dst, const W& w)
		{
			size_t srci = GetVertexsIndex(src);
			size_t dsti = GetVertexsIndex(dst);

			Edge* eg = new Edge(dsti, w);
			eg->_next = _tables[srci];
			_tables[srci] = eg;

			if (Direction == false)
			{
				Edge* eg = new Edge(srci, w);
				eg->_next = _tables[dsti];
				_tables[dsti] = eg;
			}
		}
		void Print()
		{
			//顶点
			for (size_t i = 0; i < _vertexs.size(); ++i)
			{
				std::cout << "[" << i << "]" << "->" << _vertexs[i] << std::endl;
			}
			std::cout << std::endl;

			for (size_t i = 0; i < _tables.size(); ++i)
			{
				std::cout << "[" << _vertexs[i] << " # " << i << "]" << " -> ";
				Edge* cur = _tables[i];
				while (cur)
				{
					std::cout << "[" << _vertexs[cur->_dsti] << " # "
						<< cur->_dsti <<" # " <<cur->_w << "]" << " -> ";
					cur = cur->_next;
				}
				std::cout << "nullptr" << std::endl;
			}
		}
	private:
		std::vector<V> _vertexs;  //顶点集合
		std::map<V, size_t> _indexMap;  //顶点映射的下标关系
		std::vector<Edge*> _tables; //邻接表
	};

// 	void TestGraph1()
// 	{
// 		Graph<char, int, true> g("0123", 4);
// 		g.AddEdge('0', '1', 1);
// 		g.AddEdge('0', '3', 4);
// 		g.AddEdge('1', '3', 2);
// 		g.AddEdge('1', '2', 9);
// 		g.AddEdge('2', '3', 8);
// 		g.AddEdge('2', '1', 5);
// 		g.AddEdge('2', '0', 3);
// 		g.AddEdge('3', '2', 6);
// 
// 		g.Print();
// 	}
	void TestGraph1()
	{
		std::string a[] = { "张三","李四","王五","赵六" };
		Graph<std::string, int> g1(a, 4);
		g1.AddEdge("张三", "李四",100 );
		g1.AddEdge("张三", "王五",200 );
		g1.AddEdge("王五", "赵六",30 );
		g1.Print();
	}
}

