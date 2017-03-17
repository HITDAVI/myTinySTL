#ifndef _MYTINYSTL_ITERATOR_H_
#define _MYTINYSTL_ITERATOR_H_

#include <cstddef>

namespace myTinySTL{
	//�������õ��ͱ�
	//��֧��operator++�������ֻ�֧��operator--��������֧�����У�����p+-n��p[n],p1-p2,p1<p2
	struct input_iterator_tag{}; //ֻ��
	struct output_iterator_tag{}; //ֻд
	struct forward_iterator_tag : public input_iterator_tag{}; //�����д

	struct bidirectional_iterator_tag : public forward_iterator_tag{}; //˫���ƶ�

	struct random_access_iterator_tag : public bidirectional_iterator_tag{};

	template <class T, class Distance> 
	struct input_iterator
	{
		typedef input_iterator_tag	iterator_category;
		typedef T					value_type;
		typedef Distance			difference_type;
		typedef T*					pointer;
		typedef T&					reference;
	};
	struct output_iterator
	{
		typedef output_iterator_tag iterator_category;
		typedef void                value_type;
		typedef void                difference_type;
		typedef void                pointer;
		typedef void                reference;
	};
	template <class T, class Distance> 
	struct forward_iterator
	{
		typedef forward_iterator_tag	iterator_category;
		typedef T						value_type;
		typedef Distance				difference_type;
		typedef T*						pointer;
		typedef T&						reference;
	};
	template <class T, class Distance> 
	struct bidirectional_iterator
	{
		typedef bidirectional_iterator_tag	iterator_category;
		typedef T							value_type;
		typedef Distance					difference_type;
		typedef T*							pointer;
		typedef T&							reference;
	};
	template <class T, class Distance> 
	struct random_access_iterator
	{
		typedef random_access_iterator_tag	iterator_category;
		typedef T							value_type;
		typedef Distance					difference_type;
		typedef T*							pointer;
		typedef T&							reference;
	};

	template<class Category, class T, class Distance = ptrdiff_t, class Pointer = T*, class Reference = T&>
	struct iterator
	{
		typedef Category	iterator_category;
		typedef T			value_type;
		typedef Distance	difference_type;
		typedef Pointer		pointer;
		typedef Reference	reference;
	};

	//traits����:
	template<class Iterator>
	struct iterator_traits
	{
		typedef typename Iterator::iterator_category	iterator_category;
		typedef typename Iterator::value_type			value_type;
		typedef typename Iterator::difference_type		difference_type;
		typedef typename Iterator::pointer				pointer;
		typedef typename Iterator::reference 			reference;
	};
	//���ԭ��ָ���traitsƫ�ػ�
	template<class T>
	struct iterator_traits<T*>
	{
		typedef random_access_iterator_tag 	iterator_category;
		typedef T 							value_type;
		typedef ptrdiff_t 					difference_type;
		typedef T*							pointer;
		typedef T& 							reference;
	};
	//pointer to const �ػ�
	template<class T>
	struct iterator_traits<const T*>
	{
		typedef random_access_iterator_tag 	iterator_category;
		typedef T 							value_type;
		typedef ptrdiff_t 					difference_type;
		typedef const T*					pointer;
		typedef const T& 					reference;
	};
	//�ж�iterator������
	template<class Iterator>
	inline typename iterator_traits<Iterator>::iterator_category iterator_category(const Iterator &It){
		typedef typename iterator_traits<Iterator>::iterator_category category;
		return category(); //ע��˴������ţ�category��һ��struct
	}

	//��ȡ��������value_type
	template<class Iterator>
	inline typename iterator_traits<Iterator>::value_type* value_type(const Iterator &It){
		return static_cast<typename iterator_traits<Iterator>::value_type*> (0);
	}

	//��ȡ��������distance_type
	template<class Iterator>
	inline typename iterator_traits<Iterator>::difference_type* difference_type(const Iterator &It){
		return static_cast<typename iterator_traits<Iterator>::difference_type*> (0);
	}



	//����distance����
	template<class InputIterator>
	inline iterator_traits<InputIterator>::difference_type 
		__distance(InputIterator first, InputIterator last, input_iterator_tag){  //ע�����tag���𵽱������
		iterator_traits<InputIterator>::difference_type n = 0;
		while (first != last){
			++first;
			++n;
		}
		return n;
	}

	template<class RandomAccessIterator>
	inline iterator_traits<RandomAccessIterator>::difference_type 
		__distance(RandomAccessIterator first, RandomAccessIterator last, random_access_iterator_tag){ 
		
		return last - first;
	}

	template<class InputIterator>
	inline iterator_traits<InputIterator>::difference_type
		distance(InputIterator first, InputIterator last){ 
		
		typedef typename iterator_traits<InputIterator>::iterator_category category;
		return __distance(first, last, category());
	}

	//����advance����
	template <class InputIterator, class Distance>
	inline void __advance(InputIterator& i, Distance n, input_iterator_tag){
		while (n--)
			++i;
	}

	template <class BidirectionalIterator, class Distance>
	inline void __advance(BidirectionalIterator& i, Distance n, bidirectional_iterator_tag){
		if (n >= 0)
			while (n--)
				++i;
		else
			while (n++)
				--i;
	}

	template <class RandomAccessIterator, class Distance>
	inline void __advance(RandomAccessIterator& i, Distance n, random_access_iterator_tag){
		i += n;
	}

	template <class InputIterator, class Distance>
	inline void advance(InputIterator& i, Distance n){
		__advance(i, n, iterator_category(i)); //����
	}
}

#endif