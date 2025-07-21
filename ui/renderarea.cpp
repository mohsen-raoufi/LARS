/**
 * @file renderarea.cpp
 * @brief Implementation of the RenderArea class for rendering graphical elements in the UI.
 *
 * This file contains the implementation of the RenderArea class, which is responsible for rendering
 * various graphical elements such as markers, gradients, images, and shapes on the UI. It utilizes
 * the Qt framework for rendering and painting operations.
 *
 * The RenderArea class is initialized with a WorldModel object, which provides the necessary data
 * for rendering. The class handles the following functionalities:
 * - Loading and setting up various graphical assets such as markers, images, and brushes.
 * - Handling paint events to draw different elements on the UI.
 * - Updating painters and gradients based on the WorldModel data.
 * - Managing timers for periodic updates and refreshes.
 *
 * The class supports rendering of various elements including:
 * - Background field
 * - Markers
 * - SCIoI Logo
 * - Initial points
 * - Heat maps
 * - Centroids
 * - Balls
 * - Robot circles
 * - Collective circles
 * - Voronoi diagrams
 * - Network connections
 * - Traces
 *
 * The class also provides methods for updating painters and gradient painters based on the current
 * state of the WorldModel.
 *
 * @note The class contains several commented-out sections of code that can be enabled for additional
 * functionalities or debugging purposes.
 *
 * @see renderarea.h
 */


#include "renderarea.h"
#include <QDebug>

#include <opencv2/opencv.hpp>
#include <QTimer>

/**
 * @brief Constructs a RenderArea widget for rendering graphical elements in the UI.
 *
 * Initializes the RenderArea, setting up graphical assets, brushes, pens, and timers
 * for periodic updates. Loads resources such as markers, logo, arena images, and custom brushes.
 * Associates the provided WorldModel instance for access to rendering data.
 * Also sets up gradients, pens, and event connections needed for UI drawing and updates.
 *
 * @param wm Pointer to the WorldModel providing data and state for rendering.
 */
