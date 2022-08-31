//
// Created by leolaxie on 2022/8/31.
// Copyright 2022, Tencent Inc.
//

#include "heavy.h"

Heavy f()
{
    Heavy h;
    return h;
}

void t1()
{
    Heavy h1 = Heavy(); // default-ctor + RVO
    // other formats:
    // Heavy h(); // no!
    // Heavy h=();
    // Heavy h={};
    // Heavy h{};
    Heavy &&h2 = Heavy(); // default-ctor + ref-to-rvalue
    const Heavy &h3 = Heavy(); // default-ctor + ref-to-const
    // or, Heavy const &
}

void t2()
{
    Heavy h1 = f(); // RVO
    // Heavy &h = f(); // inlegal
    Heavy &&h2 = f(); // ref-to-rvalue
    Heavy const &h3 = f(); // ref-to-const
}

int main()
{
    std::cout << "t1" << std::endl;
    t1();
    std::cout << "t2" << std::endl;
    t2();
}