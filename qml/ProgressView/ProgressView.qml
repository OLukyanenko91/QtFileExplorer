import QtQuick
import QtQuick.Layouts
import QtQuick.Controls
import "../"
import "../utils.js" as Utils


Item {
    // SIGNALS

    signal pauseTask()
    signal resumeTask()
    signal cancelTask()
    signal showed()
    signal hidden()

    // PROPERTIES

    property real pTaskId:          0
    property int  pCurrentProgress: 0
    property bool pRunning:         true

    // FUNCTIONS

    function showCopyingProgress(itemsCount: int,
                                 fromPath: String,
                                 toPath: String) {
        info.reset("Copying",
                    itemsCount,
                    fromPath,
                    toPath)

        root.visible = true
    }

    function showDeletingProgress(itemsCount: int,
                                  fromPath: String) {
        info.reset("Deleting",
                    itemsCount,
                    fromPath,
                    "")

        root.visible = true
    }

    function showMovingProgress(itemsCount: int,
                                fromPath: String,
                                toPath: String) {
        info.reset("Moving",
                    itemsCount,
                    fromPath,
                    toPath)

        root.visible = true
        showed()
    }

    function hide() {
        root.visible = false
        pCurrentProgress = 0
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
                // FUNCTIONS

                function reset(operationType: String,
                               itemsCount: String,
                               fromPath: String,
                               toPath: String) {
                    operationTypeInfo.text = operationType
                    countInfo.text = itemsCount
                    to.visible = (toPath ? true : false)
                    controlButton.enabled = true
                    cancelButton.enabled = true
                    progress.indeterminate = false

                    fromInfo.setText(Utils.cutPathEnd(fromPath),
                                     fromPath)
                    toInfo.setText(Utils.cutPathEnd(toPath),
                                   toPath)
                }

                function clear() {
                    operationTypeInfo.text = ""
                    countInfo.text = ""

                    fromInfo.clear()
                    toInfo.clear()
                }

                // DATA

                id: info

                Text { id: operationTypeInfo }
                Text { id: countInfo }
                Text { text: "item(s) from" }
                CLabel {
                    id: fromInfo
                    pColor: "blue"
                }
                Text {
                    id: to
                    text: "to"
                }
                CLabel {
                    id: toInfo
                    pColor: "blue"
                }
            }

            RowLayout {
                id: controls
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

    onVisibleChanged: visible ? showed() : hidden()
}