RenderArea::RenderArea(WorldModel *wm) :
    QWidget()
{
    _wm = wm;
    //    qDebug() << "hey there! I am running RenderArena";
    //    this->setSizePolicy(QSizePolicy::Expanding);
    //    this->resize(1920, 1080);
    //    this->update();

    this->bias_X = _wm->bias_X;
    this->bias_X = _wm->bias_Y;

    // Video playback support
    videoTimer = new QTimer(this);
    connect(videoTimer, &QTimer::timeout, this, &RenderArea::grabVideoFrame);
    videoPlaying = false;

    marker0 = QPixmap(":/Files/marker0.png");
    marker1 = QPixmap(":/Files/marker1.png");
    marker2 = QPixmap(":/Files/marker2.png");
    marker3 = QPixmap(":/Files/marker3.png");

    //    arenaImg = QPixmap(":/Files/arena.png");

    SCIoIImg = QPixmap(":/Files/SCIoI_Logo.png");

    webPage = QPixmap(":/Files/webpage.png");

    centroidImage = QPixmap(":/Files/centroid.png");

    ballImage = QPixmap(":/Files/ball.png");

    brush_field = new QBrush(_wm->fieldCol);
    brush_insideRect = new QBrush(Qt::NoBrush); //new QBrush(QColor::fromRgb(245, 206, 66),Qt::Dense5Pattern);//SolidPattern);
    pen_insideRect = new QPen(QColor::fromRgb(245, 206, 66), 3);//, Qt::Dense5Pattern);
    brush_yrobot = new QBrush(QColor::fromRgb(255,255,0),Qt::SolidPattern);
    brush_initPoints = new QBrush(QColor::fromRgb(255,255,0),Qt::SolidPattern);
    brush_initPoints2 = new QBrush(QColor::fromRgb(0,255,0),Qt::SolidPattern);

    //    brush_yrobot_MT = new QBrush(QColor::fromRgb(255,255,0),Qt::NoBrush);
    pen_pnts2Draw = new QPen(QColor::fromRgb(255,255,0), 0.5, Qt::DotLine);
    pen_circ2Draw = new QPen(QColor::fromRgb(255,0,0), 1.5, Qt::DotLine);
    //    pen_network = new QPen(QColor::fromRgb(255,255,255), 0.5, Qt::SolidLine); // White
    pen_network = new QPen(QColor::fromRgb(21, 255, 0), 1.25, Qt::SolidLine); // White
    //    pen_voronoii = new QPen(QColor::fromRgb(0,0,0), 1.5, Qt::SolidLine); // black
    pen_voronoii = new QPen(QColor::fromRgb(183, 233, 214), 1.5, Qt::SolidLine); // light cyan

    //    pen_RobCust1 = new QPen(QColor::fromRgb(255,255,0), 1.0, Qt::DotLine);
    pen_RobCust1 = new QPen(QColor::fromRgb(255,255,0), 1.0, Qt::SolidLine);

    //    pen_tracePnts = new QPen(QColor::fromRgb(0,152,255), 1.0, Qt::SolidLine);
    pen_tracePnts = new QPen(QColor::fromRgb(0,255,0), 1.0, Qt::SolidLine);

    brush_brobot = new QBrush(QColor::fromRgb(50,50,255),Qt::SolidPattern);
    brush_test = _wm->brush_robotCustom_0;//new QBrush(QColor::fromRgb(3, 252, 248),Qt::SolidPattern);
    //    brush_test = new QBrush(Qt::NoBrush);

    updateGradientPainter();

    //    int arenaHalfWidth = (int) ((_wm->marker2_pos.x()-_wm->marker1_pos.x())/2);
    //    radGradient = new QRadialGradient(QPoint(_wm->marker0_pos.x()+arenaHalfWidth,_wm->marker0_pos.y()+arenaHalfWidth),arenaHalfWidth);//15, 15, 15, 15, 15);
    //    int whiteInt = 190, midGrayInt = 100;
    //    // black center
    ////    radGradient->setColorAt(0.0, QColor::fromRgb(0,0,0));
    ////    radGradient->setColorAt(1.0, QColor::fromRgb(whiteInt,whiteInt,whiteInt));

    //    // white center
    //    radGradient->setColorAt(0.9, QColor::fromRgb(0,0,0));
    //    radGradient->setColorAt(0.0, QColor::fromRgb(whiteInt,whiteInt,whiteInt));

    //    radGradient->setColorAt(0.5, QColor::fromRgb(midGrayInt,midGrayInt,midGrayInt));
    ////    radGradient->setColorAt(1.0, QColor::fromRgb(whiteInt,whiteInt,whiteInt));

    radGradientRob = new QRadialGradient(QPoint(0, 0), _wm->robRad);//15, 15, 15, 15, 15);
    QColor robGradientCol = _wm->brush_robotCustom_0->color();
    robGradientCol.setAlphaF(1.0);
    radGradientRob->setColorAt(0.0, robGradientCol);
    robGradientCol.setAlphaF(0.0);
    radGradientRob->setColorAt(1.0, robGradientCol);

    expArena = new QRect(_wm->expFieldRect);


    //    QPainter painter(this);
    //    painter = QPainter(this);
    //    painter.setRenderHint(QPainter::TextAntialiasing);
    //    painter.setRenderHint(QPainter::Antialiasing);
    //    painter.setRenderHint(QPainter::HighQualityAntialiasing);
    //    painter.setRenderHint(QPainter::SmoothPixmapTransform);

    updatePainters();


    _timer.start(15);
    //    _timer.start(30);
    connect(&_timer,SIGNAL(timeout()), this, SLOT(refresh()));


    //    qDebug() << "Render Area size: " << this->width() << ", " << this->height();

    //    _noiseTimer.start(200);
    //    connect(&_noiseTimer,SIGNAL(timeout()), this, SLOT(toggleNoiseBool()));


    // TO DOs:
    // Consider using QOpenGLWidgets
    // consider updating painters whenever needed! rather than every specific time steps!
    //
}

