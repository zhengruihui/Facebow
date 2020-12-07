import QtQuick 2.0

Item {

    property int menuBarHeight: 0
    Skull{
        anchors.bottom: parent.bottom
        anchors.left: parent.left
        width: parent.width*0.5
        height: parent.height-menuBarHeight

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
            width: parent.width
            source: "Resources/Image/Person2.jpg"
        }

    }


}
