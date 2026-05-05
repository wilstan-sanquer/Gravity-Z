#include "grav_ball.h"
#include <float.h>
#include <QDateTime>
#include <QJsonDocument>   // Pour manipuler le document global
#include <QJsonObject>     // Pour les structures { "cle": "valeur" }
#include <QJsonArray>      // Si tu as des listes [ ... ]
#include <QJsonValue>      // Pour manipuler une donnée précise
#include <QJsonParseError> // TRES important pour savoir pourquoi ça crash


grav_ball::grav_ball(float X,float Y,float mass,float coefficient_f){
    m_X=X;
    m_Y=Y;
    m_mass=mass;
    m_coefficient_f=coefficient_f;
    m_time=QDateTime::currentSecsSinceEpoch();
}

float grav_ball::calcule_grav()
{

    float m_v=1;
    float g = 9.81;
    float fg = m_mass * g;
    float ft = 1/2 * 1.2 * m_v * m_v * 0.785 * m_coefficient_f ;
    m_v=ft-fg;
    m_Y = m_v  - m_Y ;
    if (m_v>m_v_max){
        m_v_max=m_v;
    }
    return m_Y ;
}

float grav_ball::get_Y(){
    return m_Y ;
}
QString grav_ball::grav_report(){
    float duree = (QDateTime::currentMSecsSinceEpoch() - m_time) / 1000.0f;
    float force_j = 0.5f * m_mass * m_v_max * m_v_max;

    QJsonObject dataObj;
    dataObj["total_duration_s"] = duree;
    dataObj["max_speed_ms"]     = m_v_max;
    dataObj["contact_force_j"]  = force_j;

    QJsonObject jsonObj;
    jsonObj["id"]     = 1;
    jsonObj["status"] = "floor";
    jsonObj["data"]   = dataObj;

    return QString(QJsonDocument(jsonObj).toJson(QJsonDocument::Indented));
}
