add_executable(test_duplicate duplicate.cpp)
add_test(NAME duplicate COMMAND test_duplicate WORKING_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}")

embed(test_duplicate "text.txt" "text.txt")
embed(test_duplicate "text.txt")