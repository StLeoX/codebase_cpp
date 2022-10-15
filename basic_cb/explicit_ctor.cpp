//
// Created by leolaxie on 2022/9/5.
// Copyright 2022, Tencent Inc.
//
#include <iostream>

using namespace std;

class C
{
public:
    C() { cout << "no parameters ctor" << endl; }

    explicit C(int i = -1)
    {
        cout << "all default arguments ctor" << endl;
        _a = i;
    }

private:
    int _a;

};

int main()
{
//    C c; // CompilingError: call of overloaded 'C()' is ambiguous
//    C c(); // Compiled, non ctor was called (cout nothing), weather there is `explicit`
}