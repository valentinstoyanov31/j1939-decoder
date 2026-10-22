#include <gtest/gtest.h>

#include "j1939/version.hpp"

// Demonstrate some basic assertions.
TEST(VersionTest, BasicAssertions) {
  // Expect equality.
  EXPECT_EQ(j1939::version(), "1.0");
}

TEST(FailureTest, BasicAssertions) {
  // Expect equality.
  EXPECT_EQ(j1939::version(), "1.1");
}