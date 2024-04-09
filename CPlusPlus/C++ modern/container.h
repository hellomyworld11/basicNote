#pragma once
#include <iostream>
#include <vector>

//1. ����vector clear˵����
// clear������黹�ڴ棬 ֻ�е���shrink_to_fit()�����ͷ��ڴ�


//2.std::forward_list ���б����� ʹ�õ����������ʵ��

//3. �������� std::map/std::set����ЩԪ���ڲ�ͨ�����������ʵ�֣� �����������ƽ�����ӶȾ�Ϊ O(log(size))
//std::unordered_map/std::unordered_multimap �� std::unordered_set/std::unordered_multiset�� ����������

//4. Ԫ��
#include <tuple>
#include <iostream>
auto get_student(int id)
{
    // �������ͱ��ƶ�Ϊ std::tuple<double, char, std::string>
    if (id == 0)
        return std::make_tuple(3.8, 'A', "����");
    if (id == 1)
        return std::make_tuple(2.9, 'C', "����");
    if (id == 2)
        return std::make_tuple(1.7, 'D', "����");
    return std::make_tuple(0.0, 'D', "null");
    // ���ֻд 0 ������ƶϴ���, ����ʧ��
}
int main()
{
    auto student = get_student(0);
    std::cout << "ID: 0, "
        << "GPA: " << std::get<0>(student) << ", "
        << "�ɼ�: " << std::get<1>(student) << ", "
        << "����: " << std::get<2>(student) << '\n';
    double gpa;
    char grade;
    std::string name;
    // Ԫ����в��
    std::tie(gpa, grade, name) = get_student(1);
    std::cout << "ID: 1, "
        << "GPA: " << gpa << ", "
        << "�ɼ�: " << grade << ", "
        << "����: " << name << '\n';
}