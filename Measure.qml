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
    //anchors.fill: parent


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

                    highlighted: view3DSkull.camera == cameraPerspectiveRight
                    onClicked: {
                        view3DSkull.camera = cameraPerspectiveRight
                    }

                }

                MButton{
                    width: 31
                    height: 31
                    haveText: false
                    anchors.horizontalCenter: parent.horizontalCenter

                    normalImagelUrl: "Resources/assets/skull/left.png"
                    pressedImageUrl: "Resources/assets/skull/left_sel.png"

                    highlighted: view3DSkull.camera == cameraPerspectiveLeft
                    onClicked: {
                        view3DSkull.camera = cameraPerspectiveLeft
                    }

                }

                MButton{
                    width: 31
                    height: 31
                    haveText: false
                    anchors.horizontalCenter: parent.horizontalCenter

                    normalImagelUrl: "Resources/assets/skull/front.png"
                    pressedImageUrl: "Resources/assets/skull/front_sel.png"

                    highlighted: view3DSkull.camera == cameraPerspectiveFront
                    onClicked: {
                        view3DSkull.camera = cameraPerspectiveFront
                    }

                }

                MButton{
                    width: 31
                    height: 31
                    haveText: false
                    anchors.horizontalCenter: parent.horizontalCenter

                    normalImagelUrl: "Resources/assets/skull/top.png"
                    pressedImageUrl: "Resources/assets/skull/top_sel.png"

                    highlighted: view3DSkull.camera == cameraPerspectiveTop
                    onClicked: {
                        view3DSkull.camera = cameraPerspectiveTop
                    }

                }

                MButton{
                    width: 31
                    height: 31
                    haveText: false
                    anchors.horizontalCenter: parent.horizontalCenter

                    normalImagelUrl: "Resources/assets/skull/oblique.png"
                    pressedImageUrl: "Resources/assets/skull/oblique_sel.png"

                    highlighted: view3DSkull.camera == cameraPerspectiveRightOblique
                    onClicked: {
                        view3DSkull.camera = cameraPerspectiveRightOblique
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
            camera: cameraPerspectiveRightOblique
            importScene: standAloneScene
            renderMode: View3D.Offscreen


            environment: SceneEnvironment {
                clearColor: "#949597"
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
            color: "#949597"
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

    SerialPort{
            onPositionChanged: {
                skullModel2.x = x;
                skullModel2.y = y+yOffset;
                skullModel2.z = z;
                skullModel2.eulerRotation.x = tilt;
                skullModel2.eulerRotation.y = heading;
                skullModel2.eulerRotation.z = roll;
            }
    }

}
