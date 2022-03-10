#include <vector>
#include "task5.h"

int N;
std::vector<std::vector<int>> matrix;
std::vector<int> vector;
std::vector<int> result;

std::vector<int> create_random_vector(int);
void print_vector(std::vector<int>);
std::vector<std::vector<int>> create_random_matrix(int);
void print_matrix(std::vector<std::vector<int>>);
std::vector<int> multiply_sequentially(std::vector<std::vector<int>>, std::vector<int>);
void foo(int, int, std::mutex&);

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

    matrix = create_random_matrix(N);
    //print_matrix(matrix);

    vector = create_random_vector(N);
    //print_vector(vector);
    //std::cout << std::endl;

    std::chrono::time_point<std::chrono::high_resolution_clock> start, end;
    start = std::chrono::high_resolution_clock::now();

    std::vector<int> res = multiply_sequentially(matrix, vector);

    end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> diff = end - start;

    //print_vector(res);

    double time = diff.count();
    std::cout << "Time to process sequentially: " << time << "s" << std::endl;

    for (int i = 0; i < N; ++i) {
        result.push_back(0);
    }

    int k = N / P;

    start = std::chrono::high_resolution_clock::now();

    for (int i = 0; i < P; i++) {
        threads[i] = std::thread(foo, k * i, k * (i + 1) - 1, ref(mx));
    }

    for (int i = 0; i < P; i++) {
        threads[i].join();
    }

    end = std::chrono::high_resolution_clock::now();
    diff = end - start;

   //print_vector(result);

    time = diff.count();
    std::cout << "Time to process parallel: " << time << "s" << std::endl;

    delete[] threads;
    return 0;
}

std::vector<int> create_random_vector(int size)
{
    std::vector<int> res(size);
    for (int i = 0; i < size; i++) {
        res[i] = (rand() % 3 + 1);
    }
    return res;
}

void print_vector(std::vector<int> v)
{
    for (int i : v) {
        std::cout << i << " ";
    }
    std::cout << std::endl;
}

std::vector<std::vector<int>> create_random_matrix(int size)
{
    std::vector<std::vector<int>> res;
    for (int i = 0; i < size; i++) {
        res.emplace_back();
        for (int j = 0; j < size; ++j) {
            res[i].push_back(rand() % 3 + 1);
        }
    }
    return res;
}

void print_matrix(std::vector<std::vector<int>> m)
{
    for (const std::vector<int>& line : m) {
        for (int item : line) {
            std::cout << item << " ";
        }
        std::cout << std::endl;
    }
    std::cout << std::endl;
}

std::vector<int> multiply_sequentially(std::vector<std::vector<int>> m, std::vector<int> v) {
    std::vector<int> res;

    for (int i = 0; i < m.size(); i++) {
        res.push_back(0);
        for (int j = 0; j < v.size(); j++) {
            res[i] += m[i][j] * v[j];
        }
    }
    
    return res;
}

void foo(int from, int to, std::mutex& mx)
{
    for (int i = from; i <= to; i++) {
        for (int j = 0; j < vector.size(); j++) {
            result[i] += matrix[i][j] * vector[j];
        }
    }
}
