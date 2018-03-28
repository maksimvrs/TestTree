import QtQuick 2.0
import QtQuick.Controls 2.2
import QtQuick.Controls.Material 2.3
import QtQuick.Layouts 1.3

Page {
    title: qsTr("Тест в разработке")

    RowLayout {
        anchors.fill: parent

        Label {
            Layout.fillWidth: true
            text: qsTr("На данный момент тест находится в разработке.")
            anchors.centerIn: parent
            horizontalAlignment: Text.AlignHCenter
            wrapMode: Text.WordWrap
        }
    }
}
