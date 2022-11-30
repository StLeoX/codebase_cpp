//
// Created by StLeoX on 2022/11/17.
// Passing the copy of `this` object to lambda
//

#include <iostream>
#include <string>
#include <thread>

class Data
{
private:
    std::string name;
public:
    Data(const std::string &s) : name(s)
    {
    }

    auto startThreadWithCopyOfThis() const
    {
        // start and return new thread using this after 3 seconds:
        using namespace std::literals;
        std::thread t([*this]
                      {
                          std::this_thread::sleep_for(1s);
                          std::cout << name << '\n';
                      });
        return t;
    }
};

int main()
{
    std::thread t;
    {
        Data d{"c1"};
        t = d.startThreadWithCopyOfThis();
    } // d is no longer valid
    t.join();
}