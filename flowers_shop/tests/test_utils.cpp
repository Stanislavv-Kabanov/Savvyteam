#include <gtest/gtest.h>
#include "../includes/utils.h"

TEST(UtilsTest, GetCurrentDateLength) {
    std::string date = Utils::getCurrentDate();
    EXPECT_EQ(date.length(), 10);
}

TEST(UtilsTest, GetCurrentDateFormat) {
    std::string date = Utils::getCurrentDate();
    EXPECT_EQ(date[4], '-');
    EXPECT_EQ(date[7], '-');
}

TEST(UtilsTest, StringToDouble) {
    double result = Utils::stringToDouble("123.45");
    EXPECT_DOUBLE_EQ(result, 123.45);
}

TEST(UtilsTest, StringToInt) {
    int result = Utils::stringToInt("123");
    EXPECT_EQ(result, 123);
}

TEST(UtilsTest, DaysDifference) {
    int days = Utils::daysDifference("2024-03-01", "2024-03-03");
    EXPECT_EQ(days, 2);
}

int main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
