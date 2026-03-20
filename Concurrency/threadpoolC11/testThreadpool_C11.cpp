#include "threadpool.h"
#include <iostream>
#include <string>

int sum(int a, int b)
{
	return a + b;
}

int sum1(int a, int b, int c)
{
	return a + b + c;
}

int main()
{
	ThreadPool pool;

	//1.传入普通函数
	std::future<int> ret1 = pool.enqueue(sum, 1, 2);
	std::future<int> ret2 = pool.enqueue(sum1, 1, 2, 3);

	std::cout << ret1.get() << std::endl;
	std::cout << ret2.get() << std::endl;

	//2. 传入lambda函数
	std::future<std::string> ret3 = pool.enqueue(
		[] { std::string s = "hellowrold"; return s;  }
	);
	std::cout << ret3.get() << std::endl;

	//3. 传入function
	for (size_t i = 0; i < 1000; i++)
	{
		std::function<void(int)> funtest1 = [](int i) { std::cout << std::this_thread::get_id() << "执行funtest: " << i << std::endl; };
		pool.enqueue(funtest1, i);
	}
	
	return 0;
}