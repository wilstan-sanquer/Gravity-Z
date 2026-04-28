#ifndef GRAV_BALL_H
#define GRAV_BALL_H

class grav_ball
{
public:
    grav_ball(float X,float Y,float mass,float coefficient_f );
    float calcule_grav ();
    float get_Y();
private :
    float m_X;
    float m_Y;
    float m_mass;
    float m_coefficient_f ;
};

#endif // GRAV_BALL_H
