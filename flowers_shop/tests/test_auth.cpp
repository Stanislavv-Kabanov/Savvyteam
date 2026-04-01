#include <gtest/gtest.h>
#include "../includes/auth.h"
#include "../includes/database.h"

class AuthTest : public ::testing::Test {
protected:
    Database db;
    
    void SetUp() override {
        sqlite3_open("test.db", &db.db);
        db.exec("CREATE TABLE users ("
                "user_id INTEGER PRIMARY KEY AUTOINCREMENT,"
                "last_name TEXT, first_name TEXT, phone TEXT, email TEXT,"
                "registration_date TEXT, is_active INTEGER)");
        db.exec("INSERT INTO users VALUES (1, 'Test', 'User', '+375291234567', 'test@email.com', '2024-01-01', 1)");
    }
    
    void TearDown() override {
        db.disconnect();
        remove("test.db");
    }
};

TEST_F(AuthTest, LoginSuccess) {
    Auth auth;
    bool result = auth.login("test@email.com", "+375291234567", db);
    EXPECT_TRUE(result);
    EXPECT_TRUE(auth.isLoggedIn());
}

TEST_F(AuthTest, LoginFails) {
    Auth auth;
    bool result = auth.login("wrong@email.com", "+375290000000", db);
    EXPECT_FALSE(result);
}

TEST_F(AuthTest, LogoutWorks) {
    Auth auth;
    auth.login("test@email.com", "+375291234567", db);
    auth.logout();
    EXPECT_FALSE(auth.isLoggedIn());
}

int main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
