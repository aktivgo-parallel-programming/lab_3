#include "task2.h"

void foo();

int main()
{
    srand(time(nullptr));

    int P = 1;
    std::cout << "Input P: ";
    std::cin >> P;
    if (P < 1 || P > 10) {
        return -1;
    }
    std::cout << std::endl;

    auto* threads = new std::thread[P];

    for (int i = 0; i < P; i++) {
        threads[i] = std::thread(foo);
    }

    std::cout << "Main thread id = " << std::this_thread::get_id() << std::endl;

    for (int i = 0; i < P; i++) {
        threads[i].join();
    }

    delete[] threads;
    return 0;
}

void foo()
{
    std::cout << "Thread " << std::this_thread::get_id() << " start..." << std::endl;
    for (int i = 0; i < 100; i++) {
        std::cout << "Thread id = " << std::this_thread::get_id() << std::endl;
        std::this_thread::sleep_for(std::chrono::milliseconds(1000 + (rand() % (2000 - 1000 + 1))));
    }


    std::cout << "Thread " << std::this_thread::get_id() << " finish!" << std::endl;
}
