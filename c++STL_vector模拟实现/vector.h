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
		//���캯��
		vector()
			:_start(nullptr)
			,_finish(nullptr)
			,_endofstorage(nullptr)
		{}
		~vector()  //��������
		{
			delete[]_start;
			_finish = _start = _endofstorage = nullptr;
		}
		//vector(const vector<T>& v)//��������  ���   v2(v1)    ��һ��д��
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
		//�ڶ��ֿ�������д��
		vector(const vector<T>& v)
			:_start(nullptr)      //�����ʼ��
			, _finish(nullptr)
			, _endofstorage(nullptr)
		{
			reserve(v.capacity());   //�����Ȱѿռ俪����
			for (const auto& e : v)
			{
				push_back(e);
			}
		} 
		//vector<T>& operator=(const vector<T>& v)   //��ֵ   ��һ�ִ�ͳд��
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
		vector<T>& operator=(vector<T> v)   //��ֵ()   �ڶ����ִ�д��  v1=v3
		{
		    swap(v);    //��Ҫ�ֽڵ���ȫ��swap()��ʵ�ֽ�������Ϊ�������ۼ����漰�������������Լ�ʵ��swap()�����������ȫ��swap()��ʵ��ָ��Ľ������ɡ�
			return *this;
		}
		void swap(vector<T>& v)   
		{
			std::swap(_start, _start);    //����ȫ�ֵ�swap()
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
					//memcpy(tmp, _start, sizeof(T) * size());//ע��:memcpy()Ҳ�ǰ��ֽڿ���������ǳ����.�����Զ���������T��string����ʱ���漰���ݿ���ʱ��Ҫ���������     
					for (size_t i = 0; i < size(); ++i)        //������ʹ��memcpy()��������Ҫʹ��T���͵�operator=��������ĸ�ֵ������
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
		T& operator[](size_t i)  //�ɶ���д
		{
			assert(i < size());
			return _start[i];
		}
		const T& operator[](size_t i)const  //ֻ��
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
		void push_back(const T& x)//��ֹT��������������ͣ����ٿ������죬����β�御��������
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
				//������ݣ�pos��������ʧЧ�ˡ��������¼���pos��λ��
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
		iterator _start;// ����ĵ�һ��λ��
		iterator _finish;//�������һ��Ԫ�ص���һ��λ��  _finish=_star+Ԫ�ظ���(size);
		iterator _endofstorage;//����  _endofstorage= _start+����(capacity);
	};
    
	template<class T>
	void vector_Print(const vector<T>& v)
	{
		//��һ��
		for (auto e : v)
		{
			std::cout << e << " ";
		}
		std::cout << std::endl;
		//�ڶ���
		//for (size_t i = 0; i < v.size(); ++i)
		//{
		//	std::cout << v[i] << " ";
		//}
		//std::cout << std::endl;
		////////������
		//vector<int>::const_iterator it = v.begin();
		//while (it != v.end())
		//{
		//	std::cout << *it << " ";
		//	++it;
		//}
		//std::cout << std::endl;
	}
}