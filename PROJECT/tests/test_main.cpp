#include <gtest/gtest.h>
#include <filesystem>
#include <fstream>
#include <vector>
#include <string>

namespace fs = std::filesystem;


// Main function for Google Test
int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}

// SHOULD BE ALLWAYS WORKING
TEST(MUST_PASS, AssertionTrue) {
    EXPECT_TRUE(true);
}

