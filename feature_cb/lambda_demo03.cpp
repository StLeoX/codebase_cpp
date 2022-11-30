//
// Created by StLeoX on 2022/11/30.
// Ways to implement `recursive lambda`
//

#include <functional>
#include <iostream>

// 1. with `std::function` and through capture list
void impl01()
{
    const std::function<int(int)> factorial = [&factorial](int n)
    {
        return n > 1 ? n * factorial(n - 1) : 1;
    };
    std::cout << factorial(10) << std::endl;
}

// 2. define a `generic lambda` and pass itself as an argument
void impl02()
{
    const auto factorial = [](int n)
    {
        // define a generic lambda
        const auto fact_impl = [](int n, const auto &impl) -> int
        {
            return n > 1 ? n * impl(n - 1, impl) : 1;
        };
        // pass itself
        return fact_impl(n, fact_impl)
    };
    std::cout << factorial(10) << std::endl;
}

int main(int argc, char *argv[])
{
    impl01();
    impl02();
    return 0;
}

