import QtQuick 2.15
import QtQuick3D 1.15
import QtQuick.Controls 2.14
import SerialPort 1.0
import QtGraphicalEffects 1.15
import Patient 1.0


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

    property int frontSize: 14




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

            anchors.centerIn: parent
            width: parent.width-40
            height: parent.height-90
            color: "#FFFFFF"
            radius: 6

            Rectangle{
                id:searchRectangle
                anchors.top: parent.top
                anchors.left: parent.left
                width: 303
                height: parent.height
                border.width: borderWidth;
                border.color: "transparent";
                color: "#FFFFFF"
                radius: 6

                Rectangle{
                    anchors.top: parent.top
                    anchors.horizontalCenter: parent.horizontalCenter
                    anchors.topMargin: 10
                    width: parent.width - 37
                    height: 36


                    Image {
                        id: searchImage
                        anchors.left: parent.left
                        anchors.verticalCenter: parent.verticalCenter
                        anchors.rightMargin: 10
                        source: "Resources/Patient/search.png"
                    }


                    TextField {
                        id: inputField
                        placeholderText: qsTr("输入姓名")
                        anchors.top: parent.top
                        anchors.horizontalCenter: parent.horizontalCenter
                       // anchors.topMargin: 10
                        width: parent.width - 30
                        height: parent.height

                        selectByMouse: true
                        font.pointSize: 11



                        background: Rectangle {
                            width: parent.width
                            height: parent.height
                            anchors.bottom: parent.bottom
                            color: "transparent"
                            border.color: "transparent"

                            }


                        property bool editing: false

                        onTextEdited: editing = true;
                        onEditingFinished: editing = false;
                        onTextChanged: {

                            console.log(inputField.text)
                        }
                    }



                    Image {
                        id: addImage
                        anchors.right: parent.right
                        anchors.verticalCenter: parent.verticalCenter
                        source: "Resources/Patient/add.png"
                    }

                    Rectangle{
                        anchors.right: addImage.left
                        anchors.verticalCenter: parent.verticalCenter
                        width: 1
                        height: addImage.height
                        color: "transparent"
                        border.color: "#DDE2E7"

                    }

                    Rectangle{
                        anchors.bottom: parent.bottom

                        width: parent.width
                        height: 1
                        color: "transparent"
                        border.color: "#DDE2E7"

                    }


                }





            }

            //第一行
            Rectangle{
                x: 343
                y: 24
                width: parent.width - 380
                height: 24
                color: "transparent"

                Image {
                    x: 0
                    anchors.verticalCenter: parent.verticalCenter
                    source: "Resources/Patient/patient_details.png"
                }


                Text {
                    text: qsTr("患者详情")
                    x: 28
                    anchors.verticalCenter: parent.verticalCenter
                    color: "#0DAF9D"
                    font.pixelSize: frontSize
                }
                Text {
                    text: qsTr("编辑")
                    anchors.right: parent.right
                    anchors.verticalCenter: parent.verticalCenter
                    anchors.rightMargin: 16
                    color: "#0DAF9D"
                    font.pixelSize: frontSize

                    MouseArea{
                        anchors.fill: parent
                        onPressed: {
                            editDialog.visible = true
                            //dialogShadow.visible = true
                            //rootRectangle.opacity = 0.8

                            //rootRectangleDropShadow.opacity = 0.8
                        }

                    }
                }



            }




            Rectangle{
                x: 343
                y: 59
                width: parent.width - 380
                height: 53
                color: "transparent"
                border.color: "#DDE2E7"
                radius: 5



                Text {
                    id:idText
                    text: qsTr("ID: A34543")
                    x: 14
                    anchors.verticalCenter: parent.verticalCenter
                    font.pixelSize: frontSize
                    font.family: "SourceHanSansCN-Regular"
                    color: "#323C47"
                }

                Text {
                    id:idName
                    text: qsTr("姓名: 陈同学")
                    x: parent.width/4
                    anchors.verticalCenter: parent.verticalCenter
                    font.pixelSize: frontSize
                    font.family: "SourceHanSansCN-Regular"
                    color: "#323C47"
                }

                Text {
                    id: idSex
                    text: qsTr("性别: 女")
                    x: parent.width/4*2
                    anchors.verticalCenter: parent.verticalCenter
                    font.pixelSize: frontSize
                    font.family: "SourceHanSansCN-Regular"
                    color: "#323C47"
                }

                Text {
                    id:idBirthday
                    text: qsTr("出生年月: 1974-11-14")
                    x: parent.width/4*3
                    anchors.verticalCenter: parent.verticalCenter
                    font.pixelSize: frontSize
                    font.family: "SourceHanSansCN-Regular"
                    color: "#323C47"
                }

            }



            //第二行
            Image {
                x: 343
                y: 152
                source: "Resources/Patient/report.png"
            }
            Text {
                text: qsTr("报告")
                x: 372
                y: 158
                color: "#0DAF9D"
                font.pixelSize: frontSize
            }

            Rectangle{
                x: 343
                y: 189
                width: 178
                height: 152
                color: "transparent"
                border.color: "#DDE2E7"
                radius: 5


                Image {
                    anchors.centerIn: parent
                    source: "Resources/Patient/PDF.png"
                }
            }

            Rectangle{
                x: 553
                y: 189
                width: 178
                height: 152
                color: "transparent"
                border.color: "#DDE2E7"
                radius: 5


                Image {
                    anchors.centerIn: parent
                    source: "Resources/Patient/PDF.png"
                }
            }



            //第三行
            Rectangle{
                x: 343
                y: 383.5
                width: parent.width - 380
                height: 24
                color: "transparent"

                Image {
                    x: 0
                    anchors.verticalCenter: parent.verticalCenter
                    source: "Resources/Patient/diagnose.png"
                }


                Text {
                    text: qsTr("诊断信息")
                    x: 28
                    anchors.verticalCenter: parent.verticalCenter
                    color: "#0DAF9D"
                    font.pixelSize: frontSize
                }
                Text {
                    text: qsTr("编辑")
                    anchors.right: parent.right
                    anchors.verticalCenter: parent.verticalCenter
                    anchors.rightMargin: 16
                    color: "#0DAF9D"
                    font.pixelSize: frontSize

                    MouseArea{
                        anchors.fill: parent
                        onPressed: {

                        }

                    }
                }



            }



                TextField {
                    placeholderText: qsTr("输入诊断信息")
                    x: 343
                    y: 416.5

                    width: parent.width - 380
                    height: parent.height - 483

                    selectByMouse: true
                    font.pointSize: frontSize

                    background: Rectangle {
                        anchors.centerIn: parent
                        width: parent.width
                        height: parent.height

                        color: "transparent"
                        border.color: "#DDE2E7"
                        radius: 5

                        }





                }

                MDialog{
                    id: editDialog
                    width: 560
                    height: 491
                    anchors.centerIn: parent
                    visible: false


                }

















            DropShadow {
                id:searchRectangleDropShadow
                anchors.fill: searchRectangle
                transparentBorder: true
                horizontalOffset: 1
                verticalOffset: 0
                radius: 30
                samples: 61
                color: "#aa000000"
                spread: 0.0
                source: searchRectangle
            }
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
        id:rootRectangleDropShadow
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
