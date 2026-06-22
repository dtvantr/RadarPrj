import QtQuick
import QtQuick.Controls
import QtQuick.Layouts
import QtQuick.Window

Window {
    id: generatorWindow

    width: 320
    height: 240

    visible: false

    title: "Target Generator"

    color: "#202020"

    property bool running: false

    ColumnLayout {
        anchors.fill: parent
        anchors.margins: 20

        spacing: 15

        Text {
            text: "Target Generator"

            color: "lime"

            font.pixelSize: 22
            font.bold: true

            Layout.alignment: Qt.AlignHCenter
        }

        TextField {
            id: targetCountInput

            placeholderText: "Number of targets"

            text: "1000"

            validator: IntValidator {
                bottom: 1
                top: 100000
            }

            Layout.fillWidth: true
        }

        Button {
            text: running
                  ? "Running..."
                  : "Start"

            contentItem: Text {
                text: parent.text
                color: "black"
            }

            enabled: !running

            Layout.fillWidth: true

            onClicked: {
                var count =
                        parseInt(targetCountInput.text)

                if(isNaN(count) || count <= 0)
                    return

                processManager.startSender(count)

                running = true
            }
        }

        Button {
            text: "Stop"
            contentItem: Text {
                text: parent.text
                color: "black"
            }

            enabled: running

            Layout.fillWidth: true

            onClicked: {

                processManager.stopSender()

                running = false
            }
        }

        Rectangle {
        Layout.fillWidth: true
            height: 1

            color: "#404040"
        }

        Text {
            text: running
                  ? "Generator is sending targets"
                  : "Generator stopped"

            color: running
                   ? "lime"
                   : "gray"

            Layout.alignment: Qt.AlignHCenter
        }
    }
}