/**
 * @brief Start playing a video from the given file path.
 * @param filename Path to the video file.
 */
void RenderArea::playVideo(const std::string& filename)
{
    videoCapture.open(filename);
    if (videoCapture.isOpened()) {
        videoPlaying = true;
        videoTimer->start(33); // ~30 FPS
    }
}

void RenderArea::stopVideo()
{
    // Needs to be checked fully
    if (videoPlaying) {
        videoTimer->stop();                // Stop the timer
        videoCapture.release();            // Release the video file
        videoPlaying = false;              // Update your state
        qDebug() << "Video stopped.";
    }
}

/**
 * @brief Grab the next frame from the video and update the display.
 */
void RenderArea::grabVideoFrame()
{
    if (!videoCapture.isOpened()) return;
    cv::Mat frame;
    if (videoCapture.read(frame)) {
        cv::cvtColor(frame, frame, cv::COLOR_BGR2RGB);
        videoFrame = QImage((const uchar*)frame.data, frame.cols, frame.rows, frame.step, QImage::Format_RGB888).copy();
        update();
    } else {
        if (frame.empty()) { // loop the video
            // end of the video: reset to beginning
            videoCapture.set(cv::CAP_PROP_POS_FRAMES, 0);
//            continue;
        }
        else{
        videoCapture.release();
        videoTimer->stop();
        videoPlaying = false;
        }
    }
}

/**
 * @brief Refresh the RenderArea display.
 *
 * Calls updatePainters() and schedules a repaint.
 */
void RenderArea::refresh()
{
    //    qDebug() << "updating ..";
    updatePainters(); // Remove this later, and update Painters whenever needed!
    update();
}

/**
 * @brief Returns the index of the most central node in a graph (by degree centrality).
 * @param graph igraph_t object representing the network graph.
 * @return Index of the node with highest degree centrality.
 */
int RenderArea::getMostCentralNode(const igraph_t& graph) {
    igraph_vector_int_t centrality;
    igraph_vector_int_init(&centrality, 0);

    // Calculate degree centrality
    igraph_degree(&graph, &centrality, igraph_vss_all(), IGRAPH_ALL, IGRAPH_NO_LOOPS);

    // Find the index of the most central node
    int max_centrality_index = igraph_vector_int_which_max(&centrality);

    // Cleanup
    igraph_vector_int_destroy(&centrality);

    return max_centrality_index;
}

/**
 * @brief Handles the paint event for the RenderArea widget.
 *
 * Draws all relevant graphical elements including background, markers, images, robots, networks, and overlays.
 * Uses current state of the WorldModel for data and configuration.
 *
 * @param event Pointer to the paint event (unused).
 */
