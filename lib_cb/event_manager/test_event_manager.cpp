//
// Created by StLeoX on 2022/10/17.
//

#include <iostream>
#include "Event.h"
#include "EventManager.h"

class SystemA
{
public:
    SystemA()
    {
        REGISTER_EVENT(&SystemA::OnTest, this);
    }

    void OnTest(TestEvent &event)
    {
        std::cout << "From SystemA a = " << event.a << " b = " << event.b << std::endl;
    }
};


class SystemB
{
public:
    SystemB()
    {
        REGISTER_EVENT(&SystemB::OnTest, this);
    }

    void OnTest(TestEvent &event)
    {
        std::cout << "From SystemB a = " << event.a << " b = " << event.b << std::endl;
    }
};

void OnTest(TestEvent &event)
{
    std::cout << "From OnTest Function a = " << event.a << " b = " << event.b << std::endl;
}


int main()
{
    SystemA a;
    SystemB b;
    EventManager::GetSingleton().RegisterEvent(OnTest);
    TestEvent event{1, 2.5};
    EMIT_EVENT(event)
    return 0;
}
