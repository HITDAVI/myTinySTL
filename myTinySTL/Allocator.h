#ifndef _MYTINYSTL_ALLOCATOR_H_
#define _MYTINYSTL_ALLOCATOR_H_

#include "Alloc.h"
#include "Construct.h"

#include <cassert>
#include <new>

namespace myTinySTL{
	template<class T, class Alloc>
	class simple_alloc{
	public:
		//静态成员函数，绑定类，非对象
		static T *allocate(size_t n){
			return 0 == n ? 0 : (T*)alloc::allocate(n * sizeof(T));
		}

		static T *allocate(void){
			return (T*)alloc::allocate(sizeof(T));
		}

		static void deallocate(T *p, size_t n){
			if (n != 0)
				alloc::deallocate(p, n * sizeof(T));
		}

		static void deallocate(T *p){
			alloc::deallocate(p, sizeof(T));
		}
	};
}

#endif