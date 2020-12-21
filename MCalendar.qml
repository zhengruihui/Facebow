import QtQuick 2.0

import QtQuick.Controls 1.4
import QtQuick.Controls.Styles 1.4

Item {

    property string dateValue

    Calendar{
        id: calendar
        anchors.topMargin: 0
        anchors.top: parent.bottom
        visible: true
        activeFocusOnTab: true
        onReleased: {
            text = date;
            text = text.substr(0, 10);
            dateValue = text;
            visible = true;
        }

    }

//    Button{
//        id: downBtn
//        width: 22
//        anchors.right: parent.right
//        anchors.rightMargin: 0
//        anchors.bottom: parent.bottom
//        anchors.bottomMargin: 0
//        anchors.top: parent.top
//        anchors.topMargin: 0
//        onClicked: calendar.visible = !calendar.visible
//    }

//    onDateValueChanged: {
//        text = dateValue;
//        calendar.selectedDate = dateValue;
//    }


}
