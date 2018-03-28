import QtQuick 2.0
import QtQuick.Controls 2.2
import QtQuick.Controls.Material 2.3
import QtQuick.Layouts 1.3

Page {
    id: resultEditor
    title: qsTr("Редактор результата")

    signal accepted()
    property string text: textEditor.text

    ColumnLayout {
        anchors.fill: parent
        spacing: 20
        anchors.margins: 20

        TextArea {
            id: textEditor
            Layout.fillWidth: true
            Layout.fillHeight: true
            textFormat: TextEdit.RichText
        }

        Button {
            id: ok
            Layout.fillWidth: true
            text: "Сохранить и выйти"
            onClicked: resultEditor.accepted()
        }
    }
}
