cmake_minimum_required(VERSION 3.28.3)

project(Fex VERSION 1.0 LANGUAGES CXX)

find_package(Qt6 REQUIRED COMPONENTS Widgets Core Gui)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

file(GLOB Src src/*)

set(RESOURCES
    resources/resources.qrc
)

add_executable(${PROJECT_NAME} ${Src} ${RESOURCES})

install(TARGETS ${PROJECT_NAME} 
    RUNTIME DESTINATION ${CMAKE_SOURCE_DIR}
)
target_compile_definitions(Fex PRIVATE SOURCE_DIR="${CMAKE_CURRENT_SOURCE_DIR}")
target_link_libraries(${PROJECT_NAME} PRIVATE Qt6::Widgets Qt6::Core Qt6::Gui)