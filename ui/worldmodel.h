#ifndef WORLDMODEL_H
#define WORLDMODEL_H

#include <QList>
#include <QDebug>
#include <QColor>
#include <QPainter>
#include <opencv2/opencv.hpp>

#include <boost/graph/adjacency_list.hpp>
#include <boost/graph/graph_traits.hpp>
#include <boost/graph/graphviz.hpp>

#include <igraph/igraph.h>

//// Define the graph type using Boost adjacency_list
//typedef boost::adjacency_list<boost::vecS, boost::vecS, boost::undirectedS> Graph;
//typedef boost::graph_traits<Graph>::vertex_descriptor Vertex;
//typedef boost::graph_traits<Graph>::edge_descriptor Edge;

enum BrushType {
    GRADIENT,
    IMAGE,
//    VIDEO,
    SOLID,
    NULL_BRUSH
};


struct wmCircle {
    QPoint pos;
    int r;
    QColor col;
    int thickness;
    std::string text;
    bool transparent;
};



class WorldModel
{
public:
    explicit WorldModel();
    double time;

    //    QPoint fieldTL = QPoint(0,0);
    //    QSize fieldSize = QSize(1000,1000);

    // to put the wood margins in the shade
#ifdef FOR_KILOBOT
    QPoint fieldTL = QPoint(390,0);
    QSize fieldSize = QSize(1000,1200);
#else
    QPoint fieldTL = QPoint(135,120);
    QSize fieldSize = QSize(1000,1000);
#endif


    // Markers Pos in Projected Space: set 1
    //    QPoint marker0_pos = QPoint(1100,500);
    //    QPoint marker1_pos = QPoint(1100,1000);
    //    QPoint marker2_pos = QPoint(1600,500);
    //    QPoint marker3_pos = QPoint(1600,1000);

#ifdef FOR_KILOBOT
    int arenaWidth = 1030;
    int arenaHeight = 1030;
    QPoint marker0_pos = QPoint(395, 0);
//    QPoint marker0_pos = QPoint(1100+50, 300);
#else

    // Largest arena for THYMIO LARGER
    int arenaWidth = 1560;
    int arenaHeight = 930;
    QPoint marker0_pos = QPoint(140, 140);


//     Largest arena for THYMIO
//        int arenaWidth = 1350;
//        int arenaHeight = 700;
//        QPoint marker0_pos = QPoint(340, 300);
#endif

    QPoint marker1_pos = QPoint(marker0_pos.x(), marker0_pos.y() + arenaHeight);
    QPoint marker2_pos = QPoint(marker0_pos.x() + arenaWidth, marker0_pos.y());
    QPoint marker3_pos = QPoint(marker0_pos.x() + arenaWidth, marker0_pos.y() + arenaHeight);

    int marker_length = 50;
    QPoint marker0_BR  = QPoint(marker0_pos + QPoint(marker_length,marker_length));

    QRect expFieldRect;
    QPolygon expFieldPoints;
    BrushType expFieldType, robBrushType;

    int noiseTileNo = 50, noiseTimeIntv = -1;
    double noiseStrength = 0.2;

    QPixmap arenaImg, arenaProcessedImg;

    QRect insideRect = QRect(0,0,0,0);
    QRect outsideRect;

    cv::Size capSize = cv::Size(960,600); //  cv::Size(600,400);

    QList<QPoint> pointsToDraw;

    QPoint centroid;

    QList<QPoint> rob_Type0_pos;
    QList<bool> rob_toEnlight;

    QVector<QPoint> kiloPosVec, kiloPosVecOnFrame;
    QVector<cv::Scalar> kiloColor;
    QVector<QVector <QPoint>> rob_traces;

    QBrush *brush_robotCustom_0 = new QBrush(QColor::fromRgb(3, 252, 248), Qt::SolidPattern);
    bool boolNullBrushForRobots = false;
    int robRad = 50;

    QPoint ballPos = QPoint(0,0);
    QPointF ballVel = QPointF(1.0,1.0);
    int ballSpeed = 10, ballRad = 60;

//    Graph robot_graph;

    // Pos@Cap = ScaleArena2Cap * Pos@Arena + biasArena2Cap
    //    QVector2D<float> scaleArena2Cap;
    //    QVector2D<float> biasArena2Cap;


    // Painter Bias (TOP LEFT)
    int bias_X = 0, bias_Y = 0;

    // Field HSV
    QColor fieldCol;
    //    int fieldH = 0, fieldS = 0, fieldV = 0;

    bool loadImgBackground;

    void setFieldColorHSV(int H, int S, int V);
    void setFieldColor(QColor color);
    void setFieldSize(QSize size);
    void setRobotCustomColor(QColor color);
    void setNullRobotCustomBrush(bool boolNullBrush);

//    void create_empty_graph(QList <QPoint> points);

    bool drawTrace = false, drawBoundary = true, drawHeatMap = false, drawColCircles = false, drawRobCircles = false, drawInitPoint = false;
    bool drawNetwork = false, drawVoronoii = false, drawCentroid = false, drawWithColors = true, spatialNetwork=false, drawBall=false;

    int dummy_var = 0, dummy_var2=0;

    QVector <wmCircle> circles2Draw;

    cv::Mat heatMap;

public slots:
    //    void setFieldH(int H);
    //    void setFieldV(int V);

    //    Knowledge *kn;

    //----Graphical Debug-----
    //    QList<Segment2D> voronoi;
    //    bool showVoronoi;
    //    QList<Vector2D> selected;

    //    //---UDP 2 Matlab
    //    bool sendUDP;
    //    int indexOfUDP;
    //    QString whichUDP;

};

#endif // WORLDMODEL_H
