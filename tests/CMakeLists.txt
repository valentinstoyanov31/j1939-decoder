add_executable(
    test_version
    test_version.cpp
)

target_link_libraries(
    test_version
    PRIVATE
        j1939
        GTest::gtest_main
)

include(GoogleTest)
gtest_discover_tests(test_version)