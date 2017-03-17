#ifndef _MYTINYSTL_TYPE_TRAITS_H_
#define _MYTINYSTL_TYPE_TRAITS_H_

namespace myTinySTL{
	struct _true_type{ };
	struct _false_type{ };

	//特性萃取 特例化样本 萃取的是型别的特性，区别于iterator的特性，本文件属于typetraits
	template<class _Tp>
	struct _type_traits{
		typedef _false_type	   has_trivial_default_constructor; //默认构造
		typedef _false_type    has_trivial_copy_constructor;//默认拷贝构造
		typedef _false_type    has_trivial_assignment_operator;//默认赋值
		typedef _false_type    has_trivial_destructor;//默认析构
		typedef _false_type    is_POD_type;
	};

	//空<>表示我们将为所有的模板参数提供实参，这是全特化？
	template<>
	struct _type_traits<bool> {
		typedef _true_type    has_trivial_default_constructor;
		typedef _true_type    has_trivial_copy_constructor;
		typedef _true_type    has_trivial_assignment_operator;
		typedef _true_type    has_trivial_destructor;
		typedef _true_type    is_POD_type;
	};

	template<>
	struct _type_traits<char> {
		typedef _true_type    has_trivial_default_constructor;
		typedef _true_type    has_trivial_copy_constructor;
		typedef _true_type    has_trivial_assignment_operator;
		typedef _true_type    has_trivial_destructor;
		typedef _true_type    is_POD_type;
	};

	template<>
	struct _type_traits<signed char> {
		typedef _true_type    has_trivial_default_constructor;
		typedef _true_type    has_trivial_copy_constructor;
		typedef _true_type    has_trivial_assignment_operator;
		typedef _true_type    has_trivial_destructor;
		typedef _true_type    is_POD_type;
	};

	template<>
	struct _type_traits<unsigned char> {
		typedef _true_type    has_trivial_default_constructor;
		typedef _true_type    has_trivial_copy_constructor;
		typedef _true_type    has_trivial_assignment_operator;
		typedef _true_type    has_trivial_destructor;
		typedef _true_type    is_POD_type;
	};

	template<>
	struct _type_traits<wchar_t> {
		typedef _true_type    has_trivial_default_constructor;
		typedef _true_type    has_trivial_copy_constructor;
		typedef _true_type    has_trivial_assignment_operator;
		typedef _true_type    has_trivial_destructor;
		typedef _true_type    is_POD_type;
	};

	template<>
	struct _type_traits<short> {
		typedef _true_type    has_trivial_default_constructor;
		typedef _true_type    has_trivial_copy_constructor;
		typedef _true_type    has_trivial_assignment_operator;
		typedef _true_type    has_trivial_destructor;
		typedef _true_type    is_POD_type;
	};

	template<>
	struct _type_traits<unsigned short> {
		typedef _true_type    has_trivial_default_constructor;
		typedef _true_type    has_trivial_copy_constructor;
		typedef _true_type    has_trivial_assignment_operator;
		typedef _true_type    has_trivial_destructor;
		typedef _true_type    is_POD_type;
	};

	template<>
	struct _type_traits<int> {
		typedef _true_type    has_trivial_default_constructor;
		typedef _true_type    has_trivial_copy_constructor;
		typedef _true_type    has_trivial_assignment_operator;
		typedef _true_type    has_trivial_destructor;
		typedef _true_type    is_POD_type;
	};

	template<>
	struct _type_traits<unsigned int> {
		typedef _true_type    has_trivial_default_constructor;
		typedef _true_type    has_trivial_copy_constructor;
		typedef _true_type    has_trivial_assignment_operator;
		typedef _true_type    has_trivial_destructor;
		typedef _true_type    is_POD_type;
	};

	template<>
	struct _type_traits<long> {
		typedef _true_type    has_trivial_default_constructor;
		typedef _true_type    has_trivial_copy_constructor;
		typedef _true_type    has_trivial_assignment_operator;
		typedef _true_type    has_trivial_destructor;
		typedef _true_type    is_POD_type;
	};

	template<>
	struct _type_traits<unsigned long> {
		typedef _true_type    has_trivial_default_constructor;
		typedef _true_type    has_trivial_copy_constructor;
		typedef _true_type    has_trivial_assignment_operator;
		typedef _true_type    has_trivial_destructor;
		typedef _true_type    is_POD_type;
	};

	template<>
	struct _type_traits<long long> {
		typedef _true_type    has_trivial_default_constructor;
		typedef _true_type    has_trivial_copy_constructor;
		typedef _true_type    has_trivial_assignment_operator;
		typedef _true_type    has_trivial_destructor;
		typedef _true_type    is_POD_type;
	};

