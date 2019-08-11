#include <exception>      // std::exception, std::current_exception
#include <functional>     // std::ref
#include <future>         // std::promise, std::future
#include <iostream>       // std::cout
#include <thread>         // std::thread

void SetSharedState(std::promise<int>& promise) {
  int val;
  std::cout << "Enter an integer value: " << std::endl;
  // 设置 cin 异常，若输入不是 int 类型则 raise.
  std::cin.exceptions(std::ios::failbit);
  try {
    std::cin >> val;
    promise.set_value(val);
  } catch (...) {
    // 为 promise 设置异常.
    promise.set_exception(std::current_exception());
  }
}

void PrintSharedState(std::future<int>& future) {
  try {
    int val = future.get();
    std::cout << "value: " << val << '\n';
  } catch (std::exception& ex) {
    std::cout << "[Exception caught: " << ex.what() << "]\n";
  }
}

int main()
{
  // 生成 promise 对象并与 future 对象关联.
  std::promise<int> promise;
  std::future<int> future = promise.get_future();

  // 线程1设置共享状态的值，线程2打印共享状态的值.
  std::thread thread1(SetSharedState, std::ref(promise));
  std::thread thread2(PrintSharedState, std::ref(future));

  thread1.join();
  thread2.join();
  return 0;
}