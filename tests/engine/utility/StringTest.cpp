#include <gtest/gtest.h>

#include <utility/String.h>

using namespace chira;

TEST(String, startsWith) {
    std::string test = "StartEnd";
    EXPECT_TRUE(String::startsWith(test, "Start"));
    EXPECT_TRUE(String::startsWith(test, 'S'));
    EXPECT_FALSE(String::startsWith(test, "xxx"));
    EXPECT_FALSE(String::startsWith(test, 'x'));
}

TEST(String, endsWith) {
    std::string test = "StartEnd";
    EXPECT_TRUE(String::endsWith(test, "End"));
    EXPECT_TRUE(String::endsWith(test, 'd'));
    EXPECT_FALSE(String::endsWith(test, "xxx"));
    EXPECT_FALSE(String::endsWith(test, 'x'));
}

TEST(String, contains) {
    std::string test = "StartEnd";
    EXPECT_TRUE(String::contains(test, "tEn"));
    EXPECT_TRUE(String::contains(test, 'E'));
    EXPECT_FALSE(String::contains(test, "txn"));
    EXPECT_FALSE(String::contains(test, 'x'));
}

TEST(String, remove) {
    std::string test1 = "Test String", test2 = "Test String", test3 = "Test String";
    String::remove(test1, 'S');
    String::remove(test2, 't');
    String::remove(test3, 's');
    EXPECT_STREQ(test1.c_str(), "Test tring");
    EXPECT_STREQ(test2.c_str(), "Tes Sring");
    EXPECT_STREQ(test3.c_str(), "Tet String");
}

TEST(String, split) {
    auto vec1 = String::split("TestString1:TestString2:TestString3", ':');
    ASSERT_EQ(vec1.size(), 3);
    EXPECT_STREQ(vec1[0].c_str(), "TestString1");
    EXPECT_STREQ(vec1[1].c_str(), "TestString2");
    EXPECT_STREQ(vec1[2].c_str(), "TestString3");

    auto vec2 = String::split("Test String 1,Test String 2,Test String 3", ',');
    ASSERT_EQ(vec2.size(), 3);
    EXPECT_STREQ(vec2[0].c_str(), "Test String 1");
    EXPECT_STREQ(vec2[1].c_str(), "Test String 2");
    EXPECT_STREQ(vec2[2].c_str(), "Test String 3");
}

TEST(String, changeCase) {
    std::string test = "Howdy, I'm mixEd-CasE!";
    EXPECT_STREQ(String::toLower(test).c_str(), "howdy, i'm mixed-case!");
    EXPECT_STREQ(String::toUpper(test).c_str(), "HOWDY, I'M MIXED-CASE!");
}

TEST(String, stripWhitespace) {
    // Whitespace
    EXPECT_STREQ(String::stripLeft("\t\n\r\v\f test").c_str(), "test");
    EXPECT_STREQ(String::stripRight("test \t\n\r\v\f").c_str(), "test");
    EXPECT_STREQ(String::strip("\t\n\r\v\f test \t\n\r\v\f").c_str(), "test");

    // Manually specified
    EXPECT_STREQ(String::stripLeft(" test", " ").c_str(), "test");
    EXPECT_STREQ(String::stripRight("test ", " ").c_str(), "test");
    EXPECT_STREQ(String::strip(" test ", " ").c_str(), "test");
}

TEST(String, replace) {
    // Single instance
    {
        std::string test{"Mary had a little lamb"};
        String::replace(test, "little", "ginormous");
        EXPECT_STREQ(test.c_str(), "Mary had a ginormous lamb");
    }

    // Multiple instances
    {
        std::string test{"Mary's little lamb was very little"};
        String::replace(test, "little", "big");
        EXPECT_STREQ(test.c_str(), "Mary's big lamb was very big");
    }
}

TEST(String, join) {
    std::vector<int> empty{};
    std::vector<int> ints{0, 2, 8, 42};
    std::vector<float> floats{0.f, 2.5f, 42.f};
    std::vector<std::string_view> strings{"i", "am", "a", "lot", "of", "strings"};

    EXPECT_STREQ(String::join(empty, ", ").c_str(), "");
    EXPECT_STREQ(String::join(ints, ", ").c_str(), "0, 2, 8, 42");
    EXPECT_STREQ(String::join(floats, ", ").c_str(), "0, 2.5, 42");
    EXPECT_STREQ(String::join(strings, ", ").c_str(), "i, am, a, lot, of, strings");

    EXPECT_STREQ(String::join(empty, ", ", " end").c_str(), " end");
    EXPECT_STREQ(String::join(ints, " : ", " end").c_str(), "0 : 2 : 8 : 42 end");
    EXPECT_STREQ(String::join(floats, " : ", " end").c_str(), "0 : 2.5 : 42 end");
    EXPECT_STREQ(String::join(strings, " : ", " end").c_str(), "i : am : a : lot : of : strings end");
}
