#include <cstdio>

#include "primes.h"

int main() {
  printf("Primes up to 100 (naive algorithm):\n");
  for (int i = 0; i < 100; i++) {
    if (is_prime_naive(i)) printf(" %d", i);
  }
  printf("\n");

  printf("Primes up to 100 (Miller-Rabin, deterministic):\n");
  for (int i = 0; i < 100; i++) {
    if (is_prime_miller_rabin(i)) printf(" %d", i);
  }
  printf("\n");

  printf("Primes up to 100 (Miller-Rabin, random):\n");
  for (int i = 0; i < 100; i++) {
    if (is_prime_miller_rabin_random(i, 10)) printf(" %d", i);
  }
  printf("\n");

  printf("First 20-digit prime: ");
  uint64_t i = 1e19;
  while (!is_prime_miller_rabin_random(i, 20)) i++;
  printf("%llu\n", i);
}
