import QtQuick 2.15
import QtQuick3D 1.15
import QtQuick.Controls 2.14
import QtGraphicalEffects 1.15


Item {

    property var zoomFactor: 7
    property int zoomFactorMax: 10
    property int zoomFactorMin: 2
    property int lightBrightness: 70
    property int yOffset: -15


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
            source: "qrc:/Resources/Mesh/skull1.mesh"
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
            source: "qrc:/Resources/Mesh/skull2.mesh"
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

}
