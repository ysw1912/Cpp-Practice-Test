### std::future

C++ 并发高级接口 std::future 对象内部存储一个异步调用的结果，即将来会被赋予的值，可通过 get() 访问该值，但如果该值还未被设置，那么 get() 将会阻塞。

可通过 3 种异步调用方式

1. std::promise
2. std::packaged_task
3. std::async

与 future 对象关联，设置该值。