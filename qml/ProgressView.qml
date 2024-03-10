import QtQuick
import QtQuick.Layouts
import QtQuick.Controls


Item {
    // SIGNALS

    signal pauseTask()
    signal resumeTask()
    signal cancelTask()

    // PROPERTIES

    property real pTaskId:          0
    property int  pCurrentProgress: 0
    property bool pRunning:         true

    // FUNCTIONS

    function show() {
        visible = true
    }

    function hide() {
        visible = false
    }

    // DATA

    id: root
    visible: false

    Rectangle {
        anchors.fill: parent
        color: "gray"
        opacity: 0.5
    }

    Rectangle {
        width: 400
        height: 100
        color: "white"
        radius: 10
        anchors.centerIn: parent

        ColumnLayout {
            anchors.fill: parent
            anchors.margins: 15

            RowLayout {
                Text { text: "Copying" }
                Text { text: "1"}
                Text { text: "item from" }
                Text {
                    text: "Test1"
                    color: "blue"
                }
                Text { text: "to"}
                Text {
                    text: "Test2"
                    color: "blue"
                }
            }

            RowLayout {
                Layout.fillWidth: true

                Text {
                    text: (!pRunning ? "Paused - " : "") + pCurrentProgress + "% complete"
                    font.pointSize: 12
                    Layout.fillWidth: true
                }

                Button {
                    id: controlButton
                    text: pRunning ? "Pause" : "Resume"

                    onPressed: {
                        pRunning = !pRunning

                        pRunning ? resumeTask() : pauseTask()
                    }
                }

                Button {
                    id: cancelButton
                    Layout.alignment: Qt.AlignRight
                    text: "Cancel"

                    onPressed: {
                        cancelTask()

                        controlButton.enabled = false
                        cancelButton.enabled = false
                        progress.indeterminate = true
                    }
                }
            }

            ProgressBar {
                id: progress
                Layout.fillWidth: true
                from: 0
                to: 100
                value: root.visible ? pCurrentProgress : 0
                opacity: pRunning ? 1 : 0.5
            }
        }
    }
}
