//
// Created by StLeoX on 2022/11/22.
// Abstract：std::tuple 使用示例
//

#include <tuple>
#include <iostream>

auto get_student(int id)
{
    // 返回类型被推断为 std::tuple<double, char, std::string>
    if (id == 0)
        return std::make_tuple(3.8, 'A', "张三");
    if (id == 1)
        return std::make_tuple(2.9, 'C', "李四");
    if (id == 2)
        return std::make_tuple(1.7, 'D', "王五");
    return std::make_tuple(0.0, 'D', "null");
    // 如果写 return 0 或其他不一致的类型，会出现类型推断错误，在编译期报错。
}

int main()
{
    // 利用 std::get 获取元组元素
    auto student = get_student(0);
    std::cout << "ID: 0, "
              << "GPA: " << std::get<0>(student) << ", "
              << "成绩: " << std::get<1>(student) << ", "
              << "姓名: " << std::get<2>(student) << '\n';

    // 利用 std::tie 对元组进行拆包，前提是声明相关变量
    double gpa;
    char grade;
    std::string name;
    std::tie(gpa, grade, name) = get_student(1);
    std::cout << "ID: 1, "
              << "GPA: " << gpa << ", "
              << "成绩: " << grade << ", "
              << "姓名: " << name << '\n';

    // 利用 结构化绑定 对元组进行拆包，不需要声明相关变量
    const auto &[gpa2, grade2, name2] = get_student(2);
    std::cout << "ID: 2, "
              << "GPA: " << gpa2 << ", "
              << "成绩: " << grade2 << ", "
              << "姓名: " << name2 << '\n';

    return 0;
}
