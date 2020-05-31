import QtQuick 2.12
import QtQuick.Layouts 1.12
import QtQuick.Controls 2.12
import QtQuick.Controls.Imagine 2.12
import QtQuick.Window 2.0
import QtWebView 1.1
import com.mycompany.qmlcomponents 1.0

ApplicationWindow {

    visible: true
    width: 640
    height: 480
    id:root
    title: qsTr("Traffic system")
    objectName:"window1"
    readonly property color colorGlow: "#1d6d64"
    readonly property color colorWarning: "#d5232f"
    readonly property color colorMain: "#6affcd"
    readonly property color colorBright: "#ffffff"
    readonly property color colorLightGrey: "#888"
    readonly property color colorDarkGrey: "#333"

    readonly property int fontSizeExtraSmall: Qt.application.font.pixelSize * 0.8
    readonly property int fontSizeMedium: Qt.application.font.pixelSize * 1.5
    readonly property int fontSizeLarge: Qt.application.font.pixelSize * 2
    readonly property int fontSizeExtraLarge: Qt.application.font.pixelSize * 5

    Item {
        id: column
        anchors.fill: parent
        anchors.margins: 10
        Frame {
            id:navigation_bar
            anchors.left: parent.left
            anchors.leftMargin: 5
            anchors.rightMargin: 5
            anchors.top: parent.top
            anchors.right: parent.right
            //            anchors.bottom: mainRowLayout0.top
            height:button.height+20
            Item {
                id: row
                anchors.fill: parent
                Button {
                    id: pauseBtn
                    font.pixelSize: fontSizeExtraSmall
                    text: "Pause"
                    onClicked: cup_provider.pauseButtonClicked()// model.submit()
                }


                Button {
                    id: button
                    text: "new"
                    anchors.left: pauseBtn.right
                    anchors.leftMargin: 10
                    checkable: true
                    font.pixelSize: fontSizeExtraSmall
                }
                Item{
                    anchors.leftMargin: 10
                    anchors.left: button.right
                    anchors.bottom: button.bottom
                    anchors.right: parent.right
                    anchors.top:button.top

                    ComboBox {

                        id: cameraCB
                        font.pixelSize: fontSizeExtraSmall
                        anchors.fill: parent
                        textRole: qsTr("")

                        model: cam_info_provider.names
                        currentIndex: cam_info_provider.selected
                        onCurrentIndexChanged:{
                            cam_info_provider.onSelectedChanged(cameraCB.currentIndex)
                        }

                        popup: Popup {

                            y:parent.height*2/3
                            width: cameraCB.width
                            implicitHeight: contentItem.implicitHeight
                            padding: 1

                            contentItem: ListView {
                                clip: true
                                implicitHeight: contentHeight
                                model: cameraCB.popup.visible ? cameraCB.delegateModel : null
                                currentIndex: cameraCB.highlightedIndex
                                section.delegate:Rectangle { color: "#000000"; radius: 0 }
                                highlight: Rectangle { color: "#000000"; radius: 0 }

//                                ScrollIndicator.vertical: ScrollIndicator { }
                            }
                            BorderImage {
                                source: "qrc:/imagine-assets/itemdelegate-background-pressed@2x.9.png"
                                width: parent.width; height: parent.height
                                border.left: 1; border.top: 1
                                border.right: 1; border.bottom: 1
                            }
                        }
                    }
                }

            }
        }
        Row {
            id: main_body
            objectName: "main_body"
            anchors.top:navigation_bar.bottom
            anchors.left: parent.left
            anchors.right: parent.right
            anchors.bottom: parent.bottom
            anchors.margins: 5
            spacing: 5



            Frame {
                state:"mid"
                property var width_pr: parent.width/2
                property var height_pr: parent.height
                Layout.margins: 5
                id: cam_frame
                objectName: "cam_frame"
                width: width_pr
                height: height_pr

                Item {
                    anchors.fill: parent
                    ImageItem {
                        id: imageViewer
                        objectName:"imageViewer"
                        anchors.centerIn: parent
                        image: {
                            update();
                            cup_provider.image
                        }
                        width: {
                            if((image_width * parent.height)/image_height <= parent.width)
                                (image_width * parent.height)/image_height
                            else if((image_height * parent.width)/image_width <= parent.height)
                                parent.width
                        }
                        height:{
                            if((image_width * parent.height)/image_height <= parent.width)
                                parent.height
                            else if((image_height * parent.width)/image_width <= parent.height)
                                (image_height * parent.width)/image_width
                        }

                        MouseArea {
                            anchors.fill: parent
                            onPositionChanged: {
                                console.log('DragChanged\t' + mouseX + "\t" +mouseY)
                            }
                        }

                    }


                }


                ToolButton {
                    property var source_pr : "qrc:/logos/expand.png"
                    background: border_toggle_cam
                    id: toggle_cam
                    Image{
                        id: cam_toggle_img
                        source: toggle_cam.source_pr
                        anchors.fill: parent
                        mipmap: true

                    }
                    height: {Math.min(Math.max(cam_frame.width_pr/8, 30), 50)}
                    width:  {Math.min(Math.max(cam_frame.width_pr/8, 30), 50)}
                    MouseArea{
                        clip: true
                        anchors.fill: parent
                        onClicked: {
                            onClicked: cam_frame.state = (cam_frame.state == "mid"? "min" : "mid")

                            if(cam_frame.state==="min"){
                                map_frame.state = "max";
                            }
                            else if(cam_frame.state=== "mid"){
                                map_frame.state = "mid"
                            }
                            else if(cam_frame.state==="max"){
                                map_frame.state = "min"
                            }

                            console.log(parent.availableHeight + parent.objectName + "\t" + parent.parent.objectName);
                        }
                    }
                    BorderImage {
                        id: border_toggle_cam
                        source: "qrc:/imagine-assets/button-background-checked@2x.9.png"
                        width: parent.width; height: parent.height
                        border.left: 5; border.top: 5
                        border.right: 5; border.bottom: 5

                    }

                }



                states: [
                    State {
                        name: "max"
                        PropertyChanges { target: cam_frame; width_pr:parent.width * 5/6;height_pr:parent.height;}
                        PropertyChanges { target: toggle_cam; source_pr:"qrc:/logos/resize.png";}
                    },
                    State {
                        name: "mid"
//                        PropertyChanges { target: cam_frame; width_pr:parent.width/2;height_pr:parent.height;} // why this has no effect i dont know
                        PropertyChanges { target: toggle_cam; source_pr:"qrc:/logos/resize.png";}
                    },
                    State {
                        name: "min"
                        PropertyChanges { target: cam_frame; width_pr:parent.width /6;height_pr:parent.height/3}
                        PropertyChanges { target: toggle_cam; source_pr:"qrc:/logos/expand.png";}
                    }
                ]

            }






            Frame {
                id:map_frame
                objectName: "map_frame"
                state:"mid"
                property var width_pr: parent.width/2
                property var height_pr:parent.height
                Layout.margins: 5
                width: width_pr
                height:height_pr


                WebView {
                    id: webView
                    width: parent.width
                    height: parent.height
                    Component.onCompleted: {

                        var resource = 'qrc:/map.html';

                        var xhr = new XMLHttpRequest;
                        xhr.open('GET', resource);
                        xhr.onreadystatechange = function() {
                            if (xhr.readyState === XMLHttpRequest.DONE) {
                                var response = xhr.responseText;
                                webView.loadHtml(response);
                            }
                        };
                        xhr.send();
                    }

                    onLoadingChanged:{
                        if(loadRequest.status == WebView.LoadSucceededStatus){
                            runJavaScript("initMap();")
                        }
                    }

                }


                ToolButton {
                    property var source_pr : "qrc:/logos/expand.png"
                    background: name
                    id: toggle_map
                    Image{
                        id: map_toggle_img
                        source: toggle_map.source_pr
                        anchors.fill: parent
                        mipmap: true

                    }
                    height: {Math.min(Math.max(map_frame.width_pr/8, 30), 50)}
                    width:  {Math.min(Math.max(map_frame.width_pr/8, 30), 50)}
                    MouseArea{
                        clip: true
                        anchors.fill: parent
                        onClicked: {
                            map_frame.state = (map_frame.state == "mid"? "min" : "mid");
                            if(map_frame.state==="min"){
                                cam_frame.state = "max";
                            }
                            else if(map_frame.state=== "mid"){
                                cam_frame.state = "mid"
                            }
                            else if(map_frame.state==="max"){
                                cam_frame.state = "min"
                            }
                            console.log(parent.availableHeight + parent.objectName + "\t" + parent.parent.objectName);
                        }
                    }
                    BorderImage {
                        id: name
                        source: "qrc:/imagine-assets/button-background-checked@2x.9.png"
                        width: parent.width; height: parent.height
                        border.left: 5; border.top: 5
                        border.right: 5; border.bottom: 5

                    }

                }

                states: [
                    State {
                        name: "max"
                        PropertyChanges { target: map_frame; width_pr:main_body.width * 5 /6;height_pr:main_body.height;}
                        PropertyChanges { target: toggle_map; source_pr:"qrc:/logos/resize.png";}
                    },
                    State {
                        name: "mid"
//                        PropertyChanges { target: map_frame; width_pr:main_body.width/2;height_pr:main_body.height;} // why this has no effect i dont know
                        PropertyChanges { target: toggle_map; source_pr:"qrc:/logos/resize.png";}
                    },
                    State {
                        name: "min"
                        PropertyChanges { target: map_frame; width_pr:main_body.width/6;height_pr:main_body.height/3;}
                        PropertyChanges { target: toggle_map; source_pr:"qrc:/logos/expand.png";}
                    }

                ]

            }
        }
    }
}






