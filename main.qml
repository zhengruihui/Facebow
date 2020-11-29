import QtQuick
import QtQuick3D
import QtQuick.Controls


Window {
    id: window
    width: 1280
    height: 720
    visible: true
    title: qsTr("Facebow")


    property var factor : 0.014

    Node {
        id: standAloneScene


        DirectionalLight {
            eulerRotation.x: 0
            eulerRotation.y: 45
            eulerRotation.z: 0
            brightness: 0.5
        }
        DirectionalLight {
            eulerRotation.x: 0
            eulerRotation.y: 135
            eulerRotation.z: 0
            brightness: 0.5
        }

        DirectionalLight {
            eulerRotation.x: 0
            eulerRotation.y: -45
            eulerRotation.z: 0
            brightness: 0.5
        }
        DirectionalLight {
            eulerRotation.x: 0
            eulerRotation.y: -135
            eulerRotation.z: 0
            brightness: 0.5
        }


//        DirectionalLight {
//            eulerRotation.x: 0
//            eulerRotation.y: -45
//            eulerRotation.z: 0
//            brightness: 0.5
//        }



//        DirectionalLight {
//            eulerRotation: Qt.vector3d(135, 110, 0)
//            brightness: 1
//        }


        Model {

            source: "Resources/Mesh/skull1.mesh"
            y: -50
            scale: Qt.vector3d(window.width*0.5*factor, window.width*0.5*factor, window.width*0.5*factor)
            materials: [
                PrincipledMaterial {
                    baseColor: "#DAD9BB"
                    metalness: 0.1
                    roughness: 0.1
                    opacity: 1.0
                }
            ]

        }



        Model {

            source: "Resources/Mesh/skull2.mesh"            
            y: -50
            scale: Qt.vector3d(window.width*0.5*factor, window.width*0.5*factor, window.width*0.5*factor)
            materials: [
                PrincipledMaterial {
                    baseColor: "#DAD9BB"
                    metalness: 0.1
                    roughness: 0.1
                    opacity: 1.0
                }
            ]

//            PropertyAnimation on eulerRotation.x {
//                loops: Animation.Infinite
//                duration: 5000
//                to: 0
//                from: 10
//            }
//            PropertyAnimation on eulerRotation.y {
//                loops: Animation.Infinite
//                duration: 5000
//                to: -20
//                from: 20
//            }


        }






        //! [cameras start]
        // The predefined cameras. They have to be part of the scene, i.e. inside the root node.
        // Animated perspective camera

        // Stationary orthographic camera viewing from the front
        OrthographicCamera {
            id: cameraOrthographicFront
            z: 600
        }
        //! [cameras end]

        // Stationary orthographic camera viewing from right
        OrthographicCamera {
            id: cameraOrthographicRight
            x: 600
            eulerRotation.y: 90
        }
        //! [cameras end]

        // Stationary orthographic camera viewing from left
        OrthographicCamera {
            id: cameraOrthographicLeft
            x: -600
            eulerRotation.y: -90
        }
         //! [cameras end]

        // Stationary orthographic camera viewing from the top
        OrthographicCamera {
            id: cameraOrthographicTop
            y: 600
            eulerRotation.x: -90
        }
        //! [cameras end]

    }

    Rectangle {
        id: leftRectangle
        anchors.bottom: parent.bottom
        anchors.left: parent.left
        width: parent.width * 0.5
        height: parent.height
        color: "#848895"
        border.color: "black"

        View3D {
            id: topRightView
//            anchors.top: parent.top
//            anchors.right: parent.right
//            anchors.left: parent.left
//            anchors.bottom: parent.bottom
//            anchors.verticalCenter: parent.verticalCenter
            anchors.centerIn: parent
            anchors.fill:parent
            camera: cameraOrthographicFront
            importScene: standAloneScene
            renderMode: View3D.Underlay


            environment: SceneEnvironment {
                clearColor: "#848895"
                backgroundMode: SceneEnvironment.Color
            }
        }



        Row {
            id: controlsContainer
            anchors.bottom: parent.bottom
            anchors.horizontalCenter: parent.horizontalCenter
            spacing: 10
            padding: 10

            RoundButton {
                text: "Front"
                highlighted: topRightView.camera == cameraOrthographicFront
                onClicked: {
                    topRightView.camera = cameraOrthographicFront
                }
            }

            RoundButton {
                text: "Right"
                highlighted: topRightView.camera == cameraOrthographicRight
                onClicked: {
                    topRightView.camera = cameraOrthographicRight
                }
            }

            RoundButton {
                text: "Left"
                highlighted: topRightView.camera == cameraOrthographicLeft
                onClicked: {
                    topRightView.camera = cameraOrthographicLeft
                }
            }

            RoundButton {
                text: "Top"
                highlighted: topRightView.camera == cameraOrthographicTop
                onClicked: {
                    topRightView.camera = cameraOrthographicTop
                }
            }
        }
    }


    Rectangle {
        id: rightRectangle
        anchors.bottom: parent.bottom
        anchors.right: parent.right
        width: parent.width * 0.5
        height: parent.height
        color: "transparent"
        border.color: "black"


        Image {
            id: name
            anchors.fill: parent
            source: "Resources/Image/Person.jpg"
        }

    }


}
