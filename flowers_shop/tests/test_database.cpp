#include <gtest/gtest.h>
#include "../includes/database.h"
#include "../includes/utils.h"
#include <iostream>

class DatabaseTest : public ::testing::Test {
protected:
    Database db;

    void SetUp() override {
        remove("test.db");
        sqlite3_open("test.db", &db.db);

        db.exec("CREATE TABLE flowers ("
            "flower_id INTEGER PRIMARY KEY AUTOINCREMENT,"
            "name TEXT, variety TEXT, price_per_unit REAL)");

        db.exec("CREATE TABLE config ("
            "config_id INTEGER PRIMARY KEY AUTOINCREMENT,"
            "config_key TEXT UNIQUE, config_value TEXT)");

        db.exec("CREATE TABLE arrangements ("
            "arrangement_id INTEGER PRIMARY KEY AUTOINCREMENT,"
            "name TEXT)");

        db.exec("CREATE TABLE arrangement_compositions ("
            "id INTEGER PRIMARY KEY AUTOINCREMENT,"
            "arrangement_id INTEGER, flower_id INTEGER, quantity INTEGER)");

        db.exec("CREATE TABLE orders ("
            "order_id INTEGER PRIMARY KEY AUTOINCREMENT,"
            "user_id INTEGER, arrangement_id INTEGER, quantity INTEGER,"
            "order_date TEXT, completion_date TEXT, total_price REAL)");

        db.exec("CREATE TABLE users ("
            "user_id INTEGER PRIMARY KEY AUTOINCREMENT,"
            "last_name TEXT, first_name TEXT, phone TEXT, email TEXT)");

        db.exec("INSERT INTO flowers (name, variety, price_per_unit) VALUES "
            "('Rose', 'Red', 5.0), ('Rose', 'White', 6.0)");

        db.exec("INSERT INTO arrangements (name) VALUES ('Test Bouquet')");
        db.exec("INSERT INTO arrangement_compositions (arrangement_id, flower_id, quantity) VALUES (1, 1, 3)");

        db.exec("INSERT INTO config (config_key, config_value) VALUES "
            "('SURCHARGE_1_DAY_PERCENT', '25'),"
            "('SURCHARGE_2_DAY_PERCENT', '15')");
    }

    void TearDown() override {
        db.disconnect();
        remove("test.db");
    }
};

// Тест 1: Проверка добавления цветка
TEST_F(DatabaseTest, AddFlowerWorks) {
    bool result = db.addFlower("Tulip", "Yellow", 3.5);
    EXPECT_TRUE(result);

    auto flowers = db.getAllFlowers();
    EXPECT_EQ(flowers.size(), 3);
}

// Тест 2: Проверка получения всех цветов
TEST_F(DatabaseTest, GetAllFlowersReturnsData) {
    auto flowers = db.getAllFlowers();
    EXPECT_GE(flowers.size(), 2);
    EXPECT_EQ(flowers[0]["name"], "Rose");
}

// Тест 3: Проверка расчета стоимости заказа
TEST_F(DatabaseTest, CalcOrderCostWorks) {
    double cost = db.calcOrderCost(1, 2, "2024-03-01", "2024-03-02");
    EXPECT_GT(cost, 0);
    // 3 розы * 5.0 * 2 композиции = 30 + 25% = 37.5
    EXPECT_DOUBLE_EQ(cost, 37.5);
}

// Тест 4: Проверка расчета без надбавки
TEST_F(DatabaseTest, CalcOrderCostNoSurcharge) {
    double cost = db.calcOrderCost(1, 2, "2024-03-01", "2024-03-05");
    EXPECT_DOUBLE_EQ(cost, 30.0);
}

// Тест 5: Проверка добавления заказа
TEST_F(DatabaseTest, AddOrderWithCostWorks) {
    bool result = db.addOrderWithCost(1, 1, 2, "2024-03-01", "2024-03-02");
    EXPECT_TRUE(result);

    auto orders = db.query("SELECT * FROM orders");
    EXPECT_EQ(orders.size(), 1);
}

// Тест 6: Проверка обновления цены цветка
TEST_F(DatabaseTest, UpdateFlowerPriceWorks) {
    bool result = db.updateFlowerPrice(1, 10.0);
    EXPECT_TRUE(result);

    auto flower = db.query("SELECT price_per_unit FROM flowers WHERE flower_id=1");
    EXPECT_DOUBLE_EQ(std::stod(flower[0]["price_per_unit"]), 10.0);
}

// Тест 7: Проверка запрета повышения цены >10%
TEST_F(DatabaseTest, CheckPriceIncreaseBlocksLargeIncrease) {
    bool result = db.checkPriceIncrease(1, 10.0); // 5.0 -> 10.0 = 100% increase
    EXPECT_FALSE(result);
}

// Тест 8: Проверка разрешения повышения цены <=10%
TEST_F(DatabaseTest, CheckPriceIncreaseAllowsSmallIncrease) {
    bool result = db.checkPriceIncrease(1, 5.4); // 5.0 -> 5.4 = 8% increase
    EXPECT_TRUE(result);
}

// Тест 9: Проверка получения конфигурации
TEST_F(DatabaseTest, GetConfigWorks) {
    auto config = db.getConfig();
    EXPECT_GE(config.size(), 2);
}

int main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}