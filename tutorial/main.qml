import QtQuick 2.9
import QtQuick.Window 2.2

Window {
    visible: true
    width: 640
    height: 480
    title: qsTr("Hello World")

    TextInput {
        id: textInput
        x: 311
        y: 88
        width: 80
        height: 20
        text: qsTr("Text Input")
        font.pixelSize: 12
    }
}
