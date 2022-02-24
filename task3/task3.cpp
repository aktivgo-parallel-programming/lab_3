#include "task3.h"

int cnt = 0;
void foo(std::mutex&);

int main()
{
    srand(time(nullptr));

    std::cout << "Cnt = " << cnt << std::endl;

    int P = 1;
    std::cout << "Input P: ";
    std::cin >> P;
    if (P < 1 || P > 10) {
        return -1;
    }
    std::cout << std::endl;

    auto* threads = new std::thread[P];
    std::mutex mx;

    for (int i = 0; i < P; i++) {
        threads[i] = std::thread(foo, ref(mx));
    }

    std::unique_lock<std::mutex> ulmx(mx);
    std::cout << "Main thread id = " << std::this_thread::get_id() << std::endl;
    ulmx.unlock();

    for (int i = 0; i < P; i++) {
        threads[i].join();
    }

    std::cout << "Cnt = " << cnt << std::endl;

    delete[] threads;
    return 0;
}

void foo(std::mutex& mx)
{
    std::cout << "Thread " << std::this_thread::get_id() << " start..." << std::endl;
    while(cnt < 100) {
        std::this_thread::sleep_for(std::chrono::milliseconds(rand()%1000));
        std::lock_guard<std::mutex> lgmx(mx);
        if (cnt < 100) {
            std::cout << "Cnt for thread " << std::this_thread::get_id() << " = " << ++cnt << std::endl;
        }
    }

    std::cout << "Thread " << std::this_thread::get_id() << " finish!" << std::endl;
}
