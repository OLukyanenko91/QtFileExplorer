cmake_minimum_required(VERSION 3.16)

project(QtFileExplorer VERSION 0.1.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(Qt6 6.2 REQUIRED COMPONENTS Quick QuickControls2 Widgets)

qt_standard_project_setup()

qt_add_executable(appQtFileExplorer
    src/main.cpp
    src/Controller.cpp
    src/Explorer/Explorer.cpp
    src/Explorer/ExplorerData.hpp
    src/Explorer/History/History.cpp
    src/Explorer/File/File.cpp
    src/Explorer/File/FileIconProvider.cpp
    src/TasksManager/TasksManager.cpp
    src/TasksManager/Task/Task.cpp
    src/TasksManager/Task/CopyFilesTask.cpp
    src/TasksManager/Task/DeleteFilesTask.cpp
    src/TasksManager/Task/MoveFilesTask.cpp
)

qt_add_qml_module(appQtFileExplorer
    URI QtFileExplorer
    VERSION 1.0
    QML_FILES qml/MainWindow.qml
              qml/FilesView.qml
              qml/Dialogs/ProgressDialog.qml
              qml/Dialogs/InputDialog.qml
              qml/Dialogs/PropertiesDialogs/FilePropertiesDialog.qml
              qml/Dialogs/PropertiesDialogs/DriverPropertiesDialog.qml
              qml/CButton.qml
              qml/CLabel.qml
              qml/utils.js
)

target_link_libraries(appQtFileExplorer
    PRIVATE Qt6::Quick Qt6::Widgets Qt6::QuickControls2
)
