//
// Created by leo on 2022/2/9.
// Abstract：借助 std::variant 和 std::visit 实现对 std::tuple 的遍历访问
// ref：https://changkun.de/modern-cpp/zh-cn/04-containers/#%E8%BF%90%E8%A1%8C%E6%9C%9F%E7%B4%A2%E5%BC%95
// 动机：std::get<I>(T) 的泛型I依赖于一个编译期常数（典型如constexpr），所以借助 std::variant 的和类型性实现“运行时索引”
//

#include <tuple>
#include <iostream>
#include <variant>

template<size_t n, typename... T>
constexpr std::variant<T...> _tuple_index(const std::tuple<T...> &tpl, size_t i)
{
    if constexpr (n >= sizeof...(T))
        throw std::out_of_range("out_of_range");
    if (i == n)
        return std::variant<T...>{std::in_place_index<n>, std::get<n>(tpl)};
    return _tuple_index<(n < sizeof...(T) - 1 ? n + 1 : 0)>(tpl, i);
}

template<typename... T>
constexpr std::variant<T...> tuple_index(const std::tuple<T...> &tpl, size_t i)
{
    return _tuple_index<0>(tpl, i);
}

template<typename T0, typename ... Ts>
std::ostream &operator<<(std::ostream &s, std::variant<T0, Ts...> const &v)
{
    std::visit([&](auto &&x) { s << x; }, v);
    return s;
}

void demo01()
{
    std::tuple<std::string, double, double, int> t("123", 4.5, 6.7, 8);
    int i = 1;
    std::cout << tuple_index(t, i) << std::endl;
}

template<typename T>
auto tuple_len(T &t) -> size_t
{
    return std::tuple_size<T>::value;
}

void demo02()
{
    std::tuple<std::string, double, double, int> t("123", 4.5, 6.7, 8);
    // 通过下标进行遍历
    for (int i = 0; i != tuple_len(t); ++i)
    {
        // 泛型化的访问行为
        std::cout << tuple_index(t, i) << std::endl;
    }
}