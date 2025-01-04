#include <iostream>
#include <cassert>

// 假设 exercise.h 提供了 ASSERT 宏
//#include "../exercise.h"
#define ASSERT(condition, message) do { if (!(condition)) { std::cerr << message << std::endl; return 1; } } while(0)

struct Fibonacci {
    int numbers[11];

    // 将 get 函数声明为 constexpr，以便在编译时计算
    constexpr int get(int i) const {
        return numbers[i]; // 直接返回数组中的值
    }
};

int main(int argc, char **argv) {
    // 使用 constexpr 初始化 Fibonacci 数组
    constexpr Fibonacci FIB{{0, 1, 1, 2, 3, 5, 8, 13, 21, 34, 55}};
    ASSERT(FIB.get(10) == 55, "fibonacci(10) should be 55");
    std::cout << "fibonacci(10) = " << FIB.get(10) << std::endl;
    return 0;
}
