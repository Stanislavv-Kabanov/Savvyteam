#include <gtest/gtest.h>
#include <cstdio>           
#include "../includes/database.h"
#include "../includes/utils.h" 

class DatabaseTest : public ::testing::Test {
protected:
    Database db;
    
    void SetUp() override {
        sqlite3_open("test.db", &db.db);
        
        db.exec("CREATE TABLE flowers (flower_id INTEGER PRIMARY KEY, name TEXT, variety TEXT, price_per_unit REAL)");
        db.exec("INSERT INTO flowers VALUES (1, 'Rose', 'Red', 5.0)");
        db.exec("CREATE TABLE config (config_key TEXT, config_value TEXT)");
        db.exec("INSERT INTO config VALUES ('SURCHARGE_1_DAY_PERCENT', '25')");
        db.exec("CREATE TABLE arrangements (arrangement_id INTEGER PRIMARY KEY, name TEXT)");
        db.exec("INSERT INTO arrangements VALUES (1, 'Test Bouquet')");
        db.exec("CREATE TABLE arrangement_compositions (id INTEGER PRIMARY KEY, arrangement_id INTEGER, flower_id INTEGER, quantity INTEGER)");
        db.exec("INSERT INTO arrangement_compositions VALUES (1, 1, 1, 3)");
    }
    
    void TearDown() override {
        db.disconnect();
        remove("test.db");
    }
};

TEST_F(DatabaseTest, AddFlowerWorks) {
    bool result = db.addFlower("Tulip", "Yellow", 3.5);
    EXPECT_TRUE(result);
}

TEST_F(DatabaseTest, GetAllFlowers) {
    auto flowers = db.getAllFlowers();
    EXPECT_GE(flowers.size(), 1);
}

TEST_F(DatabaseTest, UpdateFlowerPrice) {
    bool result = db.updateFlowerPrice(1, 10.0);
    EXPECT_TRUE(result);
}

TEST_F(DatabaseTest, CalcOrderCost) {
    double cost = db.calcOrderCost(1, 2, "2024-03-01", "2024-03-02");
    EXPECT_GT(cost, 0);
}

int main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
