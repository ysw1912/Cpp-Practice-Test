#include "utils.h"

#include <assert.h>
#include <iostream>             // std::cout
#include <future>               // std::async, std::future
#include <chrono>               // std::chrono::milliseconds

int main()
{
  int num = 444444443;
  // 异步调用函数.
  std::future<bool> future = std::async(std::launch::async, IsPrime, num);
  // 检查当前 future 对象是否有效，即是否与某个共享状态相关联.
  assert(future.valid());

  // 等待共享状态的标志变为 ready, 若超时, 则继续等待.
  std::cout << "Checking";
  std::chrono::milliseconds span(100);
  while (future.wait_for(span) == std::future_status::timeout)
    std::cout << '.';

  bool value = future.get();
  std::cout << "\n" << num << " is " << (value ? "" : "not ") << "a prime.\n";

  // 返回共享的 future 对象, 可以被多次访问, future 对象本身不和任何共享状态相关联.
  std::future<int> fut = std::async([]{ return 10; });
  std::shared_future<int> shared_future = fut.share();
  assert(!fut.valid());
  std::cout << "value: " << shared_future.get() << '\n';
  std::cout << "value * 2: " << shared_future.get() * 2 << '\n';

  auto func = [](char c, int interval) {
    for (int i = 0; i < 5; ++i) {
      std::this_thread::sleep_for(std::chrono::milliseconds(interval));
      std::cout << c;
    }
  };
  // 异步调用函数, 即开启另外一个线程中调用.
  std::future<void> future1(std::async(std::launch::async, func, '1', 100));
  std::future<void> future2(std::async(std::launch::async, func, '2', 200));
  future1.get();
  future2.get();
  std::cout << '\n';
  // 延迟调用函数, 即访问共享状态时调用.
  future1 = std::async(std::launch::deferred, func, '1', 100);
  future2 = std::async(std::launch::deferred, func, '2', 200);
  future1.get();
  future2.get();
  std::cout << '\n';
  return 0;
}
