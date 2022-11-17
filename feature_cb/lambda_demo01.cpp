//
// Created by leo on 2022/2/9.
// 本节：lambda函数的定义，以及捕获自由变量的多种方式。
//

// lambda函数的一般形式
/**
 * [捕获列表](参数列表) mutable(可选) 异常属性 -> 返回类型 {
 *     // 函数体
 * }
 * */

// 值捕获
void lambda_value_capture() {
    int value = 1;
    auto copy_value = [value] {
        return value;
    };
    value = 100;
    auto stored_value = copy_value();
    std::cout << "stored_value = " << stored_value << std::endl;
    // 这时, stored_value == 1, 而 value == 100.
    // 因为 copy_value 在创建时就保存了一份 value 的拷贝
}

// 引用捕获，使用引用符号&
void lambda_reference_capture() {
    int value = 1;
    auto copy_value = [&value] {
        return value;
    };
    value = 100;
    auto stored_value = copy_value();
    std::cout << "stored_value = " << stored_value << std::endl;
    // 这时, stored_value == 100, value == 100.
    // 因为 copy_value 保存的是引用
}

// 表达式捕获
#include <iostream>
#include <memory>  // implements make_unique
int lambda_expr_capture() {
    auto important = std::make_unique<int>(1);
    auto add = [v1 = 1, v2 = std::move(important)](int x, int y) -> int {
        return x+y+v1+(*v2);
    };
    std::cout << add(3,4) << std::endl;
    return 0;
}


using foo = void(int); // 定义函数类型, using创建别名
void functional(foo f) { // 定义在参数列表中的函数类型 foo 被视为退化后的函数指针类型 foo*
    f(1); // 通过函数指针调用函数
}

int main() {
    auto f = [](int value) {
        std::cout << value << std::endl;
    };
    // 当 Lambda 表达式的捕获列表为空时，闭包对象还能够转换为函数指针值进行传递。
    functional(f); // 传递闭包对象，隐式转换为 foo* 类型的函数指针值
    f(1); // lambda 表达式调用
    return 0;
}

