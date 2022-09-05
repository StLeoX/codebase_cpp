//
// Created by leolaxie on 2022/9/5.
// Copyright 2022, Tencent Inc.
//
// ref AS ret
// why: https://www.zhihu.com/question/353263548

#include <iostream>

using namespace std;

double vals[] = {10.1, 12.6, 33.1, 24.1, 50.0};

double &setValues(int i)
{
    double &ref = vals[i];
    return ref;   // 返回第 i 个元素的引用，ref 是一个引用变量，ref 引用 vals[i]
}

int main()
{
    cout << "before" << endl;
    for (int i = 0; i < 5; i++)
    {
        cout << "vals[" << i << "] = ";
        cout << vals[i] << endl;
    }

    setValues(1) = 20.23; // 改变第 2 个元素
    setValues(3) = 70.8;  // 改变第 4 个元素

    cout << "after" << endl;
    for (int i = 0; i < 5; i++)
    {
        cout << "vals[" << i << "] = ";
        cout << vals[i] << endl;
    }
    return 0;
}
