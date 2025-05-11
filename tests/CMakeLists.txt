file(GLOB tests LIST_DIRECTORIES true "*")

foreach(item ${tests})
    if (IS_DIRECTORY ${item})
        add_subdirectory(${item})
    endif()
endforeach()

