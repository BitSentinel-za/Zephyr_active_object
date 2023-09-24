cmake_minimum_required(VERSION 3.20.0)
find_package(Zephyr REQUIRED HINTS $ENV{ZEPHYR_BASE})

project(wrapper C ASM CXX)

set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_STANDARD 14)

include_directories( src/control_thread src/event src/application)

# Add our main executable
FILE(GLOB app_sources src/*.cpp 
                      src/control_thread/*.cpp 
                      src/control_thread/*.h
                      src/event/*cpp
                      src/event/*h
                      src/application/*cpp
                      src/application/*.h)

target_sources(app PRIVATE ${app_sources}) 
