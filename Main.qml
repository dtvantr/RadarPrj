import QtQuick
import QtQuick.Controls
import QtQuick.Layouts

ApplicationWindow {
    id: root

    visible: true

    width: 1400
    height: 900

    title: "Radar Tracking System"



    GeneratorWindow {
        id: generatorWindow
    }

    ColumnLayout {
        anchors.fill: parent

        spacing: 5

        Rectangle {
            Layout.fillWidth: true
            Layout.preferredHeight: 70

            color: "#202020"

            RowLayout {
                anchors.fill: parent
                anchors.margins: 10

                spacing: 10

                Label {
                    text: "Heading"
                    color: "white"
                }

                TextField {
                    id: headingField

                    text: radarModel.heading

                    validator: DoubleValidator {
                        bottom: 0
                        top: 360
                    }

                    Layout.preferredWidth: 100
                }

                Label {
                    text: "Alpha"
                    color: "white"
                }

                TextField {
                    id: alphaField

                    text: radarModel.alpha

                    validator: DoubleValidator {
                        bottom: 1
                        top: 360
                    }

                    Layout.preferredWidth: 100
                }

                Button {
                    text: "Apply"

                    onClicked: {
                        radarModel.heading =
                                parseFloat(headingField.text)

                        radarModel.alpha =
                                parseFloat(alphaField.text)
                    }
                }

                Item {
                    Layout.fillWidth: true
                }

                Button {
                    text: "Generator"

                    onClicked: {
                        generatorWindow.show()
                        generatorWindow.raise()
                        generatorWindow.requestActivate()
                    }
                }
            }
        }

        MapView {
            Layout.fillWidth: true
            Layout.fillHeight: true
        }
    }
}