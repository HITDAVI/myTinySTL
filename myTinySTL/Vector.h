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
	//�ռ������� alloc alloc.h 
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
		//simple_alloc �� allocator�Ŀռ�������
		typedef simple_alloc<value_type, Alloc> data_allocator;
		//vector�������ռ䣬��ָ������𵽵������Ĺ��ܣ�����һ��random_access_iterator
		iterator start; //Ŀǰʹ�ÿռ��ͷ
		iterator finish; //Ŀǰʹ�ÿռ��β(ǰ�պ�)
		iterator end_of_storage; //���ÿռ��β
		
		void insert_aux(iterator position, const T& x);
		
		void deallocate(){
			if (start)
				//�黹��end_of_storage - start����С�ռ��start�ĵ�ַ
				data_allocator::deallocator(start, end_of_storage - start);
		}

		//����n��С�ռ䣬����x��ʼ��
		iterator allocate_and_fill(size_type n, const T& x){
			//��ȡ�ڴ�ռ�
			iterator result = data_allocator::allocate(n);
			//�ڻ�ȡ���ڴ��ϴ�������
			unitialized_fill_n(result, n, x);
			return result;
		}

		//����n��С�ռ䣬����x��ʼ��
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
			//return true;�˴�������vector���Ȳ�һ�����
			return (first1 == last1 && first2 == last2);
		}

		vector() :start(0), finish(0), end_of_storage(0){ }
		vector(size_type n, const T& value){ fill_initialize(n, value); }
		vector(int n, const T& value){ fill_initialize(n, value); }
		vector(long n, const T& value){ fill_initialize(n, value); }
		//explicit�ؼ���ֻ����һ���������๹�캯����Ч
		//����, �����˵�һ�����������������������Ĭ��ֵ��ʱ��, explicit�ؼ�����Ȼ��Ч
		//��Ϊ���� vector x(1),������vector x = 1��
		explicit vector(size_type n){ fill_initialize(n, T()); } 

		vector(const std::initializer_list<T> v){//C++11�����ԣ�֧��vector x = {a,b,c,...}
			auto start_v = v.begin();
			auto end_v = v.end();
			size_type n = v.size();
			fill_initialize(n, T());
			finish = myTinySTL::copy() //algorithm
		}
		
		~vector(){
			//����->�ͷ��ڴ�
			destroy(start, finish);//construct.h��ȫ�ֺ���
			deallocate();//vector�ĳ�Ա����
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
		//positionλ�ò���n��Ԫ�أ�Ԫ�س�ʼֵΪx
		T x_copy = x;
		if (n != 0){
			if (size_type(end_of_storage - finish) >= n){
				//���ÿռ乻��
				//const size_type elema_after = finish - position;
				unitialized_fill_n(finish, n, x_copy);
				uninitialized_copy(position, finish, position + n);
				fill(position, position + n, x_copy);
				finish += n;
			}
			else{
				//������װ������Ԫ��ʱ�������³��ȣ��ɳ����������+��������
				const size_type old_size = size();
				const size_type new_size = old_size + max(old_size, n);
				//�����µ�vector�ռ�
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
					//�������쳣���׳��쳣���ع�
					destroy(new_start, new_finish);//�����쳣ʱ��new_finish�Ѿ�������һ�Σ������destroy��
					data_allocator::deallocate(new_start, new_size);
					throw;
				}
				//����ͷžɵ�vector
				destroy(start, finish);
				deallocate();//��Ա����
				//�������
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