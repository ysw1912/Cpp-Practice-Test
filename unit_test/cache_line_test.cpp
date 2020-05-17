// Cache line(64 bytes)是CPU同步的基本单位，缓存行隔离比伪共享效率高.
#include <chrono>
#include <thread>

struct Padding {
  volatile long p[7];
};

struct ClassWithoutPadding {
  volatile long x;
};

struct ClassWithPadding {
  volatile Padding p1;
  volatile long x;
  volatile Padding p2;
};

int main() {
  ClassWithoutPadding arr1[2];

  auto start = std::chrono::steady_clock::now();
  auto t1 = std::thread([&arr1]{
      for (int i = 0; i < 10000000; i++) {
        arr1[0].x = 1;
      }
  });
  auto t2 = std::thread([&arr1]{
      for (int i = 0; i < 10000000; i++) {
        arr1[1].x = 1;
      }
  });
  t1.join();
  t2.join();
  auto end = std::chrono::steady_clock::now();
  printf("\ntime: %f\n", static_cast<double>(std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count()));

  ClassWithPadding arr2[2];

  start = std::chrono::steady_clock::now();
  auto t3 = std::thread([&arr2]{
      for (int i = 0; i < 10000000; i++) {
        arr2[0].x = 1;
      }
  });
  auto t4 = std::thread([&arr2]{
      for (int i = 0; i < 10000000; i++) {
        arr2[1].x = 1;
      }
  });
  t3.join();
  t4.join();
  end = std::chrono::steady_clock::now();
  printf("\ntime: %f\n", static_cast<double>(std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count()));

  return 0;
}
