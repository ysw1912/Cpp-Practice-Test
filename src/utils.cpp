#include "utils.h"

// Returns true iff n is a prime number.
bool IsPrime(int n) {
  if (n <= 1) return false;
  if (n % 2 == 0) return n == 2;

  // Now, we have that n is odd and n >= 3.
  for (int i = 3; ; i += 2) {
    if (i > n / i) break;
    if (n % i == 0) return false;
  }
  return true;
}
