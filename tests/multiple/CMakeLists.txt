add_executable(test_multiple multiple.cpp)
add_test(NAME multiple COMMAND test_multiple WORKING_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}")

embed(test_multiple "text1.txt" "text2.txt")