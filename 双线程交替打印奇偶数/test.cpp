#include<iostream>
#include<thread>
#include<mutex>
#include<condition_variable>

int main()
{
	bool flag=true;
	int n = 100;
	std::mutex mtx;
	std::condition_variable cv;
	std::thread t1([&]() 
		{
			for (int i = 0; i < n; i += 2) {
				std::unique_lock<std::mutex> lock(mtx);
				cv.wait(lock, [&flag]()->bool {return flag; });
				std::cout << i << std::endl;
				flag = false;
				cv.notify_one();
			}
		 });
	std::thread t2([&]()
		{
			for (int j = 1; j < n; j+= 2) {
				std::unique_lock<std::mutex> lock(mtx);
				cv.wait(lock, [&flag]()->bool {return !flag; });
				std::cout << j << std::endl;
				flag = true;
				cv.notify_one();
			}
		});
	t1.join();
	t2.join();
	return 0;
}