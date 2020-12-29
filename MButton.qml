import QtQuick 2.9
import QtQuick.Controls 2.5


Rectangle {
    id: root
    property url normalImagelUrl
    //property url hoveredUrl
    property url pressedImageUrl
    //property url disabledUrl

    property string normalTextColor
    property string pressedTextColor


    property bool  highlighted: false
    property bool haveText: true
    property bool hover: false

    property alias imageItem: img
    property alias imageUrl: img.source
    property alias imageWidth: img.width
    property alias imageHeight: img.height

    property alias textItem: t
    property alias text: t.text
    property alias textColor: t.color
    property alias containsMouse: area.containsMouse
    property alias containsPress: area.containsPress
    signal clicked();

    color: "transparent"
    Image {
        id: img
        source: highlighted ? pressedImageUrl : normalImagelUrl
        anchors.horizontalCenter: parent.horizontalCenter
        y: haveText? (parent.height - img.height - t.height)/2 : (parent.height - img.height)/2

    }
    Text {
        id: t
        verticalAlignment: Text.AlignVCenter
        horizontalAlignment: Text.AlignHCenter
        anchors.horizontalCenter: parent.horizontalCenter
        anchors.top: img.bottom
        anchors.topMargin: 2
        color: highlighted ? pressedTextColor : normalTextColor
        visible: haveText? true : false
        font.family: "Source Code Pro"
    }

    MouseArea {
        id: area
        anchors.fill: parent
        hoverEnabled: true
        onClicked: root.clicked();
        cursorShape: Qt.PointingHandCursor

        onEntered: {
            if(hover)
            {
                root.color = "grey"
            }

        }
        onExited: {

            if(hover)
            {
                root.color = "transparent"
            }


        }


    }

}
