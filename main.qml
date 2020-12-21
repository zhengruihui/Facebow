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
    property int rightBarWidth: 50
    property var menuBarColor: "#1f2026"
    property int currentPage: 1
    property int currentButton: 1
    property bool normalWindow: true


    id: mainWindow
//    width: 1366
//    height: 768
    width: 1400
    height: 800
    visible: true
    color: menuBarColor


    flags: Qt.Window | Qt.FramelessWindowHint

    function changePage(page)
    {
        if(page === currentPage)
        {

        }
        else if(page === 1)
        {
            information.visible = true
            measure.visible = false
            track.visible = false
            report.visible = false
            help.visible = false
        }
        else if(page === 2)
        {
            information.visible = false
            measure.visible = true
            track.visible = false
            report.visible = false
            help.visible = false
        }
        else if(page === 3)
        {
            information.visible = false
            measure.visible = false
            track.visible = true
            report.visible = false
            help.visible = false
        }
        else if(page === 4)
        {
            information.visible = false
            measure.visible = false
            track.visible = false
            report.visible = true
            help.visible = false
        }
        else if(page === 5)
        {
            information.visible = false
            measure.visible = false
            track.visible = false
            report.visible = false
            help.visible = true
        }

        currentPage = page
    }


    Rectangle {
        id:topBar
        anchors.top: parent.top
        width: parent.width
        height: topBarHeight
        color: menuBarColor


        MouseArea {
            anchors.fill: parent
            acceptedButtons: Qt.LeftButton
            property point clickPos: "0,0"
            onPressed: {
                clickPos = Qt.point(mouse.x, mouse.y)
            }


            onPositionChanged: {
                //鼠标偏移量
                var delta = Qt.point(mouse.x - clickPos.x, mouse.y - clickPos.y)


                //如果mainwindow继承自QWidget,用setPos
                mainWindow.setX(mainWindow.x + delta.x)
                mainWindow.setY(mainWindow.y + delta.y)
            }
        }

        Row{
            anchors.top: parent.top
            anchors.left: parent.left
            width: parent.width
            height: topBarHeight
            leftPadding: 81


            Text {
                anchors.verticalCenter: parent.verticalCenter
                text: qsTr("ECIDME")
                color: "#DEDEDE"
                width: parent.width
                wrapMode: Text.WordWrap
                font.family: "Dubai Medium" // Dubai Medium // Arial Black
                font.pixelSize: 36
                font.bold: true

             }



        }


        Row {
            anchors.top: parent.top
            anchors.left: parent.left
            width: parent.width
            height: topBarHeight
            leftPadding: parent.width-180

            spacing: 0

            MButton{
                width: 42
                height: 30
                haveText: false
                anchors.verticalCenter: parent.verticalCenter

                normalImagelUrl: "Resources/assets/menubar/min.png"
                pressedImageUrl: "Resources/assets/menubar/min_sel.png"
                hover:true
                onClicked: {
                    mainWindow.showMinimized()
                    currentButton = 1
                }

            }

            MButton{
                width: 42
                height: 30
                haveText: false
                anchors.verticalCenter: parent.verticalCenter

                normalImagelUrl: "Resources/assets/menubar/max.png"
                pressedImageUrl: "Resources/assets/menubar/max_sel.png"
                hover:true
                highlighted: !normalWindow
                onClicked: {
                    if(normalWindow)
                    {
                        //mainWindow.showFullScreen()
                        mainWindow.showMaximized()
                        currentButton = 2
                        normalWindow = false
                    }
                    else{
                        mainWindow.showNormal()
                        normalWindow = true
                    }

                }

            }

            MButton{
                width: 42
                height: 30
                haveText: false
                anchors.verticalCenter: parent.verticalCenter

                normalImagelUrl: "Resources/assets/menubar/close.png"
                pressedImageUrl: "Resources/assets/menubar/close_sel.png"
                hover:true
                onClicked: {
                    mainWindow.close()
                    currentButton = 3
                }

            }





        }






    }




    Rectangle{
        id:bottomBar
        anchors.bottom: parent.bottom
        anchors.left: parent.left
        anchors.right: parent.right

        height:bottomBarHeight
        color: menuBarColor

    }



    Rectangle{
        id:leftBar
        anchors.top: parent.top
        anchors.left: parent.left
        width: leftBarWidth
        height: parent.height
        color: menuBarColor



        Column {         
            id: columnButton1
            anchors.top: parent.top
            width: parent.width
            height: parent.height
            topPadding: 127


            spacing: 11
            padding: 10



            MButton{
                width: 80
                height: 60
                anchors.horizontalCenter: parent.horizontalCenter

                normalImagelUrl: "Resources/assets/navigation/information.png"
                pressedImageUrl: "Resources/assets/navigation/information_sel.png"
                text: qsTr("Information")
                normalTextColor: "#DEDEDE"
                pressedTextColor: "#0DAF9D"              
                hover:true

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
                text: qsTr("Measure")
                normalTextColor: "#DEDEDE"
                pressedTextColor: "#0DAF9D"
                hover:true
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
                text: qsTr("Track")
                normalTextColor: "#DEDEDE"
                pressedTextColor: "#0DAF9D"
                hover:true
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
                text: qsTr("Report")
                normalTextColor: "#DEDEDE"
                pressedTextColor: "#0DAF9D"
                hover:true
                highlighted: currentPage == 4
                onClicked: {
                    changePage(4)
                }

            }

        }
        Column{
            id: columnButton2
            anchors.top: parent.top
            anchors.left: parent.left
            width: leftBarWidth
            height: parent.height
            topPadding: parent.height-90

            MButton{
                width: 80
                height: 60
                anchors.horizontalCenter: parent.horizontalCenter
                normalImagelUrl: "Resources/assets/navigation/help.png"
                pressedImageUrl: "Resources/assets/navigation/help_sel.png"
                text: qsTr("Help")
                normalTextColor: "#DEDEDE"
                pressedTextColor: "#0DAF9D"
                hover:true
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
        color: menuBarColor
    }





    Information{
        id:information
        anchors.top: topBar.bottom
        anchors.bottom: bottomBar.top
        anchors.left: leftBar.right
        anchors.right: rightBar.left
        visible: true
    }


    Measure{
        id:measure
        anchors.top: topBar.bottom
        anchors.bottom: bottomBar.top
        anchors.left: leftBar.right
        anchors.right: rightBar.left
        visible: false
    }

    Track{
        id:track
        anchors.top: topBar.bottom
        anchors.bottom: bottomBar.top
        anchors.left: leftBar.right
        anchors.right: rightBar.left
        visible: false
    }



    Report{
        id:report
        anchors.top: topBar.bottom
        anchors.bottom: bottomBar.top
        anchors.left: leftBar.right
        anchors.right: rightBar.left
        visible: false
    }

    Help{
        id:help
        anchors.top: topBar.bottom
        anchors.bottom: bottomBar.top
        anchors.left: leftBar.right
        anchors.right: rightBar.left
        visible: false
    }





}
