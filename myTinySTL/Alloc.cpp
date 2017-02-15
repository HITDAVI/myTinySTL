#include "Alloc.h"

namespace myTinySTL{
	char * alloc::start_free = 0;
	char * alloc::end_free = 0;
	size_t alloc::heap_size = 0;
	alloc::obj * alloc::free_list[_NFREELISTS] = { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };

	//空间配置函数
	//配置内存->构造   析构->释放内存
	//构造与析构在construct.h
	void * alloc::allocate(size_t n){
		//大于128，移交第一级配置器
		if (n > _MAX_BYTES){
			return malloc(n); //相当于 ::operator new()
		}
		int index = FREELIST_INDEX(n);
		obj *result = free_list[index];
		if (result == 0){
			//没找到可用freelist，准备重新填充freelist
			void *r = refill(ROUND_UP(n));
			return r;
		}
		else{
			//调整freelist
			free_list[index] = result->next_free_list;
			return result;
		}
	}

	void alloc::deallocate(void *p, size_t n){
		//大于128归还给堆
		if (n > _MAX_BYTES){
			free(p);
			return;
		}
		//小于128归还给freelist
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
		//尝试取得nobjs个区块作为freelist的新节点
		char * chunk = chunk_alloc(n, nobjs);
		//
	}
}