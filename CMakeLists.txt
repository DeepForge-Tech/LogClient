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
            jsoncpp_static
    )
    set(TEST_LIBRARIES
            Client
            jsoncpp_static
            libcurl_static
            GTest::gtest_main
            GTest::gmock_main
    )
elseif (APPLE)
    set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_CXX_FLAGS} -lstdc++")
    set(LIBRARIES
            jsoncpp_static
            libcurl_static
    )
    set(TEST_LIBRARIES
            Client
            jsoncpp_static
            libcurl_static
            GTest::gtest_main
            GTest::gmock_main
    )
elseif (UNIX)
    set(LIBRARIES
            jsoncpp_static
            libcurl_static
    )
    set(TEST_LIBRARIES
            Client
            jsoncpp_static
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

FetchContent_Declare(
        googletest
        URL https://github.com/google/googletest/archive/03597a01ee50ed33e9dfd640b249b4be3799d395.zip
)
FetchContent_MakeAvailable(googletest)
set(TEST_SOURCE_FILES
#        ${SOURCE_FILES}
        src/test/MainTest.cpp
        src/test/MainTest.hpp
        #   ./src/test/MainTest.hpp
)
enable_testing()
add_executable(
        ClientTest
        include/LogClient/LogClient.hpp
        ${TEST_SOURCE_FILES}
)
target_link_libraries(
        ClientTest
        ${TEST_LIBRARIES}
)
include(GoogleTest)
gtest_discover_tests(ClientTest)

# if(APPLE)
#   file(MAKE_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/Client.app/Contents)
#   file(MAKE_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/Client.app/Contents/MacOS)
#   file(MAKE_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/Client.app/Contents/Resources)
#   # Поиск всех файлов в исходной папке
#   file(GLOB ALL_SOURCE_FILES "${CMAKE_CURRENT_SOURCE_DIR}/src*")
#   # Копирование всех найденных файлов в целевую папку
#   file(COPY ${ALL_SOURCE_FILES} DESTINATION "${CMAKE_CURRENT_SOURCE_DIR}/Client.app/Contents/Resources")
#   file(COPY ${CMAKE_CURRENT_SOURCE_DIR}/build/Client DESTINATION "${CMAKE_CURRENT_SOURCE_DIR}/Client.app/Contents/MacOS")
#   file(COPY ${CMAKE_CURRENT_SOURCE_DIR}/Info.plist DESTINATION "${CMAKE_CURRENT_SOURCE_DIR}/Client.app/Contents")
# endif()
