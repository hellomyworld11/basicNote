#pragma once
#include <iostream>
#include <thread>
#include <mutex>
#include <list>

class A
{
public:
	void Push()
	{
		
		for (int i = 0; i < 100000; i++)
		{
			std::cout << "Push: " << i << std::endl;
			std::unique_lock<std::mutex> lock(mutex_);
			msgQueue_.push_back(i);
			cond_.notify_one();
		}
	}

	void Pop()
	{
		int ret;
		for (int i = 0; i < 100000; i++)
		{
			bool bret = OutMsgLULProc(ret);
			if (bret)
			{
				std::cout << "Pop: " << ret << std::endl;
			}
			else {
				std::cout << "msgqueue empty " << i << std::endl;
			}
		}
	}

	bool OutMsgLULProc(int& ret)
	{	
		std::unique_lock<std::mutex> lock(mutex_);
		cond_.wait(lock, [this]() {
			return !msgQueue_.empty();
			});
		if (!msgQueue_.empty())
		{
			ret = msgQueue_.front();
			msgQueue_.pop_front();
			return true;
		}
		return false;
	}

	void hello(int i)
	{
		std::cout << "hello : " << i << std::endl;
	}

private:
	std::list<int> msgQueue_;
	std::mutex mutex_;
	std::condition_variable cond_;
};
