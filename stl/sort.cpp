//
// Created by leolaxie on 2022/7/19.
//

#include <cstdio>
#include <cstdint>
#include <stdint.h>
#include <string>
#include <vector>
#include <unordered_map>
#include <algorithm>

bool cmp(std::pair<std::string, uint32_t> &a, std::pair<std::string, uint32_t> &b)
{
    return a.first < b.first;
}

static void sort_table_by_first(const std::unordered_map<std::string, uint32_t> &src, std::vector<std::pair<std::string, uint32_t>> *dst)
{
    if (dst == nullptr) return;
    // 拷贝方式1
    dst->insert(dst->begin(), src.begin(), src.end());

    // 拷贝方式2
    for (const auto &item: src)
        dst->push_back({item.first, item.second});

    // 比较方式1
    std::sort(dst->begin(), dst->end(), cmp);

    // 比较方式2
    std::sort(dst->begin(), dst->end(), [=](std::pair<std::string, uint32_t> &a, std::pair<std::string, uint32_t> &b)
    {
        return a.first < b.first;
    });
}


void test_sort_table_by_first()
{
    std::unordered_map<std::string, uint32_t> in1 = {{"cd", 1},
                                                     {"bc", 2},
                                                     {"a",  3},
                                                     {"b",  4}};
    std::vector<std::pair<std::string, uint32_t>> out1;
    sort_table_by_first(in1, &out1);
    for (auto &item: out1)
    {
        printf("%s-%u\n", item.first.c_str(), item.second);
    }
}