	template<>
	struct _type_traits<unsigned long long> {
		typedef _true_type    has_trivial_default_constructor;
		typedef _true_type    has_trivial_copy_constructor;
		typedef _true_type    has_trivial_assignment_operator;
		typedef _true_type    has_trivial_destructor;
		typedef _true_type    is_POD_type;
	};

	template<>
	struct _type_traits<float> {
		typedef _true_type    has_trivial_default_constructor;
		typedef _true_type    has_trivial_copy_constructor;
		typedef _true_type    has_trivial_assignment_operator;
		typedef _true_type    has_trivial_destructor;
		typedef _true_type    is_POD_type;
	};

	template<>
	struct _type_traits<double> {
		typedef _true_type    has_trivial_default_constructor;
		typedef _true_type    has_trivial_copy_constructor;
		typedef _true_type    has_trivial_assignment_operator;
		typedef _true_type    has_trivial_destructor;
		typedef _true_type    is_POD_type;
	};

	template<>
	struct _type_traits<long double> {
		typedef _true_type    has_trivial_default_constructor;
		typedef _true_type    has_trivial_copy_constructor;
		typedef _true_type    has_trivial_assignment_operator;
		typedef _true_type    has_trivial_destructor;
		typedef _true_type    is_POD_type;
	};

	template <class T>
	struct _type_traits<T*> {
		typedef _true_type    has_trivial_default_constructor;
		typedef _true_type    has_trivial_copy_constructor;
		typedef _true_type    has_trivial_assignment_operator;
		typedef _true_type    has_trivial_destructor;
		typedef _true_type    is_POD_type;
	};

	template<>
	struct _type_traits<char*> {
		typedef _true_type    has_trivial_default_constructor;
		typedef _true_type    has_trivial_copy_constructor;
		typedef _true_type    has_trivial_assignment_operator;
		typedef _true_type    has_trivial_destructor;
		typedef _true_type    is_POD_type;
	};

	template<>
	struct _type_traits<signed char*> {
		typedef _true_type    has_trivial_default_constructor;
		typedef _true_type    has_trivial_copy_constructor;
		typedef _true_type    has_trivial_assignment_operator;
		typedef _true_type    has_trivial_destructor;
		typedef _true_type    is_POD_type;
	};

	template<>
	struct _type_traits<unsigned char*> {
		typedef _true_type    has_trivial_default_constructor;
		typedef _true_type    has_trivial_copy_constructor;
		typedef _true_type    has_trivial_assignment_operator;
		typedef _true_type    has_trivial_destructor;
		typedef _true_type    is_POD_type;
	};

	template<>
	struct _type_traits<const char*> {
		typedef _true_type    has_trivial_default_constructor;
		typedef _true_type    has_trivial_copy_constructor;
		typedef _true_type    has_trivial_assignment_operator;
		typedef _true_type    has_trivial_destructor;
		typedef _true_type    is_POD_type;
	};

	template<>
	struct _type_traits<const signed char*> {
		typedef _true_type    has_trivial_default_constructor;
		typedef _true_type    has_trivial_copy_constructor;
		typedef _true_type    has_trivial_assignment_operator;
		typedef _true_type    has_trivial_destructor;
		typedef _true_type    is_POD_type;
	};

	template<>
	struct _type_traits<const unsigned char*> {
		typedef _true_type    has_trivial_default_constructor;
		typedef _true_type    has_trivial_copy_constructor;
		typedef _true_type    has_trivial_assignment_operator;
		typedef _true_type    has_trivial_destructor;
		typedef _true_type    is_POD_type;
	};

	/*
	template <class _Tp> struct _is_Integer {
		typedef _false_type _Integral;
	};


	template<>
	struct _is_Integer<bool> {
		typedef _true_type _Integral;
	};


	template<>
	struct _is_Integer<char> {
		typedef _true_type _Integral;
	};

	template<>
	struct _is_Integer<signed char> {
		typedef _true_type _Integral;
	};

	template<>
	struct _is_Integer<unsigned char> {
		typedef _true_type _Integral;
	};

	template<>
	struct _is_Integer<wchar_t> {
		typedef _true_type _Integral;
	};

	template<>
	struct _is_Integer<short> {
		typedef _true_type _Integral;
	};

	template<>
	struct _is_Integer<unsigned short> {
		typedef _true_type _Integral;
	};

	template<>
	struct _is_Integer<int> {
		typedef _true_type _Integral;
	};

	template<>
	struct _is_Integer<unsigned int> {
		typedef _true_type _Integral;
	};

	template<>
	struct _is_Integer<long> {
		typedef _true_type _Integral;
	};

	template<>
	struct _is_Integer<unsigned long> {
		typedef _true_type _Integral;
	};

	template<>
	struct _is_Integer<long long> {
		typedef _true_type _Integral;
	};

	template<>
	struct _is_Integer<unsigned long long> {
		typedef _true_type _Integral;
	};
	*/
}

#endif