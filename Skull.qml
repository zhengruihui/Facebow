import QtQuick 2.15
import QtQuick3D 1.15
import QtQuick.Controls 2.14
import SerialPort 1.0

Item {

    property var zoomFactor: 7
    property int buttonSkullHeight: 60
    property int zoomFactorMax: 10
    property int zoomFactorMin: 2
    property int lightBrightness: 70
    property int yOffset: -15


    Node {
        id: standAloneScene
        //! [rootnode]

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

//        Model {
//            source: "#Rectangle"
//            y: -200
//            scale: Qt.vector3d(150, 150, 150)
//            eulerRotation.x: -90
//            materials: [
//                DefaultMaterial {
//                    diffuseColor: Qt.rgba(0.8, 0.6, 0.4, 1.0)

//                }
//            ]
//        }


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
        id: topRight
        anchors.top: parent.top
        anchors.left: parent.left
        width: parent.width
        height: parent.height - buttonSkullHeight
        color: "transparent"
        //border.color: "white"
        //border.width: 2

        View3D {
            id: view3DSkull
            anchors.fill: parent
            camera: cameraPerspectiveLeftOblique
            importScene: standAloneScene
            renderMode: View3D.Underlay

            environment: SceneEnvironment {
                clearColor: "#848895"
                backgroundMode: SceneEnvironment.Color
            }
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
        anchors.bottom: parent.bottom
        anchors.left: parent.left
        width: parent.width
        height: buttonSkullHeight
        color: "#848895"
        //border.color: "black"
        //border.width: 2

        Row {
            id: controlsContainer
            anchors.bottom: parent.bottom
            anchors.centerIn: parent
            spacing: 10
            padding: 10

            RoundButton {
                text: "Front"
                highlighted: view3DSkull.camera == cameraPerspectiveFront
                onClicked: {
                    view3DSkull.camera = cameraPerspectiveFront
                }
            }

            RoundButton {
                text: "Left"
                highlighted: view3DSkull.camera == cameraPerspectiveLeft
                onClicked: {
                    view3DSkull.camera = cameraPerspectiveLeft
                }
            }

            RoundButton {
                text: "LeftOblique"
                highlighted: view3DSkull.camera == cameraPerspectiveLeftOblique
                onClicked: {
                    view3DSkull.camera = cameraPerspectiveLeftOblique
                }
            }

            RoundButton {
                text: "Right"
                highlighted: view3DSkull.camera == cameraPerspectiveRight
                onClicked: {
                    view3DSkull.camera = cameraPerspectiveRight
                }
            }

            RoundButton {
                text: "RightOblique"
                highlighted: view3DSkull.camera == cameraPerspectiveRightOblique
                onClicked: {
                    view3DSkull.camera = cameraPerspectiveRightOblique
                }
            }


            RoundButton {
                text: "Top"
                highlighted: view3DSkull.camera == cameraPerspectiveTop
                onClicked: {
                    view3DSkull.camera = cameraPerspectiveTop
                }
            }
        }
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
