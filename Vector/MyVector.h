/*���ļ�Ϊ�Զ���ļ�ª��Vectorģ��,��д�����л�������뷨,������������ʱ��δ��ʵ��
Ҳ�ڱ�д�Ĺ����и��ܵ���debug�Ŀ���*/
#ifndef MYVECTOR_H_
#define MYVECTOR_H_
#include<iostream>
#include<vector>
using namespace std;

//����Ϊ�ռ��������Ķ���,��STL�еĶ�����ͬ,�����¶�����deallocate()
template<typename Type>
struct Allocator
{
	Type* allocate(size_t size) // �����ڴ�
	{
		return (Type*)malloc(sizeof(Type) * size);
	}
	void deallocate(Type* p) // �ͷ��ڴ�
	{
		free(p);
		p = nullptr;
	}
	void construct(Type* p,const Type& val) // �������
	{
		new (p) Type(val); 
	}
	void destroy(Type* p) // �ͷŶ���
	{
		p->~Type(); 
	}
};

//ģ��������

template<typename Type,typename Alloc = Allocator<Type>>
class MyVector 
{
private:
	Type* vec_first;
	Type* vec_last;
	Type* vec_end;
	Alloc v_alloc;
public:
	
	MyVector(int size = 10)//���캯��
	{
		vec_first = v_alloc.allocate(size);
		vec_last = vec_first;
		vec_end = vec_first + size;
		
	}
	
	~MyVector()//��������
	{
		for (Type* i = vec_first; i != vec_last; i++)
		{
			v_alloc.destroy(i);
		}
		v_alloc.deallocate(vec_first);
		vec_first = vec_last = vec_end = nullptr;
	}

	MyVector(const MyVector<Type>& rhs) //���ƹ��캯��
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
	//��ĳ����������
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
	
	Type & operator[](int index) const //��������[]��
	{
		if (index < size())
			return vec_first[index];
	}

	void erase(Type val)//ɾ��ָ��ֵ
	{
		if (isempty())
			cout << "������,û���κ�ֵ!" << endl;
		int index = find(val);
		int max = size();
		v_alloc.destroy(vec_first+index);//
		for (int i = index; i < max-1; i++)
		{
			vec_first[i] = vec_first[i + 1];
		}
		cout << "��ɾ��" << val << "�����" << endl;
	}


	void clear()//ɾ����������
	{
		if (vec_first)
			v_alloc.deallocate(vec_first);
		vec_first = vec_last = nullptr;
	}


	MyVector<Type> & operator=(MyVector<Type>& rhs)//���ظ�ֵ�����
	{
		if (this == &rhs)
		{
			cout << "��Ч�ĸ�ֵ";
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
	
	//����Ϊʵ�ֲ����ķ���
public:
	void resize() //����
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

	bool isempty()const //�ж��Ƿ�Ϊ��
	{
		return vec_first == vec_last;
	}

	bool isfull()const //�ж��Ƿ�����
	{
		return vec_last == vec_end;
	}

	int size()const //���������С
	{
		return vec_last - vec_first;
	}

	void push_back(const Type& val) //�ӱ����������
	{
		if (isfull())
			resize();
		v_alloc.construct(vec_last, val);
		vec_last++;
	}

	void push_front(const Type& val);//��ǰ���������

	Type back() const//�������һ��ֵ
	{
		cout <<"���һ����Ϊ: "<< *(vec_last - 1) << endl;
		return *(vec_last - 1);
	}

	Type pop_back()//ɾ�����һ������
	{
		if (isempty())
			return 0;
		Type value = *vec_last;
		vec_last--;
		v_alloc.destroy(vec_last);
		return value;
	}

	void sort()//ѡ������,��Ȼ����ʹ�ÿ�������,����������������
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

	int find(Type val)//����ָ��Ԫ��,����������
	{
		int size = this->size();
		int i;
		for ( i = 0; i < size; i++)
		{
			if (vec_first[i] == val)
			{
				cout << "�ҵ�����,��������Ϊ:" << i << endl;
				return i;
			}
		}
		cout << "û�������" << endl;
		return -1;
	}

	void print()  //���δ�ӡ
	{
		int n = this->size();
		for ( int i = 0; i < n; i++)
		{
			cout << vec_first[i] << " ";
		}
	}


};

#endif 
/*�����Ľ�֮��*/