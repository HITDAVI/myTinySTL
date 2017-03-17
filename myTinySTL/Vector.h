#ifndef _MYTINYSTL_VECTOR_H_
#define _MYTINYSTL_VECTOR_H_

#include "Algorithm.h"
#include "Allocator.h"
#include "Construct.h"
#include "Uninitialized.h"
#include "Iterator.h"
#include <iostream>
#include <initializer_list>

namespace myTinySTL{
	//空间配置器 alloc alloc.h 
	template<class T, class Alloc=alloc>
	class Vector{
	public:
		typedef T value_type;
		typedef T* pointer;
		typedef T* iterator;
		typedef T& reference;
		typedef const T* const_pointer;
		typedef size_t size_type;
		typedef ptrdiff_t difference_type;
	protected:
		//simple_alloc 是 allocator的空间配置器
		typedef simple_alloc<value_type, Alloc> data_allocator;
		//vector是连续空间，故指针可以起到迭代器的功能，且是一个random_access_iterator
		iterator start; //目前使用空间的头
		iterator finish; //目前使用空间的尾(前闭后开)
		iterator end_of_storage; //可用空间的尾
		
		void insert_aux(iterator position, const T& x);
		
		void deallocate(){
			if (start)
				//归还（end_of_storage - start）大小空间给start的地址
				data_allocator::deallocator(start, end_of_storage - start);
		}

		//分配n大小空间，并以x初始化
		iterator allocate_and_fill(size_type n, const T& x){
			//获取内存空间
			iterator result = data_allocator::allocate(n);
			//在获取的内存上创建对象
			unitialized_fill_n(result, n, x);
			return result;
		}

		//分配n大小空间，并以x初始化
		void fill_initialize(size_type n, const T& value){
			start = allocate_and_fill(n, value);
			finish = start + n;
			end_of_storage = finish;
		}
	public:
		iterator begin(){ return start; }
		iterator end(){ return finish; }
		size_type size() const{ return size_type(end() - begin()); }
		size_type capacity() const { return size_type(end_of_storage - begin()); }
		bool empty() const { return begin() == end(); }
		reference operator[](size_type n){ return *(begin() + n); }
		bool operator==(const vector& other) const {
			auto first1 = begin(), last1 = end();
			auto first2 = other.begin(), last2 = other.begin();
			for (; first1 != last1 && first2 != last2; ++first1, ++first2){
				if (*first1 != *first2)
					return false;
			}
			//return true;此处错。两个vector长度不一定相等
			return (first1 == last1 && first2 == last2);
		}

		vector() :start(0), finish(0), end_of_storage(0){ }
		vector(size_type n, const T& value){ fill_initialize(n, value); }
		vector(int n, const T& value){ fill_initialize(n, value); }
		vector(long n, const T& value){ fill_initialize(n, value); }
		//explicit关键字只对有一个参数的类构造函数有效
		//例外, 当除了第一个参数以外的其他参数都有默认值的时候, explicit关键字依然有效
		//意为可以 vector x(1),不可以vector x = 1；
		explicit vector(size_type n){ fill_initialize(n, T()); } 

		vector(const std::initializer_list<T> v){//C++11新特性，支持vector x = {a,b,c,...}
			auto start_v = v.begin();
			auto end_v = v.end();
			size_type n = v.size();
			fill_initialize(n, T());
			finish = myTinySTL::copy() //algorithm
		}
		
		~vector(){
			//析构->释放内存
			destroy(start, finish);//construct.h的全局函数
			deallocate();//vector的成员函数
		}

		reference front(){ return *begin(); }
		reference back(){ return *end(); }
		void push_back(const T& x){
			if (finish != end_of_storage){
				construct(finish, x);
				finish++;
			}
			else{
				insert_aux(end(), x);
			}
		}

		void pop_back(){
			--finish;
			destroy(finish);
		}

		iterator erase(iterator position){
			if (position + 1 != end())
				copy(position + 1, finish, position);
			finish--;
			destroy(finish);
			return position;
		}

		iterator erase(iterator start_erase, iterator end_erase){
			size_type erase_size = end_erase - start_erase;
			if (end_erase + 1 != end()){
				size_type left = finish - end_erase;
				copy(end_erase, finish, start_erase);
				destroy(start_erase+left, finish);
			}
			else{
				destroy(start_erase, finish);
			}
			finish = finish - erase_size;
			return start_erase;
		}

		void resize(size_type new_size, const T& x = T()){
			if (new_size < size())
				erase(begin() + new_size, end());
			else
				insert(end(), new_size - size(), x);
		}

		//void resize(size_type new_type){ resize(newsize, T()); }
		void clear(){ erase(begin(), end()); }

		void insert(iterator position, size_type n, const T& x);

	};

	template<class T, class Alloc>
	void Vector<T, Alloc>::insert(iterator position, size_type n, const T& x){
		//position位置插入n个元素，元素初始值为x
		T x_copy = x;
		if (n != 0){
			if (size_type(end_of_storage - finish) >= n){
				//备用空间够用
				//const size_type elema_after = finish - position;
				unitialized_fill_n(finish, n, x_copy);
				uninitialized_copy(position, finish, position + n);
				fill(position, position + n, x_copy);
				finish += n;
			}
			else{
				//不足以装下增加元素时，决定新长度：旧长度两倍或旧+新增个数
				const size_type old_size = size();
				const size_type new_size = old_size + max(old_size, n);
				//配置新的vector空间
				iterator new_start = data_allocator::allocate(new_size);
				if (!new_start){
					std::cout << "out of memory" << endl;
					return;
				}
				iterator new_finish = new_start;
				try{
					new_finish = uninitialized_copy(strat, position, new_start);
					new_finish = unitialized_fill_n(new_finish, n, x);
					new_finish = uninitialized_copy(position, finish, new_finish);
				}
				catch (...){
					//若出现异常，抛出异常，回滚
					destroy(new_start, new_finish);//发生异常时，new_finish已经配置了一段，把这段destroy掉
					data_allocator::deallocate(new_start, new_size);
					throw;
				}
				//清除释放旧的vector
				destroy(start, finish);
				deallocate();//成员函数
				//调整标记
				start = new_start;
				finish = new_finish;
				end_of_storage = new_start + new_size;
			}
		}
	}

	template<class T, class Alloc>
	void Vector<T, Alloc>::insert_aux(iterator position, const T& x){
		if (finish != end_of_storage){
			construct(finish, *(finish - 1));
			++finish;
			T x_copy = x;
			copy_backward(position, finish - 2, finish - 1);
			*position = x_copy;
		}
		else{
			const size_type old_size = size();
			const size_type new_size = old_size != 0 ? 2 * old_size : 1;

			iterator new_start = data_allocator::allocate(new_size);
			iterator old_size = new_start;
			try{
				new_finish = uninitialized_copy(start, position, new_start);
				construct(new_finish, x);
				++new_finish;
				new_finish = uninitialized_copy(position, finish, new_finish);
			}
			catch (...){
				destroy(new_start, new_finish);
				data_allocator::deallocate(new_start, new_size);
				throw;
			}
			destroy(begin(), end());
			deallocate();
			start = new_start;
			finish = new_finish;
			end_of_storage = new_start + new_size;
		}
	}
}

#endif