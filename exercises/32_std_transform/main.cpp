#include "../exercise.h"
#include <algorithm>
#include <string>
#include <vector>
#include <sstream> // 用于 std::ostringstream

int main(int argc, char **argv) {
    std::vector<int> val{8, 13, 21, 34, 55};
    std::vector<std::string> ans;

    // 预留空间以提高效率
    ans.resize(val.size());

    // 使用 std::transform 进行转换
    std::transform(val.begin(), val.end(), ans.begin(), [](int num) {
        std::ostringstream oss;
        oss << (num * 2); // 将数字乘以 2 并转换为字符串
        return oss.str();
    });

    // 断言检查
    ASSERT(ans.size() == val.size(), "ans size should be equal to val size");
    ASSERT(ans[0] == "16", "ans[0] should be 16");
    ASSERT(ans[1] == "26", "ans[1] should be 26");
    ASSERT(ans[2] == "42", "ans[2] should be 42");
    ASSERT(ans[3] == "68", "ans[3] should be 68");
    ASSERT(ans[4] == "110", "ans[4] should be 110");

    return 0;
}
