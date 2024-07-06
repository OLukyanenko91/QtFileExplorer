cmake_minimum_required(VERSION 3.16)

project(QtFileExplorer VERSION 0.1.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(Qt6 6.2 REQUIRED COMPONENTS Quick QuickControls2 Widgets)

qt_standard_project_setup()

qt_add_executable(appQtFileExplorer
    main.cpp
    Controller.cpp
    Explorer/Explorer.cpp
    Explorer/ExplorerData.hpp
    Explorer/History/History.cpp
    Explorer/File/File.cpp
    Explorer/File/FileIconProvider.cpp
    TasksManager/TasksManager.cpp
    TasksManager/Task/Task.cpp
    TasksManager/Task/CopyFilesTask.cpp
    TasksManager/Task/DeleteFilesTask.cpp
    TasksManager/Task/MoveFilesTask.cpp
)

qt_add_qml_module(appQtFileExplorer
    URI QtFileExplorer
    VERSION 1.0
    QML_FILES qml/MainWindow.qml
              qml/FilesView.qml
              qml/ProgressView/ProgressView.qml
              qml/CButton.qml
              qml/CLabel.qml
              qml/utils.js
)

target_link_libraries(appQtFileExplorer
    PRIVATE Qt6::Quick Qt6::Widgets Qt6::QuickControls2
)
