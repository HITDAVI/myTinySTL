#include "Alloc.h"

namespace myTinySTL{
	char * alloc::start_free = 0;
	char * alloc::end_free = 0;
	size_t alloc::heap_size = 0;
	alloc::obj * alloc::free_list[_NFREELISTS] = { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };

	//�ռ����ú���
	//�����ڴ�->����   ����->�ͷ��ڴ�
	//������������construct.h
	void * alloc::allocate(size_t n){
		//����128���ƽ���һ��������
		if (n > _MAX_BYTES){
			return malloc(n); //�൱�� ::operator new()
		}
		int index = FREELIST_INDEX(n);
		obj *result = free_list[index];
		if (result == 0){
			//û�ҵ�����freelist��׼���������freelist
			void *r = refill(ROUND_UP(n));
			return r;
		}
		else{
			//����freelist
			free_list[index] = result->next_free_list;
			return result;
		}
	}

	void alloc::deallocate(void *p, size_t n){
		//����128�黹����
		if (n > _MAX_BYTES){
			free(p);
			return;
		}
		//С��128�黹��freelist
		else{
			int index = FREELIST_INDEX(n);
			obj *q = static_cast<obj*> (p);
			q->next_free_list = free_list[index];
			free_list[index] = q;
		}
	}

	void * alloc::reallocate(void *p, size_t old_sz, size_t new_sz){
		deallocate(p, old_sz);
		p = allocate(new_sz);
		return p;
	}

	void * alloc::refill(size_t n){
		int nobjs = 20;
		//����ȡ��nobjs��������Ϊfreelist���½ڵ�
		char * chunk = chunk_alloc(n, nobjs);
		//
	}
}