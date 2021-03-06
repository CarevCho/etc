// cpp_template_function.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

#include <iostream>

template <typename T>
T add(T a, T b)
{
	T result;
	result = a + b;
	return (result);
}

//function template usage 
template <typename T>
int SizeOf(T a)
{
	return sizeof(a);
}

int main()
{
	int a = 0; int b = 1;
	int c;
	c = add(a, b);
	std::cout << c << std::endl;
	std::cout << SizeOf(3.4f) << std::endl;
	std::cout << SizeOf(3) << std::endl;
	std::cout << SizeOf(3.4) << std::endl;
	return 0;
}