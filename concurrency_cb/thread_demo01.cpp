//
// Created by leolaxie on 2022/9/21.
//

#include <iostream>
#include <string>
#include <thread>
#include <mutex>
#include <condition_variable>
#include <functional>
#include <chrono>

std::mutex m;
std::condition_variable cv;
std::string data;
bool ready = false;
bool processed = false;

void worker_thread()
{
    // Wait until main() sends data
    std::unique_lock<std::mutex> lk(m);
    cv.wait(lk, [] { return ready; });

    // after the wait, we own the lock.
    std::cout << "Worker thread is processing data\n";
    data += " after processing";

    // Send data back to main()
    processed = true;
    std::cout << "Worker thread signals data processing completed\n";

    // Manual unlocking is done before notifying, to avoid waking up
    // the waiting thread only to block again (see notify_one for details)
    lk.unlock();
    cv.notify_one();
}

void condition_variable_demo()
{
    std::thread worker(worker_thread);

    data = "Example data";
    // send data to the worker thread
    {
        std::lock_guard<std::mutex> lk(m);
        ready = true;
        std::cout << "main() signals data ready for processing\n";
    }
    cv.notify_one();

    // wait for the worker
    {
        std::unique_lock<std::mutex> lk(m);
        cv.wait(lk, [] { return processed; });
    }
    std::cout << "Back in main(), data = " << data << '\n';

    worker.join();
}


// callback hell
void AsyncAddOne(int value, std::function<void(int)> callback)
{
    std::thread([value, callback]
                {
                    std::cout << value;
                    std::this_thread::sleep_for(std::chrono::milliseconds(100));
                    callback(value + 1);
                }).detach();
}

void callback_hell_demo()
{
    AsyncAddOne(1, [](int result)
    {
        AsyncAddOne(result, [](int result)
        {
            AsyncAddOne(result, [](int result)
            {
                std::cout << result;
            });
        });
    });
}

int main()
{
    callback_hell_demo();
}