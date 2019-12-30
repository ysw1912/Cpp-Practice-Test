
#include <cstdarg>
#include <ctime>
#include <iostream>

void log_error(char* fmt, ...) {
  va_list args;
  va_start(args, fmt);
  char buf[256];
  vsnprintf(buf, sizeof(buf), fmt, args);
  va_end(args);
}

void demo_timeval() {
  struct timeval start{}, end{};
  mingw_gettimeofday(&start, nullptr);
  for (long i = 0; i < 1e8; i++);
  mingw_gettimeofday(&end, nullptr);
  long start_ms = start.tv_sec * 1000 + start.tv_usec / 1000;
  long end_ms = end.tv_sec * 1000 + end.tv_usec / 1000;
  printf("timeval   Duration: %ld (ms)\n", end_ms - start_ms);
}

void demo_clock() {
  clock_t start = clock();
  for (long i = 0; i < 1e8; i++);
  clock_t end = clock();
  double secs = static_cast<double>(end - start) / CLOCKS_PER_SEC;
  printf("clock()   Duration: %.3lf (ms)\n", secs * 1000);
}

// Recommended.
void demo_timespec() {
  struct timespec start{}, end{};
  clock_gettime(CLOCK_PROCESS_CPUTIME_ID, &start);
  for (long i = 0; i < 1e8; i++);
  clock_gettime(CLOCK_PROCESS_CPUTIME_ID, &end);
  double start_ms =
      static_cast<double>(start.tv_sec) * 1000 + start.tv_nsec / 1e6;
  double end_ms =
      static_cast<double>(end.tv_sec) * 1000 + end.tv_nsec / 1e6;
  printf("timespec  Duration: %.3lf (ms)\n", end_ms - start_ms);
}

int main() {
  printf("%zd\n", (1 << 15) - 1);
//  demo_timeval();
//  demo_clock();
//  demo_timespec();

  return 0;
}
