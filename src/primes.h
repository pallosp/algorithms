#include <cstddef>
#include <cstdint>

// Tests all 6k±1 divisors up to √x
bool is_prime_naive(uint64_t x);

// Deterministic Miller-Rabin algorithm. Selects the witnesses as per
// https://en.wikipedia.org/wiki/Miller%E2%80%93Rabin_primality_test
bool is_prime_miller_rabin(uint32_t x);

// Runs the Miller-Rabin algorithm `attempts` times.
// Tells whether x is a prime with ≤(1/4)^attempts false positive and zero
// false negative rate.
bool is_prime_miller_rabin_random(uint64_t x, size_t attempts);
