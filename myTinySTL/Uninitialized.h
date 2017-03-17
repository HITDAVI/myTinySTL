#ifndef _MYTINYSTL_UNINITIALIZED_H_
#define _MYTINYSTL_UNINITIALIZED_H_

#include "Algorithm.h"
#include "TypeTraits.h"
#include "Construct.h"
#include "Iterator.h"

namespace myTinySTL{
	//δ��ʼ���Ŀ��������ѻ�õ��ڴ��ϴ���һЩԪ��
	//POD�汾���POD�汾��δ��ʼ������
	
	//��[first, last)���������copy��dest��ʼ���ڴ���
	//�����������Ͳ�ͬ��POD������ͬ�Ŀ�������
	//�����const char* ��const w_char_t* �����ػ��汾?����
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
			construct((dest + i), *first); //construct.h��
		}
		return (dest + i);
	}
	
	//���Ŀ��������δ��ʼ���ģ�Ӧ����uninitialized_copy�� ������copy
	template<class InputIterator, class ForwardIterator, class T>
	ForwardIterator uninitialized_copy(InputIterator first, InputIterator last,
		ForwardIterator dest){
		//��iterator_traits<>�õ�����������������T������_type_traits�õ�T�Ƿ�ΪPOD
		typedef typename _type_traits<iterator_traits<first>::value_type>::is_POD_type isPOD;
		return _uninitialized_copy_aux(first, last, dest, is_POD());
	}

	//-----------------δ��ʼ����copy����ĳһ�ض�ֵ��ʼ��-----------------------------
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

	//-----------------δ��ʼ����copy����ĳһ�ض�����n��ʼ��-----------------------------
	template<class ForwardIterator, class Size, class T>
	ForwardIterator _unitialized_fill_n_aux(ForwardIterator first, Size n, const T& value, _true_type){
		return fill_n(first, n, x);
	}

	template<class ForwardIterator, class Size, class T>
	ForwardIterator _unitialized_fill_n_aux(ForwardIterator first, Size n, const T& value, _false_type){
		int i = 0;
		for (; i != n; ++i){
			construct((T*)(first + i), x); //��ַ+value
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