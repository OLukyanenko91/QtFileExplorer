import QtQuick
import QtQuick.Controls


Button {
    // PROPERTIES

    property string pText: ""

    // DATA

    implicitHeight: 35
    text: pText
    font.pointSize: 8
    font.bold: true
}
