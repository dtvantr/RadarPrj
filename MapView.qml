import QtQuick
import QtLocation
import QtPositioning

Item {
    implicitWidth: 800
    implicitHeight: 600

    Plugin {
        id: osmPlugin
        name: "osm"
    }

    Map {
        id: map

        property real sweepOffset: -radarModel.alpha / 2

        NumberAnimation on sweepOffset {
            from: -radarModel.alpha / 2
            to: radarModel.alpha / 2

            duration: 2000
            loops: Animation.Infinite

            running: true
        }

        anchors.fill: parent
        plugin: osmPlugin

        zoomLevel: 17

        center: QtPositioning.coordinate(
                    radarModel.radarLat,
                    radarModel.radarLon)

        // RADAR RANGE

        MapCircle {
            center: QtPositioning.coordinate(
                        radarModel.radarLat,
                        radarModel.radarLon)

            radius: 250

            color: "#1500FF00"
            border.color: "green"
            border.width: 2
        }

        // RADAR SECTOR

        MapPolygon {
            id: radarSector

            color: "#3000FF00"
            border.color: "lime"
            border.width: 2

            path: createSector()
        }

        MapPolyline {
            id: sweepLine

            line.width: 4
            line.color: "lime"

            path: createSweepLine()

            z: 9998
        }

        // RADAR CENTER

        MapQuickItem {
            coordinate: QtPositioning.coordinate(
                            radarModel.radarLat,
                            radarModel.radarLon)

            anchorPoint.x: 10
            anchorPoint.y: 10

            z: 10000

            sourceItem: Item {
                width: 20
                height: 20

                Rectangle {
                    anchors.centerIn: parent
                    width: 14
                    height: 14
                    radius: 7
                    color: "blue"
                    border.color: "white"
                    border.width: 2
                }

                Rectangle {
                    anchors.centerIn: parent
                    width: 3
                    height: 20
                    color: "white"
                    rotation: radarModel.heading
                }
            }
        }

        // TARGETS

        MapItemView {
            model: radarModel.targets

            delegate: MapQuickItem {

                coordinate: QtPositioning.coordinate(
                                modelData.latitude,
                                modelData.longitude)

                // visible: modelData.visible

                anchorPoint.x: 8
                anchorPoint.y: 8

                z: 9999

                sourceItem: Column {
                    spacing: 2

                    Rectangle {
                        width: 8
                        height: 8
                        radius: 4

                        color: modelData.visible
                                   ? "red"
                                   : "gray"

                        border.color: "white"
                        border.width: 1
                    }

                    Text {
                        text: modelData.id
                        color: "red"
                        font.pixelSize: 10
                        anchors.horizontalCenter: parent.horizontalCenter
                    }
                }
            }
        }

        // CREATE SECTOR FUNCTION

        function createSector()
        {
            var points = []

            var lat = radarModel.radarLat
            var lon = radarModel.radarLon

            var radius = 250

            // center
            points.push(QtPositioning.coordinate(lat, lon))

            var start = radarModel.heading - radarModel.alpha / 2
            var end   = radarModel.heading + radarModel.alpha / 2

            for (var angle = start; angle <= end; angle += 2)
            {
                var rad = angle * Math.PI / 180

                var dx = radius * Math.cos(rad)
                var dy = radius * Math.sin(rad)

                var pointLat =
                        lat + dy / 111320.0

                var pointLon =
                        lon + dx /
                        (111320.0 * Math.cos(lat * Math.PI / 180))

                points.push(
                    QtPositioning.coordinate(pointLat, pointLon)
                )
            }

            // close polygon
            points.push(QtPositioning.coordinate(lat, lon))

            return points
        }

        function createSweepLine()
        {
            var lat = radarModel.radarLat
            var lon = radarModel.radarLon

            var radius = 250

            var angle =
                    radarModel.heading + sweepOffset

            var rad = angle * Math.PI / 180

            var dx = radius * Math.cos(rad)
            var dy = radius * Math.sin(rad)

            var pointLat =
                    lat + dy / 111320.0

            var pointLon =
                    lon + dx /
                    (111320.0 * Math.cos(lat * Math.PI / 180))

            return [
                QtPositioning.coordinate(lat, lon),
                QtPositioning.coordinate(pointLat, pointLon)
            ]
        }

        Component.onCompleted: {
            radarSector.path = createSector()
            sweepLine.path = createSweepLine()
        }

        // UPDATE SECTOR KHI ĐỔI HEADING / ALPHA

        Connections {
            target: radarModel

            function onHeadingChanged() {
                radarSector.path = map.createSector()
                sweepLine.path = map.createSweepLine()
            }

            function onAlphaChanged() {
                radarSector.path = map.createSector()
                sweepLine.path = map.createSweepLine()
            }
        }

        onSweepOffsetChanged: {
            sweepLine.path = createSweepLine()
        }
    }
}