/****************************************************************************
**
** Copyright (C) 2019 The Qt Company Ltd.
** Contact: https://www.qt.io/licensing/
**
** This file is part of the examples of the Qt Toolkit.
**
** $QT_BEGIN_LICENSE:BSD$
** Commercial License Usage
** Licensees holding valid commercial Qt licenses may use this file in
** accordance with the commercial license agreement provided with the
** Software or, alternatively, in accordance with the terms contained in
** a written agreement between you and The Qt Company. For licensing terms
** and conditions see https://www.qt.io/terms-conditions. For further
** information use the contact form at https://www.qt.io/contact-us.
**
** BSD License Usage
** Alternatively, you may use this file under the terms of the BSD license
** as follows:
**
** "Redistribution and use in source and binary forms, with or without
** modification, are permitted provided that the following conditions are
** met:
**   * Redistributions of source code must retain the above copyright
**     notice, this list of conditions and the following disclaimer.
**   * Redistributions in binary form must reproduce the above copyright
**     notice, this list of conditions and the following disclaimer in
**     the documentation and/or other materials provided with the
**     distribution.
**   * Neither the name of The Qt Company Ltd nor the names of its
**     contributors may be used to endorse or promote products derived
**     from this software without specific prior written permission.
**
**
** THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
** "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
** LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
** A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
** OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
** SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
** LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
** DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
** THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
** (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
** OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE."
**
** $QT_END_LICENSE$
**
****************************************************************************/

import QtQuick 2.15
import QtQuick.Window 2.14
import QtQuick3D 1.15
import QtQuick.Controls 2.14
import SerialPort 1.0

Window {
    id: window
    width: 1280
    height: 720
    visible: true
    title: "Facebow"

    property var zoomFactor: 7
    property int buttonSkullHeight: 60
    property int zoomFactorMax: 10
    property int zoomFactorMin: 2

    Node {
        id: standAloneScene
        //! [rootnode]

        DirectionalLight {
            //ambientColor: Qt.rgba(0.5, 0.5, 0.5, 1.0)
            //brightness: 0.5

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
            y: 0
            scale: Qt.vector3d(zoomFactor, zoomFactor, zoomFactor)
            materials: [
                PrincipledMaterial {
                    baseColor: "#DAD9BB"
                    metalness: 0.75
                    roughness: 0.1
                    specularAmount: 1.0
                    //indexOfRefraction: 2.5
                    opacity: 1.0
                }
            ]

        }

        Model {
            id: skullModel2
            source: "Resources/Mesh/skull2.mesh"
            y: 0
            scale: Qt.vector3d(zoomFactor, zoomFactor, zoomFactor)
            materials: [
                PrincipledMaterial {
                    baseColor: "#DAFFFF"
                    metalness: 0.75
                    roughness: 0.1
                    specularAmount: 1.0
                    //indexOfRefraction: 2.5
                    opacity: 1.0
                }
            ]



        }

        //! [cameras start]
        // The predefined cameras. They have to be part of the scene, i.e. inside the root node.
        // Animated perspective camera

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
            y: 600
            eulerRotation.x: -90
        }
        //! [cameras start]

        // Second animated perspective camera



    }

    Rectangle {
        id: topRight
        anchors.top: parent.top
        anchors.left: parent.left
        width: parent.width
        height: parent.height - buttonSkullHeight
        color: "transparent"
        border.color: "black"

        View3D {
            id: topRightView
            anchors.top: parent.top
            anchors.right: parent.right
            anchors.left: parent.left
            anchors.bottom: parent.bottom;
            camera: cameraPerspectiveFront
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

        Row {
            id: controlsContainer
            anchors.bottom: parent.bottom
            anchors.horizontalCenter: parent.horizontalCenter
            spacing: 10
            padding: 10

            //! [buttons]
            RoundButton {
                text: "Front"
                highlighted: topRightView.camera == cameraPerspectiveFront
                onClicked: {
                    topRightView.camera = cameraPerspectiveFront
                }
            }
            //! [buttons]
            RoundButton {
                text: "Left"
                highlighted: topRightView.camera == cameraPerspectiveLeft
                onClicked: {
                    topRightView.camera = cameraPerspectiveLeft
                }
            }

            RoundButton {
                text: "LeftOblique"
                highlighted: topRightView.camera == cameraPerspectiveLeftOblique
                onClicked: {
                    topRightView.camera = cameraPerspectiveLeftOblique
                }
            }

            RoundButton {
                text: "Right"
                highlighted: topRightView.camera == cameraPerspectiveRight
                onClicked: {
                    topRightView.camera = cameraPerspectiveRight
                }
            }

            RoundButton {
                text: "RightOblique"
                highlighted: topRightView.camera == cameraPerspectiveRightOblique
                onClicked: {
                    topRightView.camera = cameraPerspectiveRightOblique
                }
            }


            RoundButton {
                text: "Top"
                highlighted: topRightView.camera == cameraPerspectiveTop
                onClicked: {
                    topRightView.camera = cameraPerspectiveTop
                }
            }
        }
    }

//    Rectangle{
//        anchors.top: parent.top
//        anchors.right: parent.right
//        height: parent.height
//        Image {
//            id: person
//            anchors.top: parent.top
//            anchors.right: parent.right
//            height: parent.height
//            source: "Resources/Image/Person.jpg"
//        }


//    }

    SerialPort{
            onPositionChanged: {
                skullModel2.x = x;
                skullModel2.y = y;
                skullModel2.z = z;
                skullModel2.eulerRotation.x = tilt;
                skullModel2.eulerRotation.y = heading;
                skullModel2.eulerRotation.z = roll;
                console.log('skullModel2Position:', x, y, z, heading, tilt, roll)
            }
    }

}
