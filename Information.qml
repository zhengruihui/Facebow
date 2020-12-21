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
                    id:infoRectangle
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
                        MouseArea{
                            anchors.fill: parent
                            onPressed: {
                                patientInfo.append({"name": "王五", "sex":"男", "age": "5岁"})
                                console.log(infoListView.height)

                            }


                        }
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


                ListModel{
                     id: patientInfo
                     ListElement {
                         name: "张三"
                         sex: "男"
                         age: "45岁"
                     }
                     ListElement {
                         name: "李四"
                         sex: "男"
                         age: "65岁"
                     }




                }


                ListView {
                    id: infoListView
                    anchors.top: infoRectangle.bottom
                    anchors.topMargin: 10
                    width: parent.width
                    height: parent.height - 100
                    model: patientInfo
                    spacing: 10






                    delegate: Column {
                        x: 20
                        //anchors.horizontalCenter: parent.horizontalCenter
                        Rectangle{
                            id: currentPatient
                            width: 265
                            height: 50
                            border.width: 1
                            border.color: "#E9EFF4"
                            color: "#FFFFFF"
                            radius: 5

                            Image {
                                x: 14
                                anchors.verticalCenter: parent.verticalCenter
                                source: "Resources/Patient/patient.png"
                            }
                            Text {
                                x: 52
                                anchors.verticalCenter: parent.verticalCenter
                                text: name
                            }
                            Text {
                                x: 149.5
                                anchors.verticalCenter: parent.verticalCenter
                                text: sex
                            }
                            Text {
                                x: 184
                                anchors.verticalCenter: parent.verticalCenter
                                text: age
                            }

                            Column{
                                id: infoEdit
                                x: 238.7
                                anchors.verticalCenter: parent.verticalCenter
                                width: 16
                                height: 18.9
                                spacing: 4
                                Rectangle{
                                    anchors.horizontalCenter: parent.horizontalCenter
                                    width: 4
                                    height: 4
                                    radius: 2
                                    color: "#DDE2E7"
                                }
                                Rectangle{
                                    anchors.horizontalCenter: parent.horizontalCenter
                                    width: 4
                                    height: 4
                                    radius: 2
                                    color: "#DDE2E7"
                                }
                                Rectangle{
                                    anchors.horizontalCenter: parent.horizontalCenter
                                    width: 4
                                    height: 4
                                    radius: 2
                                    color: "#DDE2E7"
                                }


                            }
                            MouseArea{
                                anchors.fill: parent
                                onPressed: {
                                    currentPatient.color = "#0DAF9D"
                                    console.log("listelement: ", index)

                                }


                            }
                            MouseArea{
                                anchors.fill: infoEdit
                                onPressed: {
                                    console.log("edit info")
                                }

                            }

                        }
                    }


                    ScrollBar.vertical: ScrollBar {
                        height: infoListView.height
                        active: true
                    }

                    onCurrentIndexChanged: {
                                console.log("current index = ",currentIndex)
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
                            //editDialog.visible = true
                            //dialogShadow.visible = true
                            //rootRectangle.opacity = 0.8

                            //rootRectangleDropShadow.opacity = 0.8
                            editDialog.open()
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



                Popup {
                    id: editDialog
                    width: 560
                    height: 491
                    anchors.centerIn: parent
                    topPadding: 0
                    bottomPadding: 0
                    leftPadding: 0
                    rightPadding: 0


                    focus: true

                    closePolicy: Popup.NoAutoClose

                    enter: Transition {
                        NumberAnimation { property: "opacity"; from: 0.0; to: 1.0 }
                    }
                    exit: Transition {
                        NumberAnimation { property: "opacity"; from: 1.0; to: 0.0 }
                    }



                    background: Rectangle {
                        anchors.centerIn: parent
                        width: parent.width
                        height: parent.height



                        color: "white"
                        border.width: 1
                        border.color: "#DDE2E7"
                        radius: 5

                        }

                    Rectangle{
                        anchors.top: parent.top
                        width: parent.width
                        height: 7
                        color: "#0DAF9D"


                    }

                    //start-ID
                    Rectangle{
                        anchors.left: parent.left
                        y: 82
                        width: parent.width
                        height: 50
                        color: "transparent"

                        Text {
                            text: qsTr("ID")
                            x: 34.5
                            anchors.verticalCenter: parent.verticalCenter
                            font.pixelSize: 14
                            color: "#858585"

                        }
                        TextField {
                            placeholderText: qsTr("First Name")
                            x: 125.5
                            anchors.verticalCenter: parent.verticalCenter
                            width: 400
                            height: 50

                            selectByMouse: true
                            font.pointSize: 11



                            background: Rectangle {
                                width: parent.width
                                height: parent.height
                                anchors.bottom: parent.bottom
                                color: "transparent"
                                border.color: "#DDDDDD"
                                radius: 3

                                }
                        }



                    }//end-ID


                    //start-SEX
                    Rectangle{
                        anchors.left: parent.left
                        y: 175
                        width: parent.width
                        height: 50
                        color: "transparent"

                        Text {
                            text: qsTr("性别")
                            x: 34.5
                            anchors.verticalCenter: parent.verticalCenter
                            font.pixelSize: 14
                            color: "#858585"

                        }
                        Rectangle {
                            x: 125.5
                            anchors.verticalCenter: parent.verticalCenter
                            width: 400
                            height: 50
                            color: "transparent"
                            border.color: "#DDDDDD"
                            radius: 3
                        }

                    }//end-SEX


                    //start-Birthday
                    Rectangle{
                        anchors.left: parent.left
                        y: 246
                        width: parent.width
                        height: 50
                        color: "transparent"

                        Text {
                            text: qsTr("出生年月")
                            x: 34.5
                            anchors.verticalCenter: parent.verticalCenter
                            font.pixelSize: 14
                            color: "#858585"

                        }


                        TextField {
                            placeholderText: qsTr("1975-11-12")
                            x: 125.5
                            anchors.verticalCenter: parent.verticalCenter
                            width: 400
                            height: 50

                            selectByMouse: true
                            font.pointSize: 11



                            background: Rectangle {
                                width: parent.width
                                height: parent.height
                                anchors.bottom: parent.bottom
                                color: "transparent"
                                border.color: "#DDDDDD"
                                radius: 3

                                }
                            ListModel{
                                 id: listmodel_year
                                 ListElement{yname:"1970"}
                                 ListElement{yname:"1971"}
                                 ListElement{yname:"1972"}
                                 ListElement{yname:"1973"}
                                 ListElement{yname:"1974"}
                                 ListElement{yname:"1975"}
                                 ListElement{yname:"1976"}
                                 ListElement{yname:"1977"}
                                 ListElement{yname:"1978"}
                                 ListElement{yname:"1979"}
                                 ListElement{yname:"1980"}
                                 ListElement{yname:"1981"}
                                 ListElement{yname:"1982"}
                                 ListElement{yname:"1983"}
                                 ListElement{yname:"1984"}


                            }
                            Component{
                                id: com_delegate_year
                                Column{
                                    id: wrapper_year
                                    Text {
                                        id: nameText
                                        text: yname
                                        color: wrapper_year.PathView.isCurrentItem ? "#14c0f5" : "#dcdcdc"
                                    }
                                }
                            }

                            PathView{
                                id: pathview_start_year
                                anchors.top: parent.bottom
                                width: parent.width
                                height: parent.height
                                model:listmodel_year
                                delegate: com_delegate_year
                                pathItemCount: 5
                                preferredHighlightBegin: 0.5
                                preferredHighlightEnd: 0.5
                                path: Path{
                                    startX: 0
                                    startY: -30
                                    PathLine{x:0; y:25}
                                    PathLine{x:0; y:45}
                                    PathLine{x:0; y:65}
                                }

                            }



                        }

                    }//end-Birthday





                    Text {
                        x: 33
                        y: 27
                        text: qsTr("编辑信息")
                        font.pixelSize: 24
                    }




                    Button{
                        text: qsTr("确定")
                        x: 306
                        y: 429
                        width: 100
                        height: 28
                        background: Rectangle{
                            anchors.centerIn: parent
                            width: parent.width
                            height: parent.height

                            color: "#0DAF9D"
                            border.color: "#DDE2E7"
                            radius: 14

                        }
                        onPressed: {
                            editDialog.close()


                        }

                    }

                    Button{
                        text: qsTr("取消")
                        x: 426
                        y: 429
                        width: 100
                        height: 28
                        background: Rectangle{
                            anchors.centerIn: parent
                            width: parent.width
                            height: parent.height

                            color: "#0DAF9D"
                            border.color: "#DDE2E7"
                            radius: 14

                        }
                        onPressed: {
                            editDialog.close()

                        }

                    }






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
