import QtQuick 2.9
import QtQuick.Controls 2.2
import QtQuick.Controls.Material 2.3
import QtQuick.Layouts 1.3
import Test 1.0

Page {
    id: runTest
    title: qsTr("Тест")

    ColumnLayout{
        anchors.fill: parent
        spacing: 20
        anchors.margins: 20

        Label {
            id: question
            Layout.fillWidth: true
            clip: true
            wrapMode: Text.WordWrap
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

        Result {
            id: resultPage
            text: test.result
            StackView.onRemoved: {
                test.back()
            }
        }

        Test {
            id: test
            onResultOpen: root.push(resultPage)
        }

        RowLayout {
            Layout.fillWidth: true
            Layout.alignment: Qt.AlignHCenter | Qt.AlignVCenter
            spacing: 20
            anchors.margins: 20
            Button {
                id: back
                Material.background: "#ffa000"
                Layout.alignment: Qt.AlignHCenter
                text: "Назад"
                onClicked: {
                    test.back()
                }
            }
        }
    }
}
