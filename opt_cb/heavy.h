//
// Created by leolaxie on 2022/8/31.
// Copyright 2022, Tencent Inc.
//

#ifndef CPP_CODE_BASE_HEAVY_H
#define CPP_CODE_BASE_HEAVY_H

#include <iostream>
#include <string>

class Heavy
{
public:
    Heavy() // 无参构造
    {
        cnt += 1;
        std::cout << "default ctor, h" << cnt << std::endl;
    };

    ~Heavy() // 析构
    {
        std::cout << "dtor, h" << cnt << std::endl;
        cnt -= 1;
    };

    Heavy(Heavy const &h) // 拷贝构造
    {
        std::cout << "copy ctor " << std::endl;
        s = h.s;
    }

    Heavy &operator=(Heavy const &h) // 拷贝赋值
    {
        std::cout << "copy operator=" << std::endl;
        s = h.s;
        return *this;
    }

    Heavy(Heavy &&h) // 移动构造
    {
        std::cout << "move ctor" << std::endl;
        s = std::move(h.s);
    }

    Heavy &operator=(Heavy &&h) // 移动赋值
    {
        std::cout << "move operator=" << std::endl;
        s = std::move(h.s);
        return *this;
    }

private:
    static uint cnt;
    std::string s{};

};

uint Heavy::cnt = 0;

#endif //CPP_CODE_BASE_HEAVY_H
