import QtQuick 2.0
import QtQuick.Controls 2.2
import QtQuick.Layouts 1.3

Page {
    id: resultEditor
    title: qsTr("Stack")

    ColumnLayout {
        anchors.fill: parent
        spacing: 20
        anchors.margins: 20

        signal accepted()
        property string text: textEditor.text

        TextEdit {
            id: textEditor
            Layout.fillWidth: true
            Layout.fillHeight: true
        }

        Button {
            id: ok
            Layout.fillWidth: true
            onClicked: accepted()
        }
    }
}
