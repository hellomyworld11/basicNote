#pragma once


//constexpr 让用户显式的声明函数或对象构造函数在编译期会成为常量表达式

void test_Constexpr()
{
#define LEN 10

	char arr[LEN];
	char arr1[10];
	int len = 10;
//	char arr2[len];     error
	const int len_1 = 10 + len;
//	char arr3[len_1];   error
	constexpr int len_2 = 10 + 1;
	char arr4[len_2];

}