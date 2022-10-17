## lib_cb

ToC:

- uuid_generator: UUID生成器。线程安全，全局唯一。
- event_manager: event管理器。自定义evet结构，非线程安全且多个相同事件的处理函数调用顺序不确定。