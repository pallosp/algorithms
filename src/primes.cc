#include <cmath>
#include <cstdint>
#include <cstdio>

namespace {
typedef unsigned __int128 uint128_t;

uint64_t pow_mod(uint64_t base, uint64_t exp, uint64_t mod) {
  uint64_t r = 1;
  while (exp) {
    if (exp & 1) {
      r = (uint128_t)r * base % mod;
    }
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

// According to
// https://en.wikipedia.org/wiki/Miller%E2%80%93Rabin_primality_test
// it's enough to run the algorithm for a small set of witnesses.
//
// For each row, if x ≤ first element, it's sufficient to check the rest of the
// non-zero elements in the row. The last element is always zero.
const uint64_t *witnesses[] = {
    (uint64_t[]){2046, 2, 0},
    (uint64_t[]){9'080'190, 32, 72, 0},
    (uint64_t[]){4'759'123'140, 2, 7, 61, 0},
    (uint64_t[]){1'122'004'669'632, 2, 13, 23, 1'662'803, 0},
    (uint64_t[]){2'152'302'898'746, 2, 3, 5, 7, 11, 0},
    (uint64_t[]){3'474'749'660'382, 2, 3, 5, 7, 11, 13, 0},
    (uint64_t[]){341'550'071'728'320, 2, 3, 5, 7, 11, 13, 17, 0},
    (uint64_t[]){3'825'123'056'546'413'050, 2, 3, 5, 7, 11, 13, 17, 19, 23, 0},
    (uint64_t[]){std::numeric_limits<uint64_t>::max(), 2, 3, 5, 7, 11, 13, 17,
                 19, 23, 29, 31, 37, 0},
};

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

bool is_prime_miller_rabin(uint64_t x) {
  if (x == 1 || (x % 2 == 0 && x != 2)) return false;
  for (const uint64_t *witness_spec : witnesses) {
    if (x >= witness_spec[0]) continue;
    for (int i = 1; witness_spec[i] != 0; i++) {
      if (x == witness_spec[i]) return true;
      if (!is_probably_prime(x, witness_spec[i])) return false;
    }
    break;
  }
  return true;
}
