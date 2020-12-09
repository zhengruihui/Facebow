import QtQuick 2.15
import QtQuick.Window 2.14
import QtQuick3D 1.15
import QtQuick.Controls 2.5
import SerialPort 1.0
import QtQuick.Controls.Styles 1.4

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
        else{
            if(page === 1)
            {
                mainLoader.source = "MeasuringSteps.qml"
                currentPage = 1
            }
            else if(page === 2)
            {
                mainLoader.source = "Report.qml"
                currentPage = 2
            }

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
        anchors.top: parent.top
        anchors.left: parent.left
        width: leftBarWidth
        height: parent.height
        color: barColor

        Column {
            id: controlsContainer
            anchors.top: parent.top
            anchors.left: parent.left
            anchors.centerIn: parent
            width: parent.width

            spacing: 20
            padding: 10

            IconButton {
                id: btn_camera
                img_src: "qrc:/camera.png";
                btn_txt: "相机"
                onClickedLeft: setInfoText(btn_txt + " Left Button click")
                onClickedRight: setInfoText(btn_txt + " Right Button click")
            }



            Button {

                anchors.horizontalCenter: parent.horizontalCenter


                background: Image{
                    id:backgroundMeasure
                    source: "Resources/assets/navigation/view.png"
                }



                Text{
                    text: qsTr("Measure")
                    anchors.top: backgroundMeasure.bottom
                    anchors.horizontalCenter: parent.horizontalCenter


                }


//                style: ButtonStyle {
//                    background: Rectangle {
//                        color: control.hovered?"#a0a0a0":"#c0c0c0";
//                        border.width: control.pressed?2:1;
//                        border.color: "white";
//                    }
//                    label: Label {
//                        text: control.text; // 设置label样式后，按钮显示以此text为准
//                        color: "black";
//                        font.pixelSize: 24;
//                        font.bold: true;
//                    }
//                }



                highlighted: currentPage == 1
                onClicked: {
                    backgroundMeasure.source = "Resources/assets/navigation/view_sel.png"
                    mainLoader.source = "MeasuringSteps.qml"
                    changePage(1)

                }
            }

            Button {
                anchors.horizontalCenter: parent.horizontalCenter
                Text{
                    text: qsTr("Report")
                    anchors.centerIn: parent

                }

                highlighted: currentPage == 2
                onClicked: {
                    mainLoader.source = "Report.qml"
                    changePage(2)
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





        source: "MeasuringSteps.qml"

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
