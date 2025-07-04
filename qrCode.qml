import QtQuick 2.0

Item {
    width: 100; height: 100

    Rectangle {
        anchors.fill: parent
        objectName: "rect"
    }


    Image {
        id: qr_TopLeft
        anchors.fill: parent
        source: "qrc:/Files/qr-code_TL.png"
    }

    //    Image {
    //        id: qr_bottomRight
    //        source: "./Files/qr-qr-code_BR.png"
    //    }
}


