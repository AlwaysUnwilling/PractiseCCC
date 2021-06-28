#pragma once
#include<string.h>
#include<assert.h>
#include<iostream>
namespace myString 
{
	class string
	{
	public:
		//迭代器
		typedef char* iterator;
		iterator begin()
		{
			return _str;
		}
		iterator end()
		{
			return _str + _size;
		}
		string(const char* str = "")  //构造函数
		{
			_size = strlen(str);
			_capacity = _size;
			_str = new char[_capacity + 1];
			strcpy(_str, str);
		}
		//string(const string& s)  //拷贝构造  s2(s1)   深拷贝
		//	:_str(new char[s._capacity + 1])
		//{
		//	strcpy(_str, s._str);
		//	_size = s._size;
		//	_capacity = s._capacity;
		//}
		string(const string& s)    //拷贝构造现代写法   深拷贝  :对于string tmp除了作用域调用析构函数时因为交换完成后 tmp._str其实已经是空指针了。
			:_str(nullptr)
		{
			//string tmp(s._str);
			string tmp(s);
			std::swap(_str, tmp._str);
		}
		//string& operator=(const string& s)       //s1=s2；赋值
		//{
		//	/*if (_str != s._str)*/
		//	if (this != &s)
		//	{
		//		if (_capacity < s._capacity)
		//		{
		//			char* tmp = new char[s._capacity + 1];
		//			delete[]_str;
		//			_str = tmp;
		//		}
		//		strcpy(_str, s._str);
		//		_size = s._size;
		//		_capacity = s._capacity;
		//	}
		//	return *this;
		//}
		string& operator=(const string& s)  //赋值现代写法
		{
			string tmp(s);
			std::swap(_str, tmp._str);
			return *this;
		}
		size_t size()const
		{
			return _size;
		}
		size_t capacity()const
		{
			return _capacity;
		}
		char& operator[](size_t i)
		{
			assert(i < _size);
			return _str[i];
		}
		const char& operator[](size_t i)const
		{
			assert(i < _size);
			return _str[i];
		}
		const char* c_str()
		{
			return _str;
		}
		void reserve(size_t n)
		{
			char* tmp = new char[n + 1];
			strcpy(tmp, _str);
			delete[] _str;
			_str = tmp;
		}
		void push_back(char ch)
		{
			if (_size == _capacity)
			{
				//std::cout << "new space" <<std::endl;
				size_t _newcapacity = _capacity == 0 ? 2 : 2 * _capacity;
				reserve(_newcapacity);
				_capacity = _newcapacity;
			}
			_str[_size] = ch;
			++_size;
			_str[_size] = '\0';   //有可能'\0'被覆盖掉，所以需要在末尾补上'\0'。
		}
		void append(const char* str)
		{
			size_t len = strlen(str);
			if (len + _size > _capacity)
			{
				size_t _newcapacity = len + _size;
				reserve(_newcapacity);
				_capacity = _newcapacity;
			}
			//for (size_t i = 0; i < n; i++)
			//{
			//	push_back(str[i]);
			//}
			//strcat(_str, str);
			strcpy(_str + _size, str);
			_size += len;
		}
		string& operator+=(const char* str)
		{
			append(str);
			return *this;
		}
		string& operator+=(char ch)
		{
			push_back(ch);
			return *this;
		}
		void insert(size_t pos, char ch)
		{
			assert(pos <= _size);
			if (_size == _capacity)
			{
				size_t _newcapacity = _capacity == 0 ? 2 : _capacity * 2;
				reserve(_newcapacity);
				_capacity = _newcapacity;
			}
			int end = _size;
			while (end-pos+1)
			{
				_str[end + 1] = _str[end];
				end--;
			}
			_str[pos] = ch;
			++_size;
		}
		void insert(size_t pos, const char* str)
		{
			assert(pos <= _size);
			size_t len = strlen(str);
			if (_size + len > _capacity)
			{
				size_t _newcapacity = _size + len;
				reserve(_newcapacity);
				_capacity = _newcapacity;
			}
			size_t end = _size;
			while (end-pos+1)
			{
				_str[end + len] = _str[end];
				end--;
			}
			//strncpy(_str + pos, str, len);
			size_t begin = pos;
			size_t i = 0;
			while (i<=len)
			{
				_str[begin++] = str[i++];
			}
			_size += len;
		}
		void resize(size_t n, char ch = '\0')
		{
			if (n < _size)
			{
				_str[n] = '\0';
				_size = n;
			}
			else
			{
				if (n > _capacity)
				{
					_capacity = n;
					reserve(_capacity);
				}
				for (size_t i = _size; i < n; ++i)
				{
					_str[i] = ch;
				}
				_size = n;
				_str[_size] = '\0';
			}
		}
		//void insert(size_t pos, const char* str)
		//{
		//	assert(pos < _size);
		//	size_t len = strlen(str);
		//	if (_size + len >_capacity)
		//	{
		//		_capacity = _capacity == 0 ? 2 : _capacity * 2;
		//		reserve(_capacity);
		//	}
		//	int end = _size;
		//	while (end >= pos)
		//	{
		//		_str[end + len] = _str[end];
		//		--end;
		//	}
		//	strncpy(_str + pos, str, len);
		//	_size += len;
		//	//return *this;
		//}


		void erase(size_t pos, size_t len = npos)
		{
			assert(pos < _size);
			if (_size - pos <= len)
			{
				_str[pos] = '\0';
				_size = pos;
			}
			else
			{
				int  begin = pos;
				while (begin + len <= _size)
				{
					_str[begin] = _str[begin + len];
					++begin;
				}
				_size -= len;
			}
		}
		size_t find(char ch, size_t pos = 0)
		{
			for (size_t i = pos; i < _size; ++i)
			{
				if (_str[i] == ch)
				{
					return i;
				}
			}
			return npos;
		}
		size_t find(const char* str, size_t pos = 0)
		{
			char* p=strstr(_str, str);
			if (p == nullptr)
			{
				return npos;
			}
			return p - _str;
		}
		bool operator>(const string& s)
		{
			return strcmp(_str, s._str) > 0;
		}
		bool operator>=(const string& s)
		{
			return *this > s || *this == s;
		}
		bool operator==(const string& s)
		{
			return strcmp(_str, s._str) == 0;
		}
		bool operator<(const string& s)
		{
			return !(*this >= s);
		}
		bool operator<=(const string& s)
		{
			return *this < s || *this == s;
		}
		bool operator!=(const string& s)
		{
			return !(*this == s);
		}
		~string()
		{
			delete[]_str;
			_str = nullptr;
			_size = _capacity = 0;
		}
	private:
		char* _str;
		size_t _size;//已经有多少个有效字符
		size_t _capacity;  //可以存多少个有效字符   '\0'不是有效字符
		static size_t npos;
	};
	size_t string::npos= -1;
	std::ostream& operator<< (std::ostream& out, const string& s)
	{
		for (size_t i = 0; i < s.size(); ++i)
		{
			std::cout << s[i];
		}
		return out;
	}
	std::istream& operator>> (std::istream& in, string& s)
	{
		while (1)
		{
			char ch;
			//ch = getchar();
			ch = in.get();
			if (ch == '\n')
				break;
			else
				s += ch;
		}
		return in;
	}
}

