#ifndef MOBILEOBJECT_H
#define MOBILEOBJECT_H

#include <QDebug>
#include <QTimer>
#include <vector>

using namespace std;

//#include "geom.h"
#include "position.h"

#define LAST_COUNT 4

struct PositionTime
{
    Position pos;

    double time;
    PositionTime()
    {
        time = 0;
    }
};

class MobileObject : public QObject
{
    Q_OBJECT

public:
    explicit MobileObject();
    virtual void seenAt(vector<Position> p, double t, int c) = 0;

    bool isValid;

    Position pos;
    Position pos_predicted;
    double time;

    int camera_timeout;

    Position vel;

protected:
    PositionTime last_post[LAST_COUNT];
    PositionTime vel_post;
    void appendPostc(PositionTime &post);

//private:
    QTimer timer_seen;
    int    timer_seen_interval;
    QTimer timer_vel;
    int    timer_vel_interval;
    void   vel_calc();

private slots:
    void timer_seen_timeout();
    void timer_vel_timeout();

};

#endif // MOBILEOBJECT_H
