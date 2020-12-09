import QtQuick 2.0
import QtQuick.Controls 1.4
import QtQuick.Controls.Styles 1.4
Item {

    Button
    {
        id: root_Button
        property string nomerPic: "qrc:/Images/001.png"
        property string hoverPic: "qrc:/Images/002.png"
        property string pressPic: "qrc:/Images/003.png"
        style: ButtonStyle
        {
            background:Rectangle
            {
                implicitHeight:root_Button.height
                implicitWidth:root_Button.width
                Image
                {
                    anchors.fill: parent
                    source:
                    {
                        if(control.hovered)
                        {
                            if(control.pressed)
                            {
                                pressPic
                            }
                            else
                            {
                                hoverPic
                            }
                        }
                        else
                        {
                            nomerPic
                        }
                    }
                }
            }
        }
    }

}
