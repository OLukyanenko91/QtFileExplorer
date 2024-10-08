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

    function show(file) {
        root.visible = true

        image.source = "image://fileIconProvider/" + file.path
        header.text = "Properties: " + file.name
        type.text = file.suffix
        location.text = file.location
        sizeLabel.text = Utils.convertBytesToShortString(file.size) + " (" +
                         Utils.convertBytesToString(file.size) + " bytes)"
        createdTime.text = file.createdTime
        modifiedTime.text = file.lastModifiedTime
        lastOpenedTime.text = file.lastReadTime
        onlyReadingCheckBox.checked = file.onlyReading
        hiddenCheckBox.checked = file.hidden
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
        height: 390
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
                    id: type
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
                }

                Label {
                    id: location
                    Layout.fillWidth: true
                    wrapMode: TextEdit.WordWrap
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


            RowLayout {
                Label {
                    text: "Modified:"
                    Layout.preferredWidth: 70
                }

                Label {
                    id: modifiedTime
                    Layout.fillWidth: true
                }
            }

            RowLayout {
                Label {
                    text: "Opened:"
                    Layout.preferredWidth: 70
                }

                Label {
                    id: lastOpenedTime
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
