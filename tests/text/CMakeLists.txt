add_executable(test_text text.cpp)
add_test(NAME text COMMAND test_text WORKING_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}")

embed(test_text "text.txt")