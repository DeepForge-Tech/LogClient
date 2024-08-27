cmake_minimum_required(VERSION 3.18)

if (WIN32)
    set(TEST_LIBRARIES
            Client
            jsoncpp_lib
            libcurl_static
            GTest::gtest_main
            GTest::gmock_main
    )
elseif (APPLE)
    set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_CXX_FLAGS} -lstdc++")
    set(TEST_LIBRARIES
            Client
            jsoncpp_lib
            libcurl_static
            GTest::gtest_main
            GTest::gmock_main
    )
elseif (UNIX)
    set(TEST_LIBRARIES
            Client
            jsoncpp_lib
            libcurl_static
            GTest::gtest_main
            GTest::gmock_main
    )
endif ()

FetchContent_Declare(
        googletest
        URL https://github.com/google/googletest/archive/03597a01ee50ed33e9dfd640b249b4be3799d395.zip
)
FetchContent_MakeAvailable(googletest)

include_directories(${CMAKE_CURRENT_SOURCE_DIR}/include)

set(TEST_SOURCE_FILES
        src/UnitTest/UnitTest.cpp
)
enable_testing()
add_executable(
        UnitTest_LogClient
        ${TEST_SOURCE_FILES}
)
target_link_libraries(
    UnitTest_LogClient
        ${TEST_LIBRARIES}
)
include(GoogleTest)
gtest_discover_tests(UnitTest_LogClient)
