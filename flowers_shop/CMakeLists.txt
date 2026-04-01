cmake_minimum_required(VERSION 3.10)
project(FlowerShop)

set(CMAKE_CXX_STANDARD 11)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fprofile-arcs -ftest-coverage")

find_package(SQLite3 REQUIRED)
find_package(GTest REQUIRED)
find_package(Threads REQUIRED)

include_directories(includes ${SQLite3_INCLUDE_DIRS} ${GTEST_INCLUDE_DIRS})

set(SOURCES
    src/database.cpp
    src/auth.cpp
    src/flower_shop.cpp
    src/utils.cpp
)

add_executable(flower_shop src/main.cpp ${SOURCES})
target_link_libraries(flower_shop ${SQLite3_LIBRARIES})

enable_testing()
function(create_flower_test TEST_NAME TEST_SOURCE)
    add_executable(${TEST_NAME} ${TEST_SOURCE} ${SOURCES})
    target_link_libraries(${TEST_NAME} GTest::GTest ${SQLite3_LIBRARIES} Threads::Threads)
    add_test(NAME ${TEST_NAME} COMMAND ${TEST_NAME})
endfunction()

create_flower_test(test_auth tests/test_auth.cpp)
create_flower_test(test_utils tests/test_utils.cpp)
create_flower_test(test_database tests/test_database.cpp)
