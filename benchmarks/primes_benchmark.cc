#include <benchmark/benchmark.h>

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
    for (unsigned i = 0; i < 100; i++) is_prime_naive(UINT_MAX - i);
  }
}
BENCHMARK(IsPrimeNaive_uint32_max);

static void IsPrimeMillerRabin_uint32_max(benchmark::State &state) {
  for (auto _ : state) {
    for (unsigned i = 0; i < 100; i++) is_prime_miller_rabin(UINT_MAX - i);
  }
}
BENCHMARK(IsPrimeMillerRabin_uint32_max);

BENCHMARK_MAIN();
