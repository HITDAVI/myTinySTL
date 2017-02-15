#ifndef _MYTINYSTL_ALLOC_H_
#define _MYTINYSTL_ALLOC_H_

#include <cstdlib>

namespace myTinySTL{
	class alloc{
	private:
		enum {_ALIGN = 8}; //小型区块上调边界
		enum {_MAX_BYTES = 128}; //小型区块的上限
		enum {_NFREELISTS = _MAX_BYTES / _ALIGN}; //free lists 个数

	private:
		//free list
		//用union避免了为了维护list指针的内存耗费
		union obj{
			union obj * next_free_list;
			char client_data[1];
		};
		static obj *free_list[_NFREELISTS];

	private:
		//内存池分配情况
		static char *start_free; //内存池起始位置
		static char *end_free; //内存池结束位置
		static size_t heap_size;

	private:
		//将bytes上调至8倍数
		static size_t ROUND_UP(size_t bytes){
			return ((bytes + _ALIGN-1) & ~(_ALIGN-1));
		}
		//free list 索引,根据区块大小，决定使用第n号freelist
		static size_t FREELIST_INDEX(size_t bytes){
			return ((bytes+_ALIGN - 1) / _ALIGN - 1);
		}
		//freelist某个槽中没有可用空间时，从内存池中获取空间
		static void *refill(size_t n);
		//从内存池中获取空间
		static char *chunk_alloc(size_t size, int &nobjs);

	public:
		static void *allocate(size_t n);
		static void deallocate(void *p, size_t n);
		static void *reallocate(void *p, size_t old_sz, size_t new_sz);
	};
}

#endif