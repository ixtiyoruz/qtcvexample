import QtQuick 2.12
import QtQuick.Window 2.12
import com.mycompany.qmlcomponents 1.0

Window {

    visible: true
    width: 640
    height: 480
    id:root
    title: qsTr("Hello World")
    objectName:"window1"
    Row{
        id:row1
        objectName:"row1"
        anchors.horizontalCenter: root.horizontalCenter
        anchors.verticalCenter: parent.verticalCenter
        Rectangle
        {

            width: root.width/2
            height: root.height
            anchors.verticalCenter: parent.verticalCenter
            color:"black"
            onScaleChanged: console.log("scale changed")
            id:imageRect

            ImageItem {
                id: imageViewer
                objectName:"imageViewer"
                width: {

                    if(parent.height < parent.width)
                        (parent.height/image_height) * image_width
                    else
                        parent.width
                }
                height:{
                    if(parent.height < parent.width)
                        parent.height
                    else
                        (parent.width/image_width) * image_height
                }
                anchors.centerIn: parent
                //source: "images/identicon.png"

            }
        }
        Rectangle
        {
            width: root.width/2
            height: root.height
            color:"red"
        }
    }
}
