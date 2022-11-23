//
// Created by StLeoX on 2022/11/23.
// C++11 std::regex 的各种用例
//


#include <iostream>
#include <string>
#include <regex>

static const std::string fnames[] = {"foo.txt", "bar.txt", "test", "a0.txt", "AAA.txt"};
// 在 C++ 中 \ 会被作为字符串内的转义符，
// 为使 \. 作为正则表达式传递进去生效，需要对 \ 进行二次转义，从而有 \\.
static const std::regex regex1("[a-z]+\\.txt");
// 或基于 原始字符串字面量 写法，R"(str)"
// static const std::regex regex1(R"([a-z]+\.txt)");

auto demo01() -> void
{
    for (const auto &fname: fnames)
        std::cout << fname << ": " << std::regex_match(fname, regex1) << std::endl;
}

auto demo02() -> void
{
    // 结果集：保存每一个匹配的结果，类型类似于 vector<string>
    std::smatch match_result;
    int match_count = 0;
    for (const auto &fname: fnames)
    {
        if (std::regex_match(fname, match_result, regex1))
        {
            for (const auto &item: match_result)
            {
                std::cout << "result" << (++match_count) << " is " << item.str() << std::endl;
            }
        }
    }
}

int main(int argc, char *argv[])
{
    demo01();
    std::cout << "" << std::endl;
    demo02();
    return 0;
}