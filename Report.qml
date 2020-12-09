import QtQuick 2.15
import QtQuick3D 1.15
import QtQuick.Controls 2.14
import SerialPort 1.0
import QtGraphicalEffects 1.15

Item {
    property int topBarHeight: 20

    property int bottomBarHeight: 40

    property int leftBarWidth: 20

    property int rightBarWidth: 40

    property var barColor: "#1f2026"

    property int borderWidth: 4


    anchors.fill: parent

    Rectangle {
        id: rootRectangle
        anchors.top: parent.top
        anchors.left: parent.left
        width: parent.width
        height: parent.height

        color: "#1f2026"
        border.width: borderWidth;
        border.color: "transparent";
        radius: 6//圆角半径




        Rectangle{
            id:topBar
            anchors.top: parent.top
            anchors.horizontalCenter: parent.horizontalCenter
            width: parent.width-2*borderWidth
            height:topBarHeight
            color: barColor


        }

        Rectangle{
            id:bottomBar
            anchors.bottom: parent.bottom
            anchors.horizontalCenter: parent.horizontalCenter
            width: parent.width-2*borderWidth
            height:bottomBarHeight
            color: barColor

        }



        Rectangle{
            id:leftBar
            anchors.left: parent.left
            anchors.verticalCenter: parent.verticalCenter
            width: leftBarWidth
            height: parent.height-2*borderWidth
            color: barColor

        }

        Rectangle{
            id:rightBar
            anchors.right: parent.right
            anchors.verticalCenter: parent.verticalCenter
            width: leftBarWidth
            height: parent.height-2*borderWidth
            color: barColor
        }










    }












    DropShadow {
        anchors.fill: rootRectangle
        transparentBorder: true
        horizontalOffset: -15
        verticalOffset: 15
        radius: 20
        samples: 41
        color: "#80000000"
        spread: 0.1
        source: rootRectangle
    }
    DropShadow {
        anchors.fill: rootRectangle
        transparentBorder: true
        horizontalOffset: 5
        verticalOffset: -5
        radius: 20.0
        samples: 41
        color: "#80000000"
        spread: 0.1
        source: rootRectangle
    }



}
