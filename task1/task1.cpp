#include "task1.h"

void foo(int);

int main()
{
    std::thread myTh1(foo, 1);
    std::thread myTh2(foo, 2);

    std::cout << "Main thread id = " << std::this_thread::get_id() << std::endl;

    myTh1.join();
    myTh2.join();

    return 0;
}

void foo(int n)
{
    std::cout << "Thread " << std::this_thread::get_id() << " start..." << std::endl;
    for (int i = n; i <= 100; i += 2) {
        std::cout << "Thread " << n << " Num = " << i << std::endl;
        std::this_thread::sleep_for(std::chrono::seconds(1));
    }

    std::cout << "Thread " << std::this_thread::get_id() << " finish!" << std::endl;
}
