cmake_minimum_required(VERSION 3.4)
set(CMAKE_MESSAGE_LOG_LEVEL "WARNING")
set(EXECUTABLE_OUTPUT_PATH "bin")
project(swiper)

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

    set(WINDOWS_C_FLAGS "${CMAKE_C_FLAGS} /INCREMENTAL:NO /std:c17 /Ox /WX /W4 /wd4204")
    set(WINDOWS_CXX_FLAGS "${CMAKE_CXX_FLAGS} /INCREMENTAL:NO /std:c++17 /Ox /WX /W4 /wd4204")
    set(CMAKE_C_FLAGS "${WINDOWS_C_FLAGS}")
    set(CMAKE_CXX_FLAGS "${WINDOWS_CXX_FLAGS}")
else()
    set(UNIX_C_FLAGS "${CMAKE_C_FLAGS} -O3 -Werror")
    set(UNIX_CXX_FLAGS "${CMAKE_CXX_FLAGS} -O3 -Werror")
    set(GNU_C_FLAGS "${UNIX_C_FLAGS} -std=gnu17 -Wextra -Wall -pedantic")
    set(GNU_CXX_FLAGS "${UNIX_CXX_FLAGS} -std=c++17 -Wextra -Wall -pedantic -Weffc++")
    set(LLVM_FLAGS "-Wmost")
    set(CLANG_C_FLAGS "${GNU_C_FLAGS} ${LLVM_FLAGS}")
    set(CLANG_CXX_FLAGS "${GNU_CXX_FLAGS} ${LLVM_FLAGS}")

    if(CMAKE_C_COMPILER_ID MATCHES "Clang")
        set(CMAKE_C_FLAGS "${CLANG_C_FLAGS}")
        set(CMAKE_CXX_FLAGS "${CLANG_CXX_FLAGS}")
    else()
        set(CMAKE_C_FLAGS "${GNU_C_FLAGS}")
        set(CMAKE_CXX_FLAGS "${GNU_CXX_FLAGS}")
    endif()
endif()

include_directories(include)

add_executable(bench-swiper src/cmd/bench-swiper/main.cpp src/swiper.cpp)

find_program(PERF "perf")

if(MSVC)
    add_custom_target(bench COMMAND powershell -Command "Measure-Command {$<TARGET_FILE:bench-swiper>}")
elseif(PERF)
    add_custom_target(bench COMMAND sudo perf stat -dde "branches,branch-misses,cycles,instructions,cache-references,cache-misses" $<TARGET_FILE:bench-swiper>)
else()
    add_custom_target(bench COMMAND /usr/bin/time --verbose $<TARGET_FILE:bench-swiper>)
endif()

add_custom_target(cppcheck COMMAND cppcheck -q --force --enable=all --inline-suppr --suppressions-list=suppressions.cfg --error-exitcode=1 -U__SANITIZE_ADDRESS__ -I include src)
add_custom_target(cpplint COMMAND sail include src | xargs -n 1 cpplint)
add_custom_target(vera++ COMMAND sail include src | xargs -n 1 vera++)

# Missing linter ports
if(MSVC)
    add_custom_target(lint DEPENDS cppcheck)
else()
    add_custom_target(lint DEPENDS cppcheck cpplint vera++)
endif()

if(
    CMAKE_C_COMPILER_ID MATCHES "Clang" AND
    NOT CMAKE_SYSTEM_NAME MATCHES "Darwin"
)
    set(SANITIZE_TIMEOUT_SEC 10)
    set(FUZZER_RUNTIME_FLAGS "-max_total_time=${SANITIZE_TIMEOUT_SEC}")

    add_executable(test-swiper src/cmd/test-swiper/main.cpp src/swiper.cpp)

    set(SANITIZE_RULES "fuzzer,address,undefined")
    set(SANITIZE_FLAGS "-fsanitize=${SANITIZE_RULES} -fno-sanitize-recover=${SANITIZE_RULES}")

    set_target_properties(
        test-swiper
        PROPERTIES
        RUNTIME_OUTPUT_DIRECTORY "debug"
        COMPILE_FLAGS "-g ${SANITIZE_FLAGS}"
        LINK_FLAGS "${SANITIZE_FLAGS}"
        COMPILE_DEFINITIONS "__SANITIZE_ADDRESS__"
    )

    add_custom_target(fuzz COMMAND $<TARGET_FILE:test-swiper> "${FUZZER_RUNTIME_FLAGS}")
else()
    add_custom_target(fuzz)
endif()

add_custom_target(doc COMMAND doxygen Doxyfile)
add_custom_target(clean-cmake COMMAND sh clean-cmake.sh)