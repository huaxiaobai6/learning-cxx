#include "../exercise.h"
#include <iostream>
#include <cmath> // 用于 std::fabs

// 函数模板定义
template <typename T>
T plus(T a, T b) {
    return a + b;
}

int main(int argc, char **argv) {
    // 整数测试
    ASSERT(plus(1, 2) == 3, "Plus two int");
    ASSERT(plus(1u, 2u) == 3u, "Plus two unsigned int");

    // 浮点数测试
    ASSERT(plus(1.25f, 2.5f) == 3.75f, "Plus two float");
    ASSERT(plus(1.25, 2.5) == 3.75, "Plus two double");

    // 由于浮点数运算可能存在精度问题，直接使用 == 比较可能不可靠。
    // 我们可以通过比较两个浮点数的差值是否在一个很小的范围内来判断它们是否相等。
    const double epsilon = 1e-9; // 定义一个很小的误差范围
    ASSERT(std::fabs(plus(0.1, 0.2) - 0.3) < epsilon, "Plus two double with epsilon");
    return 0;
}