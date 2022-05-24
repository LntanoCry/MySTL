/*
#include<iostream>
#include"MyVector.h"
using namespace std;


	template<typename Type, typename Alloc = Allocator<Type>>
	 MyVector<Type>::resize()
	{
		int size = vec_end - vec_first;
		Type* newvec = v_alloc.allocate(size * 2);
		for (Type* i = vec_first; i != vec_last; i++)
		{
			v_alloc.construct(newvec, vec_first[i]);
			v_alloc.destroy(i);
		}
		v_alloc.deallocate(vec_first);
		vec_first = newvec;
		vec_last = vec_first + size;
		vec_end = vec_first + size * 2;
	}
	template<typename Type, typename Alloc = Allocator<Type>>
	MyVector<Type>& MyVector::operator=(MyVector<Type>&rhs)//重载赋值运算符
	{
		if (this == &rhs)
		{
			cout << "无效的赋值";
			return *this;
		}
		for (Type* i = vec_first; i != vec_last; i++)
		{
			v_alloc.destroy(i);
		}
		v_alloc.deallocate(rhs.vec_first);

		int len = rhs.vec_last - rhs.vec_first;
		int size = rhs.vec_end - rhs.vec_first;
		*this.vec_first = v_alloc.allocate(size);
		for (Type* i = rhs.vec_first; i != rhs.vec_last; i++)
		{
			v_alloc.construct(*this.vec_first + i, rhs.vec_first[i])
		}
		*this.vec_last = *this.vec_first + len;
		*this.vec_end = *this.vec_first + size;

		return *this;
	}
	template<typename Type, typename Alloc = Allocator<Type>>
	bool MyVector::isfull()const
	{
		return vec_last == vec_end;
	}
	template<typename Type, typename Alloc = Allocator<Type>>
	bool MyVector::isempty()const
	{
		return vec_first == vec_last;
	}
	template<typename Type, typename Alloc = Allocator<Type>>
	int MyVector::size()const
	{
		return vec_last - vec_first;
	}
	template<typename Type, typename Alloc = Allocator<Type>>
	void MyVector::push_back(const Type & val)
	{
		if (isfull())
			resize();
		v_alloc.construct(vec_last, val);
		vec_last++;
	}
	template<typename Type, typename Alloc = Allocator<Type>>
	Type MyVector::pop_back()
	{
		if (isempty())
			return;
		Type value = *vec_last;
		vec_last--;
		v_alloc.destroy(vec_last);
		return value;
	}
	template<typename Type, typename Alloc = Allocator<Type>>
	int MyVector::find(Type val)//查找指定元素
	{
		for (Type* i = vec_first; i != vec_last; i++)
		{
			if (vec_first[i] == val)
				return i;
		}
		cout << "没有这个数" << endl;
		return 0;
	}
	template<typename Type, typename Alloc = Allocator<Type>>
	void MyVector::sort(MyVector<Type>&rhs)
	{
		int n = size();
		for (int i = 0; i < n; i++)
		{
			int min = i;
			for (int j = i + 1; j < n; j++)
			{
				if (vec_firsr[j] < vec_first[min])
					min = j;
			}
			if (i != min)
			{
				swap(vec_first[i], vec_first[min]);
			}
		}
	}
	template<typename Type, typename Alloc = Allocator<Type>>
	void print()  //依次打印
	{
		for (Type* i = vec_first; i != vec_last; i++)
		{
			cout << vec_first[i] << endl;
		}
	}
	*/




