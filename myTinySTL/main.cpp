#include "jjalloc.h"
#include <vector>
#include <iostream>

using namespace std;

template<class T>
struct  MyIter{
	typedef T value_type;
	T* ptr;
	MyIter(T* p = 0) :ptr(p){ }
	T& operator*() const { return *ptr; }
};

template<class I>
typename I::value_type func(I ite){ return *ite; }
int main(){
	/*
	int ia[5] = { 1, 2, 3, 4, 5 };
	unsigned int i;
	vector<int, JJ::allocator<int> > iv(ia, ia + 4);
	for (i = 0; i < iv.size(); i++)
		cout << iv[i] << " ";
	cout << endl;
	*/
	MyIter<int> ite(new int(8));
	cout << func(ite) << endl;
	system("pause");
}