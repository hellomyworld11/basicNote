#include <iostream>
#include <future>
#include <thread>

int mythread()
{
	std::cout << "mythread: " << std::this_thread::get_id() << std::endl;
	std::chrono::milliseconds dura(5000);
	std::this_thread::sleep_for(dura);
	std::cout << "mythread: end" << std::this_thread::get_id() << std::endl;
	return 5;
}


void testAsync()
{
	std::cout << "mainthread: " << std::this_thread::get_id() << std::endl;
	std::future<int> ret = std::async(mythread);

	int retnum = ret.get();

	std::cout << "mainthread end getret is : " << retnum << std::endl;
}

void testPackaged_task()
{
	std::packaged_task<int()> task(mythread);

	std::thread t(std::ref(task));
	t.join();
	std::future<int> ret = task.get_future();
	std::cout << "ret: " << ret.get() << std::endl;
}


int main()
{
	//testAsync();
	testPackaged_task();
	return 0;
}