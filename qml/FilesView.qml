import QtQuick
import QtQuick.Window
import QtQuick.Layouts
import QtQuick.Controls
import CustomData


ListView {
    readonly property string rSelectedColor:    "#cce7fe"
    readonly property string rHighlightedColor: "#e4f3fe"
    readonly property string rDefaultColor:     "#ffffff"
    readonly property int    rDefaultIndex:     -1

    property var mViewModel: ({})

    function clearSelections() {
        for (let index = 0; index < count; index++) {
            let item = root.itemAtIndex(index)
            if (item) {
                item.color = root.rDefaultColor
            }
        }
    }

    function resetSelectedIndex() {
        root.currentIndex = root.rDefaultIndex
    }

    function receiveKeyboardInput() {
        root.focus = true
    }

    function selectItem(index: int) {

        let item = root.itemAtIndex(index)
        if (item) {
            item.color = root.rSelectedColor
        }
    }

    id: root
    Layout.fillHeight: parent
    Layout.fillWidth: parent
    model: mViewModel
    focus: true
    clip: true
    spacing: 1
    boundsBehavior: Flickable.StopAtBounds
    ScrollBar.vertical: ScrollBar {}

    delegate: Rectangle {
        id: listViewItemBackground
        height: 25
        width: parent ? parent.width : 0
        color: root.rDefaultColor

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
                font.pointSize: 10
            }
        }

        MouseArea {
            anchors.fill: parent
            hoverEnabled: true
            enabled: root.enabled

            onEntered: {
                if (root.currentIndex !== index) {
                    let item = root.itemAtIndex(index)
                    item.color = root.rHighlightedColor
                }
            }

            onExited: {
                if (root.currentIndex !== index) {
                    let item = root.itemAtIndex(index)
                    if (item) {
                        item.color = root.rDefaultColor
                    }
                }
            }

            onClicked: {
                root.currentIndex = index
                selectedItemsCount.text = "1 item selected"

                let size = controller.getFileSize(path)
                if (size.length) {
                    selectedItemSize.text = size
                }
            }

            onDoubleClicked: {
                root.resetSelectedIndex()
                statusBar.clear()
                controller.open(path)
            }
        }
    }

    onCurrentIndexChanged: {
        clearSelections()
        selectItem(currentIndex)
    }

    Keys.onPressed: (event)=> {
        console.log("key pressed")
        if (event.key === Qt.Key_Left) {
            console.log("move left");
        }

        event.accepted = true;
    }

    Component.onCompleted: currentIndex = root.rDefaultIndex
}
