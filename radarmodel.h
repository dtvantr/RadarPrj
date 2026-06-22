#ifndef RADARMODEL_H
#define RADARMODEL_H

#include <QObject>
#include <QVector>
#include <QVariantList>

#include "target.h"

class RadarModel : public QObject
{
    Q_OBJECT

    Q_PROPERTY(
        QVariantList targets
            READ targets
                NOTIFY targetsChanged
        )

    Q_PROPERTY(
        double heading
            READ heading
                WRITE setHeading
                    NOTIFY headingChanged
        )

    Q_PROPERTY(
        double alpha
            READ alpha
                WRITE setAlpha
                    NOTIFY alphaChanged
        )

    Q_PROPERTY(
        double radarLat
            READ radarLat
                CONSTANT
        )

    Q_PROPERTY(
        double radarLon
            READ radarLon
                CONSTANT
        )

public:

    explicit RadarModel(
        QObject *parent = nullptr
        );

    QVariantList targets() const;

    double heading() const;
    double alpha() const;

    double radarLat() const;
    double radarLon() const;

public slots:

    void setTargets(
        const QVector<Target> &targets
        );

    void updateTargets(
        const QList<Target> &targets
        );

    void setHeading(
        double heading
        );

    void setAlpha(
        double alpha
        );

signals:

    void targetsChanged();

    void headingChanged();

    void alphaChanged();

private:

    void updateVisibility();

private:

    QVector<Target> m_targets;

    double m_heading;
    double m_alpha;

    double m_radarLat;
    double m_radarLon;
};

#endif