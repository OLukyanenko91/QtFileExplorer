import QtQuick
import QtQuick.Window
import QtQuick.Layouts
import QtQuick.Controls
import CustomData


ListView {
    // PROPERTIES

    readonly property string rSelectedColor:    "#cce7fe"
    readonly property string rHighlightedColor: "#e4f3fe"
    readonly property string rDefaultColor:     "#ffffff"
    readonly property int    rDefaultIndex:     -1

    property var pSelectedIndexesList: []
    property var pModel:               ({})

    // FUNCTIONS

    function clearSelections() {
        for (let index = 0; index < count; index++) {
            pModel.updateItemSelection(index, false, false)

            let viewItem = root.itemAtIndex(index)
            if (viewItem) {
                viewItem.updateColor()
            }
        }

        pSelectedIndexesList = []
    }

    function selectItem(index: int) {
        pModel.updateItemSelection(index, true, false)

        let viewItem = root.itemAtIndex(index)
        if (viewItem) {
            viewItem.updateColor()
        }
    }

    function unselectItem(index: int) {
        pModel.updateItemSelection(index, false, true)

        let viewItem = root.itemAtIndex(index)
        if (viewItem) {
            viewItem.updateColor()
        }
    }

    function updateSelectedIndexesList() {
        var selectedIndexes = []

        for (let index = 0; index < count; index++) {
            if (pModel.itemSelected(index)) {
                selectedIndexes.push(index)
            }
        }

        pSelectedIndexesList = selectedIndexes
    }

    function getSelectedFiles() {
        var selectedFiles = []

        for(let index in pSelectedIndexesList) {
            var item = pModel.get(pSelectedIndexesList[index])
            if (item) {
                selectedFiles.push(item.path)
            }
        }

        return selectedFiles
    }

    // DATA

    id: root
    Layout.fillHeight: parent
    Layout.fillWidth: parent
    model: pModel
    focus: true
    clip: true
    spacing: 1
    boundsBehavior: Flickable.StopAtBounds
    ScrollBar.vertical: ScrollBar {
        policy: ScrollBar.AlwaysOn
    }

    delegate: Rectangle {
         // FUNCTIONS

        function updateColor() {
            viewDelegate.color = selected ? root.rSelectedColor :
                                 highlighted ? root.rHighlightedColor : root.rDefaultColor
        }

        // DATA

        id: viewDelegate
        height: 25
        width: parent ? parent.width : 0

        RowLayout {
            // Roles
            //   name        - file name
            //   path        - file path
            //   type        - file type (file, folder, driver)
            //   selected    - is selected (true/false)
            //   highlighted - is focused (true/false)

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
                text: type === ItemInfo.DRIVER ? "Local Disk (" + name + ")" : name
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
                if (!pModel.itemSelected(index)) {
                    pModel.updateItemSelection(index, false, true)
                    updateColor()
                }
            }

            onExited: {
                if (!pModel.itemSelected(index)) {
                    pModel.updateItemSelection(index, false, false)
                    updateColor()
                }
            }

            onClicked: (mouse)=> {
                if (mouse.modifiers & Qt.ControlModifier) {
                    if (pModel.itemSelected(index)) {
                        unselectItem(index)
                    }
                    else {
                        selectItem(index)
                    }
                }
                else {
                    clearSelections()
                    selectItem(index)
                }

                updateSelectedIndexesList()
            }

            onDoubleClicked: {
                statusBar.clear()
                controller.open(path)
            }
        }

        Component.onCompleted: updateColor()
    }

    onCurrentIndexChanged: {
        clearSelections()
        selectItem(currentIndex)
    }

    Keys.onPressed: (event)=> {
//        console.log("key pressed")
//        if (event.key === Qt.Key_Left) {
//            console.log("move left");
//        }

        event.accepted = true;
    }

    Component.onCompleted: currentIndex = root.rDefaultIndex
}
