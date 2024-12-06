#include "../src/primes.h"

#include <gtest/gtest.h>

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
  EXPECT_TRUE(is_prime_miller_rabin(INT_MAX));
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
