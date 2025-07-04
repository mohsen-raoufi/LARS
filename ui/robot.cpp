#include "robot.h"
#define NO_CAMERA -1

Robot::Robot() :
    MobileObject()
{
}

void Robot::seenAt(vector<Position> p, double t, int c)
{
    if(p.size()<1) return;
    //    isValid = true;
    timer_seen.start(timer_seen_interval); //restart

    PositionTime ans;
    ans.time = t;

    Vector2D buff;
    int min_i = 0;
    buff = p[min_i].loc - pos_predicted.loc ;
    double min_d = buff.length();
    for(size_t i=0; i < p.size(); i++)
    {
        buff = p[i].loc - pos_predicted.loc ;
        double d = buff.length();
        if(d < min_d)
        {
            min_d = d;
            min_i = i;
        }
    }

    ans.pos.loc = p[min_i].loc;
    ans.pos.dir = p[min_i].dir;


    time = ans.time;
    pos = ans.pos;
    vel_calc();
    isValid = true ;
    camera_timeout = 0;

}
