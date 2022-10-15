//
// Created by StLeoX on 2022/10/15.
//

#include <iostream>
#include <thread>
#include <string>
#include <mutex>

using namespace std;

mutex mt;

void lock_guard_demo()
{
    for (int i = 10; i--;)
    {
        lock_guard<mutex> guard(mt);
        cout << "print thread: " << i << endl;
    }
}

void unique_lock_demo()
{
    for (int i = 10; i--;)
    {
        std::unique_lock guard(mt);
        cout << "print thread: " << i << endl;
        // guard.unlock(); // 能提前释放锁，以减小封锁粒度
    }
}

int main()
{
    thread t(lock_guard_demo);
    for (int i = 10; i--;)
    {
        lock_guard<mutex> guard(mt);
        cout << "print main: " << i << endl;
    }
    t.join();
    return 0;
}