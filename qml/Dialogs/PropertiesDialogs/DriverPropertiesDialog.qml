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

    function show(driver) {
        root.visible = true

        image.source = "image://fileIconProvider/" + driver.path
        fileSystem.text = driver.fileSystem
        type.text = driver.diskType
        header.text = "Properties: " + driver.name + " (" + driver.diskLetter + ":)"
        diskLetter.text = "Disk " + driver.diskLetter
        usedSpaceGB.text = Utils.convertBytesToGigabytes(driver.usedSpace) + " GB"
        usedSpaceB.text = Utils.convertBytesToString(driver.usedSpace) + " bytes"
        freeSpaceGB.text = Utils.convertBytesToGigabytes(driver.freeSpace) + " GB"
        freeSpaceB.text = Utils.convertBytesToString(driver.freeSpace) + " bytes"
        capacityGB.text = Utils.convertBytesToGigabytes(driver.capacity) + " GB"
        capacityB.text = Utils.convertBytesToString(driver.capacity) + " bytes"
        capacityIndication.value = (driver.usedSpace / driver.capacity * 100) / 100
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
        width: 275
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
                    Layout.preferredWidth: 60
                }

                Label {
                    id: type
                }
            }

            RowLayout {
                Label {
                    text: "File system:"
                    Layout.preferredWidth: 60
                }

                Label {
                    id: fileSystem
                }
            }

            Rectangle {
                color: "lightgrey"
                Layout.preferredHeight: 1.5
                Layout.fillWidth: true
            }

            RowLayout {
                Layout.fillWidth: true

                Rectangle {
                    color: "steelblue"
                    width: 15
                    height: 15
                }

                Label {
                    text: "Used:"
                    Layout.preferredWidth: 70
                }

                Label {
                    id: usedSpaceB
                    Layout.fillWidth: true
                    horizontalAlignment: Text.AlignRight
                }

                Label {
                    id: usedSpaceGB
                    Layout.preferredWidth: 50
                    horizontalAlignment: Text.AlignRight
                }
            }

            RowLayout {
                Rectangle {
                    color: "grey"
                    width: 15
                    height: 15
                }

                Label {
                    text: "Free:"
                    Layout.preferredWidth: 70
                }

                Label {
                    id: freeSpaceB
                    Layout.fillWidth: true
                    horizontalAlignment: Text.AlignRight
                }

                Label {
                    id: freeSpaceGB
                    Layout.preferredWidth: 50
                    horizontalAlignment: Text.AlignRight
                }
            }

            Rectangle {
                color: "lightgrey"
                Layout.preferredHeight: 1.5
                Layout.fillWidth: true
            }

            RowLayout {
                Label {
                    text: "Capacity:"
                    Layout.preferredWidth: 70
                }

                Label {
                    id: capacityB
                    Layout.fillWidth: true
                    horizontalAlignment: Text.AlignRight
                }

                Label {
                    id: capacityGB
                    Layout.preferredWidth: 50
                    horizontalAlignment: Text.AlignRight
                }
            }

            ProgressBar {
                id: capacityIndication
                padding: 1
                Layout.alignment: Qt.AlignCenter

                background: Rectangle {
                    implicitWidth: 200
                    implicitHeight: 6
                    color: "#e6e6e6"
                    radius: 3
                }

                contentItem: Item {
                    implicitWidth: 200
                    implicitHeight: 4

                    Rectangle {
                        width: capacityIndication.visualPosition * parent.width
                        height: parent.height
                        radius: 2
                        color: "steelblue"
                    }
                }
            }

            Label {
                id: diskLetter
                Layout.alignment: Layout.Center
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
