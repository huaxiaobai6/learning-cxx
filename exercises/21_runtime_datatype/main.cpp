#include "../exercise.h"
#include <cmath>

enum class DataType {
    Float,
    Double,
};

struct TaggedUnion {
    DataType type;
    union {
        float f;
        double d;
    };
};

// Sigmoid 函数分别针对 float 和 double
float sigmoid(float x) {
    return 1.0f / (1.0f + std::exp(-x));
}

double sigmoid(double x) {
    return 1.0 / (1.0 + std::exp(-x));
}

TaggedUnion sigmoid_dyn(TaggedUnion x) {
    TaggedUnion ans{x.type};

    // 根据 type 调用相应的 sigmoid 函数
    if (x.type == DataType::Float) {
        ans.f = sigmoid(x.f);
    } else if (x.type == DataType::Double) {
        ans.d = sigmoid(x.d);
    }

    return ans;
}

// ---- 不要修改以下代码 ----
int main(int argc, char **argv) {
    TaggedUnion xf{DataType::Float};
    xf.f = 5.f;
    auto yf = sigmoid_dyn(xf);
    ASSERT(yf.type == DataType::Float, "type mismatch");
    ASSERT(yf.f == 1 / (1 + std::exp(-5.f)), "sigmoid float");

    TaggedUnion xd{DataType::Double};
    xd.d = 5.0;
    auto yd = sigmoid_dyn(xd);
    ASSERT(yd.type == DataType::Double, "type mismatch");
    ASSERT(yd.d == 1 / (1 + std::exp(-5.0)), "sigmoid double");
    return 0;
}
