import QtQuick
import QtQuick.Window
import QtQuick.Layouts
import QtQuick.Controls


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
            }

            Button {
                text: ">"
            }

            Button {
                text: "^"
            }

            TextField {
                Layout.fillWidth: parent
            }

            TextField {
                Layout.preferredWidth: 300
                placeholderText: "Search"
            }
        }

        ListView {
            readonly property string rSelectedColor: "#cce7fe"
            readonly property string rHighlightedColor: "#e4f3fe"
            readonly property string rDefaultColor: "#ffffff"

            function clearSelections() {
                for (let index = 0; index < count; index++) {
                    let item = listView.itemAtIndex(index)
                    item.color = listView.rDefaultColor
                }
            }

            function selectItem(index: int) {
                let item = listView.itemAtIndex(index)
                item.color = listView.rSelectedColor
            }

            id: listView
            Layout.fillHeight: parent
            Layout.fillWidth: parent
            model: model
            focus: true
            clip: true
            spacing: 1

            delegate: Rectangle {
                height: 20
                width: parent.width

                Text {
                    text: model.name
                    anchors.verticalCenter: parent.verticalCenter
                }

                MouseArea {
                    anchors.fill: parent
                    hoverEnabled: true

                    onClicked: {
                        listView.currentIndex = index
                    }
                    onEntered: {
                        if (listView.currentIndex != index) {
                            let item = listView.itemAtIndex(index)
                            item.color = listView.rHighlightedColor
                        }
                    }
                    onExited: {
                        if (listView.currentIndex != index) {
                            let item = listView.itemAtIndex(index)
                            item.color = listView.rDefaultColor
                        }
                    }
                }
            }

            onCurrentIndexChanged: {
                clearSelections()
                selectItem(currentIndex)
            }

            Component.onCompleted: currentIndex = -1
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
        id: model

        function appendItem(name) {
            model.append({"name": name})
        }
    }

    Component.onCompleted: {
        var drivers = controller.getDrivers()

        for(let driver in drivers) {
            model.appendItem(drivers[driver])
        }
    }
}