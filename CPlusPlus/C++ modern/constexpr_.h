#pragma once


//constexpr ���û���ʽ����������������캯���ڱ����ڻ��Ϊ�������ʽ

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