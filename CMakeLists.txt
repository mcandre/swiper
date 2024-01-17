cmake_minimum_required(VERSION 3.5)

set(CMAKE_MESSAGE_LOG_LEVEL "WARNING")
set(EXECUTABLE_OUTPUT_PATH "../bin")
set(CMAKE_C_STANDARD 17)
set(CMAKE_CXX_STANDARD 17)

project(swiper)

file(GLOB_RECURSE C_SOURCE_FILES *.h *.c)
file(GLOB_RECURSE CPP_SOURCE_FILES *.cppm *.hpp *.cpp)
file(GLOB_RECURSE CXX_SOURCE_FILES *.cppm *.hpp *.cpp *.h *.c)

include(${CMAKE_BINARY_DIR}/conanbuildinfo.cmake)
conan_basic_setup(TARGETS)

set_property(
    DIRECTORY .
    APPEND PROPERTY
    ADDITIONAL_CLEAN_FILES
    "html;${EXECUTABLE_OUTPUT_PATH};debug;debug.log;Makefile;build.ninja;.ninja_deps;Testing;CTestTestfile.cmake;CMakeFiles;CMakeCache.txt;cmake_install.cmake;conanbuildinfo.cmake;conanbuildinfo.txt;conaninfo.txt;graph_info.json;conan.lock"
)

if(MSVC)
    set(CMAKE_LIBRARY_OUTPUT_DIRECTORY "${EXECUTABLE_OUTPUT_PATH}")
    set(CMAKE_LIBRARY_OUTPUT_DIRECTORY_DEBUG "${EXECUTABLE_OUTPUT_PATH}")
    set(CMAKE_LIBRARY_OUTPUT_DIRECTORY_RELEASE "${EXECUTABLE_OUTPUT_PATH}")
    set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY "${EXECUTABLE_OUTPUT_PATH}")
    set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY_DEBUG "${EXECUTABLE_OUTPUT_PATH}")
    set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY_RELEASE "${EXECUTABLE_OUTPUT_PATH}")
    set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${EXECUTABLE_OUTPUT_PATH}")
    set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_DEBUG "${EXECUTABLE_OUTPUT_PATH}")
    set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_RELEASE "${EXECUTABLE_OUTPUT_PATH}")
    set(CPPFLAGS "/EHsc /Ox /Wv:18 /INCREMENTAL:NO /WX /W4 /wd4204")
    set(CMAKE_CXX_FLAGS "${CPPFLAGS} ${CMAKE_CXX_FLAGS} /std:c++17")
    set(CMAKE_C_FLAGS "${CPPFLAGS} ${CMAKE_C_FLAGS} /std:c17")
else()
    set(CPPFLAGS "${CPPFLAGS} -O3 -Werror -Wextra -Wall -pedantic")
    set(CMAKE_CXX_FLAGS "${CPPFLAGS} ${CMAKE_CXX_FLAGS} -Weffc++ -std=c++17")
    set(CMAKE_C_FLAGS "${CPPFLAGS} ${CMAKE_C_FLAGS} -std=gnu17")

    if(CMAKE_C_COMPILER_ID MATCHES "Clang")
        set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wmost")
        set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wmost")

        if(NOT DEFINED ENV{TARGET} AND NOT CMAKE_SYSTEM_NAME MATCHES "Darwin")
            set(CMAKE_CXX_CLANG_TIDY clang-tidy -header-filter=${CMAKE_SOURCE_DIR})
            set(CMAKE_C_CLANG_TIDY clang-tidy -header-filter=${CMAKE_SOURCE_DIR})
        endif()
    endif()
endif()

include_directories(include ${CONAN_INCLUDE_DIRS})

add_executable(bench-swiper src/cmd/bench-swiper/main.cpp src/swiper.cpp)
target_link_libraries(bench-swiper CONAN_PKG::nanobench)

if(
    CMAKE_C_COMPILER_ID MATCHES "Clang" AND
    CLANG_VERSION_MAJOR VERSION_GREATER_EQUAL 9 AND
    NOT MSVC
)
    add_dependencies(bench-swiper swiper.profdata)

    add_executable(bench-swiper-instrument src/cmd/bench-swiper/main.cpp src/swiper.cpp)
    target_link_libraries(bench-swiper-instrument CONAN_PKG::nanobench)
    set(PGO_GENERATE_FLAGS "-fprofile-generate")
    set_target_properties(
        bench-swiper-instrument
        PROPERTIES
        COMPILE_FLAGS "${PGO_GENERATE_FLAGS}"
        LINK_FLAGS "${PGO_GENERATE_FLAGS}"
    )

    # Train on "cheez"
    add_custom_target(swiper.profraw COMMAND "${CMAKE_COMMAND}" -E env LLVM_PROFILE_FILE=swiper.profraw $<TARGET_FILE:bench-swiper-instrument> "00071B030141")
    add_dependencies(swiper.profraw bench-swiper-instrument)

    add_custom_target(swiper.profdata COMMAND llvm-profdata merge -output swiper.profdata swiper.profraw)
    add_dependencies(swiper.profdata swiper.profraw)

    set(PGO_USE_FLAGS "-fprofile-use=swiper.profdata")
    set_target_properties(
        bench-swiper
        PROPERTIES
        COMPILE_FLAGS "-flto ${PGO_USE_FLAGS}"
        LINK_FLAGS "-flto ${PGO_USE_FLAGS}"
    )
