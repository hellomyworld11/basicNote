#pragma once
#include <memory>
#include <iostream>
using namespace std;
//重要  智能指针与内存管理


//1. RAII 与引用计数
//RAII 指资源获取即初始化技术。 即 构造函数的时候申请空间，而在析构函数（在离开作用域时调用）的时候释放空间

//2. std::shared_ptr
// 记录多少个 shared_ptr 共同指向一个对象，从而消除显示的调用 delete，当引用计数变为零的时候就会将对象自动删除。


void foo(shared_ptr<int> i)
{
	(*i)++;
}


int testShared_ptr()
{
	auto pointer = make_shared<int>(10);
	foo(pointer);
	cout << *pointer << endl;

	cout << "count1: " << pointer.use_count() << endl;  //查看引用计数的个数
	auto pointer1 = pointer;
	cout << "count2: " << pointer.use_count() << endl;
	pointer1.reset();   //减少1个引用计数
	cout << "count3: " << pointer.use_count() << endl;

	int* p = pointer1.get();
	if (p == nullptr)
	{
		cout << "reset 后被释放" << endl;
	}
	int* pori = pointer.get();
	if (pori != nullptr)
	{
		cout << "原指针" << pori << endl;
	}
	return 0;
}



//3. std::unique_ptr 
// 是一种独占的智能指针，它禁止其他智能指针与其共享同一个对象，从而保证代码的安全
//template<typename T, typename ...Args>
//std::unique_ptr<T> make_unique(Args&& ...args) {
//	return std::unique_ptr<T>(new T(std::forward<Args>(args)...));
//}

int testUnique_ptr()
{
	std::unique_ptr<int> pointer = std::make_unique<int>(10); // make_unique 从 C++14 引入
	//std::unique_ptr<int> pointer2 = pointer; // 非法
}

//4.std::weak_ptr
//弱引用指针 弱引用不会引起引用计数增加
#include <iostream>
#include <memory>

std::weak_ptr<int> gw;

void observe()
{
	std::cout << "use_count == " << gw.use_count() << ": ";
	if (auto spt = gw.lock()) { // 使用之前必须复制到 shared_ptr
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