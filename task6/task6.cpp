#include "task6.h"

int N;
std::vector<long long> sums;

void foo(int, int, int, std::mutex&);

int main(int argc, char *argv[])
{
    if (argc != 2) {
        return -1;
    }

    N = atoi(argv[1]);

    srand(time(nullptr));

    int P = 1;
    std::cout << "Input P: ";
    std::cin >> P;
    if (P < 1 || P > 10) {
        return -1;
    }
    std::cout << std::endl;

    auto* threads = new std::thread[P];
    std::mutex mx;

    int k = N / P;
    for (int i = 0; i < P; ++i) {
        sums.push_back(0);
    }

    std::chrono::time_point<std::chrono::high_resolution_clock> start, end;
    start = std::chrono::high_resolution_clock::now();

    for (int i = 0; i < P; i++) {
        int from = k * i + 1;
        int to = i == P - 1 ? k * (i + 1) + N % P : k * (i + 1);
        threads[i] = std::thread(foo, i, from, to, ref(mx));
    }

    for (int i = 0; i < P; i++) {
        threads[i].join();
    }

    long long result = 0;
    for (int i = 0; i < P; i++) {
        result += sums[i];
    }

    end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> diff = end - start;

    std::cout << "Result " << result << std::endl;

    double time = diff.count();
    std::cout << "Time to sum: " << time << "s" << std::endl;

    delete[] threads;
    return 0;
}

void foo(int l, int from, int to, std::mutex& mx)
{
    long long sum = 0;
    for (int i = from; i <= to; i++) {
        sum += i;
    }

    sums[l] = sum;
    /*std::unique_lock<std::mutex> ulmx(mx);
    std::cout << "Thread " << l << " from = " << from << " to = " << to << " sums[" << l << "] = " << sums[l] << std::endl;
    ulmx.unlock();*/
}
