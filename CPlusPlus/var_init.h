#pragma once
#include <iostream>
#include <vector>

//1. c++17 if�����ڿ��Զ���ֲ�����
void test_if_var()
{
    std::vector<int> vec = { 1, 2, 3, 4 };
    // �� c++17 ֮ǰ
    const std::vector<int>::iterator itr = std::find(vec.begin(), vec.end(), 2);
    if (itr != vec.end()) {
        *itr = 3;
    }
    // ��Ҫ���¶���һ���µı���
    const std::vector<int>::iterator itr2 = std::find(vec.begin(), vec.end(), 3);
    if (itr2 != vec.end()) {
        *itr2 = 4;
    }
    // ����� 1, 4, 3, 4
    for (std::vector<int>::iterator element = vec.begin(); element != vec.end(); ++element)
        std::cout << *element << std::endl;

    // ����ʱ�����ŵ� if �����  C++ 17
    if (const std::vector<int>::iterator itr = std::find(vec.begin(), vec.end(), 3);
        itr != vec.end()) {
        *itr = 4;
    }
}


//2. std::tuple �������ڹ���һ��Ԫ�飬���������������ֵ��
std::tuple<int, double, std::string> f() {
    return std::make_tuple(1, 2.3, "456");
}

void test_tuple () {
    auto [x, y, z] = f();
    std::cout << x << ", " << y << ", " << z << std::endl;
    return ;
}

//3. �����Ƶ� auto  decltype
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

//4. if constexpr ����ʱ���ж�Ч�ʸ�
#include <iostream>
template<typename T>
auto print_type_info(const T& t) {
    if constexpr (std::is_integral<T>::value) { //����ʱ��ȷ���ĸ��߼�
        return t + 1;
    }
    else {
        return t + 0.001;
    }
}
int main() {
    std::cout << print_type_info(5) << std::endl;
    std::cout << print_type_info(3.14) << std::endl;
}

