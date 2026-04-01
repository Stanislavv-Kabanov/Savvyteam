cmake_minimum_required(VERSION 3.10)
project(FlowerShop)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/bin)

find_package(SQLite3 REQUIRED)

include_directories(${SQLite3_INCLUDE_DIRS})
include_directories(includes)

set(SOURCES
    src/database.cpp
    src/auth.cpp
    src/flower_shop.cpp
    src/utils.cpp
)

add_executable(flower_shop src/main.cpp ${SOURCES})
target_link_libraries(flower_shop ${SQLite3_LIBRARIES})

add_custom_command(TARGET flower_shop POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory
        ${CMAKE_SOURCE_DIR}/sql
        ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/sql
    COMMENT "Copying SQL files..."
)

enable_testing()

find_package(GTest REQUIRED)
include_directories(${GTEST_INCLUDE_DIRS})

add_executable(test_utils tests/test_utils.cpp ${SOURCES})
target_link_libraries(test_utils ${GTEST_LIBRARIES} ${SQLite3_LIBRARIES} pthread)
add_test(NAME test_utils COMMAND test_utils)

add_executable(test_auth tests/test_auth.cpp ${SOURCES})
target_link_libraries(test_auth ${GTEST_LIBRARIES} ${SQLite3_LIBRARIES} pthread)
add_test(NAME test_auth COMMAND test_auth)

add_executable(test_database tests/test_database.cpp ${SOURCES})
target_link_libraries(test_database ${GTEST_LIBRARIES} ${SQLite3_LIBRARIES} pthread)
add_test(NAME test_database COMMAND test_database)
