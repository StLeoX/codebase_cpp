//
// Created by StLeoX on 2022/11/27.
// c++2a std::ranges usecases : Ranges and Projections
// How to implement those projections: templates and std::invoke.
// `std::invoke` provides a uniform invoke syntax for various callable objects, including:
//   - regular call - no dereferencing needed;
//   - via reference wrapper - so we have to call .get() to get the object;
//   - in other cases we assume it’s a pointer, and then we need to dereference it. Typically, smart pointers.
//

#include <algorithm>
#include <iostream>
#include <ranges>
#include <vector>

void demo01(){
    std::vector vec { -1, 2, -3, 4, -5, 6 };
    auto print = [](int i) { std::cout << i << ", "; };
    std::ranges::sort(vec);
    std::cout << "regular sort:\n";
    std::ranges::for_each(vec, print);  // -5, -3, -1, 2, 4, 6,
}

void demo02(){
    std::vector vec { -1, 2, -3, 4, -5, 6 };
    auto print = [](int i) { std::cout << i << ", "; };
    std::cout << "with abs() projection: \n";
    /* 语义为：按照元素的绝对值进行排序；
     * 实现为：类似于map，先对元素逐个应用 map 获取一个中间序列，再传入 sort；
     * */
    std::ranges::sort(vec, {}, [](int i) { return std::abs(i); });
    std::ranges::for_each(vec, print);  // -1, 2, -3, 4, -5, 6,
}

struct Task {
    std::string desc;
    unsigned int priority { 0 };
};

/* 一个有用的实例
 * 实现了类似于 Python 的 sort(lambda, list) 的效果；
 * 即对依照结构的字段（Task::priority）进行排序，且避免了对 compare 行为的重写；
 * */
int demo03(){
    std::vector<Task> tasks {
            { "clean up my room", 10 }, {"finish homework", 5 },
            { "test a car", 8 }, { "buy new monitor", 12 }
    };
    auto print = [](Task& t) {
        std::cout << t.desc << ", priority: " << t.priority << '\n';
    };
    std::ranges::sort(tasks, std::ranges::greater{}, &Task::priority);
    std::cout << "my next priorities:\n";
    std::ranges::for_each(tasks, print);
}

