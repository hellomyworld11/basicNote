#include <iostream>
#include <thread>





int main() {
    std::thread t([]() {
        std::cout << "hello world." << std::endl;
        });
    t.join();


    getchar();

    return 0;
}