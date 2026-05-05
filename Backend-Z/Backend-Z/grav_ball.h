#ifndef GRAV_BALL_H
#define GRAV_BALL_H
#include <QDateTime>
#include<QString>
class grav_ball
{
public:
    grav_ball(float X,float Y,float mass,float coefficient_f );
    float calcule_grav ();
    float get_Y();
    QString grav_report();
private :
    float m_X;
    float m_Y;
    float m_mass;
    float m_coefficient_f ;
    qint64 m_time;
    float m_v_max;
    float m_v;


};

#endif // GRAV_BALL_H
