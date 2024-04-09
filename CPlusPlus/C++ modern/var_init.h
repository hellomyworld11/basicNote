#pragma once
#include <iostream>
#include <vector>

//1. c++17 if括号内可以定义局部变量
void test_if_var()
{
    std::vector<int> vec = { 1, 2, 3, 4 };
    // 在 c++17 之前
    const std::vector<int>::iterator itr = std::find(vec.begin(), vec.end(), 2);
    if (itr != vec.end()) {
        *itr = 3;
    }
    // 需要重新定义一个新的变量
    const std::vector<int>::iterator itr2 = std::find(vec.begin(), vec.end(), 3);
    if (itr2 != vec.end()) {
        *itr2 = 4;
    }
    // 将输出 1, 4, 3, 4
    for (std::vector<int>::iterator element = vec.begin(); element != vec.end(); ++element)
        std::cout << *element << std::endl;

    // 将临时变量放到 if 语句内  C++ 17
    if (const std::vector<int>::iterator itr = std::find(vec.begin(), vec.end(), 3);
        itr != vec.end()) {
        *itr = 4;
    }
}


//2. std::tuple 容器用于构造一个元组，进而囊括多个返回值。
std::tuple<int, double, std::string> f() {
    return std::make_tuple(1, 2.3, "456");
}

void test_tuple () {
    auto [x, y, z] = f();
    std::cout << x << ", " << y << ", " << z << std::endl;
    return ;
}

//3. 类型推导 auto  decltype
//C++11
template<typename T, typename U>
auto add2(T x, U y) -> decltype(x + y) {
    return x + y;
}

//C++14
template<typename T, typename U>
auto add3(T x, U y) {
    return x + y;
}

//4. if constexpr 编译时做判断效率高
#include <iostream>
template<typename T>
auto print_type_info(const T& t) {
    if constexpr (std::is_integral<T>::value) { //编译时能确定哪个逻辑
        return t + 1;
    }
    else {
        return t + 0.001;
    }
}
void test_print_type_infot() {
    std::cout << print_type_info(5) << std::endl;
    std::cout << print_type_info(3.14) << std::endl;
}

//5. 委托构造  继承构造
#include <iostream>
class Base {
public:
    int value1;
    int value2;
    Base() {
        value1 = 1;
    }
    Base(int value) : Base() { // 委托 Base() 构造函数
        value2 = value;
    }
};
class Subclass : public Base {
public:
    using Base::Base; // 继承构造
};
void test_BaseCon() {
    Base b(2);
    std::cout << b.value1 << std::endl;
    std::cout << b.value2 << std::endl;

    Subclass s(3);
    std::cout << s.value1 << std::endl;
    std::cout << s.value2 << std::endl;
}


