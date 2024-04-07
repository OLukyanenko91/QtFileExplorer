import QtQuick
import QtQuick.Controls


Button {
    // PROPERTIES

    property string pText:    ""
    property bool   pEnabled: false

    // DATA

    implicitHeight: 35
    text: pText
    font.pointSize: 8
    font.bold: true
    enabled: pEnabled
}
