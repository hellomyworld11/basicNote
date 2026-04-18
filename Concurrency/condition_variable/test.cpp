#include "a.h"

int main()
{
	A a;
	//通过类成员函数方式创建线程
	std::thread tOut(&A::Pop, &a);
	std::thread tin(&A::Push, &a);
	tOut.join();
	tin.join();
	//std::thread test(&A::hello, &a, 2);
	//test.join();
	std::cout << "main end" << std::endl;
	return 0;
}