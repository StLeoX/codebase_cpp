//
// Created by leolaxie on 2022/8/31.
// Copyright 2022, Tencent Inc.
//

#include <iostream>

int main()
{
    if (__cplusplus > 201703L) std::cout << "C++2a" << std::endl;
    else if (__cplusplus == 201703L) std::cout << "C++17" << std::endl;
    else if (__cplusplus == 201402L) std::cout << "C++14" << std::endl;
    else if (__cplusplus == 201103L) std::cout << "C++11" << std::endl;
    else if (__cplusplus == 199711L) std::cout << "C++98" << std::endl;
    else std::cout << "C++" << std::endl;
}
