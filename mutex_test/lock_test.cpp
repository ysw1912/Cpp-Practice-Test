#include <chrono>
#include <thread>

int main()
{
  int n = 37;
  auto start = std::chrono::steady_clock::now();
  for (int i = 0; i < n; i++) {
    std::thread([]{ printf("."); }).detach();
    std::this_thread::sleep_for(std::chrono::milliseconds(1000 / n));
  }
  auto end = std::chrono::steady_clock::now();
  printf("\ntime: %f\n", static_cast<double>(std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count()));
  return 0;
}
