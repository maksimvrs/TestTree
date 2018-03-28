import QtQuick 2.9
import QtQuick.Controls 2.2
import QtQuick.Controls.Material 2.3
import QtQuick.Layouts 1.3
import Test 1.0

Page {
    id: createTest
    title: qsTr("Редактор теста")

    ColumnLayout{
        anchors.fill: parent
        spacing: 20
        anchors.margins: 20

        Label {
            Layout.fillWidth: true
            Layout.preferredWidth: 40
            Layout.preferredHeight: 40
            text: "Вопрос"
            font.pixelSize: 22
            horizontalAlignment: Text.AlignHCenter
        }

        TextField {
            id: questionInput
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
            Layout.fillWidth: true
            Layout.preferredWidth: 40
            Layout.preferredHeight: 40
            text: "Варианты ответов"
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
                    test.question = questionInput.text
                    if (test.nextIsResult(text)) {
//                        test.addResult(text)
                    }
                    else {
                        test.addQuestion(text)
                    }
                }
            }
        }

        Test {
            id: test
        }

        RowLayout {
            Layout.fillWidth: true
            Layout.alignment: Qt.AlignHCenter | Qt.AlignVCenter
            spacing: 20
            anchors.margins: 20
            RoundButton {
                id: back
                height: width
                radius: width / 2
                Layout.alignment: Qt.AlignLeft
                text: "\u003C"
                font.pointSize: 24
                font.bold: true
                onClicked: {
                    test.question = questionInput.text
                    test.back()
                }
            }

            RoundButton {
                id: add
                Layout.alignment: Qt.AlignHCenter
                height: width
                radius: width / 2
                text: "\u002B"
                font.pointSize: 24
                font.bold: true
                onClicked: {
                    inputAnswer.open()
                }

                InputAnswer {
                    id: inputAnswer
                    parent: createTest
                    onAccepted: {
                        if (isQuestion) {
                            test.addAnswer(text)
                        }
                        else {
                            test.addResult(text)
                        }
                    }
                }
            }

            RoundButton {
                id: remove
                height: width
                radius: width / 2
                Layout.alignment: Qt.AlignRight
                text: "\u00D7"
                font.pointSize: 24
                font.bold: true
                onClicked: {
//                    test.clear()
                }
            }
        }
    }
}
