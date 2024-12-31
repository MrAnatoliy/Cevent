cmake_minimum_required(VERSION 3.28)

project(EventSystem)

set(CMAKE_C_STANDARD 11)
set(CMAKE_C_STANDARD_REQUIRED True)

set(CMAKE_C_COMPILER gcc)

include_directories(${PROJECT_SOURCE_DIR}/include)

set(SOURCES
    src/EventQueue.c
    src/EventDispatcher.c
    src/EventHandlerHashMap.c
    main.c
)

add_executable(EventSystem ${SOURCES})