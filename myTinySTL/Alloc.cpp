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
		char *chunk = chunk_alloc(n, nobjs);
		//1.���һ����
		if (nobjs == 1)
		{
			return chunk;
		}
		//2.��һ����Ͷ�,������free-list����
		obj *result = (obj*)chunk;
		obj *next_obj = (obj*)(chunk + n);
		obj *current_obj = next_obj;
		free_list[FREELIST_INDEX(n)] = current_obj;
		for (int i = 2; i <= nobjs; ++i)
		{
			if (i == nobjs)
			{
				current_obj->next_free_list = 0;
				break;
			}
			else
			{
				next_obj = (obj*)((char*)(next_obj)+n);
				current_obj->next_free_list = next_obj;
				current_obj = next_obj;
			}
		}
		return result;
	}

	char *alloc::chunk_alloc(size_t size, int &nobjs)
	{
		char *result;
		size_t total_bytes = size*nobjs;         //�����ܴ�С
		size_t bytes_left = end_free - start_free; //�ڴ����ʣ��ռ��С

		//1.>=�����ڴ�
		if (bytes_left >= total_bytes)
		{
			result = start_free;
			start_free += total_bytes;
			return result;
		}
		//2.>=һ����
		else if (bytes_left >= size)
		{
			nobjs = bytes_left / size;
			total_bytes = nobjs*size;
			result = start_free;
			start_free += total_bytes;
			return result;
		}
		//3.�ڴ����һ����Ĵ�С���޷��ṩ
		else
		{
			//��ʣ����ڴ�ؿռ�����free-list
			if (bytes_left>0)
			{
				int index = FREELIST_INDEX(bytes_left);
				((obj*)(start_free))->next_free_list = free_list[index];
				free_list[index] = (obj*)(start_free);
			}
			//����Ϊ�ڴ���������ڴ�
			size_t bytes_to_get = 2 * total_bytes + ROUND_UP(heap_size >> 4);
			start_free = static_cast<char*>(malloc(bytes_to_get));
			//��������ʧ��
			if (start_free == 0)
			{
				//��free-list�в鿴�Ƿ������������Ŀռ�
				for (int i = size; i <= _MAX_BYTES; i += -_ALIGN)
				{
					int index = FREELIST_INDEX(i);
					if (free_list[index] != 0)
					{
						start_free = (char*)(free_list[index]);
						free_list[index] = free_list[index]->next_free_list;
						end_free = start_free + i;
						return chunk_alloc(size, nobjs);
					}
				}
				end_free = 0;
				return nullptr;
			}
			//��������ɹ�
			else
			{
				heap_size += bytes_to_get;
				end_free = start_free + bytes_to_get;
				return chunk_alloc(size, nobjs);
			}
		}

	}
}