import QtQuick 2.15
import QtQuick.Window 2.14
import QtQuick3D 1.15
import QtQuick.Controls 2.14
import SerialPort 1.0


Window {
    property int menuBarHeight: 0


    id: mainWindow
    width: 1280
    height: 720
    visible: true
    color: "black"




    Page1{
        id:page1
        anchors.fill: parent
        visible: true
        opacity: 1
    }

    Page2{
        id:page2
        anchors.fill: parent
        visible: false
        opacity: 0
    }





    Rectangle{
        anchors.top: parent.top
        anchors.left: parent.left
        width: 60
        height: parent.height


        Column {
            id: controlsContainerx
            anchors.top: parent.top
            anchors.left: parent.left
            anchors.centerIn: parent

            spacing: 10
            padding: 10

            RoundButton {
                text: qsTr("Page1")
                onClicked: {
                    page2.visible = false
                    page2.opacity = 0
                    page1.visible = true
                    page1.opacity = 1
                }
            }

            RoundButton {
                text: qsTr("Page2")
                onClicked: {
                    page1.visible = false
                    page1.opacity = 0
                    page2.visible = true
                    page2.opacity = 1
                }
            }

        }


    }


//    flags: Qt.Window | Qt.FramelessWindowHint

//    MenuBar{
//        id: menuBar
//        anchors.top: parent.top
//        anchors.left: parent.left
//        anchors.right: parent.right
//        height: menuBarHeight
//    }



}
