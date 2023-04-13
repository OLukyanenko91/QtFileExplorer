cmake_minimum_required(VERSION 3.16)

project(QtFileExplorer VERSION 0.1 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(Qt6 6.2 REQUIRED COMPONENTS Quick)

qt_standard_project_setup()

qt_add_executable(appQtFileExplorer
    main.cpp
    Controller.cpp
    Explorer.cpp
)

qt_add_qml_module(appQtFileExplorer
    URI QtFileExplorer
    VERSION 1.0
    QML_FILES MainWindow.qml
)

target_link_libraries(appQtFileExplorer
    PRIVATE Qt6::Quick
)
