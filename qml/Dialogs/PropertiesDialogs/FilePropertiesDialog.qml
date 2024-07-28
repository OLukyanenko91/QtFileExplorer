import QtQuick
import QtQuick.Layouts
import QtQuick.Controls


Item {
    // SIGNALS

//    signal accepted(input: string)
//    signal showed()
//    signal hidden()

    // PROPERTIES
//    property string pTip: ""

    // FUNCTIONS

    function show(inputText) {
        root.visible = true

//        if (inputText) {
//            input.text = inputText
//            input.pDefaultInput = inputText
//        }
    }

    function hide() {
        root.visible = false

//        input.clear()
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
        width: 300
        height: 125
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
                    asynchronous: true
                    mipmap: true
//                    Layout.preferredWidth: parent.height
//                    Layout.preferredHeight: parent.height
                    fillMode: Image.PreserveAspectFit
                    source: "image://fileIconProvider/" + path
                }

                Label {
                    id: name
                    text: "DriverPropertiesDialog.qml"
                }
            }

            Rectangle {
                color: "black"
                height: 5
                width: 50
            }
        }
    }

//    onVisibleChanged: visible ? showed() : hidden()
}
