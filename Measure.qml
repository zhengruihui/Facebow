import QtQuick 2.15
import QtQuick3D 1.15
import QtQuick.Controls 2.14
import QtGraphicalEffects 1.15

Item {
    property int topBarHeight: 40

    property int bottomBarHeight: 100

    property int leftBarWidth: 40

    property int rightBarWidth: 130

    property int centerBarWidth: 20

    property var barColor: "#24242c"

    property int borderWidth: 4


    property var zoomFactor: 7
    property int buttonSkullHeight: 80
    property int zoomFactorMax: 10
    property int zoomFactorMin: 2
    property int lightBrightness: 70
    property int yOffset: -15

    property int currentButtonID : 0

    property bool startMeasure: false
    property int guideStep: 1



    Node {
        id: standAloneScene

        DirectionalLight {
            id:directionalLightFront1
            y: 424
            z: 424
            eulerRotation.x: -45
            brightness: 10

        }

        DirectionalLight {
            id:directionalLightFront2
            z: 600
            brightness: lightBrightness
        }
        DirectionalLight {
            x: 600
            eulerRotation.y: 90
            brightness: lightBrightness
        }
        DirectionalLight {
            x: -600
            eulerRotation.y: -90
            brightness: lightBrightness
        }



        Model {
            id: skullModel1
            source: "Resources/Mesh/skull1.mesh"
            y: yOffset
            scale: Qt.vector3d(zoomFactor, zoomFactor, zoomFactor)
            materials: [
                PrincipledMaterial {
                    baseColor: "#D0CFB0"
                    metalness: 0.75
                    roughness: 0.1
                    specularAmount: 0.5
                    //indexOfRefraction: 2.5
                    opacity: 1.0
                }
            ]

        }

        Model {
            id: skullModel2
            source: "Resources/Mesh/skull2.mesh"
            y: yOffset
            scale: Qt.vector3d(zoomFactor, zoomFactor, zoomFactor)
            materials: [
                PrincipledMaterial {
                    baseColor: "#DAFFFF"
                    metalness: 0.75
                    roughness: 0.1
                    specularAmount: 0.5
                    //indexOfRefraction: 2.5
                    opacity: 1.0
                }
            ]



        }

        PerspectiveCamera {
            id: cameraPerspectiveFront
            z: 600
        }

        PerspectiveCamera {
            id: cameraPerspectiveLeft
            x: -600
            eulerRotation.y: -90
        }

        PerspectiveCamera {
            id: cameraPerspectiveLeftOblique
            x: 424
            z: 424
            eulerRotation.y: 45
        }


        PerspectiveCamera {
            id: cameraPerspectiveRight
            x: 600
            eulerRotation.y: 90
        }



        PerspectiveCamera {
            id: cameraPerspectiveRightOblique
            x: -424
            z: 424
            eulerRotation.y: -45
        }

        PerspectiveCamera {
            id: cameraPerspectiveTop
            y: 519.6
            z: 300
            eulerRotation.x: -60
        }

    }

    Rectangle {
        id: rootRectangle
        anchors.top: parent.top
        anchors.left: parent.left
        width: parent.width
        height: parent.height

        color: barColor
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
            property bool modelPressed: true


            Button{
                x: 58
                anchors.verticalCenter: parent.verticalCenter
                width: 25
                height: 25
                background: Rectangle{
                    color: "transparent"
                    border.width: 0


                }

                Text {
                    text: qsTr("模型")
                    width: 16
                    height: 17
                    anchors.centerIn: parent
                    verticalAlignment: Text.AlignVCenter
                    horizontalAlignment: Text.AlignHCenter
                    color: topBar.modelPressed? "#0DAF9D" : "#DEDEDE"
                    font.pixelSize: 12
                }

                onPressed: {
                    topBar.modelPressed = true;
                    viewModel.visible = true
                    view3D.visible = false
                }

            }


            Button{
                x: 100
                anchors.verticalCenter: parent.verticalCenter
                width: 25
                height: 25
                background: Rectangle{
                    color: "transparent"
                    border.width: 0


                }

                Text {
                    text: qsTr("3D")
                    width: 16
                    height: 17
                    anchors.centerIn: parent
                    verticalAlignment: Text.AlignVCenter
                    horizontalAlignment: Text.AlignHCenter
                    color: topBar.modelPressed? "#DEDEDE" : "#0DAF9D"
                    font.pixelSize: 12
                }

                onPressed: {
                    topBar.modelPressed = false
                    viewModel.visible = false
                    view3D.visible = true
                }

            }


        }

        Rectangle{
            id:bottomBar
            anchors.bottom: parent.bottom
            anchors.horizontalCenter: parent.horizontalCenter
            width: parent.width-2*borderWidth
            height:bottomBarHeight
            color: barColor


            MButton{
                id: playID
                x: parent.width - 497
                anchors.verticalCenter: parent.verticalCenter
                width: 100
                height: 50
                normalImagelUrl: "Resources/assets/navigation/play.png"
                pressedImageUrl: "Resources/assets/navigation/play.png"
                text: qsTr("开始")
                normalTextColor: "#DEDEDE"
                pressedTextColor: "#0DAF9D"
                hover:false
                radius: 25
                color: "#454449"

                border.width: 2
                border.color: "#26272C"

                highlighted: startMeasure
                onClicked: {
                    startMeasure = !startMeasure
                }

            }

            MButton{
                id: measureSettingID
                x: parent.width - 366.7
                anchors.verticalCenter: parent.verticalCenter
                width: 100
                height: 50
                normalImagelUrl: "Resources/assets/navigation/measure_setting.png"
                pressedImageUrl: "Resources/assets/navigation/measure_setting.png"
                text: qsTr("测量设置")
                normalTextColor: "#DEDEDE"
                pressedTextColor: "#0DAF9D"
                hover:false
                radius: 25
                color: "#454449"

                border.width: 2
                border.color: "#26272C"

                onClicked: {


                }

            }

            MButton{
                id: deviceSettingID
                x: parent.width - 236.7
                anchors.verticalCenter: parent.verticalCenter
                width: 100
                height: 50
                normalImagelUrl: "Resources/assets/navigation/device_setting.png"
                pressedImageUrl: "Resources/assets/navigation/device_setting.png"
                text: qsTr("设备设置")
                normalTextColor: "#DEDEDE"
                pressedTextColor: "#0DAF9D"
                hover:false
                radius: 25
                color: "#454449"

                border.width: 2
                border.color: "#26272C"

                onClicked: {


                }

            }

//            DropShadow {
//                anchors.fill: playID
//                transparentBorder: true
//                horizontalOffset: -2
//                verticalOffset: 2
//                radius: 10
//                samples: 21
//                color: "#80000000"
//                spread: 0
//                source: playID
//            }
//            DropShadow {
//                anchors.fill: playID
//                transparentBorder: true
//                horizontalOffset: 1
//                verticalOffset: -1
//                radius: 10
//                samples: 21
//                color: "#80000000"
//                spread: 0
//                source: playID
//            }

//            DropShadow {
//                anchors.fill: measureSettingID
//                transparentBorder: true
//                horizontalOffset: -2
//                verticalOffset: 2
//                radius: 10
//                samples: 21
//                color: "#80000000"
//                spread: 0
//                source: measureSettingID
//            }
//            DropShadow {
//                anchors.fill: measureSettingID
//                transparentBorder: true
//                horizontalOffset: 1
//                verticalOffset: -1
//                radius: 10
//                samples: 21
//                color: "#80000000"
//                spread: 0
//                source: measureSettingID
//            }

//            DropShadow {
//                anchors.fill: deviceSettingID
//                transparentBorder: true
//                horizontalOffset: -2
//                verticalOffset: 2
//                radius: 10
//                samples: 21
//                color: "#80000000"
//                spread: 0
//                source: deviceSettingID
//            }
//            DropShadow {
//                anchors.fill: deviceSettingID
//                transparentBorder: true
//                horizontalOffset: 1
//                verticalOffset: -1
//                radius: 10
//                samples: 21
//                color: "#80000000"
//                spread: 0
//                source: deviceSettingID
//            }

        }



        Rectangle{
            id:leftBar
            anchors.left: parent.left
            anchors.verticalCenter: parent.verticalCenter
            width: leftBarWidth
            height: parent.height-2*borderWidth
            color: barColor



            Column {
                anchors.top: parent.top
                width: parent.width
                height: parent.height
                topPadding: topBar.height-4

                spacing: 10.2

                MButton{
                    width: 31
                    height: 31
                    haveText: false
                    anchors.horizontalCenter: parent.horizontalCenter

                    normalImagelUrl: "Resources/assets/skull/zoom_out.png"
                    pressedImageUrl: "Resources/assets/skull/zoom_out_sel.png"

                    highlighted: currentButtonID == 1
                    onClicked: {
                        zoomFactor>zoomFactorMin?zoomFactor -= 0.1:zoomFactor
                        currentButtonID = 1
                    }

                }

                MButton{
                    width: 31
                    height: 31
                    haveText: false
                    anchors.horizontalCenter: parent.horizontalCenter

                    normalImagelUrl: "Resources/assets/skull/zoom_in.png"
                    pressedImageUrl: "Resources/assets/skull/zoom_in_sel.png"

                    highlighted: currentButtonID == 2
                    onClicked: {
                        zoomFactor<zoomFactorMax?zoomFactor += 0.1:zoomFactor
                        currentButtonID = 2
                    }

                }

                MButton{
                    width: 31
                    height: 31
                    haveText: false
                    anchors.horizontalCenter: parent.horizontalCenter

                    normalImagelUrl: "Resources/assets/skull/default.png"
                    pressedImageUrl: "Resources/assets/skull/default_sel.png"

                    highlighted: currentButtonID == 3
                    onClicked: {
                         zoomFactor = 7
                        currentButtonID = 3
                    }

                }




            }

            Column{
                anchors.top: parent.top
                width: parent.width
                height: parent.height
                topPadding: 193.7

                spacing: 10.2


                MButton{
                    width: 31
                    height: 31
                    haveText: false
                    anchors.horizontalCenter: parent.horizontalCenter

                    normalImagelUrl: "Resources/assets/skull/right.png"
                    pressedImageUrl: "Resources/assets/skull/right_sel.png"

                    highlighted: viewModel.camera == cameraPerspectiveRight
                    onClicked: {
                        viewModel.camera = cameraPerspectiveRight
                    }

                }

                MButton{
                    width: 31
                    height: 31
                    haveText: false
                    anchors.horizontalCenter: parent.horizontalCenter

                    normalImagelUrl: "Resources/assets/skull/left.png"
                    pressedImageUrl: "Resources/assets/skull/left_sel.png"

                    highlighted: viewModel.camera == cameraPerspectiveLeft
                    onClicked: {
                        viewModel.camera = cameraPerspectiveLeft
                    }

                }

                MButton{
                    width: 31
                    height: 31
                    haveText: false
                    anchors.horizontalCenter: parent.horizontalCenter

                    normalImagelUrl: "Resources/assets/skull/front.png"
                    pressedImageUrl: "Resources/assets/skull/front_sel.png"

                    highlighted: viewModel.camera == cameraPerspectiveFront
                    onClicked: {
                        viewModel.camera = cameraPerspectiveFront
                    }

                }

                MButton{
                    width: 31
                    height: 31
                    haveText: false
                    anchors.horizontalCenter: parent.horizontalCenter

                    normalImagelUrl: "Resources/assets/skull/top.png"
                    pressedImageUrl: "Resources/assets/skull/top_sel.png"

                    highlighted: viewModel.camera == cameraPerspectiveTop
                    onClicked: {
                        viewModel.camera = cameraPerspectiveTop
                    }

                }

                MButton{
                    width: 31
                    height: 31
                    haveText: false
                    anchors.horizontalCenter: parent.horizontalCenter

                    normalImagelUrl: "Resources/assets/skull/oblique.png"
                    pressedImageUrl: "Resources/assets/skull/oblique_sel.png"

                    highlighted: viewModel.camera == cameraPerspectiveRightOblique
                    onClicked: {
                        viewModel.camera = cameraPerspectiveRightOblique
                    }

                }



            }





        }

        Rectangle{
            id:rightBar
            anchors.right: parent.right
            anchors.verticalCenter: parent.verticalCenter
            width: rightBarWidth
            height: parent.height-2*borderWidth
            color: barColor
            property int yOffset : 107

            Rectangle{
                id: guideStep1ID
                anchors.horizontalCenter: parent.horizontalCenter
                y: 60
                width: 80
                height: 88
                color: barColor
                MouseArea{
                    anchors.fill: parent
                    onPressed: {
                        guideStep = 1
                    }

                }
            }

            Rectangle{
                id: guideStep2ID
                anchors.horizontalCenter: parent.horizontalCenter
                y: 60+rightBar.yOffset
                width: 80
                height: 88
                color: barColor
                MouseArea{
                    anchors.fill: parent
                    onPressed: {
                        guideStep = 2
                    }

                }
            }

            Rectangle{
                id: guideStep3ID
                anchors.horizontalCenter: parent.horizontalCenter
                y: 60+2*rightBar.yOffset
                width: 80
                height: 88
                color: barColor
                MouseArea{
                    anchors.fill: parent
                    onPressed: {
                        guideStep = 3
                    }

                }
            }

            Rectangle{
                id: guideStep4ID
                anchors.horizontalCenter: parent.horizontalCenter
                y: 60+3*rightBar.yOffset
                width: 80
                height: 88
                color: barColor
                MouseArea{
                    anchors.fill: parent
                    onPressed: {
                        guideStep = 4
                    }

                }
            }

            Rectangle{
                id: guideStep5ID
                anchors.horizontalCenter: parent.horizontalCenter
                y: 60+4*rightBar.yOffset
                width: 80
                height: 88
                color: barColor
                MouseArea{
                    anchors.fill: parent
                    onPressed: {
                        guideStep = 5
                    }

                }
            }



            DropShadow {
                anchors.fill: guideStep1ID
                transparentBorder: true
                horizontalOffset: -2
                verticalOffset: 2
                radius: 10
                samples: 21
                color: "#80000000"
                spread: 0
                source: guideStep1ID
            }
            DropShadow {
                anchors.fill: guideStep2ID
                transparentBorder: true
                horizontalOffset: -2
                verticalOffset: 2
                radius: 10
                samples: 21
                color: "#80000000"
                spread: 0
                source: guideStep2ID
            }
            DropShadow {
                anchors.fill: guideStep3ID
                transparentBorder: true
                horizontalOffset: -2
                verticalOffset: 2
                radius: 10
                samples: 21
                color: "#80000000"
                spread: 0
                source: guideStep3ID
            }
            DropShadow {
                anchors.fill: guideStep4ID
                transparentBorder: true
                horizontalOffset: -2
                verticalOffset: 2
                radius: 10
                samples: 21
                color: "#80000000"
                spread: 0
                source: guideStep4ID
            }
            DropShadow {
                anchors.fill: guideStep5ID
                transparentBorder: true
                horizontalOffset: -2
                verticalOffset: 2
                radius: 10
                samples: 21
                color: "#80000000"
                spread: 0
                source: guideStep5ID
            }

        }

        Rectangle{
            id: viewID
            anchors.top: topBar.bottom
            anchors.left: leftBar.right
            width: (parent.width-leftBarWidth-rightBarWidth-centerBarWidth)/2
            height: parent.height-topBarHeight-bottomBarHeight
            color: "#454449"


            View3D {
                id: viewModel
                anchors.fill: parent
                camera: cameraPerspectiveRightOblique
                importScene: standAloneScene
                renderMode: View3D.Offscreen
                visible: true





                environment: SceneEnvironment {
                    clearColor: "#454449"
                    backgroundMode: SceneEnvironment.Color

                }

                MouseArea{
                    anchors.fill: parent
                    onWheel: {
                        var datl = wheel.angleDelta.y/120

                        if(datl>0){
                            zoomFactor<zoomFactorMax?zoomFactor += 0.1:zoomFactor;
                        }else{
                            zoomFactor>zoomFactorMin?zoomFactor -= 0.1:zoomFactor;
                        }

                    }

                }
            }


            Rectangle {
                id: view3D
                anchors.fill: parent
                color: "#454449"
                visible: false

            }


        }








        Rectangle{
            id: guideStepID
            anchors.top: topBar.bottom
            anchors.right: rightBar.left
            width: (parent.width-leftBarWidth-rightBarWidth-centerBarWidth)/2
            height: parent.height-topBarHeight-bottomBarHeight
            color: "#454449"

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


    function updatePosition(x, y, z, ex, ey, ez)
    {
        skullModel2.x = x;
        skullModel2.y = y+yOffset;
        skullModel2.z = z;
        skullModel2.eulerRotation.x = ex;
        skullModel2.eulerRotation.y = ey;
        skullModel2.eulerRotation.z = ez;
    }

}
