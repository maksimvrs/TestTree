import QtQuick 2.9
import QtQuick.Controls 2.2
import QtQuick.Layouts 1.3
import Test 1.0

Page {
    id: runTest
    title: qsTr("Test")

    ColumnLayout{
        anchors.fill: parent
        spacing: 20
        anchors.margins: 20

        Label {
            id: question
            Layout.fillWidth: true
            Layout.preferredWidth: 40
            Layout.preferredHeight: 40
            text: test.question
            font.pixelSize: 22
            horizontalAlignment: Text.AlignHCenter
        }

        ListView {
            id: list
            anchors.margins: 20
            Layout.fillWidth: true
            Layout.fillHeight: true
            flickableDirection: Flickable.VerticalFlick
            boundsBehavior: Flickable.StopAtBounds
            model: test.answers
            delegate: Button {
                anchors.left: parent.left
                anchors.right: parent.right
                height: 40
                text: modelData
                onClicked: {
                    test.next(text)
                }
            }
        }

        Test {
            id: test
            onResult: root.stackView.push("Qml/Result.qml")
        }

        RowLayout {
            Layout.fillWidth: true
            Layout.alignment: Qt.AlignHCenter | Qt.AlignVCenter
            spacing: 20
            anchors.margins: 20
            Button {
                id: back
                Layout.alignment: Qt.AlignHCenter
                text: "Назад"
                onClicked: {
                    test.back()
                }
            }
        }
    }
}
