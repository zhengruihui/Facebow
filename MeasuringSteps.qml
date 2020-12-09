import QtQuick 2.15
import QtQuick3D 1.15
import QtQuick.Controls 2.14
import SerialPort 1.0
import QtGraphicalEffects 1.15

Item {
    property int topBarHeight: 35

    property int bottomBarHeight: 80

    property int leftBarWidth: 35

    property int rightBarWidth: 100

    property int centerBarWidth: 10

    property var barColor: "#1f2026"

    property int borderWidth: 4



    property var zoomFactor: 7
    property int buttonSkullHeight: 80
    property int zoomFactorMax: 10
    property int zoomFactorMin: 2
    property int lightBrightness: 70
    property int yOffset: -15


    anchors.fill: parent


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
            x: 600
            eulerRotation.y: 90
        }

        PerspectiveCamera {
            id: cameraPerspectiveLeftOblique
            x: 424
            z: 424
            eulerRotation.y: 45
        }



        PerspectiveCamera {
            id: cameraPerspectiveRight
            x: -600
            eulerRotation.y: -90
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


            Column {
                id: controlsContainer
                anchors.centerIn: parent
                spacing: 10
                padding: 10

                Button {
                    width: leftBar.width
                    anchors.horizontalCenter: parent.horizontalCenter


                    Text {
                        text: "Front"
                        //默认坐标居中
                        anchors.centerIn: parent
                        //默认文字对齐方式为水平和垂直居中
                        verticalAlignment: Text.AlignVCenter
                        horizontalAlignment: Text.AlignHCenter
                        //默认宽度为parent的宽度，这样字太长超出范围时自动显示省略号
                        width: parent.width
                    }

                    highlighted: view3DSkull.camera == cameraPerspectiveFront
                    onClicked: {
                        view3DSkull.camera = cameraPerspectiveFront
                    }
                }

                Button {
                    width: leftBar.width
                    anchors.horizontalCenter: parent.horizontalCenter
                    Text {
                        text: "Left"
                        //默认坐标居中
                        anchors.centerIn: parent
                        //默认文字对齐方式为水平和垂直居中
                        verticalAlignment: Text.AlignVCenter
                        horizontalAlignment: Text.AlignHCenter
                        //默认宽度为parent的宽度，这样字太长超出范围时自动显示省略号
                        width: parent.width
                    }
                    highlighted: view3DSkull.camera == cameraPerspectiveLeft
                    onClicked: {
                        view3DSkull.camera = cameraPerspectiveLeft
                    }
                }

                Button {
                    width: leftBar.width
                    anchors.horizontalCenter: parent.horizontalCenter
                    Text {
                        text: "LeftOblique"
                        //默认坐标居中
                        anchors.centerIn: parent
                        //默认文字对齐方式为水平和垂直居中
                        verticalAlignment: Text.AlignVCenter
                        horizontalAlignment: Text.AlignHCenter
                        //默认宽度为parent的宽度，这样字太长超出范围时自动显示省略号
                        width: parent.width
                    }
                    highlighted: view3DSkull.camera == cameraPerspectiveLeftOblique
                    onClicked: {
                        view3DSkull.camera = cameraPerspectiveLeftOblique
                    }
                }

                Button {
                    width: leftBar.width
                    anchors.horizontalCenter: parent.horizontalCenter
                    Text {
                        text: "Right"
                        //默认坐标居中
                        anchors.centerIn: parent
                        //默认文字对齐方式为水平和垂直居中
                        verticalAlignment: Text.AlignVCenter
                        horizontalAlignment: Text.AlignHCenter
                        //默认宽度为parent的宽度，这样字太长超出范围时自动显示省略号
                        width: parent.width
                    }
                    highlighted: view3DSkull.camera == cameraPerspectiveRight
                    onClicked: {
                        view3DSkull.camera = cameraPerspectiveRight
                    }
                }

                Button {
                    width: leftBar.width
                    anchors.horizontalCenter: parent.horizontalCenter
                    Text {
                        text: "RightOblique"
                        //默认坐标居中
                        anchors.centerIn: parent
                        //默认文字对齐方式为水平和垂直居中
                        verticalAlignment: Text.AlignVCenter
                        horizontalAlignment: Text.AlignHCenter
                        //默认宽度为parent的宽度，这样字太长超出范围时自动显示省略号
                        width: parent.width
                    }
                    highlighted: view3DSkull.camera == cameraPerspectiveRightOblique
                    onClicked: {
                        view3DSkull.camera = cameraPerspectiveRightOblique
                    }
                }


                Button {
                    width: leftBar.width
                    anchors.horizontalCenter: parent.horizontalCenter
                    Text {
                        text: "Top"
                        //默认坐标居中
                        anchors.centerIn: parent
                        //默认文字对齐方式为水平和垂直居中
                        verticalAlignment: Text.AlignVCenter
                        horizontalAlignment: Text.AlignHCenter
                        //默认宽度为parent的宽度，这样字太长超出范围时自动显示省略号
                        width: parent.width
                    }
                    highlighted: view3DSkull.camera == cameraPerspectiveTop
                    onClicked: {
                        view3DSkull.camera = cameraPerspectiveTop
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
        }


        View3D {
            id: view3DSkull
            anchors.top: topBar.bottom
            anchors.left: leftBar.right
            width: (parent.width-leftBarWidth-rightBarWidth-centerBarWidth)/2
            height: parent.height-topBarHeight-bottomBarHeight
            camera: cameraPerspectiveLeftOblique
            importScene: standAloneScene
            renderMode: View3D.Overlay



            environment: SceneEnvironment {
                clearColor: "#cad8dc"
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




        Rectangle{

            anchors.top: topBar.bottom
            anchors.right: rightBar.left
            width: (parent.width-leftBarWidth-rightBarWidth-centerBarWidth)/2
            height: parent.height-topBarHeight-bottomBarHeight
            color: "#cad8dc"



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
