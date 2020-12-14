import QtQuick 2.15
import QtQuick3D 1.15
import QtQuick.Controls 2.14
import SerialPort 1.0
import QtGraphicalEffects 1.15

Item {
    property int topBarHeight: 40

    property int bottomBarHeight: 100

    property int leftBarWidth: 40

    property int rightBarWidth: 130

    property int centerBarWidth: 10

    property var barColor: "#1f2026"

    property int borderWidth: 4



    property var zoomFactor: 7
    property int buttonSkullHeight: 80
    property int zoomFactorMax: 10
    property int zoomFactorMin: 2
    property int lightBrightness: 70
    property int yOffset: -15

    property int currentButtonID : 0




    Rectangle {
        id: rootRectangle
        anchors.top: parent.top
        anchors.left: parent.left
        width: parent.width
        height: parent.height

        color: "#1f2026"
        border.width: borderWidth;
        border.color: "transparent";
        radius: 6




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
            width: rightBarWidth
            height: parent.height-2*borderWidth
            color: barColor
        }



        Rectangle{
            anchors.top: topBar.bottom
            anchors.left: leftBar.right
            width: (parent.width-leftBarWidth-rightBarWidth-centerBarWidth)/2
            height: parent.height-topBarHeight-bottomBarHeight
            color: "black"
        }

        Rectangle{

            anchors.top: topBar.bottom
            anchors.right: rightBar.left
            width: (parent.width-leftBarWidth-rightBarWidth-centerBarWidth)/2
            height: parent.height-topBarHeight-bottomBarHeight
            color: "black"



        }





    }












    DropShadow {
        anchors.fill: rootRectangle
        transparentBorder: true
        horizontalOffset: -10
        verticalOffset: 8
        radius: 30
        samples: 61
        color: "#80000000"
        spread: 0.1
        source: rootRectangle
    }
    DropShadow {
        anchors.fill: rootRectangle
        transparentBorder: true
        horizontalOffset: 5
        verticalOffset: -5
        radius: 30
        samples: 61
        color: "#80000000"
        spread: 0.1
        source: rootRectangle
    }


}
