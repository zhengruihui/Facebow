import QtQuick 2.9
import QtQuick.Window 2.14
import QtQuick3D 1.15
import QtQuick.Controls 2.5
import QtQuick.Controls.Styles 1.4
import SerialPort 1.0

Window {
    property int topBarHeight: 70

    property int bottomBarHeight: 15

    property int leftBarWidth: 80

    property int rightBarWidth: 30

    property var barColor: "#1f2026"

    property int currentPage: 1

    function changePage(page)
    {
        if(page === currentPage)
        {

        }
        else if(page === 1)
        {
            mainLoader.source = "Information.qml"
            currentPage = 1
        }
        else if(page === 2)
        {
            mainLoader.source = "Measure.qml"
            currentPage = 2
        }
        else if(page === 3)
        {
            mainLoader.source = "Track.qml"
            currentPage = 3
        }
        else if(page === 4)
        {
            mainLoader.source = "Report.qml"
            currentPage = 4
        }
        else
        {
            mainLoader.source = "Help.qml"
            currentPage = 5
        }



    }


    id: mainWindow
    width: 1280
    height: 720
    visible: true
    color: barColor


    //flags: Qt.Window | Qt.FramelessWindowHint

    Rectangle{
        id:topBar
        anchors.top: parent.top
        anchors.left: parent.left
        anchors.right: parent.right
        height:topBarHeight
        color: barColor

    }

    Rectangle{
        id:bottomBar
        anchors.bottom: parent.bottom
        anchors.left: parent.left
        anchors.right: parent.right

        height:bottomBarHeight
        color: barColor

    }

    Rectangle{
        id:leftBar
        anchors.left: parent.left
        anchors.verticalCenter: parent.verticalCenter
        width: leftBarWidth
        height: parent.height
        color: barColor



        Column {         
            id: columnButton1
            anchors.top: parent.top
            width: parent.width
            height: parent.height
            topPadding: 127

            //anchors.top: parent.top
            //anchors.left: parent.left
//            anchors.verticalCenter: parent.verticalCenter
//            width: parent.width
            //height: parent.height

            spacing: 11
            padding: 10



            MButton{
                width: 80
                height: 60
                anchors.horizontalCenter: parent.horizontalCenter

                normalImagelUrl: "Resources/assets/navigation/information.png"
                pressedImageUrl: "Resources/assets/navigation/information_sel.png"
                text: "Information"
                normalTextColor: "#DEDEDE"
                pressedTextColor: "#0DAF9D"

                highlighted: currentPage == 1
                onClicked: {
                    changePage(1)
                }

            }

            MButton{
                width: 80
                height: 60
                anchors.horizontalCenter: parent.horizontalCenter
                normalImagelUrl: "Resources/assets/navigation/measure.png"
                pressedImageUrl: "Resources/assets/navigation/measure_sel.png"
                text: "Measure"
                normalTextColor: "#DEDEDE"
                pressedTextColor: "#0DAF9D"

                highlighted: currentPage == 2
                onClicked: {
                    changePage(2)
                }

            }

            MButton{
                width: 80
                height: 60
                anchors.horizontalCenter: parent.horizontalCenter
                normalImagelUrl: "Resources/assets/navigation/track.png"
                pressedImageUrl: "Resources/assets/navigation/track_sel.png"
                text: "Track"
                normalTextColor: "#DEDEDE"
                pressedTextColor: "#0DAF9D"

                highlighted: currentPage == 3
                onClicked: {
                    changePage(3)
                }

            }

            MButton{
                width: 80
                height: 60
                anchors.horizontalCenter: parent.horizontalCenter
                normalImagelUrl: "Resources/assets/navigation/report.png"
                pressedImageUrl: "Resources/assets/navigation/report_sel.png"
                text: "Report"
                normalTextColor: "#DEDEDE"
                pressedTextColor: "#0DAF9D"

                highlighted: currentPage == 4
                onClicked: {
                    changePage(4)
                }

            }

        }
        Column{
            id: columnButton2
            anchors.bottom: parent.bottom
            width: parent.width
            height: parent.height


            bottomPadding: 20
            MButton{
                width: 80
                height: 60
                anchors.bottom: parent.bottom
                anchors.horizontalCenter: parent.horizontalCenter
                normalImagelUrl: "Resources/assets/navigation/help.png"
                pressedImageUrl: "Resources/assets/navigation/help_sel.png"
                text: "Help"
                textItem.verticalAlignment: Text.AlignTop
                normalTextColor: "#DEDEDE"
                pressedTextColor: "#0DAF9D"
                highlighted: currentPage == 5
                onClicked: {
                    changePage(5)
                }


            }

        }
    }

    Rectangle{
        id:rightBar
        anchors.top: parent.top
        anchors.right: parent.right
        width: rightBarWidth
        height: parent.height
        color: barColor
    }



    Loader{
        id: mainLoader
        anchors.top: topBar.bottom
        anchors.bottom: bottomBar.top
        anchors.left: leftBar.right
        anchors.right: rightBar.left

        source: "Measure.qml"

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
