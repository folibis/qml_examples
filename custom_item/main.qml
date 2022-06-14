import QtQuick
import QtQuick.Window
import CustomItems

Window {
    id: window
    visible: true
    height: 400
    width: 400

    Rectangle {
        id: bg
        width: 300
        height: 300
        color: "orange"
        anchors.centerIn: parent
        SequentialAnimation {
            running: true
            loops: Animation.Infinite
            PropertyAnimation { target: bg; property: "color"; to: "yellow"; duration: 2000 }
            PropertyAnimation { target: bg; property: "color"; to: "orange"; duration: 2000 }
        }

        CustomItem {
            id: item
            width: 200
            height: 200
            anchors.centerIn: parent
            SequentialAnimation {
                running: true
                loops: Animation.Infinite
                PropertyAnimation { target: item; property: "rotation"; to: 360; duration: 5000 }
                PropertyAnimation { target: item; property: "rotation"; to: 0; duration: 5000 }
            }
        }
    }


}
