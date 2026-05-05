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
    float dt = 0.05f;
    float g = 9.81f;
    float rho = 1.2f;
    float S = 0.785f; // Surface de la balle

    float fg = m_mass * g; // Poids

    // CORRECTION: std::abs(m_v) permet à la force de frottement de toujours s'opposer au sens du mouvement
    float ft = 0.5f * rho * std::abs(m_v) * m_v * S * m_coefficient_f;

    float acceleration = (fg - ft) / m_mass;

    m_v += acceleration * dt;
    m_Y -= 0.5f * m_v * dt * dt;
    m_simulated_time += dt;
    if (m_v > m_v_max) {
        m_v_max = m_v;
    }

    if (m_Y < 0) m_Y = 0;

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
