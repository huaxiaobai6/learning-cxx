#include <iostream>
#include <cassert>

// 假设 exercise.h 提供了 ASSERT 宏
//#include "../exercise.h"
#define ASSERT(condition, message) do { if (!(condition)) { std::cerr << message << std::endl; return 1; } } while(0)

struct FibonacciCache {
    unsigned long long cache[16] = {0, 1}; // 初始化前两个斐波那契数
    int cached = 2; // 当前缓存中已经计算了的斐波那契数的数量
};

static unsigned long long fibonacci(FibonacciCache &cache, int i) {
    if (i < cache.cached) {
        return cache.cache[i]; // 如果已经在缓存中，直接返回
    }

    // 如果请求的斐波那契数不在缓存中，计算它并填充缓存
    for (int j = cache.cached; j <= i; ++j) {
        if (j == 0) cache.cache[j] = 0; // 理论上不需要，因为已经初始化
        else if (j == 1) cache.cache[j] = 1; // 理论上不需要，因为已经初始化
        else cache.cache[j] = cache.cache[j - 1] + cache.cache[j - 2];
        cache.cached = j + 1; // 更新缓存计数
    }

    return cache.cache[i];
}

int main(int argc, char **argv) {
    FibonacciCache fib;
    ASSERT(fibonacci(fib, 10) == 55, "fibonacci(10) should be 55");
    std::cout << "fibonacci(10) = " << fibonacci(fib, 10) << std::endl;
    return 0;
}
