#include <gtest/gtest.h>

#include "../ImGui/csv_file.cpp"
#include "../ImGui/file.cpp"
#include "../ImGui/text_file.cpp"
#include "../ImGui/default_file.cpp"
#include "../ImGui/file_factory.cpp"

#include <vector>
#include <string>

vector<string> split(string& s) { // SPLITS STRING BY  SEPARATOR/DELIMITER
    string delimiter = " ";
    vector<string> tokens;
    size_t pos = 0;
    string token;
    while ((pos = s.find(delimiter)) != string::npos) { // IF SEPARATOR FOUND, SUBSTRING AND APPEND INTO VEC
        token = s.substr(0, pos);
        tokens.push_back(token);
        s.erase(0, pos + delimiter.length());
    }
    tokens.push_back(s);
    return tokens;
};

string remove_white(string msg) {
    if (msg.length() < 1) return msg;
    for (int j = 0; j <= 1; j++) {
        int start = 0;
        for (int i = 0; i < msg.length(); i++) {
            if (msg[i] == ' ' || msg[i] == '\n' || msg[i] == '\t') {
                start++;
            } else break;
        }
        msg = msg.substr(start);
        reverse(msg.begin(), msg.end()); // REVERSE STRING TWICE, MAYBE SLOW, BUT WORKS
    }
    return msg;
};

// Another test case
TEST(ExampleTest, MUST_BE_PASSED) {
    int a = 2;
    int b = 3;
    EXPECT_EQ(a + b, 5);
}

TEST(TEST_FSPLIT, test_1 ) {
    string sample = "WORD1 WORD2 WORD3WORD4 WORD5";
    vector<string> expected = {"WORD1", "WORD2", "WORD3WORD4", "WORD5"};

    EXPECT_EQ(split(sample), expected);
}
TEST(TEST_FSPLIT, test_2 ) {
    string sample = "WORD1WORD2 WORD3WORD4 WORD5";
    vector<string> expected = {"WORD1WORD2", "WORD3WORD4", "WORD5"};

    EXPECT_EQ(split(sample), expected);
}
TEST(TEST_FSPLIT, test_3 ) {
    string sample = "WORD1, WORD2, WORD3WORD4, WORD5,";
    vector<string> expected = {"WORD1,", "WORD2,", "WORD3WORD4,", "WORD5,"};

    EXPECT_EQ(split(sample), expected);
}


TEST(TEST_FREMOVE_WHITE, test_1 ) {
    string sample = "testing";
    string expected = "testing";
    EXPECT_EQ(remove_white(sample), expected);
}

TEST(TEST_FREMOVE_WHITE, test_2 ) {
    string sample = "     testing     ";
    string expected = "testing";
    EXPECT_EQ(remove_white(sample), expected);
}
TEST(TEST_FREMOVE_WHITE, test_3 ) {
    string sample = "     \ttesting\t    ";
    string expected = "testing";
    EXPECT_EQ(remove_white(sample), expected);
}