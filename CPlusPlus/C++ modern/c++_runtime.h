#pragma once
#include <iostream>
#include <vector>
#include <functional>

//1. lambda
//		[捕获列表](参数列表) mutable(可选)异常属性 -> 返回类型 {
//			// 函数体
//		}
//
//关于捕获
//1.[] 空捕获列表
//2.[name1, name2, …] 捕获一系列变量
//3.[&] 引用捕获, 让编译器自行推导捕获列表
//4.[=] 值捕获, 让编译器执行推导引用列表
//值捕获
void lambda_value_capture() {
    int value = 1;
    auto copy_value = [value] {
        return value;
    };
    value = 100;
    auto stored_value = copy_value();
    std::cout << "stored_value = " << stored_value << std::endl;
    // 这时, stored_value == 1, 而 value == 100.
    // 因为 copy_value 在创建时就保存了一份 value 的拷贝
}

//引用捕获
void lambda_reference_capture() {
    int value = 1;
    auto copy_value = [&value] {
        return value;
    };
    value = 100;
    auto stored_value = copy_value();
    std::cout << "stored_value = " << stored_value << std::endl;
    // 这时, stored_value == 100, value == 100.
    // 因为 copy_value 保存的是引用
}


//2. 函数对象包装器
#include <functional>
#include <iostream>
//eg 1
int foo(int para) {
    return para;
}
int test_function() {
    // std::function 包装了一个返回值为 int, 参数为 int 的函数
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
    // 将参数1,2绑定到函数 foo 上，但是使用 std::placeholders::_1 来对第一个参数进行占位
    auto bindFoo = std::bind(foo, std::placeholders::_1, 1, 2);
    // 这时调用 bindFoo 时，只需要提供第一个参数即可
    bindFoo(1);
}


//右值引用
//左值：赋值运算符左边的 
//右值: 赋值运算符右边的
//纯右值(prvalue, pure rvalue)，纯粹的右值，要么是纯粹的字面量，例如 10, true；
//将亡值如下 : 返回temp 会 把内容复制到v 并销毁temp 这样会浪费时间和资源。  temp代表将亡值
std::vector<int> foo() {
    std::vector<int> temp = { 1, 2, 3, 4 };
    return temp;
}
std::vector<int> v = foo();
//在 C++11 之后，编译器做了一些工作，此处的左值 temp 会被进行此隐式右值转换， 
//等价于 static_cast<std::vector<int> &&>(temp)，进而此处的 v 会将 foo 局部返回的值进行移动。 也就是移动语义。

//右值引用： T &&    右值引用的声明让这个临时值的生命周期得以延长、只要变量还活着，那么将亡值将继续存活。
//std::move 函数 将左值参数无条件的转换为右值
#include <iostream>
#include <string>
void reference(std::string& str) {
    std::cout << "左值" << std::endl;
}
void reference(std::string&& str) {
    std::cout << "右值" << std::endl;
}
int main()
{
    std::string lv1 = "string,"; // lv1 是一个左值
    // std::string&& r1 = lv1; // 非法, 右值引用不能引用左值
    std::string&& rv1 = std::move(lv1); // 合法, std::move可以将左值转移为右值
    std::cout << rv1 << std::endl; // string,
    const std::string& lv2 = lv1 + lv1; // 合法, 常量左值引用能够延长临时变量的生命周期
    // lv2 += "Test"; // 非法, 常量引用无法被修改
    std::cout << lv2 << std::endl; // string,string
    std::string&& rv2 = lv1 + lv2; // 合法, 右值引用延长临时对象生命周期
    rv2 += "Test"; // 合法, 非常量引用能够修改临时变量
    std::cout << rv2 << std::endl; // string,string,string,Test
    reference(rv2); // 输出左值
    return 0;
}