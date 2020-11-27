import QtQuick 2.15
import QtQuick.Window 2.14
import QtQuick3D 1.15
import QtQuick.Controls 2.14


Window {
    id: window
    width: 1280
    height: 720
    visible: true
    title: qsTr("Facebow")//


    property var factor : 0.014
    // The root scene
    //! [rootnode]
    Node {
        id: standAloneScene
        //! [rootnode]

        DirectionalLight {
            ambientColor: Qt.rgba(1.0, 1.0, 1.0, 1.0)

        }





        Model {

            source: "Resources/Mesh/skull1.mesh"
            y: -100
            scale: Qt.vector3d(window.width*0.5*factor, window.width*0.5*factor, window.width*0.5*factor)
            materials: [
                PrincipledMaterial {
                    baseColor: "#DAD9BB"
                    metalness: 0.75
                    roughness: 0.1
                    specularAmount: 1.0
                    indexOfRefraction: 2.5
                    opacity: 1.0
                }
            ]

        }



        Model {

            source: "Resources/Mesh/skull2.mesh"
            y: -100
            scale: Qt.vector3d(window.width*0.5*factor, window.width*0.5*factor, window.width*0.5*factor)
            materials: [
                PrincipledMaterial {
                    baseColor: "#DAD9BB"
                    metalness: 0.75
                    roughness: 0.1
                    specularAmount: 1.0
                    indexOfRefraction: 2.5
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
        color: "transparent"
        border.color: "black"

//        Label {
//            text: "Perspective"
//            anchors.top: parent.top
//            anchors.right: parent.right
//            anchors.margins: 10
//            color: "#222840"
//            font.pointSize: 14
//        }

        View3D {
            id: topRightView
            anchors.top: parent.top
            anchors.right: parent.right
            anchors.left: parent.left
            anchors.bottom: parent.bottom;
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