endif()

find_program(PERF "perf")

if(PERF)
    add_custom_target(bench COMMAND sudo -E perf stat -dde "branches,branch-misses,cycles,instructions,cache-references,cache-misses" $<TARGET_FILE:bench-swiper> "00091C080F5E")
elseif(MSVC)
    add_custom_target(bench COMMAND powershell -Command "Measure-Command { $<TARGET_FILE:bench-swiper> 00091C080F5E | Out-Default }")
elseif(APPLE)
    add_custom_target(bench COMMAND /usr/bin/time -l $<TARGET_FILE:bench-swiper> "00091C080F5E")
elseif("${CMAKE_SYSTEM_NAME}" MATCHES "Linux")
    add_custom_target(bench COMMAND /usr/bin/time --verbose $<TARGET_FILE:bench-swiper> "00091C080F5E")
else()
    add_custom_target(bench COMMAND /usr/bin/time $<TARGET_FILE:bench-swiper> "00091C080F5E")
endif()

if(MSVC)
    set(HOME "$ENV{HOMEDRIVE}$ENV{HOMEPATH}")
    set(ARTIFACT_BENCH bench-swiper.exe)
else()
    set(HOME "$ENV{HOME}")
    set(ARTIFACT_BENCH bench-swiper)
endif()

file(TO_NATIVE_PATH "${HOME}/bin" INSTALL_DIR)
file(TO_NATIVE_PATH "${INSTALL_DIR}/${ARTIFACT_BENCH}" INSTALL_FILE_BENCH)

install(PROGRAMS $<TARGET_FILE:bench-swiper> DESTINATION "${INSTALL_DIR}")

if(MSVC)
    add_custom_target(uninstall COMMAND del /s /q "${INSTALL_FILE_BENCH}")
else()
    add_custom_target(uninstall COMMAND rm -f "${INSTALL_FILE_BENCH}")
endif()

add_custom_target(cpplint COMMAND cpplint --recursive ../include ../src)
add_custom_target(clang-format COMMAND clang-format -i ${CXX_SOURCE_FILES})
add_custom_target(yamllint COMMAND yamllint ..)
add_custom_target(unmake COMMAND unmake ..)
add_custom_target(unmake_dry_run COMMAND unmake -n ..)

# Missing linter ports
if(MSVC)
    add_custom_target(lint DEPENDS yamllint unmake unmake_dry_run)
else()
    add_custom_target(lint DEPENDS cpplint clang-format yamllint unmake unmake_dry_run)
endif()

add_executable(test-swiper src/cmd/test-swiper/main.cpp src/swiper.cpp)

enable_testing()
add_test(NAME swiper_unit_test COMMAND $<TARGET_FILE:test-swiper>)

if(
    CMAKE_C_COMPILER_ID MATCHES "Clang" AND
    CMAKE_C_COMPILER_VERSION VERSION_GREATER_EQUAL 9 AND
    NOT CMAKE_SYSTEM_NAME MATCHES "Darwin" AND
    NOT CMAKE_SYSTEM_NAME MATCHES "Windows"
)
    set(SANITIZE_TIMEOUT_SEC 10)
    set(FUZZER_RUNTIME_FLAGS "-max_total_time=${SANITIZE_TIMEOUT_SEC}")

    add_executable(fuzz-swiper src/cmd/fuzz-swiper/main.cpp src/swiper.cpp)

    set(SANITIZE_RULES "fuzzer,address,undefined")
    set(SANITIZE_FLAGS "-flto -fsanitize=${SANITIZE_RULES} -fno-sanitize-recover=${SANITIZE_RULES}")

    set_target_properties(
        fuzz-swiper
        PROPERTIES
        RUNTIME_OUTPUT_DIRECTORY "debug"
        COMPILE_FLAGS "-g ${SANITIZE_FLAGS}"
        LINK_FLAGS "${SANITIZE_FLAGS}"
        COMPILE_DEFINITIONS "__SANITIZE_ADDRESS__"
    )

    add_custom_target(fuzz COMMAND $<TARGET_FILE:fuzz-swiper> "${FUZZER_RUNTIME_FLAGS}")
else()
    add_custom_target(fuzz)
endif()

add_custom_target(doc COMMAND doxygen Doxyfile)
