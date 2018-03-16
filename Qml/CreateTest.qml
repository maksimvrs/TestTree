import QtQuick 2.9
import QtQuick.Controls 2.2
import QtQuick.Layouts 1.3
import Test 1.0

Page {
    id: page

    title: qsTr("Test")

    ColumnLayout{
        anchors.fill: parent
        spacing: 20
        anchors.margins: 20

        Label {
            Layout.alignment: Qt.AlignCenter
            Layout.preferredWidth: 40
            Layout.preferredHeight: 40

            text: "Вопрос"

            font.pixelSize: 22
            horizontalAlignment: Text.AlignHCenter
        }

        TextField {
            id: questionInput

            Layout.alignment: Qt.AlignCenter
            Layout.fillWidth: true
            Layout.preferredHeight: 40

            text: test.question

            placeholderText: "Введите вопрос"
            horizontalAlignment: Text.AlignHCenter

            onFocusChanged: {
                test.question = questionInput.text
            }
        }

        Label {
            Layout.alignment: Qt.AlignCenter
            Layout.preferredWidth: 40
            Layout.preferredHeight: 40

            text: "Варианты ответов"

            font.pixelSize: 22
            horizontalAlignment: Text.AlignHCenter
        }

        ListView {
            id: list
            anchors.margins: 20

            Layout.alignment: Qt.AlignCenter
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
                    test.question = questionInput.text
                    test.addQuestion(text)
                }
            }
        }

        Test {
            id: test
        }

        RowLayout {
            Layout.alignment: Qt.AlignCenter

            spacing: 20
            anchors.margins: 20

            Button {
                id: back

                Layout.alignment: Qt.AlignCenter

                text: "Назад"
                onClicked: {
                    test.question = questionInput.text
                    test.back()
                }
            }

            Button {
                id: add

                Layout.alignment: Qt.AlignCenter

                text: "Добавить вариант"

                onClicked: {
                    inputAnswer.open()
                }

                InputAnswer {
                    id: inputAnswer

                    parent: page

                    onAccepted: {
                        test.addAnswer(text)

                    }
                }
            }

            Button {
                id: remove

                Layout.alignment: Qt.AlignCenter

                text: "Удалить вопрос"
                onClicked: {
//                    test.clear()
                }
            }
        }
    }
}
