cmake_minimum_required(VERSION 3.20)
project(orderbook CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_BUILD_TYPE Debug)

include_directories(include)

add_library(orderbook_lib
    src/order_book.cpp
    src/matching_engine.cpp    
)

add_executable(main main.cpp)
target_link_libraries(main orderbook_lib)

