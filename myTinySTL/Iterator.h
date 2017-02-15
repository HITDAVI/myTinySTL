#ifndef _MYTINYSTL_ITERATOR_H_
#define _MYTINYSTL_ITERATOR_H_

#include <cstddef>

namespace myTinySTL{
	//五种迭代器
	//都支持operator++，第四种还支持operator--。第五种支持所有，包括p+-n，p[n],p1-p2,p1<p2
	struct input_iterator_tag{}; //只读
	struct output_iterator_tag{}; //只写
	struct forward_iterator_tag : public input_iterator_tag{}; //允许读写
	struct bidirectional_iterator_tag : public forward_iterator_tag{}; //双向移动
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

	//traits:
	template<class Iterator>
	struct iterator_traits
	{
		typedef typename Iterator::iterator_category	iterator_category;
		typedef typename Iterator::value_type			value_type;
		typedef typename Iterator::difference_type		difference_type;
		typedef typename Iterator::pointer				pointer;
		typedef typename Iterator::reference 			reference;
	};
	//针对原生指针的traits偏特化
	template<class T>
	struct iterator_traits<T*>
	{
		typedef random_access_iterator_tag 	iterator_category;
		typedef T 							value_type;
		typedef ptrdiff_t 					difference_type;
		typedef T*							pointer;
		typedef T& 							reference;
	};
	//pointer to const 特化
	template<class T>
	struct iterator_traits<const T*>
	{
		typedef random_access_iterator_tag 	iterator_category;
		typedef T 							value_type;
		typedef ptrdiff_t 					difference_type;
		typedef const T*					pointer;
		typedef const T& 					reference;
	};
	//判断iterator的类型
	template<class Iterator>
	inline typename iterator_traits<Iterator>::iterator_category iterator_category(const Iterator &It){
		typedef typename iterator_traits<Iterator>::iterator_category iterator_category;
		return category();
	}

	//获取迭代器的value_type
	template<class Iterator>
	inline typename iterator_traits<Iterator>::value_type* value_type(const Iterator &It){
		return static_cast<typename iterator_traits<Iterator>::value_type*> (0);
	}

	//获取迭代器的distance_type
	template<class Iterator>
	inline typename iterator_traits<Iterator>::difference_type* difference_type(const Iterator &It){
		return static_cast<typename iterator_traits<Iterator>::difference_type*> (0);
	}
}

#endif