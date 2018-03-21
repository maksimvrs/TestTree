import QtQuick 2.10
import QtQuick.Controls 2.3
import QtQuick.Controls.Material 2.3

ApplicationWindow {
    id: root
    visible: true
    width: 640
    height: 480
    title: qsTr("Test")

    function push(item) {
        stackView.push(item)
    }

    header: ToolBar {
        contentHeight: toolButton.implicitHeight

        ToolButton {
            id: toolButton
            text: stackView.depth > 1 ? "\u25C0" : "\u2630"
            font.pixelSize: Qt.application.font.pixelSize * 1.6
            onClicked: {
                if (stackView.depth > 1) {
                    stackView.pop()
                } else {
                    drawer.open()
                }
            }
        }

        Label {
            text: stackView.currentItem.title
            anchors.centerIn: parent
        }
    }

    Drawer {
        id: drawer
        width: root.width * 0.66
        height: root.height

        Column {
            anchors.fill: parent

            ItemDelegate {
                text: qsTr("Тест 1 создать")
                width: parent.width
                onClicked: {
                    stackView.push("Qml/CreateTest.qml")
                    drawer.close()
                }
            }

            ItemDelegate {
                text: qsTr("Тест 1 пройти")
                width: parent.width
                onClicked: {
                    stackView.push("Qml/RunTest.qml")
                    drawer.close()
                }
            }
        }
    }

    StackView {
        id: stackView
        initialItem: "Qml/StartPage.qml"
        anchors.fill: parent
    }
}
