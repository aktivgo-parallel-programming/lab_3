#include "task4.h"

int* arr;
int N;
int* create_random_vector(int);
void print_vector(int*);
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

    arr = create_random_vector(N);
    print_vector(arr);

    int k = N / P;

    std::chrono::time_point<std::chrono::high_resolution_clock> start, end;
    start = std::chrono::high_resolution_clock::now();

    for (int i = 0; i < P; i++) {
        threads[i] = std::thread(foo, k * i, k * (i + 1) - 1, ref(mx));
    }

    for (int i = 0; i < P; i++) {
        threads[i].join();
    }

    end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> diff = end - start;

    double time = diff.count();
    std::cout << "Time to process: " << time << "s" << std::endl;

    print_vector(arr);

    delete[] arr;
    delete[] threads;
    return 0;
}

int* create_random_vector(int size)
{
    int *result = new int[size];
    for (int i = 0; i < size; i++) {
        //result[i] = 100000 + (rand() % (1000000 - 100000 + 1));
        result[i] = 100000 + (rand() % (100 - 3 + 1));
    }
    return result;
}

void print_vector(int* array)
{
    for (int i = 0; i < N; i++) {
        std::cout << array[i] << " ";
    }
    std::cout << std::endl;
}

void foo(int from, int to, std::mutex& mx)
{
    for (int i = from; i <= to; i++) {
        //std::this_thread::sleep_for(std::chrono::milliseconds(10));
        arr[i] = largest_prime_divisor(arr[i]);
        //std::lock_guard<std::mutex> lgmx(mx);
        //std::cout << "Thread " << std::this_thread::get_id() << " arr[" << i << "] = " << arr[i] << std::endl;
    }
}

int largest_prime_divisor(int n)
{
    int maxPrime = -1;

    // Пока число четное, делим его на 2
    while (n % 2 == 0) {
        maxPrime = 2;
        n /= 2;
    }

    // Пока число делится на 3, делим его на 3
    while (n % 3 == 0) {
        maxPrime = 3;
        n /= 3;
    }

    // Проходим по натуральным числам, которые не делятся на 2 и 3
    for (int i = 5; i <= sqrt(n); i += 6) {
        // Пока число делится на i, делим его на i
        while (n % i == 0) {
            maxPrime = i;
            n /= i;
        }
        // Пока число делится на i + 2, делим его на i + 2
        while (n % (i + 2) == 0) {
            maxPrime = i + 2;
            n /= i + 2;
        }
    }

    // n - простое число больше 4
    if (n > 4)
        maxPrime = n;

    return maxPrime;
}
