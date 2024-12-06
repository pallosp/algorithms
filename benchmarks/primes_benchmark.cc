#include <benchmark/benchmark.h>

#include <limits>

#include "src/primes.h"

static void IsPrimeNaive_1e6(benchmark::State &state) {
  for (auto _ : state) {
    for (unsigned i = 1; i <= 100; i++) is_prime_naive(1e6 - i);
  }
}
BENCHMARK(IsPrimeNaive_1e6);

static void IsPrimeMillerRabin_1e6(benchmark::State &state) {
  for (auto _ : state) {
    for (unsigned i = 1; i <= 100; i++) is_prime_miller_rabin(1e6 - i);
  }
}
BENCHMARK(IsPrimeMillerRabin_1e6);

static void IsPrimeNaive_2e8(benchmark::State &state) {
  for (auto _ : state) {
    for (unsigned i = 1; i <= 100; i++) is_prime_naive(2e8 - i);
  }
}
BENCHMARK(IsPrimeNaive_2e8);

static void IsPrimeMillerRabin_2e8(benchmark::State &state) {
  for (auto _ : state) {
    for (unsigned i = 1; i <= 100; i++) is_prime_miller_rabin(2e8 - i);
  }
}
BENCHMARK(IsPrimeMillerRabin_2e8);

static void IsPrimeNaive_uint32_max(benchmark::State &state) {
  for (auto _ : state) {
    for (unsigned i = 0; i < 100; i++)
      is_prime_naive(std::numeric_limits<uint32_t>::max() - i);
  }
}
BENCHMARK(IsPrimeNaive_uint32_max);

static void IsPrimeMillerRabin_uint32_max(benchmark::State &state) {
  for (auto _ : state) {
    for (uint32_t i = 0; i < 100; i++)
      is_prime_miller_rabin(std::numeric_limits<uint32_t>::max() - i);
  }
}
BENCHMARK(IsPrimeMillerRabin_uint32_max);

static void IsPrimeMillerRabin_uint64_max(benchmark::State &state) {
  for (auto _ : state) {
    for (uint32_t i = 0; i < 100; i++)
      is_prime_miller_rabin(std::numeric_limits<uint64_t>::max() - i);
  }
}
BENCHMARK(IsPrimeMillerRabin_uint64_max);

BENCHMARK_MAIN();
