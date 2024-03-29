﻿#include "task0.h"

void foo();

int main()
{
    std::thread myTh(foo);

    std::cout << "Main thread id = " << std::this_thread::get_id() << std::endl;

    myTh.detach();

    return 0;
}

void foo()
{
    std::cout << "Thread start..." << std::endl;
    for (int i = 0; i < 10; i++) {
        std::cout << "Thread id = " << std::this_thread::get_id() << std::endl;
        std::this_thread::sleep_for(std::chrono::seconds(1));
    }

    std::cout << "Thread finish!" << std::endl;
}
