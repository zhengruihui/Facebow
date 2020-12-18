import QtQuick 2.0
import QtGraphicalEffects 1.15
import QtQuick 2.15
import QtQuick3D 1.15
import QtQuick.Controls 2.14
Item {

    Rectangle{
        id: editDialog
        anchors.centerIn: parent

        width: parent.width
        height: parent.height
        color: "#FFFFFF"
        border.color: "#DDE2E7"
        radius: 5




        Button{
            text: qsTr("确定")
            x: 306
            y: 429
            width: 100
            height: 28
            background: Rectangle{
                anchors.centerIn: parent
                width: parent.width
                height: parent.height

                color: "#0DAF9D"
                border.color: "#DDE2E7"
                radius: 14

            }
            onPressed: {
                console.log("xx")


            }

        }

        Button{
            text: qsTr("取消")
            x: 426
            y: 429
            width: 100
            height: 28
            background: Rectangle{
                anchors.centerIn: parent
                width: parent.width
                height: parent.height

                color: "#0DAF9D"
                border.color: "#DDE2E7"
                radius: 14

            }
            onPressed: {


            }

        }





    }
    DropShadow {
        id:dialogShadow
        anchors.fill: editDialog
        transparentBorder: true
        horizontalOffset: 1
        verticalOffset: 0
        radius: 30
        samples: 61
        color: "#aa000000"
        spread: 0.0
        source: editDialog
    }

}
