// Intel CPU内的4bytes buffer.
#include <chrono>

#define MASK (((unsigned int)1 << (unsigned int)8) - 1)

int main() {

  char arrA[MASK];  char arrD[MASK];
  char arrB[MASK];  char arrE[MASK];
  char arrC[MASK];  char arrF[MASK];

  const int ITERATIONS = 10000000;

  auto start = std::chrono::steady_clock::now();
  int i = ITERATIONS;
  while (--i) {
    int slot = i & MASK;
    char c = static_cast<char>(i);
    arrA[slot] = c;
    arrB[slot] = c;
    arrC[slot] = c;
  }
  i = ITERATIONS;
  while (--i) {
    int slot = i & MASK;
    char c = static_cast<char>(i);
    arrD[slot] = c;
    arrE[slot] = c;
    arrF[slot] = c;
  }
  auto end = std::chrono::steady_clock::now();
  printf("\ntime: %f\n", static_cast<double>(std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count()));

  start = std::chrono::steady_clock::now();
  i = ITERATIONS;
  while (--i) {
    int slot = i & MASK;
    char c = static_cast<char>(i);
    arrA[slot] = c;
    arrB[slot] = c;
    arrC[slot] = c;
    arrD[slot] = c;
    arrE[slot] = c;
    arrF[slot] = c;
  }
  end = std::chrono::steady_clock::now();
  printf("\ntime: %f\n", static_cast<double>(std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count()));

  return 0;
}
