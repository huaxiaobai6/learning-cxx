#include <iostream>
#include <cassert>
#include <utility> // for std::move

// 假设 exercise.h 提供了 ASSERT 宏
//#include "../exercise.h"
#define ASSERT(condition, message) do { if (!(condition)) { std::cerr << message << std::endl; return 1; } } while(0)

class DynFibonacci {
    size_t *cache;
    int cached;

public:
    // 实现动态设置容量的构造器
    DynFibonacci(int capacity) : cache(new size_t[capacity]), cached(2) {
        cache[0] = 0;
        cache[1] = 1;
    }

    // 实现移动构造器
    DynFibonacci(DynFibonacci &&other) noexcept : cache(nullptr), cached(0) {
        cache = other.cache;
        cached = other.cached;

        other.cache = nullptr;
        other.cached = 0;
    }

    // 实现移动赋值
    DynFibonacci &operator=(DynFibonacci &&other) noexcept {
        if (this == &other) {
            return *this; // 处理自我赋值
        }

        delete[] cache; // 释放当前对象的资源

        cache = other.cache;
        cached = other.cached;

        other.cache = nullptr;
        other.cached = 0;

        return *this;
    }

    // 实现析构器，释放缓存空间
    ~DynFibonacci() {
        delete[] cache;
    }

    // 实现正确的缓存优化斐波那契计算
    size_t operator[](int i) {
        if (i < cached) {
            return cache[i]; // 如果已经在缓存中，直接返回
        }

        // 如果请求的斐波那契数不在缓存中，计算它并填充缓存
        for (int j = cached; j <= i; ++j) {
            if (j >= 2) { // 确保不会访问未初始化的缓存
                cache[j] = cache[j - 1] + cache[j - 2];
            }
            cached = j + 1; // 更新缓存计数
        }

        return cache[i];
    }

    // NOTICE: 不要修改这个方法
    size_t operator[](int i) const {
        ASSERT(i <= cached, "i out of range");
        return cache[i];
    }

    // NOTICE: 不要修改这个方法
    bool is_alive() const {
        return cache != nullptr;
    }
};

int main(int argc, char **argv) {
    DynFibonacci fib(12);
    ASSERT(fib[10] == 55, "fibonacci(10) should be 55");

    DynFibonacci const fib_ = std::move(fib);
    ASSERT(!fib.is_alive(), "Object moved");
    ASSERT(fib_[10] == 55, "fibonacci(10) should be 55");

    DynFibonacci fib0(6);
    DynFibonacci fib1(12);

    fib0 = std::move(fib1);
    fib0 = std::move(fib0); // 自我移动赋值，应该安全
    ASSERT(fib0[10] == 55, "fibonacci(10) should be 55");

    return 0;
}
