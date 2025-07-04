#ifndef ROBOT_H
#define ROBOT_H

#include "mobileobject.h"
//#include "controller.h"
//#include "outputbuffer.h"
#include "QDebug"

class Robot : public MobileObject
{
    Q_OBJECT

public:
    Robot();
    virtual void seenAt(vector<Position> p, double t, int c);
};

#endif // ROBOT_H
