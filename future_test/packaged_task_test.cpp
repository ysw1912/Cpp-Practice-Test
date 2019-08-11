#include <iostream>     // std::cout
#include <future>       // std::packaged_task, std::future
#include <chrono>       // std::chrono::seconds
#include <thread>       // std::thread, std::this_thread::sleep_for

#include <assert.h>

int CountDown(int from, int to) {
  std::cout << "Counting...\n";
  for (int i = from; i != to; --i) {
    std::cout << i << ' ';
    std::this_thread::sleep_for(std::chrono::seconds(1));
  }
  std::cout << "\nFinished!\n";
  return from - to;
}

int main ()
{
  // 生成 packaged_task 对象并与 future 对象关联.
  std::packaged_task<int(int,int)> task(CountDown);
  std::future<int> future = task.get_future();
  // packaged_task 设置了有效的函数或可调用对象.
  assert(task.valid());
  // 本线程完成计数任务 packaged_task::operator().
  task(3, 0);
  // 等待任务完成并获取结果.
  int value = future.get();
  std::cout << "CountDown lasted for " << value << " seconds.\n";

  // 重用 packaged_task 对象.
  task.reset();
  future = task.get_future();
  // 创建新线程完成计数任务.
  std::thread thread(std::move(task), 5, 0);
  value = future.get();
  std::cout << "CountDown lasted for " << value << " seconds.\n";
  thread.join();
  return 0;
}