import QtQuick
import QtQuick.Window
import QtQuick.Layouts
import QtQuick.Controls
import CustomData


Window {
    width: 850
    height: 400
    visible: true
    title: qsTr("File Explorer")

    ColumnLayout {
        anchors.fill: parent
        anchors.margins: 10

        RowLayout {
            Layout.preferredHeight: 20
            Layout.fillWidth: parent

            Button {
                Layout.fillWidth: parent
                text: "Move"
            }

            Button {
                Layout.fillWidth: parent
                text: "Copy"
            }

            Button {
                Layout.fillWidth: parent
                text: "Delete"
            }

            Button {
                Layout.fillWidth: parent
                text: "Rename"
            }

            Button {
                Layout.fillWidth: parent
                text: "New folder"
            }

            Button {
                Layout.fillWidth: parent
                text: "Properties"
            }
        }

        RowLayout {
            Layout.preferredHeight: 20
            Layout.fillWidth: parent

            Button {
                text: "<"

                onPressed: {
                    controller.goBack();
                }
            }

            Button {
                text: ">"

                onPressed: {
                    controller.goForward();
                }
            }

            Button {
                text: "^"
            }

            TextField {
                id: curPath
                Layout.fillWidth: parent
            }

            TextField {
                Layout.preferredWidth: 300
                placeholderText: "Search"
            }
        }

        ListView {
            readonly property string rSelectedColor:    "#cce7fe"
            readonly property string rHighlightedColor: "#e4f3fe"
            readonly property string rDefaultColor:     "#ffffff"
            readonly property int    rDefaultIndex:     -1

            function clearSelections() {
                for (let index = 0; index < count; index++) {
                    let item = listView.itemAtIndex(index)
                    if (item) {
                        item.color = listView.rDefaultColor
                    }
                }
            }

            function selectItem(index: int) {
                let item = listView.itemAtIndex(index)
                if (item) {
                    item.color = listView.rSelectedColor
                }
            }

            id: listView
            Layout.fillHeight: parent
            Layout.fillWidth: parent
            model: model
            focus: true
            clip: true
            spacing: 1
            boundsBehavior: Flickable.StopAtBounds
            ScrollBar.vertical: ScrollBar {}

            delegate: Rectangle {
                id: listViewItemBackground
                height: 20
                width: parent ? parent.width : 0
                color: listView.rDefaultColor

                RowLayout {
                    // Roles
                    //   name - file name
                    //   path - file path
                    //   type - file type (file, folder, driver)

                    spacing: 5
                    anchors.fill: parent

                    Image {
                        asynchronous: true
                        mipmap: true
                        Layout.preferredWidth: parent.height
                        Layout.preferredHeight: parent.height
                        fillMode: Image.PreserveAspectFit
                        source: "image://fileIconProvider/" + path
                    }

                    Text {
                        id: fileName
                        text: type === FileType.DRIVER ? "Local Disk (" + name + ")" : name
                        Layout.fillHeight: true
                        Layout.fillWidth: true
                        verticalAlignment: Text.AlignVCenter
                    }
                }

                MouseArea {
                    anchors.fill: parent
                    hoverEnabled: true

                    onEntered: {
                        if (listView.currentIndex !== index) {
                            let item = listView.itemAtIndex(index)
                            item.color = listView.rHighlightedColor
                        }
                    }

                    onExited: {
                        if (listView.currentIndex !== index) {
                            let item = listView.itemAtIndex(index)
                            if (item) {
                                item.color = listView.rDefaultColor
                            }
                        }
                    }

                    onClicked: {
                        listView.currentIndex = index
                    }

                    onDoubleClicked: {
                        listView.currentIndex = listView.rDefaultIndex
                        controller.open(path)
                    }
                }
            }

            onCurrentIndexChanged: {
                clearSelections()
                selectItem(currentIndex)
            }

            Component.onCompleted: currentIndex = listView.rDefaultIndex
        }

        RowLayout {
            Layout.preferredHeight: 20
            Layout.fillWidth: parent

            Label {
                text: "N items"
            }

            Rectangle {
                color: "grey"
                width: 2
                height: 10
                opacity: 0.5
            }

            Label {
                text: "N item(s) selected"
            }

            Label {
                text: "362 KB"
            }
        }
    }

    ListModel {
        function appendItem(item) {
            model.append({"name": item.name,
                          "path": item.path,
                          "type": item.type})
        }

        function appendItems(items) {
            for(let index in items) {
                model.appendItem(items[index])
            }
        }

        id: model
    }

    Component.onCompleted: {
        controller.open(controller.rootDirectory)
    }

    Connections {
        target: controller

        function onUpdateUIContents(contents) {
            model.clear()
            model.appendItems(contents)
        }

        function onUpdateUICurrentDirectory(path) {
            curPath.text = path
        }
    }
}

// TODO: Fix item highlighting
