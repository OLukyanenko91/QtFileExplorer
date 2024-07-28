import QtQuick
import QtQuick.Layouts
import QtQuick.Controls
import "../"


Item {
    // SIGNALS

    signal accepted(input: string)
    signal showed()
    signal hidden()

    // PROPERTIES
    property string pTip: ""

    // FUNCTIONS

    function show(inputText) {
        root.visible = true

        if (inputText) {
            input.text = inputText
            input.pDefaultInput = inputText
        }
    }

    function hide() {
        root.visible = false

        input.clear()
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
                id: tipLayout
                Layout.alignment: Qt.AlignCenter

                Label {
                    id: tip
                    text: pTip
                    font.bold: true
                }
            }

            RowLayout {
                id: inputLayout

                TextField {
                    // PROPERTIES
                    property string pDefaultInput: ""

                    // FUNCTIONS

                    function clear() {
                        text = ""
                    }

                    // DATA

                    id: input
                    Layout.fillWidth: true
                }
            }

            RowLayout {
                id: buttonsLayout
                Layout.alignment: Qt.AlignCenter

                CButton {
                    pText: "Ok"
                    pEnabled: input.text &&
                              input.text !== input.pDefaultInput

                    onPressed: {
                        accepted(input.text)
                    }
                }

                CButton {
                    pText: "Cancel"
                    pEnabled: true

                    onPressed: hide()
                }
            }
        }
    }

    onVisibleChanged: visible ? showed() : hidden()
}
