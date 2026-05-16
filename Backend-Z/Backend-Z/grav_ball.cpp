#include "grav_ball.h"
#include <QJsonDocument>
#include <QJsonObject>
#include <cmath> // CORRECTION: Pour utiliser std::abs()

grav_ball::grav_ball(float X,float Y,float mass,float coefficient_f){
    m_X=X;
    m_Y=Y;
    m_mass=mass;
    m_coefficient_f=coefficient_f;

    m_simulated_time = 0.0f;
    m_v = 0.0f;
    m_v_max = 0.0f;
}

float grav_ball::calcule_grav()
{
    const float dt    = 1.0f / 60.0f;
    const float g     = 9.81f;
    const float rho   = 1.2f;
    const float S     = 0.785f;
    const float SCALE = 100.0f;

    float ft = 0.0f;
    if (m_v != 0.0f)
        ft = 0.5f * rho * m_v * m_v * S * m_coefficient_f
             * (-1.0f) * m_v / std::abs(m_v);

    float acceleration = ((m_mass * g) - ft) / m_mass;
    m_v              += acceleration * dt;
    m_Y              += m_v * (SCALE * dt);
    m_simulated_time += dt;

    if (std::abs(m_v) > m_v_max)
        m_v_max = std::abs(m_v);

    return m_Y;
}

float grav_ball::get_Y(){
    return m_Y ;
}

QString grav_ball::grav_report(){
    float force_j = 0.5f * m_mass * m_v_max * m_v_max;

    QJsonObject dataObj;
    dataObj["total_duration_s"] = m_simulated_time;
    dataObj["max_speed_ms"]     = m_v_max;
    dataObj["contact_force_j"]  = force_j;

    QJsonObject jsonObj;
    jsonObj["id"]     = 1;
    jsonObj["status"] = "floor";
    jsonObj["data"]   = dataObj;

    return QString(QJsonDocument(jsonObj).toJson(QJsonDocument::Indented));
}

float grav_ball::get_v()
{
    return m_v;
}
