//
// Created by StLeoX on 2022/11/21.
// Abstract：通过 泛型std::variant 实现运行时多态
// ref：https://www.cppstories.com/2020/04/variant-virtual-polymorphism.html/
//

#include <iostream>
#include <variant>
#include <string>

// Those two classes should have derived from the base.
class Derived
{
public:
    void PrintName(std::string msg = "") const
    {
        std::cout << msg << std::endl;
        std::cout << "this is Derived" << std::endl;
    }
};

class ExtraDerived
{
public:
    void PrintName(std::string msg = "") const
    {
        std::cout << msg << std::endl;
        std::cout << "this is  ExtraDerived" << std::endl;
    }
};

// define the callable stub
struct CallPrintName
{
    void operator()(const Derived &d) { d.PrintName(); }

    void operator()(const ExtraDerived &ed) { ed.PrintName(); }
};

// two approaches for std::visit
auto demo01() -> void
{
    std::variant<Derived, ExtraDerived> xs;

    std::visit(CallPrintName{}, xs);  // the first call approach

    std::cout << "" << std::endl;

    std::visit([](const auto &obj) { obj.PrintName(); }, xs);// the second call approach
}


struct CallPrintNameWithArgs
{
    void operator()(const Derived &d) { d.PrintName(msg); }

    void operator()(const ExtraDerived &ed) { ed.PrintName(msg); }

    std::string msg;
};

// if we need to pass args
auto demo02() -> void
{
    std::variant<Derived, ExtraDerived> xs;

    auto caller = CallPrintNameWithArgs{};
    caller.msg = "this is msg1";
    std::visit(caller, xs);

    std::cout << "" << std::endl;

    std::string msg2 = "this is msg2";
    std::visit([&msg2](const auto &obj) { obj.PrintName(msg2); }, xs);
}

int main(int argc, char *argv[])
{
    demo01();
    std::cout << "" << std::endl;
    demo02();
    return 0;
}
