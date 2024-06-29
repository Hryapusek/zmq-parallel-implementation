cmake_minimum_required(VERSION 3.22)

project(s0m4b0dY_parallel_algorithms)

## load in pkg-config support
find_package(PkgConfig)
## use pkg-config to get hints for 0mq locations
pkg_check_modules(PC_ZeroMQ QUIET zmq)

## use the hint from above to find where 'zmq.hpp' is located
find_path(ZeroMQ_INCLUDE_DIR
        NAMES zmq.hpp
        PATHS ${PC_ZeroMQ_INCLUDE_DIRS}
        )

## use the hint from above to find the location of libzmq
find_library(ZeroMQ_LIBRARY
        NAMES zmq
        PATHS ${PC_ZeroMQ_LIBRARY_DIRS}
        )

add_subdirectory(../utils-library ./build/utils)
get_target_property(${s0m4b0dY_utils_lib}_INCLUDES ${s0m4b0dY_utils_lib} INCLUDE_DIRECTORIES)

set(GTEST_EXECUTABLE ON CACHE BOOL "Build gtest executable?")

set(main_lib "s0m4b0dY_parallel_algorithms_zmq")

set(COMMON_SOURCE_FILES
    src/s0_parallel_algorithms_zmq.cpp
    src/s0_jobs.cpp
    src/algorithms/reduce/reduce_default_strategy.cpp
    src/s0_utils.cpp
)

set(COMMON_PUBLIC_INCLUDES
    include/public
    ${${s0m4b0dY_utils_lib}_INCLUDES}
)

set(COMMON_PRIVATE_INCLUDES
    include/private
)

set(COMMON_LIBS ${s0m4b0dY_utils_lib} ${ZeroMQ_LIBRARY})

if (GTEST_EXECUTABLE)
    include(cmake/build_test_executable.cmake)
endif()

add_library(${main_lib} INTERFACE)

target_include_directories(${main_lib}
    INTERFACE ${COMMON_PUBLIC_INCLUDES}
    INTERFACE ${COMMON_PRIVATE_INCLUDES}
)

target_link_libraries(${main_lib} INTERFACE ${COMMON_LIBS})

# target_sources(${main_lib} # Header only?
#     PUBLIC ${COMMON_SOURCE_FILES}
# )

target_compile_features(${main_lib} INTERFACE cxx_std_20)

