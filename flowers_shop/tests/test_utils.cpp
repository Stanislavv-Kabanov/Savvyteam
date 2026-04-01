#include <gtest/gtest.h>
#include "../includes/utils.h"

// Тест 1: Проверка getCurrentDate() - возвращает строку длиной 10
TEST(UtilsTest, GetCurrentDateReturnsCorrectLength) {
    std::string date = Utils::getCurrentDate();
    EXPECT_EQ(date.length(), 10);
}

// Тест 2: Проверка формата даты YYYY-MM-DD
TEST(UtilsTest, GetCurrentDateHasCorrectFormat) {
    std::string date = Utils::getCurrentDate();
    EXPECT_EQ(date[4], '-');
    EXPECT_EQ(date[7], '-');
}

// Тест 3: Проверка stringToDouble - преобразует строку в число
TEST(UtilsTest, StringToDoubleConvertsCorrectly) {
    double result = Utils::stringToDouble("123.45");
    EXPECT_DOUBLE_EQ(result, 123.45);
}

// Тест 4: Проверка stringToDouble с пустой строкой
TEST(UtilsTest, StringToDoubleHandlesEmptyString) {
    double result = Utils::stringToDouble("");
    EXPECT_DOUBLE_EQ(result, 0.0);
}

// Тест 5: Проверка stringToInt
TEST(UtilsTest, StringToIntConvertsCorrectly) {
    int result = Utils::stringToInt("123");
    EXPECT_EQ(result, 123);
}

// Тест 6: Проверка stringToInt с пустой строкой
TEST(UtilsTest, StringToIntHandlesEmptyString) {
    int result = Utils::stringToInt("");
    EXPECT_EQ(result, 0);
}

// Тест 7: Проверка daysDifference
TEST(UtilsTest, DaysDifferenceReturnsCorrectDays) {
    int days = Utils::daysDifference("2024-03-01", "2024-03-03");
    EXPECT_EQ(days, 2);
}

// Тест 8: Проверка daysDifference с одинаковыми датами
TEST(UtilsTest, DaysDifferenceReturnsZeroForSameDate) {
    int days = Utils::daysDifference("2024-03-01", "2024-03-01");
    EXPECT_EQ(days, 0);
}

int main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}