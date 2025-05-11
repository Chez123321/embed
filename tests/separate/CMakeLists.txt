add_executable(test_separate separate.cpp)
add_test(NAME separate COMMAND test_separate WORKING_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}")

embed(test_separate "text1.txt")
embed(test_separate "text2.txt")