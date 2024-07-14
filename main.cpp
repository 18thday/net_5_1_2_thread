#include <iostream>
#include <thread>
#include <chrono>
#include <vector>

void add_two_vectors(std::vector<int>& res, const std::vector<int>& lhs, const std::vector<int>& rhs, size_t begin_pos, size_t end_pos) {
    for (size_t i = begin_pos; i < end_pos; ++i) {
        res[i] = lhs[i] + rhs[i];
    }
}

void VectorSumTest(size_t element_count, size_t thread_count) {
    std::vector<int> v1(element_count);
    std::vector<int> v2(element_count);
    std::vector<int> res;
    res.reserve(element_count);

    std::vector<std::thread> th_vec;
    th_vec.reserve(thread_count);

    size_t backet_element_count = element_count / thread_count;

    auto start = std::chrono::steady_clock::now();
    for (size_t i = 0; i < thread_count; ++i) {
        th_vec.push_back(std::thread(add_two_vectors, std::ref(res),  std::ref(v1), std::ref(v2),
                                     i * backet_element_count, std::min((i+1) * backet_element_count, v1.size())));
    }
    for (size_t i = 0; i < thread_count; ++i) {
        th_vec[i].join();
    }

    auto finish = std::chrono::steady_clock::now();
    std::chrono::duration<double> dur = finish - start;
    std::cout << '\t' << dur.count() << 's';
}

int main() {
    std::cout << "the number of concurrent threads supported by the implementation: " << std::thread::hardware_concurrency() << "\n\n";
    size_t c3 = 1'000;
    size_t c4 = 10'000;
    size_t c5 = 100'000;
    size_t c6 = 1'000'000;
    size_t c7 = 10'000'000;

    std::cout << '\t' << '\t' << '\t' << c3 << '\t' << '\t' << c4 << '\t' << '\t' << c5 << '\t' << '\t' << c6  << '\t' << '\t' << c7 << std::endl;

    {
        size_t thread_count = 1;
        std::cout << "1 thread ";
        VectorSumTest(c3, thread_count);
        VectorSumTest(c4, thread_count);
        VectorSumTest(c5, thread_count);
        VectorSumTest(c6, thread_count);
        VectorSumTest(c7, thread_count);
        std::cout << std::endl;
    }
    {
        size_t thread_count = 2;
        std::cout << "2 thread ";
        VectorSumTest(c3, thread_count);
        VectorSumTest(c4, thread_count);
        VectorSumTest(c5, thread_count);
        VectorSumTest(c6, thread_count);
        VectorSumTest(c7, thread_count);
        std::cout << std::endl;
    }
    {
        size_t thread_count = 4;
        std::cout << "4 thread ";
        VectorSumTest(c3, thread_count);
        VectorSumTest(c4, thread_count);
        VectorSumTest(c5, thread_count);
        VectorSumTest(c6, thread_count);
        VectorSumTest(c7, thread_count);
        std::cout << std::endl;
    }
    {
        size_t thread_count = 8;
        std::cout << "8 thread ";
        VectorSumTest(c3, thread_count);
        VectorSumTest(c4, thread_count);
        VectorSumTest(c5, thread_count);
        VectorSumTest(c6, thread_count);
        VectorSumTest(c7, thread_count);
        std::cout << std::endl;
    }
    {
        size_t thread_count = 16;
        std::cout << "16 thread ";
        VectorSumTest(c3, thread_count);
        VectorSumTest(c4, thread_count);
        VectorSumTest(c5, thread_count);
        VectorSumTest(c6, thread_count);
        VectorSumTest(c7, thread_count);
        std::cout << std::endl;
    }
    {
        size_t thread_count = 32;
        std::cout << "32 thread ";
        VectorSumTest(c3, thread_count);
        VectorSumTest(c4, thread_count);
        VectorSumTest(c5, thread_count);
        VectorSumTest(c6, thread_count);
        VectorSumTest(c7, thread_count);
        std::cout << std::endl;
    }
    return 0;
}
