cmake_minimum_required(VERSION 3.31)

project(embed C CXX)

add_executable(bin2c "src/bin2c.c")

set(include_dir "${CMAKE_CURRENT_SOURCE_DIR}/include" CACHE INTERNAL "Include directory")
set(src_dir "${CMAKE_CURRENT_SOURCE_DIR}/src" CACHE INTERNAL "Source directory")

function(embed target)
    target_include_directories(${target} PRIVATE "${include_dir}")
    
    target_compile_features(${target} PRIVATE cxx_auto_type cxx_generalized_initializers)

    set(sources_list ${sources})

    foreach(item ${ARGN})
        if(NOT ${item} IN_LIST sources_list)
            cmake_path(ABSOLUTE_PATH item NORMALIZE)
            cmake_path(RELATIVE_PATH item)

            list(APPEND sources_list ${item})

            string(MAKE_C_IDENTIFIER ${item} ident)

            add_custom_command(
                OUTPUT "${CMAKE_CURRENT_BINARY_DIR}/${item}.c"
                DEPENDS bin2c "${item}"
                WORKING_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}"
                COMMAND bin2c "${item}" "${CMAKE_CURRENT_BINARY_DIR}/${item}.c" ${ident}
                VERBATIM
            )

            target_sources(${target} PRIVATE "${CMAKE_CURRENT_BINARY_DIR}/${item}.c")

        endif()
    endforeach()

    set(sources ${sources_list} PARENT_SCOPE)

    set(EXTERNS "")
    set(MAP "{\n")

    foreach(item ${sources_list})
        string(MAKE_C_IDENTIFIER ${item} ident)

        list(APPEND EXTERNS "extern \"C\" const unsigned char ${ident}[];")
        list(APPEND EXTERNS "extern \"C\" const size_t ${ident}_size;")

        string(APPEND MAP "\t\t{\"${item}\", File(${ident}, ${ident}_size)},\n")
    endforeach()

    string(REPLACE ";;" ";\n" EXTERNS "${EXTERNS}")
    string(APPEND MAP "\t};")

    configure_file("${src_dir}/embed.cpp.in" "${CMAKE_CURRENT_BINARY_DIR}/embed.cpp" @ONLY)
    target_sources(${target} PRIVATE "${CMAKE_CURRENT_BINARY_DIR}/embed.cpp")
endfunction()

if(EMBED_TESTING)
    enable_testing()
    add_subdirectory("tests")
endif()
