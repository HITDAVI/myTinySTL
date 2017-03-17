#ifndef _MYTINYSTL_UNINITIALIZED_H_
#define _MYTINYSTL_UNINITIALIZED_H_

#include "Algorithm.h"
#include "TypeTraits.h"
#include "Construct.h"
#include "Iterator.h"

namespace myTinySTL{
	//未初始化的拷贝，在已获得的内存上创建一些元素
	//POD版本与非POD版本的未初始化拷贝
	
	//将[first, last)区间的数据copy到dest开始的内存中
	//根据数据类型不同（POD）做不同的拷贝策略
	//并添加const char* 和const w_char_t* 两种特化版本?待续
	template<class InputIterator, class ForwardIterator>
	ForwardIterator _uninitialized_copy_aux(InputIterator first, InputIterator last,
		ForwardIterator dest, _true_type){
		memcpy(dest, first, (last - first) * sizeof(*first));
		return dest + (last - first);
	}

	template<class InputIterator, class ForwardIterator>
	ForwardIterator _uninitialized_copy_aux(InputIterator first, InputIterator last,
		ForwardIterator dest, _false_type){
		int i = 0;
		for (; first != last; ++first, ++i){
			construct((dest + i), *first); //construct.h中
		}
		return (dest + i);
	}
	
	//如果目标区间是未初始化的，应该用uninitialized_copy， 否则用copy
	template<class InputIterator, class ForwardIterator, class T>
	ForwardIterator uninitialized_copy(InputIterator first, InputIterator last,
		ForwardIterator dest){
		//用iterator_traits<>得到迭代器的数据类型T，再用_type_traits得到T是否为POD
		typedef typename _type_traits<iterator_traits<first>::value_type>::is_POD_type isPOD;
		return _uninitialized_copy_aux(first, last, dest, is_POD());
	}

	//-----------------未初始化的copy，以某一特定值初始化-----------------------------
	template<class ForwardIterator, class T>
	void _unitialized_fill_aux(ForwardIterator first, ForwardIterator last, const T& value, _true_type){
		myTinySTL::fill(first, last, value);
	}

	template<class ForwardIterator, class T>
	void _unitialized_fill_aux(ForwardIterator first, ForwardIterator last, const T& value, _false_type){
		for (; first != last; ++first)
			construct(first, value);
	}

	template<class ForwardIterator, class T>
	void unitialized_fill(ForwardIterator first, const T& value){
		typedef _type_traits<T>::is_POD_type isPOD;
		_unitialized_fill_aux(first, last, value, isPOD());
	}

	//-----------------未初始化的copy，以某一特定数量n初始化-----------------------------
	template<class ForwardIterator, class Size, class T>
	ForwardIterator _unitialized_fill_n_aux(ForwardIterator first, Size n, const T& value, _true_type){
		return fill_n(first, n, x);
	}

	template<class ForwardIterator, class Size, class T>
	ForwardIterator _unitialized_fill_n_aux(ForwardIterator first, Size n, const T& value, _false_type){
		int i = 0;
		for (; i != n; ++i){
			construct((T*)(first + i), x); //地址+value
		}
		return (first + i);
	}

	template<class ForwardIterator, class Size, class T>
	inline ForwardIterator unitialized_fill_n(ForwardIterator first, Size n, const T& value){
		typedef _type_traits<T>::::is_POD_type isPOD;
		_unitialized_fill_n_aux(first, n, value, isPOD());
	}
}

#endif