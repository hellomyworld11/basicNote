#pragma once
#include <memory>
#include <iostream>
using namespace std;
//��Ҫ  ����ָ�����ڴ����


//1. RAII �����ü���
//RAII ָ��Դ��ȡ����ʼ�������� �� ���캯����ʱ������ռ䣬�����������������뿪������ʱ���ã���ʱ���ͷſռ�

//2. std::shared_ptr
// ��¼���ٸ� shared_ptr ��ָͬ��һ�����󣬴Ӷ�������ʾ�ĵ��� delete�������ü�����Ϊ���ʱ��ͻὫ�����Զ�ɾ����


void foo(shared_ptr<int> i)
{
	(*i)++;
}


int testShared_ptr()
{
	auto pointer = make_shared<int>(10);
	foo(pointer);
	cout << *pointer << endl;

	cout << "count1: " << pointer.use_count() << endl;  //�鿴���ü����ĸ���
	auto pointer1 = pointer;
	cout << "count2: " << pointer.use_count() << endl;
	pointer1.reset();   //����1�����ü���
	cout << "count3: " << pointer.use_count() << endl;

	int* p = pointer1.get();
	if (p == nullptr)
	{
		cout << "reset ���ͷ�" << endl;
	}
	int* pori = pointer.get();
	if (pori != nullptr)
	{
		cout << "ԭָ��" << pori << endl;
	}
	return 0;
}



//3. std::unique_ptr 
// ��һ�ֶ�ռ������ָ�룬����ֹ��������ָ�����乲��ͬһ�����󣬴Ӷ���֤����İ�ȫ
//template<typename T, typename ...Args>
//std::unique_ptr<T> make_unique(Args&& ...args) {
//	return std::unique_ptr<T>(new T(std::forward<Args>(args)...));
//}

int testUnique_ptr()
{
	std::unique_ptr<int> pointer = std::make_unique<int>(10); // make_unique �� C++14 ����
	//std::unique_ptr<int> pointer2 = pointer; // �Ƿ�
}

//4.std::weak_ptr
//������ָ�� �����ò����������ü�������
#include <iostream>
#include <memory>

std::weak_ptr<int> gw;

void observe()
{
	std::cout << "use_count == " << gw.use_count() << ": ";
	if (auto spt = gw.lock()) { // ʹ��֮ǰ���븴�Ƶ� shared_ptr
		std::cout << *spt << "\n";
	}
	else {
		std::cout << "gw is expired\n";
	}
}

int testWeak_ptr()
{
	{
		auto sp = std::make_shared<int>(42);
		gw = sp;

		observe();
	}
	observe();
}