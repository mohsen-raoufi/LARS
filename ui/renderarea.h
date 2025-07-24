#ifndef RENDERAREA_H
#define RENDERAREA_H

#include <QWidget>
#include <QPainter>
#include <QTimer>


#include "ui/worldmodel.h"

#include "geom/voronoiGenerator.h"

#define Pi 3.141592653589793238

#define WORLD_SCALE 10
#define DOUBLE_CENTER_X 476
#define DOUBLE_CENTER_Y 319
#define SINGLE_CENTER_X 370
#define SINGLE_CENTER_Y 270

#define ROBOT_R 9
#define ROBOT_D 18

#define BALL_R 4
#define NODE 4

#define ANGLE_TO_CHORD(a) 16*((a)*180/Pi+40), 16*280


class RenderArea : public QWidget
{
    Q_OBJECT
public:
    explicit RenderArea(WorldModel *wm);

    /**
     * @brief Start playing a video from the given file path.
     * @param filename Path to the video file.
     */
    void playVideo(const std::string& filename);
    void stopVideo();

private:
    WorldModel* _wm;
    QBrush *brush_field, *brush_insideRect, *brush_yrobot, *brush_yrobot_MT, *brush_brobot, *brush_test;
    QBrush *brush_initPoints, *brush_initPoints2;
    QTimer _timer; //, _noiseTimer;
    int bias_X, bias_Y;
    QPen *pen_insideRect, *pen_RobCust1, *pen_pnts2Draw, *pen_circ2Draw, *pen_network, *pen_voronoii, *pen_tracePnts;
    QPixmap marker0, marker1, marker2, marker3;
    QPixmap arenaImg, SCIoIImg, webPage, centroidImage, ballImage;
    QRadialGradient *radGradient, *radGradientRob;
    QRect *expArena;
    int robRad;
    cv::Mat heatMapTemp;
    QImage heatMapQImage;
    QRect bigFieldRect;
    QPolygon bigFieldPoly;
    QImage arenaImage;
    bool refreshNoiseBool = false;
    voronoiGenerator VoronoiiGen;
    boost::polygon::voronoi_diagram<double> vd;
    int centroid_width = 30;
    int index_node_to_light_net = -1;
    igraph_t graph;
    igraph_vector_int_t edges;

    // Video playback support
    cv::VideoCapture videoCapture;
    QImage videoFrame;
    cv::Mat frameFrame_CV;
    QTimer* videoTimer;
    bool videoPlaying;

signals:

public slots:
    void refresh();
    void paintEvent(QPaintEvent *);
    void updatePainters();
    void updateGradientPainter();
    /**
     * @brief Grab the next frame from the video and update the display.
     */
    void grabVideoFrame();

protected:
    int getMostCentralNode(const igraph_t &graph);
};

#endif // RENDERAREA_H
