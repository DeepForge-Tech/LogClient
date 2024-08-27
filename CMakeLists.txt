cmake_minimum_required(VERSION 3.18)
project(Client)
set(CMAKE_POLICY_DEFAULT_CMP0077 NEW)
set(CMAKE_CXX_STANDARD 20)
include(GNUInstallDirs)
include(FetchContent)
set(CMAKE_THREAD_PREFER_PTHREAD TRUE)
set(THREADS_PREFER_PTHREAD_FLAG TRUE)
find_package(Threads REQUIRED)
set(BUILD_SHARED_LIBS OFF)
set(CMAKE_FIND_LIBRARY_SUFFIXES .a .so .dylib)

set(CMAKE_BINARY_DIR "${CMAKE_BINARY_DIR}/bin/")
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR})

set(SOURCE_FILES
        src/LogClient.cpp
        include/LogClient/LogClient.hpp
)
if(WIN32)
        set(USE_WINDOWS_SSPI ON)
        set(USE_SCHANNEL ON)
endif()
include(${CMAKE_CURRENT_SOURCE_DIR}/cmake/DownloadDependencies.cmake)


if (CMAKE_CXX_COMPILER_ID STREQUAL "MSVC")
    set(CMAKE_CXX_FLAGS_DEBUG
            "/DWIN32 /D_WINDOWS /EHsc /WX /wd4355 /wd4251 /wd4250 /wd4996 /FS"
            CACHE STRING "Debug compiler flags" FORCE
    )
else ()
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS}")
    set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_CXX_FLAGS} -I /usr/local/include -I ../../include -DCURL_STATICLIB -Bstatic")
endif ()
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/src/)
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/include)
add_library(Client ${SOURCE_FILES})
if (WIN32)
    set(LIBRARIES
            libcurl_static
            jsoncpp_lib
    )
    set(TEST_LIBRARIES
            Client
            jsoncpp_lib
            libcurl_static
            GTest::gtest_main
            GTest::gmock_main
    )
elseif (APPLE)
    set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_CXX_FLAGS} -lstdc++")
    set(LIBRARIES
            jsoncpp_lib
            libcurl_static
    )
    set(TEST_LIBRARIES
            Client
            jsoncpp_lib
            libcurl_static
            GTest::gtest_main
            GTest::gmock_main
    )
elseif (UNIX)
    set(LIBRARIES
            jsoncpp_lib
            libcurl_static
    )
    set(TEST_LIBRARIES
            Client
            jsoncpp_lib
            libcurl_static
            GTest::gtest_main
            GTest::gmock_main
    )
endif ()

# target_sources(Client PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/src/resource.rc)
target_link_libraries(Client
        PRIVATE
        ${LIBRARIES}
)

add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/test)
