#include <iostream>
#include <cassert>

// 假设 exercise.h 提供了 ASSERT 宏
//#include "../exercise.h"
#define ASSERT(condition, message) do { if (!(condition)) { std::cerr << message << std::endl; return 1; } } while(0)

class Fibonacci {
    size_t cache[16];
    int cached;

public:
    // 实现构造函数，初始化缓存
    Fibonacci() : cached(2) {
        cache[0] = 0;
        cache[1] = 1;
    }

    // 实现正确的缓存优化斐波那契计算
    size_t get(int i) {
        if (i < cached) {
            return cache[i]; // 如果已经在缓存中，直接返回
        }

        // 如果请求的斐波那契数不在缓存中，计算它并填充缓存
        for (int j = cached; j <= i; ++j) {
            cache[j] = cache[j - 1] + cache[j - 2];
            cached = j + 1; // 更新缓存计数
        }

        return cache[i];
    }
};

int main(int argc, char **argv) {
    Fibonacci fib;
    ASSERT(fib.get(10) == 55, "fibonacci(10) should be 55");
    std::cout << "fibonacci(10) = " << fib.get(10) << std::endl;
    return 0;
}