void RenderArea::paintEvent(QPaintEvent *)
{

    QPainter painter(this);
    painter.setRenderHint(QPainter::TextAntialiasing);
    painter.setRenderHint(QPainter::Antialiasing);
    painter.setRenderHint(QPainter::HighQualityAntialiasing);
    painter.setRenderHint(QPainter::SmoothPixmapTransform);

    // Draw Background field
    painter.setBrush(*brush_field);
    painter.drawRect(bigFieldRect);

    if(_wm->drawBoundary)
    {
        painter.setBrush(*brush_insideRect);
        painter.setPen(*pen_insideRect);
        painter.drawRect(_wm->insideRect);
    }

    // Draw SCIoI Logo
    if(false) //true) //
    {
        painter.setPen(Qt::cyan);
        QFont font = painter.font();
        font.setPixelSize(20);
        painter.setFont(font);
        //    painter.drawText(260, 387, "© Project 27");
        painter.drawPixmap(700,500,600,300, SCIoIImg);
    }


    //    // Credits and info
    //    painter.drawText(265, 900, "© Project 27");
    //    painter.drawText(253, 920, "Mohsen Raoufi");
    //    painter.drawPixmap(250-5,930,140,140, webPage);

    // Draw Markers
    painter.drawPixmap(QRect(_wm->marker0_pos,QSize(_wm->marker_length,_wm->marker_length)), marker0);
    painter.drawPixmap(QRect(_wm->marker1_pos,QSize(_wm->marker_length,_wm->marker_length)), marker1);
    painter.drawPixmap(QRect(_wm->marker2_pos,QSize(_wm->marker_length,_wm->marker_length)), marker2);
    painter.drawPixmap(QRect(_wm->marker3_pos,QSize(_wm->marker_length,_wm->marker_length)), marker3);

    // Fill marker arenas

    switch (_wm->expFieldType) {
    case GRADIENT:
        painter.fillRect(*expArena, *radGradient);
        break;
    case IMAGE:
        if(_wm->noiseTimeIntv==-1)
            painter.drawPixmap(*expArena, _wm->arenaImg);
        else
            painter.drawPixmap(*expArena, _wm->arenaProcessedImg);
        break;
    case BR_VIDEO:
        if (videoPlaying && !videoFrame.isNull()) {
            painter.drawImage(*expArena, videoFrame.scaled(expArena->size()));
        }
        break;
    default:
        break;
    }




    // case: draw the INITIAL point
    if(false)
    {
        if(_wm->expFieldRect.width()<2000) // just a stupid condition so that the renderer doesn't draw a huge yellow circle
        {
            //        qDebug() << "wm widt: " << _wm->expFieldRect.width();
            painter.setBrush(*brush_initPoints2); // Qt::NoBrush);//
            painter.setPen(*pen_pnts2Draw);
            QPoint pnt = _wm->expFieldRect.center() + QPoint(0,-000); // QPoint(0,100); // QPoint(0.5*(_wm->expFieldRect.center())) // QPoint(0,(int)0.8*(_wm->expFieldRect.width()));
            painter.drawEllipse(pnt, 2, 2);

            painter.drawEllipse(pnt - QPoint(0,5), 1, 1);
            painter.drawEllipse(pnt - QPoint(0,10), 1, 1);
            painter.drawEllipse(pnt - QPoint(-8,-5), 1, 1);
            painter.drawEllipse(pnt - QPoint(8,-5), 1, 1);
        }
    }


    painter.setBrush(Qt::NoBrush);//

    if(_wm->drawInitPoint)
    {
        // Draw points2Draw: ex. init points, grid/star
        painter.setBrush(*brush_initPoints);
        painter.setPen(*pen_pnts2Draw);
        for(int i = 0; i < _wm->pointsToDraw.size(); i++){
            QPoint pnt = _wm->pointsToDraw.at(i);
            //        QPoint pnt = _wm->pointsToDraw.at(i);
            //            qDebug() << "point " << i << " is at " << pnt.x() << ", " << pnt.y();
            painter.drawEllipse(pnt, 2, 2);
            //        painter.drawPoint(pnt);
        }

        painter.setBrush(Qt::NoBrush);
        painter.setPen(*pen_pnts2Draw);
        for(int i = 0; i < _wm->pointsToDraw.size(); i++){
            QPoint pnt = _wm->pointsToDraw.at(i);
            painter.drawEllipse(pnt, _wm->robRad, _wm->robRad);
        }
    }


    if(_wm->drawHeatMap && true)
    {
        // TO DO: check if there is any better solution doing this!
        //        QPixmap temp = QPixmap("heatmap.png");
        //        painter.drawPixmap(*expArena, temp);


        //        cv::Mat frame;
        //        _wm->heatMap.copyTo(frame);
        //        QImage tempQIm((uchar*)frame.data, frame.cols, frame.rows, frame.step, QImage::Format_RGBA64);
        //        painter.drawPixmap(*expArena, QPixmap::fromImage(tempQIm));

        //        painter.drawPixmap(*expArena, _wm->heatMap);

        _wm->heatMap.copyTo(heatMapTemp);
        cv::normalize(_wm->heatMap, heatMapTemp, 0, 255, cv::NORM_MINMAX, CV_8UC4);
        //        heatMapQImage = QImage(heatMapTemp.data, heatMapTemp.cols, heatMapTemp.rows, heatMapTemp.step, QImage::Format_ARGB32);
        heatMapQImage = QImage(heatMapTemp.data, heatMapTemp.cols, heatMapTemp.rows, heatMapTemp.step, QImage::Format_RGBA8888);
        //        heatMapQImage = QImage(_wm->heatMap.data, _wm->heatMap.cols, _wm->heatMap.rows, _wm->heatMap.step, QImage::Format_ARGB32);
        //        cv::imshow("heatmap", _wm->heatMap);



        painter.drawImage(*expArena, heatMapQImage);

    }

    if(_wm->drawCentroid)
    {

        painter.drawPixmap(QRect(_wm->centroid - QPoint(centroid_width/2, centroid_width/2), QSize(centroid_width, centroid_width)), centroidImage);
        //        qDebug() << "wm centroid: " << _wm->centroid.x() << ", " << _wm->centroid.y();
    }

    if(_wm->drawBall)
    {
        // DRAW BALL!!!
        painter.drawPixmap(QRect(_wm->ballPos - QPoint(_wm->ballRad/2, _wm->ballRad/2), QSize(_wm->ballRad, _wm->ballRad)), ballImage);
        //    painter.setPen(*pen_circ2Draw);
        //    painter.drawEllipse(_wm->ballPos, 20, 20);
    }

    //    if(_wm->drawRobCircles) // // draw circles **RING** around kilobots
    //    {
    //        painter.setBrush(Qt::NoBrush);
    //        painter.setPen(*pen_RobCust1);
    //        //    for(int i = 0; i < _wm->pointsToDraw.size(); i++){
    //        for(int i = 0; i < _wm->rob_Type0_pos.size(); i++){
    //            //        QPoint pnt = _wm->pointsToDraw.at(i);
    //            QPoint pnt = _wm->rob_Type0_pos.at(i);
    //            painter.drawEllipse(pnt, _wm->robRad, _wm->robRad);
    //        }
    //    }

    // draw collective (big) circles
    if(_wm->drawColCircles)
    {
        painter.setPen(*pen_circ2Draw);
        for(int i =0; i < _wm->circles2Draw.size(); i++){
            painter.drawEllipse(_wm->circles2Draw.at(i).pos, _wm->circles2Draw.at(i).r, _wm->circles2Draw.at(i).r);
        }
    }

    painter.translate(_wm->marker0_BR);
    painter.setPen(Qt::NoPen);
    if(_wm->drawRobCircles) // // draw circles **RING** around kilobots
        painter.setPen(*pen_RobCust1);
    if(_wm->robBrushType!=NULL_BRUSH)
        painter.setBrush(*_wm->brush_robotCustom_0);
    else
        painter.setBrush(Qt::NoBrush);





    // Draw network
    if(_wm->drawNetwork){

        // Create a graph using igraph library from the _wm->rob_Type0 nodes
        igraph_empty(&graph, _wm->rob_Type0_pos.length(), IGRAPH_UNDIRECTED);
        //    igraph_vector_init(&edges, 0);

        // Add edges based on the distance between nodes
        if(_wm->spatialNetwork)
        {
            for(int i = 0; i < _wm->rob_Type0_pos.size()-1; i++){
                QPoint pnt_i = _wm->rob_Type0_pos.at(i);
                for(int j = i+1; j < _wm->rob_Type0_pos.size(); j++){
                    QPoint pnt_j = _wm->rob_Type0_pos.at(j);

                    if(pow(pnt_i.x()-pnt_j.x(),2)+pow(pnt_i.y()-pnt_j.y(),2)< _wm->dummy_var*_wm->dummy_var/10)
                    {
                        //                    igraph_vector_push_back(&edges, i);
                        //                    igraph_vector_push_back(&edges, j);
                        igraph_add_edge(&graph, i, j);
                    }

                }
            }
        }
        else if(_wm->drawVoronoii)
        {
            for (voronoi_diagram<double>::const_edge_iterator it = vd.edges().begin(); it != vd.edges().end(); ++it) {
                if (!it->is_primary()) {
                    continue;
                }

                int index = it->cell()->source_index();
                int twinIndex = it->twin()->cell()->source_index();

                if (index >= 0 && twinIndex >= 0) {
                    QPoint site = _wm->rob_Type0_pos[index];
                    QPoint twinSite = _wm->rob_Type0_pos[twinIndex];

                    //                painter.drawLine(site,twinSite);
                    igraph_add_edge(&graph, index, twinIndex);
                }
            }
        }

        // int max_degree_index = getMostCentralNode(graph);

        // index_node_to_light_net = max_degree_index;

        // // set the _wm->rob_toEnlight.at(index_node_to_light_net) to true
        // if(index_node_to_light_net>=0)
        //     _wm->rob_toEnlight[index_node_to_light_net] = true;

    }


    // Points to Draw for Robots! // needs an update!
    for(int i = 0; i < _wm->rob_Type0_pos.size(); i++){
        QPoint pnt = _wm->rob_Type0_pos.at(i);
        if(_wm->rob_toEnlight.at(i))
            switch (_wm->robBrushType) {
            case GRADIENT:
                // GRADIENT PATTERN
                painter.translate(pnt);
                painter.fillRect(QRect(-robRad, -robRad, 2*robRad, 2*robRad), *radGradientRob);
                //        //        painter.drawEllipse(pnt, _wm->robRad, _wm->robRad);
                painter.translate(-pnt);
                break;
            case SOLID:
                painter.drawEllipse(pnt, _wm->robRad, _wm->robRad);
                break;
            case NULL_BRUSH:
                painter.drawEllipse(pnt, _wm->robRad, _wm->robRad);
                break;
            default:
                painter.drawEllipse(pnt, _wm->robRad, _wm->robRad);
                break;
            }
    }



    // Draw Voronoii Diagram
    if(_wm->drawVoronoii)
    {
        painter.setPen(*pen_voronoii);
        voronoiGenerator::generateVoronoi(_wm->rob_Type0_pos, vd);  // Generate the diagram
        VoronoiiGen.update_points(_wm->rob_Type0_pos);              // Add the points to the diagram


        QRectF bounds = _wm->insideRect;

        VoronoiiGen.set_brect(bounds);                              // set the bounding rectangle: not working ideally! need a revisit

        // 2nd version
        int ctr = 0;

        for (voronoi_diagram<double>::const_edge_iterator it = vd.edges().begin(); it != vd.edges().end(); ++it) {
            ctr++;
            if (!it->is_primary()) {
                continue;
            }


            //            if(_wm->drawNetwork)
            //            {

            //            int index = it->cell()->source_index();
            //            int twinIndex = it->twin()->cell()->source_index();
            //            QPointF site = _wm->rob_Type0_pos[index];
            //            QPointF twinSite = _wm->rob_Type0_pos[twinIndex];

            //            painter.drawLine(pnt_i,pnt_j);

            //            }



            const boost::polygon::voronoi_edge<double>& edge = *it;
            if (edge.is_finite()) {
                QPointF start(edge.vertex0()->x(), edge.vertex0()->y());
                QPointF end(edge.vertex1()->x(), edge.vertex1()->y());
                painter.drawLine(start, end);
                painter.drawEllipse(QPoint(edge.vertex0()->x(), edge.vertex0()->y()), 5, 5);
            }
            // if the edges are not finite, we need to find the other end of the line to draw
            else {
                std::vector<voronoiGenerator::point_type> samples;
                VoronoiiGen.clip_infinite_edge(*it, &samples);
                //                if(samples.size()<1) continue;
                //                painter.setPen(*pen_network);
                for (std::size_t i = 0; i < samples.size(); ++i) {
                }
                painter.drawLine(QPoint(samples[0].x(), samples[0].y()), QPoint(samples[1].x(), samples[1].y()));
                painter.drawEllipse(QPoint(samples[0].x(), samples[0].y()), 5, 5);
            }
        }
    }



    // Draw network
    if(_wm->drawNetwork){

        //        // Create a graph using igraph library from the _wm->rob_Type0 nodes
        //        igraph_empty(&graph, _wm->rob_Type0_pos.length(), IGRAPH_UNDIRECTED);
        //        //    igraph_vector_init(&edges, 0);

        //        // Add edges based on the distance between nodes
        //        if(_wm->spatialNetwork)
        //        {
        //            for(int i = 0; i < _wm->rob_Type0_pos.size()-1; i++){
        //                QPoint pnt_i = _wm->rob_Type0_pos.at(i);
        //                for(int j = i+1; j < _wm->rob_Type0_pos.size(); j++){
        //                    QPoint pnt_j = _wm->rob_Type0_pos.at(j);

        //                    if(pow(pnt_i.x()-pnt_j.x(),2)+pow(pnt_i.y()-pnt_j.y(),2)< _wm->dummy_var*_wm->dummy_var/10)
        //                    {
        //                        //                    igraph_vector_push_back(&edges, i);
        //                        //                    igraph_vector_push_back(&edges, j);
        //                        igraph_add_edge(&graph, i, j);
        //                    }

        //                }
        //            }
        //        }
        //        else if(_wm->drawVoronoii)
        //        {
        //            for (voronoi_diagram<double>::const_edge_iterator it = vd.edges().begin(); it != vd.edges().end(); ++it) {
        //                if (!it->is_primary()) {
        //                    continue;
        //                }

        //                int index = it->cell()->source_index();
        //                int twinIndex = it->twin()->cell()->source_index();

        //                if (index >= 0 && twinIndex >= 0) {
        //                    QPoint site = _wm->rob_Type0_pos[index];
        //                    QPoint twinSite = _wm->rob_Type0_pos[twinIndex];

        //                    //                painter.drawLine(site,twinSite);
        //                    igraph_add_edge(&graph, index, twinIndex);
        //                }
        //            }
        //        }

        //        int max_degree_index = getMostCentralNode(graph);

        //        index_node_to_light_net = max_degree_index;

        //        // set the _wm->rob_toEnlight.at(index_node_to_light_net) to true
        //        if(index_node_to_light_net>=0)
        //            _wm->rob_toEnlight[index_node_to_light_net] = true;

        


        // Output the most central nodes for each measure
        //        std::cout << "Most central node by degree centrality: " << max_degree_index << std::endl;



        painter.setPen(*pen_network);


        // TODO: use the igraph graph instead of going through the list

        if(_wm->spatialNetwork)
        {
            for(int i = 0; i < _wm->rob_Type0_pos.size()-1; i++){
                QPoint pnt_i = _wm->rob_Type0_pos.at(i);
                for(int j = i+1; j < _wm->rob_Type0_pos.size(); j++){
                    QPoint pnt_j = _wm->rob_Type0_pos.at(j);

                    if(pow(pnt_i.x()-pnt_j.x(),2)+pow(pnt_i.y()-pnt_j.y(),2)< _wm->dummy_var*_wm->dummy_var/10)
                    {
                        painter.drawLine(pnt_i,pnt_j);
                        //            qDebug() << "Pnt1: " << pnt_i.x() << ", pnt2: " << pnt_j.x();

                    }

                }
            }
        }
        else if(_wm->drawVoronoii)
        {

            for (voronoi_diagram<double>::const_edge_iterator it = vd.edges().begin(); it != vd.edges().end(); ++it) {
                if (!it->is_primary()) {
                    continue;
                }

                int index = it->cell()->source_index();
                int twinIndex = it->twin()->cell()->source_index();

                if (index >= 0 && twinIndex >= 0) {
                    QPoint site = _wm->rob_Type0_pos[index];
                    QPoint twinSite = _wm->rob_Type0_pos[twinIndex];

                    painter.drawLine(site,twinSite);
                }
            }
        }


        igraph_destroy(&graph);
    }


    if(_wm->drawTrace)
    {
        painter.setPen(*pen_tracePnts);
        for(int i=0; i < _wm->rob_traces.size(); i++){
            //        qDebug() << "drawing traces, i: " << i << ", size: " << _wm->rob_traces.size();
            for (int j=0; j < _wm->rob_traces.at(i).size(); j++){
                //            qDebug() << "    j: " << j << ", size: " << _wm->rob_traces.at(i).size();
                painter.drawPoint(_wm->rob_traces.at(i).at(j));
                //                painter.drawEllipse(_wm->rob_traces.at(i).at(j), 1, 1);
            }
        }
    }
}

