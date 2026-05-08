cmake_minimum_required(VERSION 3.28.3)

project(Fex VERSION 1.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

file(GLOB Src src/*)

add_executable(${PROJECT_NAME} ${Src})

install(TARGETS ${PROJECT_NAME} 
    RUNTIME DESTINATION ${CMAKE_SOURCE_DIR}
)

find_package(Qt6 REQUIRED COMPONENTS Widgets Core Gui)
