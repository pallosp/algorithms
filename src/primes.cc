#include <cmath>
#include <cstdint>

namespace {
typedef unsigned __int128 uint128_t;

uint64_t pow_mod(uint64_t base, uint64_t exp, uint64_t mod) {
  uint64_t r = 1;
  while (exp) {
    if (exp & 1) r = (uint128_t)r * base % mod;
    base = (uint128_t)base * base % mod;
    exp /= 2;
  }
  return r;
}

// Runs the Miller-Rabin algorithm for the given witness (base).
// Returns true if x is probably a prime (p ≥ 0.75) assuming the witness was
// randomly selected, or false if it's definitely composite.
// Prcondition: x ≥ 2
bool is_probably_prime(uint64_t x, uint64_t witness) {
  uint64_t exp = x - 1;
  while (exp % 2 == 0) exp /= 2;
  uint64_t factor = pow_mod(witness, exp, x);
  if (factor == 1 || factor == x - 1) return true;
  while (exp < x - 1) {
    exp *= 2;
    factor = (uint128_t)factor * factor % x;
    if (factor == x - 1) return true;
  }
  return false;
}
}  // namespace

bool is_prime_naive(uint64_t x) {
  if (x == 2 || x == 3) return true;
  if (x == 1 || x % 2 == 0 || x % 3 == 0) return false;
  uint64_t max = int(std::sqrt(x));
  for (uint64_t i = 5; i <= max; i += 6) {
    if (x % i == 0 || x % (i + 2) == 0) return false;
  }
  return true;
}

bool is_prime_miller_rabin_random(uint64_t x, size_t attempts) {
  if (x == 2) return true;
  if (x < 2 || x % 2 == 0) return false;
  for (uint64_t i = 0; i < attempts; i++) {
    uint64_t base = rand() % (x - 2) + 2;
    if (!is_probably_prime(x, base)) return false;
  }
  return true;
}

bool is_prime_miller_rabin(uint32_t x) {
  // According to
  // https://en.wikipedia.org/wiki/Miller%E2%80%93Rabin_primality_test,
  // testing 2, 7 and 61 is sufficient to determine whether a 32-bit integer is
  // a prime.
  if (x == 2 || x == 7 || x == 61) return true;
  if (x == 1 || x % 2 == 0) return false;
  return is_probably_prime(x, 2) && is_probably_prime(x, 7) &&
         is_probably_prime(x, 61);
}
