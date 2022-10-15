//
// Created by leolaxie on 2022/9/21.
//

#include <variant>
#include <string>

int main()
{
    std::variant<int, std::string> a; // a = 0
    a = 1;

    int type_idx = a.index(); // type_idx = 0

}