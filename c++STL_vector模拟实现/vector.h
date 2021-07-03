#pragma once
#include<iostream>
#include<assert.h>


namespace my_vector
{
	template<class T>
	class vector
	{
	public:
		typedef T* iterator;
		typedef const T* const_iterator;
		//构造函数
		vector()
			:_start(nullptr)
			,_finish(nullptr)
			,_endofstorage(nullptr)
		{}
		~vector()  //析构函数
		{
			delete[]_start;
			_finish = _start = _endofstorage = nullptr;
		}
		//vector(const vector<T>& v)//拷贝构造  深拷贝   v2(v1)    第一种写法
		//{
		//	_start = new T[v.capacity()];
		//	_finish = _start;
		//	_endofstorage = _start + v.capacity();
		//	for (size_t i = 0; i < v.size(); ++i)
		//	{
		//		*_finish = v[i];
		//		++_finish;
		//	}
		//}
		//第二种拷贝构造写法
		vector(const vector<T>& v)
			:_start(nullptr)      //必须初始化
			, _finish(nullptr)
			, _endofstorage(nullptr)
		{
			reserve(v.capacity());   //必须先把空间开出来
			for (const auto& e : v)
			{
				push_back(e);
			}
		} 
		//vector<T>& operator=(const vector<T>& v)   //赋值   第一种传统写法
		//{
		//	if (this != &v)
		//	{
		//		delete[] _start;
		//		_start = new T[v.capacity()];
		//		memcpy(_start, v._start, sizeof(T) * v.size());
		//		_finish = _start+v.size();
		//		_endofstorage = _start + v.capacity();
		//	}
		//	return *this;
		//}
		vector<T>& operator=(vector<T> v)   //赋值()   第二种现代写法  v1=v3
		{
		    swap(v);    //不要字节调用全局swap()来实现交换，因为这样代价极大，涉及多次深拷贝；可以自己实现swap()，在里面调用全局swap()来实现指针的交换即可。
			return *this;
		}
		void swap(vector<T>& v)   
		{
			std::swap(_start, _start);    //调用全局的swap()
			std::swap(_finish, _finish);
			std::swap(_endofstorage, _endofstorage); 
		}
		void reserve(size_t n)
		{
			size_t sz = size();
			if (n > capacity())
			{
				iterator tmp = new T[n];
				if (_start)
				{
					//memcpy(tmp, _start, sizeof(T) * size());//注意:memcpy()也是按字节拷贝，属于浅拷贝.对于自定义类型如T是string对象时。涉及扩容拷贝时需要进行深拷贝；     
					for (size_t i = 0; i < size(); ++i)        //则不能再使用memcpy()，而是需要使用T类型的operator=（深拷贝）的赋值拷贝。
					{
						tmp[i] = _start[i];
					}
					delete[] _start;
				}
				_start = tmp;
				_finish = _start + sz;
				_endofstorage = _start + n;
			}
		}
		const_iterator begin()const
		{
			return _start;
		}
		iterator begin()
		{
			return _start;
		}
		iterator end()
		{
			return _finish;
		}
		const_iterator end()const
		{
			return _finish;
		}
		T& operator[](size_t i)  //可读可写
		{
			assert(i < size());
			return _start[i];
		}
		const T& operator[](size_t i)const  //只读
		{
			assert(i < size());
			return _start[i];
		}
		size_t size()const
		{
			return _finish - _start;
		}
		size_t capacity()const
		{
			return _endofstorage - _start;
		}
		void push_back(const T& x)//防止T的类型是类的类型，减少拷贝构造，所以尾插尽量传引用
		{
			//if (_finish==_endofstorage)
			//{
			//	size_t newcapacity = capacity() == 0 ? 2 : 2 * capacity();
			//	reserve(newcapacity);
			//}
			//*_finish = x;
			//_finish++;
			insert(_finish, x);
		}
		void pop_back()
		{
			//assert(_start < _finish);
			//--_finish;
			erase(_finish-1);
		}
		void insert(iterator pos, const T& x)
		{
			assert(pos <= _finish);
			if (_finish == _endofstorage)
			{
				size_t n = pos - _start;
				size_t newcapacity = capacity() ==0 ? 2 : 2 * capacity();
				reserve(newcapacity);
				//如果增容，pos迭代器就失效了。必须重新计算pos的位置
				pos = _start + n;
			}
			iterator end = _finish - 1;
			while (end >= pos)
			{
				*(end + 1) = *end;
				--end;
			}
			*pos = x;
			++_finish;
		}
		iterator erase(iterator pos)
		{
			assert(pos < _finish);
			iterator it = pos;
			while (it < _finish)
			{
				*it = *(it + 1);
				++it;
			}
			--_finish;
			return pos;
		}
		void resize(size_t n, const T& val = T())
		{
			if (n < size())
			{
				_finish = _start + n;
			}
			else
			{
				if (n > capacity())
				{
					reserve(n);
				}
				while (_finish < _start + n)
				{
					*_finish = val;
					++_finish;
			   }
			}
		}

	private:
		iterator _start;// 数组的第一个位置
		iterator _finish;//数组最后一个元素的下一个位置  _finish=_star+元素个数(size);
		iterator _endofstorage;//容量  _endofstorage= _start+容量(capacity);
	};
    
	template<class T>
	void vector_Print(const vector<T>& v)
	{
		//第一种
		for (auto e : v)
		{
			std::cout << e << " ";
		}
		std::cout << std::endl;
		//第二种
		//for (size_t i = 0; i < v.size(); ++i)
		//{
		//	std::cout << v[i] << " ";
		//}
		//std::cout << std::endl;
		////////第三种
		//vector<int>::const_iterator it = v.begin();
		//while (it != v.end())
		//{
		//	std::cout << *it << " ";
		//	++it;
		//}
		//std::cout << std::endl;
	}
}