#include "radarmodel.h"
#include "radarlogic.h"

#include <QVariantMap>
#include <cmath>

RadarModel::RadarModel(QObject *parent)
    : QObject(parent),
    m_heading(45.0),
    m_alpha(60.0),
    m_radarLat(21.0285),
    m_radarLon(105.8542)
{
    Target t;

    t.id = 1;

    t.x = 100;
    t.y = 50;

    t.type = TargetType::None;

    t.latitude =
        m_radarLat +
        t.y / 111320.0;

    t.longitude =
        m_radarLon +
        t.x /
            (
                111320.0 *
                std::cos(
                    m_radarLat *
                    M_PI / 180.0
                    )
                );

    t.visible = true;

    m_targets.append(t);
}

QVariantList RadarModel::targets() const
{
    QVariantList list;

    for(const auto &t : m_targets)
    {
        QVariantMap item;

        item["id"] = t.id;

        item["x"] = t.x;
        item["y"] = t.y;

        item["latitude"] = t.latitude;
        item["longitude"] = t.longitude;

        item["visible"] = t.visible;

        item["type"] = static_cast<int>(t.type);

        list.append(item);
    }

    return list;
}

double RadarModel::heading() const
{
    return m_heading;
}

double RadarModel::alpha() const
{
    return m_alpha;
}

double RadarModel::radarLat() const
{
    return m_radarLat;
}

double RadarModel::radarLon() const
{
    return m_radarLon;
}

void RadarModel::setHeading(double heading)
{
    if (qFuzzyCompare(m_heading, heading))
        return;

    m_heading = heading;

    updateVisibility();

    emit headingChanged();
    emit targetsChanged();
}

void RadarModel::setAlpha(double alpha)
{
    if (qFuzzyCompare(m_alpha, alpha))
        return;

    m_alpha = alpha;

    updateVisibility();

    emit alphaChanged();
    emit targetsChanged();
}

void RadarModel::setTargets(
    const QVector<Target> &targets
    )
{
    m_targets = targets;

    for(auto &t : m_targets)
    {
        t.latitude =
            m_radarLat +
            t.y / 111320.0;

        t.longitude =
            m_radarLon +
            t.x /
                (
                    111320.0 *
                    std::cos(
                        m_radarLat *
                        M_PI / 180.0
                        )
                    );
    }

    // qDebug() << "RadarModel setTargets:" << targets.size();

    updateVisibility();

    emit targetsChanged();
}

void RadarModel::updateTargets(
    const QList<Target> &targets
    )
{
    m_targets.clear();

    for(auto t : targets)
    {
        t.latitude =
            m_radarLat +
            t.y / 111320.0;

        t.longitude =
            m_radarLon +
            t.x /
                (
                    111320.0 *
                    std::cos(
                        m_radarLat *
                        M_PI / 180.0
                        )
                    );

        m_targets.append(t);
    }

    updateVisibility();

    emit targetsChanged();
}

void RadarModel::updateVisibility()
{
    for(auto &t : m_targets)
    {
        t.visible =
            RadarLogic::isInsideSector(
                t.x,
                t.y,
                250.0,
                m_heading,
                m_alpha
                );
    }
}