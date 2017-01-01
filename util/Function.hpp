#pragma once

template<class arg, class result>
class my_ptr_function_class;
template<class arg, class result>
my_ptr_function_class<arg, result> my_ptr_function(result(*f)(arg));

template<class arg, class result>
class my_ptr_function_class
{
private:
	result(*pfunc)(arg);
public:
	my_ptr_function_class(result(*f)(arg)) : pfunc(f) {}
	result operator() (arg a)
	{
		return pfunc(a);
	}
};
template<class arg, class result>
my_ptr_function_class<arg, result> my_ptr_function(result(*f)(arg))
{
	return my_ptr_function_class<arg, result>(f);
}

template<class arg1, class arg2, class result>
class my_ptr_function_class_2;
template<class arg1, class arg2, class result>
my_ptr_function_class_2<arg1, arg2, result> my_ptr_function(result(*f)(arg1, arg2));

template<class arg1, class arg2, class result>
class my_ptr_function_class_2
{
private:
	result(*pfunc)(arg1, arg2);
public:
	my_ptr_function_class_2(result(*f)(arg1, arg2)) : pfunc(f) {}
	result operator() (arg1 a1, arg2 a2)
	{
		return pfunc(a1, a2);
	}
};

template<class arg1, class arg2, class result>
my_ptr_function_class_2<arg1, arg2, result> my_ptr_function(result(*f)(arg1, arg2))
{
	return my_ptr_function_class_2<arg1, arg2, result>(f);
}

template<class arg1, class arg2, class arg3, class result>
class my_ptr_function_class_3;
template<class arg1, class arg2, class arg3, class result>
my_ptr_function_class_3<arg1, arg2, arg3, result> my_ptr_function(result(*f)(arg1, arg2, arg3));

template<class arg1, class arg2, class arg3, class result>
class my_ptr_function_class_3
{
private:
	result(*pfunc)(arg1, arg2, arg3);
public:
	my_ptr_function_class_3(result(*f)(arg1, arg2, arg3)) : pfunc(f) {}
	result operator() (arg1 a1, arg2 a2, arg3 a3)
	{
		return pfunc(a1, a2, a3);
	}
};
template<class arg1, class arg2, class arg3, class result>
my_ptr_function_class_3<arg1, arg2, arg3, result> my_ptr_function(result(*f)(arg1, arg2, arg3))
{
	return my_ptr_function_class_3<arg1, arg2, arg3, result>(f);
}


template<class T>
class SingletonBase
{
protected:
	SingletonBase()
	{
		doInit();
	}
	static T* _instance;
public:
	static T* getInstance()
	{
		if (!_instance)
			_instance = new T;
		return _instance;
	}
	virtual void doInit()
	{

	}
};

template<class T>
T* SingletonBase<T>::_instance = 0;