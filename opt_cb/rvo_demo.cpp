//
// Created by leolaxie on 2022/8/31.
// Copyright 2022, Tencent Inc.
//
// ref: https://www.jianshu.com/p/dcd3390c5c84

/* conclusion:
 * - Moving a local object in a return statement prevents copy elision;
 * - "Copying" a local object in a return statement **might** cause copy elision, then no move construction;
 * - SSA avoid move construction, with copy elision;
 * */

#include "heavy.h"

typedef Heavy (*F)();

Heavy f1()
{
    Heavy h;
    return h;
}

Heavy f2_1(int i) // unfollow SSA
{
    if (i > 0)
    {
        Heavy a;
        return a;
    } else
    {
        Heavy b;
        return b;
    }
}

Heavy f2_2(int i) // follow SSA
{
    Heavy a;
    if (i > 0)
    {
        a.s = std::to_string(i);
        return a;
    } else
    {
        a.s = std::to_string(-i);
        return a;
    }
}

Heavy f2()
{
    // return f2_1(0);
    return f2_2(0);
}

Heavy f3()
{
    Heavy h;
    return std::move(h); // call the move ctor
}

Heavy f4()
{
    Heavy h;
    return static_cast<Heavy &>(h); // call the copy stor
}


void t1(F f)
{
    f();
}

void t2(F f)
{
    const Heavy &h = f();
}

void t3(F f)
{
    Heavy h = f();
    std::cout << std::endl;
    h = f();
}

int main()
{
    std::cout << "t1" << std::endl;
    t1(f1);
    std::cout << "t2" << std::endl;
    t2(f1);
    std::cout << "t3" << std::endl;
    t3(f1);
}