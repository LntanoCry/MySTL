/*该文件为自定义的简陋版Vector模板,编写过程中还有许多想法,但迫于能力和时间未能实现
也在编写的过程中感受到了debug的快乐*/
#ifndef MYVECTOR_H_
#define MYVECTOR_H_
#include<iostream>
#include<vector>
using namespace std;

//下面为空间配置器的定义,与STL中的定义相同,仅重新定义了deallocate()
template<typename Type>
struct Allocator
{
	Type* allocate(size_t size) // 开辟内存
	{
		return (Type*)malloc(sizeof(Type) * size);
	}
	void deallocate(Type* p) // 释放内存
	{
		free(p);
		p = nullptr;
	}
	void construct(Type* p,const Type& val) // 构造对象
	{
		new (p) Type(val); 
	}
	void destroy(Type* p) // 释放对象
	{
		p->~Type(); 
	}
};

//模板类声明

template<typename Type,typename Alloc = Allocator<Type>>
class MyVector 
{
private:
	Type* vec_first;
	Type* vec_last;
	Type* vec_end;
	Alloc v_alloc;
public:
	
	MyVector(int size = 10)//构造函数
	{
		vec_first = v_alloc.allocate(size);
		vec_last = vec_first;
		vec_end = vec_first + size;
		
	}
	
	~MyVector()//析构函数
	{
		for (Type* i = vec_first; i != vec_last; i++)
		{
			v_alloc.destroy(i);
		}
		v_alloc.deallocate(vec_first);
		vec_first = vec_last = vec_end = nullptr;
	}

	MyVector(const MyVector<Type>& rhs) //复制构造函数
	{
		int len = rhs.vec_last - rhs.vec_first;
		int size = rhs.vec_end - rhs.vec_first;
		*this.vec_first = v_alloc.allocate(size);
		for (Type* i = rhs.vec_first; i != rhs.vec_last; i++)
		{
			v_alloc.construct(*this.vec_first + i, rhs.vec_first[i]);
		}
		*this.vec_last = *this.vec_first + len;
		*this.vec_end = *this.vec_first + size;
	}
	//从某处插入数据
	void insert(int index,Type val) 
	{
		if (isfull())
			resize();
		int max = size();
		int i;
		for ( i = max; i > index; i--)
		{
			vec_first[i] = vec_first[i - 1];
		}
		vec_first[i] = val;
		vec_last++;
	}
	
	Type & operator[](int index) const //重载数组[]符
	{
		if (index < size())
			return vec_first[index];
	}

	void erase(Type val)//删除指定值
	{
		if (isempty())
			cout << "空数组,没有任何值!" << endl;
		int index = find(val);
		int max = size();
		v_alloc.destroy(vec_first+index);//
		for (int i = index; i < max-1; i++)
		{
			vec_first[i] = vec_first[i + 1];
		}
		cout << "已删除" << val << "这个数" << endl;
	}


	void clear()//删除整个数组
	{
		if (vec_first)
			v_alloc.deallocate(vec_first);
		vec_first = vec_last = nullptr;
	}


	MyVector<Type> & operator=(MyVector<Type>& rhs)//重载赋值运算符
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
			v_alloc.construct(*this.vec_first + i, rhs.vec_first[i]);
		}
		*this.vec_last = *this.vec_first + len;
		*this.vec_end = *this.vec_first + size;

		return *this;
	}
	
	//以下为实现操作的方法
public:
	void resize() //扩容
	{
		int size = vec_end - vec_first;
		Type* newvec = v_alloc.allocate(size * 2);
		for (int i = 0; i < size; i++)
		{
			v_alloc.construct(newvec, vec_first[i]);
		}
		for (Type* i = vec_first; i != vec_last; i++)
		{
			v_alloc.destroy(i);
		}
		v_alloc.deallocate(vec_first);
		vec_first = newvec;
		vec_last = vec_first + size;
		vec_end = vec_first + size * 2;
	}

	bool isempty()const //判断是否为空
	{
		return vec_first == vec_last;
	}

	bool isfull()const //判断是否已满
	{
		return vec_last == vec_end;
	}

	int size()const //返回数组大小
	{
		return vec_last - vec_first;
	}

	void push_back(const Type& val) //从背后插入数据
	{
		if (isfull())
			resize();
		v_alloc.construct(vec_last, val);
		vec_last++;
	}

	void push_front(const Type& val);//从前面插入数据

	Type back() const//返回最后一个值
	{
		cout <<"最后一个数为: "<< *(vec_last - 1) << endl;
		return *(vec_last - 1);
	}

	Type pop_back()//删除最后一个数据
	{
		if (isempty())
			return 0;
		Type value = *vec_last;
		vec_last--;
		v_alloc.destroy(vec_last);
		return value;
	}

	void sort()//选择排序,虽然可以使用快速排序,但需引用两个参数
	{
		int n = size();
		for (int i = 0; i < n; i++)
		{
			int min = i;
			for (int j = i + 1; j < n; j++)
			{
				if (vec_first[j] < vec_first[min])
					min = j;
			}
			if (i != min)
			{
				swap(vec_first[i], vec_first[min]);
			}
		}
	}

	int find(Type val)//查找指定元素,并返回索引
	{
		int size = this->size();
		int i;
		for ( i = 0; i < size; i++)
		{
			if (vec_first[i] == val)
			{
				cout << "找到该数,它的索引为:" << i << endl;
				return i;
			}
		}
		cout << "没有这个数" << endl;
		return -1;
	}

	void print()  //依次打印
	{
		int n = this->size();
		for ( int i = 0; i < n; i++)
		{
			cout << vec_first[i] << " ";
		}
	}


};

#endif 
/*持续改进之中*/