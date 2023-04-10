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
            Layout.fillHeight: parent
            Layout.fillWidth: parent
            model: testListModel

            delegate: Text {
                text: model.name
            }
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
        id: testListModel

        ListElement {
            name: "Folder"
        }
        ListElement {
            name: "File1"
        }
        ListElement {
            name: "File2"
        }
    }
}
