import QtQuick
import QtQuick.Controls

Label {
    // PROPERTY

    property string pText:    ""
    property string pTipText: ""
    property string pColor:   "black"

    // FUNCTIONS
    function setText(text: string, tip: string) {
        if (text) {
            pText = text
            pTipText = tip
        }
        else {
            pText = tip
            pTipText = ""
        }
    }

    function clear() {
        pText = ""
        pTipText = ""
    }

    // DATA

    text: pText
    color: pColor
    ToolTip.text: pTipText
    ToolTip.visible: pTipText ? mouseArea.containsMouse : false

    MouseArea {
        id: mouseArea
        anchors.fill: parent
        hoverEnabled: true
    }
}
