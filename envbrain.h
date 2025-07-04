#ifndef ENVBRAIN_H
#define ENVBRAIN_H

#include <QObject>
#include <QtCore>
#include <QTimer>
#include <opencv2/opencv.hpp>
#include <opencv2/cudaarithm.hpp>

#include "ui/worldmodel.h"

class EnvBrain : public QObject
{
    Q_OBJECT
public:
    explicit EnvBrain(WorldModel *wm = nullptr);//, QObject *parent);

    QList<QPoint> makeGridPoints(int nRows=1, int nCols=1, int dx=10, int dy=10, QPoint origin=QPoint(0,0));
    QList<QPoint> makeStarPoints(int nArms=5, int nLayers=10, int d=10, QPoint origin=QPoint(0,0));

private:
    int listInd = 0, nList = 500;
    int trace_rad = 10; // [px] radius of the circles as the radius of the trace on heatmap
    WorldModel* _wm;
    QTimer _timer, _timerNoise;


    cv::Mat heatMap, heatMapOnFrame, circTemp;
//    cv::Mat heatMapGray;
//    cv::cuda::GpuMat heatMapGPU;


    // Noise:
    QImage arenaImage;




public slots:
//    void updateTraces(QVector<QPoint> posVec);
    void refresh();
    void addNoise();
    void resetHeatMap();
    void updateNoiseProps(int time_interval);
    void connect_disconnect_add_noise(bool connect_bool);
    void update_centroid();
    void update_objects_to_draw();




signals:

};

#endif // ENVBRAIN_H
