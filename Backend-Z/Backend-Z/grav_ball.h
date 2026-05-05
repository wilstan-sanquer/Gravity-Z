#ifndef GRAV_BALL_H
#define GRAV_BALL_H
#include <QString>

class grav_ball
{
public:
    grav_ball(float X,float Y,float mass,float coefficient_f );
    float calcule_grav ();
    float get_Y();
    QString grav_report();
    float get_v();
private :
    float m_X;
    float m_Y;
    float m_mass;
    float m_coefficient_f ;
    float m_simulated_time;
    float m_v_max;
    float m_v;
};

#endif // GRAV_BALL_H
