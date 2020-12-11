import QtQuick 2.0
import QtQuick.Controls 2.14

Item {

    property var barColor : "#1f2026"
    Rectangle {
        anchors.top: parent.top
        width: parent.width
        height: parent.height
        color: barColor

//        Label{
//            anchors.left: parent.left
//            anchors.verticalCenter: parent.verticalCenter
//            text: qsTr("Facebow")
//        }


        Row {
            anchors.top: parent.top
            width: 155
            height: parent.height


            spacing: 10.2




            MButton{
                width: 21.4
                height: 21.4
                haveText: false
                anchors.verticalCenter: parent.verticalCenter

                normalImagelUrl: "Resources/assets/menubar/min.png"
                pressedImageUrl: "Resources/assets/menubar/min_sel.png"


                onClicked: {

                }

            }





        }






        MouseArea {
            anchors.fill: parent
            acceptedButtons: Qt.LeftButton
            property point clickPos: "0,0"
            onPressed: {
                clickPos = Qt.point(mouse.x, mouse.y)
                console.log(onPressed)
            }


            onPositionChanged: {
                //鼠标偏移量
                var delta = Qt.point(mouse.x - clickPos.x, mouse.y - clickPos.y)


                //如果mainwindow继承自QWidget,用setPos
                mainWindow.setX(mainWindow.x + delta.x)
                mainWindow.setY(mainWindow.y + delta.y)
            }
        }
    }




}