/**
 * @brief Update painter objects (brushes, pens, gradients) to match current WorldModel state.
 */
void RenderArea::updatePainters()
{
    brush_field->setColor(_wm->fieldCol);
    bigFieldRect = QRect(_wm->fieldTL, _wm->fieldSize);

    robRad = _wm->robRad;

    QColor tmpRobCol = _wm->brush_robotCustom_0->color();
    tmpRobCol.setAlphaF(1.0);
    radGradientRob->setColorAt(0.0, tmpRobCol);
    tmpRobCol.setAlphaF(0.0);
    radGradientRob->setColorAt(1.0, tmpRobCol);
    radGradientRob->setRadius(robRad);

    expArena->setTopLeft(_wm->expFieldRect.topLeft());
    expArena->setBottomRight(_wm->expFieldRect.bottomRight());

}


/**
 * @brief Updates the gradient painter for the arena background, based on arena size and center.
 */
void RenderArea::updateGradientPainter()
{
    int arenaHalfWidth = (int) _wm->expFieldRect.width()/2;
    radGradient = new QRadialGradient(_wm->expFieldRect.center(),arenaHalfWidth);//15, 15, 15, 15, 15);

    //    radGradient->setCenter(_wm->expFieldRect.center());//QPoint(_wm->marker0_pos.x()+arenaHalfWidth,_wm->marker0_pos.y()+arenaHalfWidth));
    qDebug() << "WM exp Field cntr: " << _wm->expFieldRect.center().x() << ", " << _wm->expFieldRect.center().y();

    radGradient->setRadius(arenaHalfWidth);
    int whiteInt = 160, midGrayInt = 100;
    // white center
    //    radGradient->setColorAt(0.95, QColor::fromRgb(0,0,0));
    //    radGradient->setColorAt(0.0, QColor::fromRgb(whiteInt,whiteInt,whiteInt));
    //    radGradient->setColorAt(0.6, QColor::fromRgb(midGrayInt,midGrayInt,midGrayInt));

    radGradient->setColorAt(0.9, QColor::fromRgb(0,0,0));
    radGradient->setColorAt(0.0, QColor::fromRgb(whiteInt,whiteInt,whiteInt));
    //    radGradient->setColorAt(0.5, QColor::fromRgb(midGrayInt,midGrayInt,midGrayInt));

    // black center
    //    radGradient->setColorAt(0.0, QColor::fromRgb(0,0,0));
    //    radGradient->setColorAt(1.0, QColor::fromRgb(whiteInt,whiteInt,whiteInt));
}


