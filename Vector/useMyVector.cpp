#include<iostream>
#include"MyVector.h"
using namespace std;
int main()
{
	MyVector<int> arr;
	arr.push_back(67);
	arr.push_back(123);
	arr.push_back(45);
	arr.push_back(21);
	arr.push_back(56);
	arr.push_back(78);
	arr.print();
	cout << endl;
	arr.sort();
	cout << "ÅÅÐòÖ®ºó" << endl;
	arr.print();
	return 0;
}