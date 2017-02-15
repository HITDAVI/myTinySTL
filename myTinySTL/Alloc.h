#ifndef _MYTINYSTL_ALLOC_H_
#define _MYTINYSTL_ALLOC_H_

#include <cstdlib>

namespace myTinySTL{
	class alloc{
	private:
		enum {_ALIGN = 8}; //С�������ϵ��߽�
		enum {_MAX_BYTES = 128}; //С�����������
		enum {_NFREELISTS = _MAX_BYTES / _ALIGN}; //free lists ����

	private:
		//free list
		//��union������Ϊ��ά��listָ����ڴ�ķ�
		union obj{
			union obj * next_free_list;
			char client_data[1];
		};
		static obj *free_list[_NFREELISTS];

	private:
		//�ڴ�ط������
		static char *start_free; //�ڴ����ʼλ��
		static char *end_free; //�ڴ�ؽ���λ��
		static size_t heap_size;

	private:
		//��bytes�ϵ���8����
		static size_t ROUND_UP(size_t bytes){
			return ((bytes + _ALIGN-1) & ~(_ALIGN-1));
		}
		//free list ����,���������С������ʹ�õ�n��freelist
		static size_t FREELIST_INDEX(size_t bytes){
			return ((bytes+_ALIGN - 1) / _ALIGN - 1);
		}
		//freelistĳ������û�п��ÿռ�ʱ�����ڴ���л�ȡ�ռ�
		static void *refill(size_t n);
		//���ڴ���л�ȡ�ռ�
		static char *chunk_alloc(size_t size, int &nobjs);

	public:
		static void *allocate(size_t n);
		static void deallocate(void *p, size_t n);
		static void *reallocate(void *p, size_t old_sz, size_t new_sz);
	};
}

#endif