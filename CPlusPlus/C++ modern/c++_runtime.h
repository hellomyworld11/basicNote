#pragma once
#include <iostream>
#include <vector>
#include <functional>

//1. lambda
//		[�����б�](�����б�) mutable(��ѡ)�쳣���� -> �������� {
//			// ������
//		}
//
//���ڲ���
//1.[] �ղ����б�
//2.[name1, name2, ��] ����һϵ�б���
//3.[&] ���ò���, �ñ����������Ƶ������б�
//4.[=] ֵ����, �ñ�����ִ���Ƶ������б�
//ֵ����
void lambda_value_capture() {
    int value = 1;
    auto copy_value = [value] {
        return value;
    };
    value = 100;
    auto stored_value = copy_value();
    std::cout << "stored_value = " << stored_value << std::endl;
    // ��ʱ, stored_value == 1, �� value == 100.
    // ��Ϊ copy_value �ڴ���ʱ�ͱ�����һ�� value �Ŀ���
}

//���ò���
void lambda_reference_capture() {
    int value = 1;
    auto copy_value = [&value] {
        return value;
    };
    value = 100;
    auto stored_value = copy_value();
    std::cout << "stored_value = " << stored_value << std::endl;
    // ��ʱ, stored_value == 100, value == 100.
    // ��Ϊ copy_value �����������
}


//2. ���������װ��
#include <functional>
#include <iostream>
//eg 1
int foo(int para) {
    return para;
}
int test_function() {
    // std::function ��װ��һ������ֵΪ int, ����Ϊ int �ĺ���
    std::function<int(int)> func = foo;
    int important = 10;
    std::function<int(int)> func2 = [&](int value) -> int {
        return 1 + value + important;
    };
    std::cout << func(10) << std::endl;
    std::cout << func2(10) << std::endl;
}
//eg 2
int foo(int a, int b, int c) {
    ;
}
int main() {
    // ������1,2�󶨵����� foo �ϣ�����ʹ�� std::placeholders::_1 ���Ե�һ����������ռλ
    auto bindFoo = std::bind(foo, std::placeholders::_1, 1, 2);
    // ��ʱ���� bindFoo ʱ��ֻ��Ҫ�ṩ��һ����������
    bindFoo(1);
}


//��ֵ����
//��ֵ����ֵ�������ߵ� 
//��ֵ: ��ֵ������ұߵ�
//����ֵ(prvalue, pure rvalue)���������ֵ��Ҫô�Ǵ���������������� 10, true��
//����ֵ���� : ����temp �� �����ݸ��Ƶ�v ������temp �������˷�ʱ�����Դ��  temp������ֵ
std::vector<int> foo() {
    std::vector<int> temp = { 1, 2, 3, 4 };
    return temp;
}
std::vector<int> v = foo();
//�� C++11 ֮�󣬱���������һЩ�������˴�����ֵ temp �ᱻ���д���ʽ��ֵת���� 
//�ȼ��� static_cast<std::vector<int> &&>(temp)�������˴��� v �Ὣ foo �ֲ����ص�ֵ�����ƶ��� Ҳ�����ƶ����塣

//��ֵ���ã� T &&    ��ֵ���õ������������ʱֵ���������ڵ����ӳ���ֻҪ���������ţ���ô����ֵ��������
//std::move ���� ����ֵ������������ת��Ϊ��ֵ
#include <iostream>
#include <string>
void reference(std::string& str) {
    std::cout << "��ֵ" << std::endl;
}
void reference(std::string&& str) {
    std::cout << "��ֵ" << std::endl;
}
int main()
{
    std::string lv1 = "string,"; // lv1 ��һ����ֵ
    // std::string&& r1 = lv1; // �Ƿ�, ��ֵ���ò���������ֵ
    std::string&& rv1 = std::move(lv1); // �Ϸ�, std::move���Խ���ֵת��Ϊ��ֵ
    std::cout << rv1 << std::endl; // string,
    const std::string& lv2 = lv1 + lv1; // �Ϸ�, ������ֵ�����ܹ��ӳ���ʱ��������������
    // lv2 += "Test"; // �Ƿ�, ���������޷����޸�
    std::cout << lv2 << std::endl; // string,string
    std::string&& rv2 = lv1 + lv2; // �Ϸ�, ��ֵ�����ӳ���ʱ������������
    rv2 += "Test"; // �Ϸ�, �ǳ��������ܹ��޸���ʱ����
    std::cout << rv2 << std::endl; // string,string,string,Test
    reference(rv2); // �����ֵ
    return 0;
}