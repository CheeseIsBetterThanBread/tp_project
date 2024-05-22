find_package(GTest)

add_executable(tests EXCLUDE_FROM_ALL main_tests.cpp tests.cpp)
target_link_libraries(tests ${GTEST_LIBRARIES} command connection internal)