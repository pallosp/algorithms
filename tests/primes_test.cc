#include "../src/primes.h"

#include <gtest/gtest.h>

#include <limits>

namespace {

TEST(Primes, NaiveAlgorithm) {
  EXPECT_FALSE(is_prime_naive(0));
  EXPECT_FALSE(is_prime_naive(1));
  EXPECT_TRUE(is_prime_naive(2));
  EXPECT_TRUE(is_prime_naive(3));
  EXPECT_FALSE(is_prime_naive(4));
}

TEST(Primes, MillerRabin) {
  EXPECT_FALSE(is_prime_miller_rabin(0));
  EXPECT_FALSE(is_prime_miller_rabin(1));
  EXPECT_TRUE(is_prime_miller_rabin(2));
  EXPECT_TRUE(is_prime_miller_rabin(3));
  EXPECT_FALSE(is_prime_miller_rabin(4));
  EXPECT_FALSE(is_prime_miller_rabin(2047));  // 23×89
  EXPECT_FALSE(is_prime_miller_rabin(9'080'191));  // 2131×4261
  EXPECT_TRUE(is_prime_miller_rabin(std::numeric_limits<int32_t>::max()));
  EXPECT_TRUE(is_prime_miller_rabin(18'446'744'073'709'551'557llu));
  EXPECT_FALSE(is_prime_miller_rabin(std::numeric_limits<int64_t>::max()));
}

TEST(Primes, AlgorithmsAreEquivalent) {
  for (int i = 0; i < 100; i++) {
    EXPECT_EQ(is_prime_naive(i), is_prime_miller_rabin(i))
        << "Naive vs deterministic Miller-Rabin for " << i;
    EXPECT_EQ(is_prime_naive(i), is_prime_miller_rabin_random(i, 10))
        << "Naive vs random Miller-Rabin for " << i;
  }
}

}  // namespace
