set(BINARY ${CMAKE_PROJECT_NAME})

######### GTEST GMOCK FETCH
include(FetchContent)
FetchContent_Declare(
    googletest
    URL https://github.com/google/googletest/archive/refs/tags/v1.15.2.zip
    DOWNLOAD_EXTRACT_TIMESTAMP ON
)

set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

set(BUILD_GMOCK ON CACHE BOOL "" FORCE)
set(BUILD_GTEST ON CACHE BOOL "" FORCE)

#########

set(TEST_SOURCES
    src/patterns.cpp
    main.cpp
)

#set(ADDS_SOURCES
#    data.txt
#)
#
#file(COPY ${ADDS_SOURCES} DESTINATION ${CMAKE_CURRENT_BINARY_DIR}/adds)

add_executable(${BINARY}_tests ${TEST_SOURCES})

target_link_libraries(${BINARY}_tests ${BINARY}_lib gtest gmock)
