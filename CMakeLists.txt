cmake_minimum_required(VERSION 3.28.3)

project(TotalCommander VERSION 1.0 LANGUAGES CXX)

list(APPEND CMAKE_PREFIX_PATH "/home/rares/Qt/6.11.0/gcc_64")

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTORCC ON)

find_package(Qt6 REQUIRED COMPONENTS Widgets Core Gui)

set(SOURCES
    main.cpp
    mainwindow.cpp
    # UI widgets
    ui/ToolBarWidget.cpp
    ui/ToolTextButton.cpp
    ui/FilePanel.cpp
    ui/CenterBar.cpp
    ui/CommandBar.cpp
    ui/FunctionBar.cpp
    ui/CompareDialog.cpp
    ui/SearchDialog.cpp    
    services/FileOperations.cpp
    services/DirectoryComparator.cpp
    services/FileSearcher.cpp
    controller/FileOperationController.cpp
    controller/CompareController.cpp
    controller/SearchController.cpp
)

set(HEADERS
    mainwindow.h
    # UI widgets
    ui/ToolBarWidget.h
    ui/ToolTextButton.h
    ui/FilePanel.h
    ui/CenterBar.h
    ui/CommandBar.h
    ui/FunctionBar.h
    ui/CompareDialog.h
    ui/SearchDialog.h
    # Services
    services/FileOperations.h
    services/DirectoryComparator.h
    services/FileSearcher.h
    # Controllers
    controller/FileOperationController.h
    controller/CompareController.h
    controller/SearchController.h
)

set(RESOURCES
    resources.qrc
)

add_executable(TotalCommander ${SOURCES} ${HEADERS} ${RESOURCES})

target_include_directories(TotalCommander PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
target_compile_definitions(TotalCommander PRIVATE SOURCE_DIR="${CMAKE_SOURCE_DIR}")
target_link_libraries(TotalCommander PRIVATE Qt6::Widgets Qt6::Core Qt6::Gui)
