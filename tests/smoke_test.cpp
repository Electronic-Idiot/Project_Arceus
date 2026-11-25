#include <gtest/gtest.h>

#include "arceus/version.hpp"

TEST(SmokeTest, ReportsVersion) { EXPECT_EQ(arceus::version(), "0.1.0-dev"); }
