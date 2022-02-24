#include "task4.h"

int* arr;
int N;
int* create_random_array(int);
void print_array(int*);
void foo(int, int, std::mutex&);
int largest_prime_divisor(int);

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
    std::mutex mx;

    std::cout << "Input N: ";
    std::cin >> N;

    arr = create_random_array(N);
    print_array(arr);

    int k = N / P;
    for (int i = 0; i < P; i++) {
        threads[i] = std::thread(foo, k * i, k * (i + 1) - 1, ref(mx));
    }

    std::unique_lock<std::mutex> ulmx(mx);
    std::cout << "Main thread id = " << std::this_thread::get_id() << std::endl;
    ulmx.unlock();

    for (int i = 0; i < P; i++) {
        threads[i].join();
    }

    print_array(arr);

    delete[] arr;
    delete[] threads;
    return 0;
}

int* create_random_array(int size)
{
    int *result = new int[size];
    for (int i = 0; i < size; i++) {
        result[i] = rand() % 1000000 + 100000;
    }
    return result;
}

void print_array(int* array)
{
    for (int i = 0; i < N; i++) {
        std::cout << array[i] << " ";
    }
    std::cout << std::endl;
}

void foo(int from, int to, std::mutex& mx)
{
    std::cout << "Thread " << std::this_thread::get_id() << " start..." << std::endl;
    for (int i = from; i <= to; i++) {
        std::this_thread::sleep_for(std::chrono::milliseconds(rand()%1000));
        std::lock_guard<std::mutex> lgmx(mx);
        arr[i] = largest_prime_divisor(arr[i]);
        std::cout << "Thread " << std::this_thread::get_id() << " arr[" << i << "] = " << arr[i] << std::endl;
    }

    std::cout << "Thread " << std::this_thread::get_id() << " finish!" << std::endl;
}

int largest_prime_divisor(int num)
{
    int max = 0;
    int d = 2;
    while (d * d <= num) {
        if (num % d == 0) {
            if (d > max) {
                max = d;
            }
            num /= d;
        } else {
            d++;
        }
    }

    if (num > 1 && num > max) {
      max = num;
    }

    return max;
}
