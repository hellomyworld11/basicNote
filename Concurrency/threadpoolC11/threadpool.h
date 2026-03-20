#ifndef THREADPOOL_H
#define THREADPOOL_H
#include <vector>
#include <queue>
#include <thread>
#include <functional>
#include <mutex>
#include <future>
#include <condition_variable>


class ThreadPool {
public:
	ThreadPool(size_t num = 10);

	~ThreadPool();
	// 添加任务  尾置返回类型  返回异步调用future 
	template<class F, class... Args>
	auto enqueue(F&& f, Args&&... args) 
		->std::future<typename std::result_of<F(Args...)>::type>;
private:
	
	std::vector<std::thread> threads_;

	std::queue<std::function<void()>> tasks_;

	std::mutex task_mutex_;

	std::condition_variable condition_;

	bool stop_;
};

inline ThreadPool::ThreadPool(size_t num)
	:stop_(false)
{
	//预产生一定数量的线程
	for (size_t i = 0; i < num; i++)
	{
		//放入线程池
		threads_.emplace_back(
			//lambda 线程函数
			[this] {
					
				while (true)
				{
					//函数对象
					std::function<void()> task;

					{
						//加锁
						std::unique_lock<std::mutex> lock(this->task_mutex_);
						
						//阻塞直到被notify 并且检测 是否停止或者 任务不为空，防止虚假唤醒。
						//注意 wait阻塞时会解锁，  wait被唤醒后会加锁。
						this->condition_.wait(lock, [this] { return	this->stop_ || !this->tasks_.empty(); });

						if (this->stop_ && this->tasks_.empty())
						{
							return;
						}
						//移动，不拷贝
						task = std::move(this->tasks_.front());
						this->tasks_.pop();
					}
					//执行最外层的void()函数， 里面再执行真正的任务函数。
					task();
				}

			}
		);
	}
}

inline ThreadPool::~ThreadPool()
{
	{
		std::unique_lock<std::mutex> lock(task_mutex_);

		stop_ = true;
	}

	//唤醒所有线程使其退出阻塞态。
	condition_.notify_all();
	for (auto & athread : threads_)
	{
		//等待线程完成
		athread.join();
	}
}

template<class F, class ...Args>
inline auto ThreadPool::enqueue(F&& f, Args && ...args) 
	-> std::future<typename std::result_of<F(Args ...)>::type>
{
	//return_type 是 F(Args...)函数调用的返回类型
	using return_type = typename std::result_of<F(Args...)>::type;
	
	//1. 把所有的参数通过bind绑定,线程函数里都是统一调用形式。
	//2. packaged_task包装 F函数通过bind形式 ，之后可以获取future获取异步结果。
	//3. make_shared 用来进行packaged_task指针管理。
	auto task = std::make_shared< std::packaged_task< return_type()  >  >(
			std::bind(std::forward<F>(f), std::forward<Args>(args)...)
		);

	std::future<return_type> res = task->get_future();
	{
		//加锁
		std::unique_lock<std::mutex> lock(task_mutex_);

		if (stop_)
			throw std::runtime_error("ThreadPool stopped");
		
		//放入任务队列
		tasks_.emplace(  //再用lambda包装一层，里面用task指针去调用F函数，参数已绑定， 返回值通过future获取。
			[task]() {  (*task)(); }
		);
	}
	condition_.notify_one();
	return res;  //这里是线程函数执行的结果。 异步获取
}




#endif 

