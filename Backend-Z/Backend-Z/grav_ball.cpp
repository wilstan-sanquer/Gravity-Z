#include "grav_ball.h"
#include <float.h>

grav_ball::grav_ball(float X,float Y,float mass,float coefficient_f){
    m_X=X;
    m_Y=Y;
    m_mass=mass;
    m_coefficient_f=coefficient_f;

}

float grav_ball::calcule_grav()
{
    float v=1;
    float g = 9.81;
    float fg = m_mass * g;
    float ft = 1/2 * 1.2 * v * v * 0.785 * m_coefficient_f ;
    v=ft-fg;
    m_Y = v  - m_Y ;
    return m_Y ;
}

float grav_ball::get_Y(){
    return m_Y ;
}
