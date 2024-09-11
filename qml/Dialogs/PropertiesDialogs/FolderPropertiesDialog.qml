import QtQuick
import QtQuick.Layouts
import QtQuick.Controls
import "../../"
import "../../utils.js" as Utils


Item {
    // SIGNALS

    signal showed()
    signal hidden()

    // FUNCTIONS

    function show(folder) {
        root.visible = true

        image.source = "image://fileIconProvider/" + folder.path
        header.text = "Properties: " + folder.name
        location.text = folder.location
        sizeLabel.text = Utils.convertBytesToShortString(folder.size) + " (" +
                         Utils.convertBytesToString(folder.size) + " bytes)"
        containsLabel.text = "Files: " + folder.subFilesCount +
                             "; Folders: " + folder.subFoldersCount
        createdTime.text = folder.createdTime
        onlyReadingCheckBox.checked = folder.onlyReading
        hiddenCheckBox.checked = folder.hidden
    }

    function hide() {
        root.visible = false
    }

    // DATA

    id: root
    visible: false

    Rectangle {
        id: background
        anchors.fill: parent
        color: "gray"
        opacity: 0.5
    }

    Rectangle {
        id: controls
        width: 350
        height: 357
        color: "white"
        radius: 10
        anchors.centerIn: parent

        ColumnLayout {
            anchors.fill: parent
            anchors.margins: 15

            RowLayout {
                id: nameLayout
                Layout.alignment: Qt.AlignCenter

                Image {
                    id: image
                    asynchronous: true
                    mipmap: true
                    Layout.preferredWidth: 25
                    Layout.preferredHeight: 25
                    fillMode: Image.PreserveAspectFit
                }

                Label {
                    id: header
                }
            }

            Rectangle {
                color: "lightgrey"
                Layout.preferredHeight: 1.5
                Layout.fillWidth: true
            }

            RowLayout {
                Label {
                    text: "Type:"
                    Layout.preferredWidth: 70
                }

                Label {
                    text: "Folder"
                }
            }

            Rectangle {
                color: "lightgrey"
                Layout.preferredHeight: 1.5
                Layout.fillWidth: true
            }

            RowLayout {
                Layout.fillWidth: true

                Label {
                    text: "Location:"
                    Layout.preferredWidth: 70
                    wrapMode: TextEdit.WordWrap
                }

                Label {
                    id: location
                    Layout.fillWidth: true
                }
            }

            RowLayout {
                Label {
                    text: "Size:"
                    Layout.preferredWidth: 70
                }

                Label {
                    id: sizeLabel
                    Layout.fillWidth: true
                }
            }

            RowLayout {
                Label {
                    text: "Contains:"
                    Layout.preferredWidth: 70
                }

                Label {
                    id: containsLabel
                    Layout.fillWidth: true
                }
            }

            Rectangle {
                color: "lightgrey"
                Layout.preferredHeight: 1.5
                Layout.fillWidth: true
            }

            RowLayout {
                Label {
                    text: "Created:"
                    Layout.preferredWidth: 70
                }

                Label {
                    id: createdTime
                    Layout.fillWidth: true
                }
            }

            Rectangle {
                color: "lightgrey"
                Layout.preferredHeight: 1.5
                Layout.fillWidth: true
            }

            RowLayout {
                Label {
                    text: "Attributes:"
                    Layout.preferredWidth: 70
                }

                CheckBox {
                    id: onlyReadingCheckBox
                    text: "Only reading"
                    enabled: false
                }

                CheckBox {
                    id: hiddenCheckBox
                    text: "Hidden"
                    enabled: false
                }
            }

            CButton {
                pText: "Ok"
                Layout.preferredHeight: 25
                Layout.alignment: Layout.Center
                pEnabled: true

                onPressed: {
                    hide()
                }
            }
        }
    }

    onVisibleChanged: visible ? showed() : hidden()
}
