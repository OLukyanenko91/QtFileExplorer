import QtQuick
import QtQuick.Window
import QtQuick.Layouts
import QtQuick.Controls
import CustomData
import "ProgressView"
import "utils.js" as Utils


Window {
    // PROPERTIES

    property bool         pCuttingActive:    false
    property bool         pCopyingActive:    false
    property string       pCutCopySourceDir: ""
    property list<string> pFilesToCutCopy:   []

    // DATA

    id: root
    width: 850
    height: 400
    visible: true
    title: qsTr("File Explorer")

    ColumnLayout {
        id: controls
        anchors.fill: parent
        anchors.margins: 10

        RowLayout {
            id: mainButtons
            Layout.preferredHeight: 35
            Layout.fillWidth: parent

            CButton {
                id: newFolderButton
                Layout.fillWidth: parent
                pText: "New folder"
                pEnabled: curPath.text !== ""

                onClicked: {
                    newFolderDialog.show()
                }
            }

            CButton {
                id: cutButton
                Layout.fillWidth: parent
                pText: "Cut"
                pEnabled: listView.pSelectedIndexesList.length >= 1 &&
                          curPath.text !== ""

                onClicked: {
                    pCuttingActive = true
                    pCopyingActive = false
                    pFilesToCutCopy = listView.getSelectedFiles()
                    pCutCopySourceDir = curPath.text
                }
            }

            CButton {
                id: copyButton
                Layout.fillWidth: parent
                pText: "Copy"
                pEnabled: listView.pSelectedIndexesList.length >= 1 &&
                          curPath.text !== ""

                onClicked: {
                    pCopyingActive = true
                    pCuttingActive = false
                    pFilesToCutCopy = listView.getSelectedFiles()
                    pCutCopySourceDir = curPath.text
                }
            }

            CButton {
                id: pasteButton
                Layout.fillWidth: parent
                pText: "Paste"
                pEnabled: (pCopyingActive || pCuttingActive) &&
                          curPath.text !== ""

                onClicked: {
                    if (root.pCopyingActive) {
                        progressView.showCopyingProgress(pFilesToCutCopy.length,
                                                         pCutCopySourceDir,
                                                         curPath.text)
                        progressView.pTaskId = controller.copyFiles(pFilesToCutCopy,
                                                                    curPath.text)
                    }
                    else if (root.pCuttingActive) {
                        progressView.showMovingProgress(pFilesToCutCopy.length,
                                                        pCutCopySourceDir,
                                                        curPath.text)
                        progressView.pTaskId = controller.moveFiles(pFilesToCutCopy,
                                                                    curPath.text)
                    }
                    else {
                        throw "Incorrect state"
                    }

                    pCuttingActive = false
                }
            }

            CButton {
                id: renameButton
                Layout.fillWidth: parent
                pText: "Rename"
                pEnabled: listView.pSelectedIndexesList.length === 1 &&
                          curPath.text !== ""
            }

            CButton {
                id: deleteButton
                Layout.fillWidth: parent
                pText: "Delete"
                pEnabled: listView.pSelectedIndexesList.length >= 1 &&
                          curPath.text !== ""

                onClicked: {
                    var selectedFiles = listView.getSelectedFiles()

                    if (selectedFiles.length !== 0) {
                        progressView.showDeletingProgress(selectedFiles.length,
                                                          curPath.text)
                        progressView.pTaskId = controller.deleteFiles(selectedFiles)
                    }
                    else {
                        console.error("No selected files for deletion")
                    }
                }
            }

            CButton {
                id: propertiesButton
                Layout.fillWidth: parent
                pText: "Properties"
                pEnabled: listView.pSelectedIndexesList.length === 1
            }
        }

        RowLayout {
            id: extraControls
            Layout.preferredHeight: 35
            Layout.fillWidth: parent

            CButton {
                pText: "<"
                pEnabled: true

                onPressed: {
                    statusBar.clear()
                    controller.goBack()
                }
            }

            CButton {
                text: ">"
                pEnabled: true

                onPressed: {
                    statusBar.clear()
                    controller.goForward()
                }
            }

            CButton {
                text: "^"
                pEnabled: true
            }

            TextField {
                id: curPath
                Layout.fillWidth: parent
                Layout.preferredHeight: 35
                placeholderText: "Current path"
            }

            TextField {
                Layout.preferredWidth: 300
                Layout.preferredHeight: 35
                placeholderText: "Search"
            }
        }

        FilesView {
            id: listView
            pModel: model

            onPSelectedIndexesListChanged: {
                if (pSelectedIndexesList.length) {
                    var selectedFilesList = []

                    pSelectedIndexesList.forEach((selectedIndex) => {
                        let item = model.get(selectedIndex)
                        if (item) {
                            item.selected = true
                            selectedFilesList.push(item.path)
                        }
                    })

                    if (selectedFilesList.length) {
                        let size = controller.getFilesSize(selectedFilesList)
                        statusBar.updateSelectedItemsSize(size)
                        statusBar.updateSelectedItemsCount(selectedFilesList.length)
                    }
                }
                else {
                    statusBar.updateSelectedItemsSize("")
                    statusBar.updateSelectedItemsCount(0)
                }
            }
        }

        RowLayout {
            // FUNCTIONS

            function clear() {
                selectedItemSize.text = ""
                selectedItemsCount.text = ""
            }

            function updateItemsCount(counts) {
                itemsCount.text = (counts === 1 ? "1 item" :
                                                  counts + " items")
            }

            function updateSelectedItemsCount(counts) {
                selectedItemsCount.text = (counts === 1 ? "1 item selected" :
                                           counts > 1 ? counts + " items selected" : "")
            }

            function updateSelectedItemsSize(size) {
                selectedItemSize.text = size
            }

            // DATA

            id: statusBar
            Layout.preferredHeight: 10
            Layout.fillWidth: parent

            Label {
                id: itemsCount
                text: "0 items"
            }

            Rectangle {
                color: "grey"
                width: 1
                height: 10
                opacity: 0.5
            }

            Label {
                id: selectedItemsCount
            }

            Label {
                id: selectedItemSize
            }
        }
    }

    ProgressView {
        id: progressView
        anchors.fill: parent

        onResumeTask: controller.resumeBackgroundTask(pTaskId)
        onPauseTask: controller.pauseBackgroundTask(pTaskId)
        onCancelTask: controller.cancelBackgroundTask(pTaskId)
        onShowed: listView.enabled = false
        onHidden: listView.enabled = true
    }

    InputDialog {
        id: newFolderDialog
        anchors.fill: parent
        pTip: "Enter a folder name"

        onShowed: listView.enabled = false
        onHidden: listView.enabled = true
        onAccepted: (input) => {
            controller.createDirectory(curPath.text + "/" + input)
            hide()
        }
    }

    ListModel {
        // FUNCTIONS

        function appendItem(item) {
            model.append({"name":        item.name,
                          "path":        item.path,
                          "type":        item.type,
                          "selected":    false,
                          "highlighted": false})
        }

        function appendItems(items) {
            for(let index in items) {
                model.appendItem(items[index])
            }
        }

        function updateItemSelection(index: int,
                                     selected: Boolean,
                                     highlighted: Boolean) {
            var item = model.get(index)
            if (item) {
                item.selected = selected
                item.highlighted = highlighted
            }
        }

        function itemSelected(index: int) : Boolean {
            var item = model.get(index)
            if (item) {
                return item.selected
            }
        }

        // DATA

        id: model
    }

    Connections {
        // FUNCTIONS

        function onContentsChanged(contents) {
            listView.clearSelections()
            model.clear()
            model.appendItems(contents)
            statusBar.updateItemsCount(contents.length)
        }

        function onCurrentDirectoryChanged(path) {
            curPath.text = path
        }

        function onBackgroundTaskProgressChanged(taskId, taskProgress) {
            progressView.pCurrentProgress = taskProgress
        }

        function onBackgroundTaskFinished(taskId) {
            progressView.hide()
        }

        // DATA

        target: controller
    }

    Component.onCompleted: {
        controller.open(controller.rootDirectory)
    }
}
