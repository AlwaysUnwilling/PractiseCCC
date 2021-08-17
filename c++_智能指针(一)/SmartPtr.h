#pragma once
#include<thread>
#include<mutex>

template<class T>
class SmartPtr
{
public:
	SmartPtr(const char* ptr)
		:_ptr(ptr)
	{}
	T& operator*()
	{
		return *_ptr;
	}
	T* operator->()
	{
		return _ptr;
	}
	~SmartPtr()
	{
		if (_ptr)
		{
			cout << "delete:" << _ptr << endl;
			delete _ptr;
		}
	}
private:
	T* _ptr;
};

//简化版 智能指针
namespace my_SmartPtr
{
	//c++98 auto_ptr<T> 管理权转移  auto_ptr<T>   早期设计权限，现在不容许使用
	//缺陷：在ap1=ap2；这种场景下，ap2赋值完成后就变为空指针，如果不熟悉它的特性，继续访问ap2就会造成错误。
	template<class T>
	class auto_ptr
	{
	public:
		auto_ptr(T* ptr)
			:_ptr(ptr)
		{}
		auto_ptr(auto_ptr<T>& ap)
			:_ptr(ap._ptr)
		{
			ap._ptr = nullptr;
		}
		//ap1 = ap2;
		T& operator=(const auto_ptr<T>& ap)
		{
			if (*this != ap)
			{
				if (_ptr)
				{
					delete _ptr;
					_ptr = ap._ptr;
					ap._ptr = nullptr;
				}
			}
			return *this;
		}
		T& operator*()
		{
			return *_ptr;
		}
		T* operator->()
		{
			return _ptr;
		}
		~auto_ptr()
		{
			if (_ptr)
			{
				cout << "delete:" << _ptr << endl;
				delete _ptr;
				_ptr = nullptr;
			}
		}
	private:
		T* _ptr;
	};

	//c++11 unique_ptr 防拷贝 推荐使用
	//缺陷：如果有需要拷贝的场景，就无法使用
	template<class T>
	class unique_ptr
	{
	public:
		unique_ptr( T* ptr)
			:_ptr(ptr)
		{}
		unique_ptr(unique_ptr<T>& up) = delete;
		unique_ptr<T>& operator=(const unique_ptr<T>& up) = delete;
		T& operator*()
		{
			return *_ptr;
		}
		T* operator->()
		{
			return _ptr;
		}
		~unique_ptr()
		{
			if (_ptr)
			{
				cout << "delete:" << _ptr << endl;
				delete _ptr;
				_ptr = nullptr;
			}
		}
	private:
		T* _ptr;
	};

	//c++11 shared_ptr 共享指针(引用计数)
	//引用计数，可以拷贝
	//缺陷：循环引用
	template<class T>
	class shared_ptr
	{
	public:
		shared_ptr(T* ptr = nullptr)
			:_ptr(ptr)
			,_pcount(new int(1))
			,_pmtx(new mutex)
		{}
		shared_ptr(const shared_ptr<T>& sp)
			:_ptr(sp._ptr)
			, _pcount(sp._pcount)
			,_pmtx(sp._pmtx)
		{
			//++(*_pcount);
			add_ref_count();
		}
		//sp1=sp2;
		shared_ptr<T>& operator=(const shared_ptr<T>& sp)
		{
			if (this != &sp)
			{
				//释放sp1的原有管理权
				//if (--(*_pcount) == 0)
				//{
				//	delete _pcount;
				//	delete _ptr;
				//}
				release();
				_ptr = sp._ptr;
				_pcount = sp._pcount;
				_pmtx = sp._pmtx;
				//++(*_pcount);
				add_ref_count();
			}
			return *this;
		}
		void add_ref_count()
		{
			_pmtx->lock();
			++(*_pcount);
			_pmtx->unlock();
		}
		void release()
		{
			_pmtx->lock();
			bool flag = false;
			if (--(*_pcount) == 0 && _ptr)
			{
				cout << "delete:" << _ptr << endl;
				delete _ptr;
				_ptr = nullptr;
				delete _pcount;
				_pcount = nullptr;
				flag = true;
			}
			_pmtx->unlock();
			if (flag == true)
			{
				delete _pmtx;
				_pmtx = nullptr;
			}
		}
		T* get_ptr()const
		{
			return _ptr;
		}
		int use_count()
		{
			return *_pcount;
		}
		T& operator*()
		{
			return *_ptr;
		}
		T* operator->()
		{
			return _ptr;
		}
		~shared_ptr()
		{
			//if (--(*_pcount)==0 && _ptr)
			//{
			//	cout << "delete:" << _ptr << endl;
			//	delete _ptr;
			//	_ptr = nullptr;
			//	delete _pcount;
			//	_pcount = nullptr;
			//}
			release();
		}
	private:
		T* _ptr;
		int* _pcount;//记录共享管理资源的对象个数，最后一个析构释放资源
		mutex* _pmtx; 
	};
   //严格来说weak_ptr不是智能指针，因为它没有RAII资源管理机制
   //专门解决shared_ptr的循环引用问题
	template<class T>
	class weak_ptr
	{
	public:
		weak_ptr() = default;
		weak_ptr(const shared_ptr<T>& sp)
			:_ptr(sp.get_ptr())
		{}
		weak_ptr<T>& operator=(const shared_ptr<T>& sp)
		{
			_ptr = sp.get_ptr();
			return *this;
		}
		T& operator*()
		{
			return *_ptr;
		}
		T* operator->()
		{
			return _ptr;
		}
	private:
		T* _ptr;
	};
}