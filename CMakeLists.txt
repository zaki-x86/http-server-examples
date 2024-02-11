cmake_minimum_required(VERSION 3.27)

project(http_qtserver_examples)

# Set the directory containing Qt5 to CMAKE_MODULE_PATH
if(MSVC AND WIN32)
    set(CMAKE_PREFIX_PATH "C:\\Qt\\Qt5.12.12\\5.12.12\\msvc2017_64" ${CMAKE_PREFIX_PATH}) 
endif(MSVC AND WIN32)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

find_package(Qt5 COMPONENTS Core Network Concurrent REQUIRED)

####
# Get dependecies
####

include(FetchContent)

FetchContent_Declare(
    QHttp
    GIT_REPOSITORY https://github.com/zaki-x86/QHttp.git
    GIT_TAG main  # Replace with the desired tag or commit hash
)

FetchContent_MakeAvailable(QHttp)


####
# Set directory for shared header and sources
####

set(SHARED_DIR ${CMAKE_SOURCE_DIR}/shared)
file(GLOB SHARED_HEADERS ${SHARED_DIR}/*.h)
file(GLOB SHARED_SOURCES ${SHARED_DIR}/*.cpp)

####
# Set shared properties for all targets
####

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include_directories(
    ${CMAKE_BINARY_DIR}/_deps/qhttp-src/QHttp
    ${SHARED_DIR}
)

link_libraries(QHttp Qt5::Core Qt5::Network Qt5::Concurrent)

add_subdirectory(single_threaded_server)
add_subdirectory(multi_threaded_server)
