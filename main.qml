import QtQuick 2.15
import QtQuick.Window 2.14
import QtQuick3D 1.15
import QtQuick.Controls 2.14
import SerialPort 1.0

Window {
    id: window
    width: 1280
    height: 720
    visible: true
    title: "Facebow"

    Skull{
        anchors.top: parent.top
        anchors.left: parent.left
        width: parent.width*0.5
        height: parent.height

    }

    Rectangle{
        anchors.top: parent.top
        anchors.right: parent.right
        height: parent.height
        width: parent.width*0.5
        Image {
            id: person
            anchors.top: parent.top
            anchors.right: parent.right
            height: parent.height
            source: "Resources/Image/Person.jpg"
        }


    }

}
