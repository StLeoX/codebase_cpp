//
// Created by leolaxie on 2022/9/21.
//

#include <iostream>
#include <future>
#include <thread>

/// std::future 的三种典型使用方式
void demo01()
{
    // future from a packaged_task
    std::packaged_task<int()> task1([] { return 1; }); // wrap the function
    std::future<int> f1 = task1.get_future();  // get a future
    std::thread t1(std::move(task1)); // launch on a thread

    // future from an async()
    std::future<int> f2 = std::async(std::launch::async, [] { return 2; });

    // future from a promise
    std::promise<int> p;
    std::future<int> f3 = p.get_future();
    std::thread([&p] { p.set_value_at_thread_exit(3); }).detach(); // launch on a thread

    std::cout << "Waiting..." << std::flush;
    f1.wait();
    f2.wait();
    f3.wait();
    std::cout << "Done!\nResults are: "
              << f1.get() << ' ' << f2.get() << ' ' << f3.get() << '\n';
    t1.join();
}

/// 针对 std::future 抛出异常
void demo02()
{
    std::promise<int> p;
    std::future<int> f = p.get_future();

    std::thread t([&p]
                  {
                      try
                      {
                          // code that may throw
                          throw std::runtime_error("Error");
                      } catch (...)
                      {
                          try
                          {
                              // store anything thrown in the promise
                              p.set_exception(std::current_exception());
                          } catch (...)
                          {} // set_exception() may throw too
                      }
                  });

    try
    {
        std::cout << f.get();
    } catch (const std::exception &e)
    {
        std::cout << "Exception from the thread: " << e.what() << '\n';
    }
    t.join();
}

int main(int argc, char *argv[])
{
    demo01();
    demo02();
    return 0;
}