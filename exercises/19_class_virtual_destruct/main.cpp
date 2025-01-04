#include "../exercise.h"

struct A {
    static int num_a; // 声明静态字段

    A() {
        ++num_a;
    }
    virtual ~A() { // 虚析构函数
        --num_a;
    }

    virtual char name() const {
        return 'A';
    }
};

int A::num_a = 0; // 定义并初始化静态字段

struct B final : public A {
    static int num_b; // 声明静态字段

    B() {
        ++num_b;
    }
    ~B() {
        --num_b;
    }

    char name() const final {
        return 'B';
    }
};

int B::num_b = 0; // 定义并初始化静态字段

int main(int argc, char **argv) {
    auto a = new A;
    auto b = new B;
    ASSERT(A::num_a == 2, "Fill in the correct value for A::num_a"); // 创建了一个A和一个B，B也包含一个A
    ASSERT(B::num_b == 1, "Fill in the correct value for B::num_b");
    ASSERT(a->name() == 'A', "Fill in the correct value for a->name()");
    ASSERT(b->name() == 'B', "Fill in the correct value for b->name()");

    delete a;
    delete b;
    ASSERT(A::num_a == 0, "Every A was destroyed");
    ASSERT(B::num_b == 0, "Every B was destroyed");

    A *ab = new B; // 派生类指针可以随意转换为基类指针
    ASSERT(A::num_a == 1, "Fill in the correct value for A::num_a"); // 创建了一个B，B包含一个A
    ASSERT(B::num_b == 1, "Fill in the correct value for B::num_b");
    ASSERT(ab->name() == 'B', "Fill in the correct value for ab->name()"); // 多态调用

    B &bb = dynamic_cast<B&>(*ab); // 使用dynamic_cast进行安全转换
    ASSERT(bb.name() == 'B', "Fill in the correct value for bb->name()");

    delete ab; // 通过指针可以删除指向的对象，即使是多态对象
    ASSERT(A::num_a == 0, "Every A was destroyed");
    ASSERT(B::num_b == 0, "Every B was destroyed");

    return 0;
}
