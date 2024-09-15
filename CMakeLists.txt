cmake_minimum_required(VERSION 3.20)
project(mini-db)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
add_executable(${PROJECT_NAME})

# find_package(SDL2 REQUIRED)
# include_directories(${SDL_INCLUDE_DIRS})

target_compile_options(${PROJECT_NAME} PRIVATE -Wall -Wextra -pedantic)
target_include_directories(${PROJECT_NAME} PRIVATE "${CMAKE_CURRENT_SOURCE_DIR}/include")
# target_link_libraries(${PROJECT_NAME} SDL2::SDL2 SDL2_image)
target_sources( ${PROJECT_NAME} PRIVATE src/main.cpp src/debugger.cpp src/breakpoint.cpp src/linenoise.c)
