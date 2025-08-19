
#include "envbrain.h"

/**
 * @file envbrain.cpp
 * @brief Implementation of EnvBrain, environment logic and utilities for the robot arena.
 *
 * Handles collective environment modeling, heatmap processing, noise management, and geometric utilities.
 */



/**
 * @brief Constructs the EnvBrain object.
 *
 * Initializes environment logic, heatmaps, ball velocity, and timers for periodic updates.
 * @param wm Pointer to the world model.
 */
EnvBrain::EnvBrain(WorldModel *wm)
{

    this->_wm = wm;
    qDebug() << "env Brain Defined: EXP FIELD SIZE: " << _wm->expFieldRect.width() << ", " << _wm->expFieldRect.height();
    //    heatMap = cv::Mat::ones(_wm->expFieldRect.width(), _wm->expFieldRect.height(), CV_64F);
    //    cv::Mat temp(_wm->expFieldRect.width(), _wm->expFieldRect.height(), CV_8UC4, cv::Scalar(0,0,0,0));

    resetHeatMap();

    ////    cv::Mat temp(_wm->expFieldRect.width(), _wm->expFieldRect.height(), CV_64FC4, cv::Scalar(0,0,0,0));
    //    cv::Mat temp(_wm->expFieldRect.height(), _wm->expFieldRect.width(), CV_64FC4, cv::Scalar(0,0,0,0));
    //    temp.copyTo(this->heatMap);

    //    cv::Mat temp2(_wm->capSize.width, _wm->capSize.height, CV_64FC3, cv::Scalar(0,0,0));
    //    temp2.copyTo(this->heatMapOnFrame);

    qDebug() << "env Brain Defined: Cap size: " << _wm->capSize.width << ", " << _wm->capSize.height;

    double ball_vel_x = rand()/double(RAND_MAX);
    double ball_vel_y = rand()/double(RAND_MAX);
    double ball_speed = sqrt(ball_vel_x*ball_vel_x + ball_vel_y*ball_vel_y);
    //    _wm->ballVel = QPointF(float(ball_vel_x/ball_speed), float(ball_vel_y/ball_speed)); // COMMENT THIS FOR EVALUATION
    qDebug() << "ballvel: " << ball_vel_x << ", " << ball_vel_y;


    //    _wm->ballPos.setY(100);
    //    _wm->ballPos.setX(50);
    //    qDebug() << "ballPos: " << _wm->ballPos.x() << ", " << _wm->ballPos.y();


#ifdef FOR_KILOBOT
    _timer.start(30);
//    _timer.start(10);
#else
    _timer.start(50);
#endif
    connect(&_timer,SIGNAL(timeout()), this, SLOT(refresh())); // to refresh heatmap and collective circles

    _timerNoise.start(1000);
    //    connect(&_timerNoise,SIGNAL(timeout()), this, SLOT(addNoise()));
}

/**
 * @brief Generates a grid of points within the arena, helpful for initialization of an experiment.
 * @param nRows Number of rows.
 * @param nCols Number of columns.
 * @param dx Horizontal spacing between points.
 * @param dy Vertical spacing between points.
 * @param origin Top-left origin for the grid.
 * @return List of grid points.
 */
QList<QPoint> EnvBrain::makeGridPoints(int nRows, int nCols, int dx, int dy, QPoint origin)
{
    QList<QPoint> pointList;
    //    QPoint tmp;
    for(int i=0; i<nCols; i++)
    {
        for(int j=0; j<nRows; j++)
        {
            pointList.append(QPoint(i*dx,j*dy) + origin);
        }
    }

    return pointList;
}

/**
 * @brief Generates star-shaped point arrangements centered at a given origin, helpful for initialization of an experiment.
 * @param nArms Number of star arms.
 * @param nLayers Number of layers (distance steps) on each arm.
 * @param d Distance between layers.
 * @param origin Center of the star.
 * @return List of star points.
 */
QList<QPoint> EnvBrain::makeStarPoints(int nArms, int nLayers, int d, QPoint origin)
{
    QList<QPoint> pointList;

    for(int i=0; i<nArms; i++)
    {
        float theta = (float)i * 2.0 * 3.1416/((float) nArms);
        for(int j=0; j<nLayers; j++)
        {
            int dist2O = (j+1)*d;
            pointList.append(QPoint(dist2O*cos(theta),dist2O*sin(theta)) + origin);
        }
    }

    return pointList;
}

/**
 * @brief Resets the heatmap to an initial (zeroed) state.
 */
void EnvBrain::resetHeatMap()
{
    //    cv::Mat temp(_wm->expFieldRect.width(), _wm->expFieldRect.height(), CV_64FC4, cv::Scalar(0,0,0,0));
    //    cv::Mat temp(_wm->expFieldRect.height(), _wm->expFieldRect.width(), CV_64FC4, cv::Scalar(0,0,0,0));

    cv::Mat temp(_wm->expFieldRect.height(), _wm->expFieldRect.width(), CV_8UC4, cv::Scalar(0,0,0,0)); // efficient
    temp.copyTo(this->heatMap);

    //    cv::Mat temp2(_wm->capSize.width, _wm->capSize.height, CV_8UC3, cv::Scalar(0,0,0));
    //    temp2.copyTo(this->heatMapOnFrame);
}

/**
 * @brief Updates the noise timer interval exponentially with respect to a slider/time parameter.
 * @param time_interval User-defined time interval (slider value).
 */
void EnvBrain::updateNoiseProps(int time_interval)
{
    //    qDebug() << "Noise Timer is updated: " << _wm->noiseFreq;
    //    qDebug() << "time interval: " << time_interval << ", val: " << double(time_interval)/10.0 + 1;
    int time_int_exp = pow(2, int(double(time_interval)/200.0) + 4);
    qDebug() << "EnvBrain: Time interval is set (exponentially) to: " << time_int_exp;
    _timerNoise.setInterval(time_int_exp); //_wm->noiseTimeIntv);
    //    _timerNoise.stop();
    //    _timerNoise.start(_wm->noiseFreq);
}

/**
 * @brief Connects or disconnects the timer for adding noise to the environment.
 * @param connect_bool If true, connect; else disconnect.
 */
void EnvBrain::connect_disconnect_add_noise(bool connect_bool)
{
    if(connect_bool)
    {
        connect(&_timerNoise,SIGNAL(timeout()), this, SLOT(addNoise()));
    }
    else
    {
        disconnect(&_timerNoise,SIGNAL(timeout()), this, SLOT(addNoise()));
    }
}

/**
 * @brief (Placeholder) Updates centroid of robot distribution. [Empty function]
 */
void EnvBrain::update_centroid()
{

}

/**
 * @brief Updates objects (e.g., the ball) to be drawn in the environment.
 *
 * Handles movement, collision with arena bounds, and collisions with robot circles.
 */
void EnvBrain::update_objects_to_draw()
{
    if(_wm->drawBall)
    {
        _wm->ballSpeed = _wm->dummy_var2/20;

//        qDebug() << "BEFORE : ballPos: " << _wm->ballPos.x() << ", " << _wm->ballPos.y();
        // Update position based on velocity
        QPointF movement = _wm->ballSpeed * _wm->ballVel;
        //    qDebug() << "ballvel: " << _wm->ballVel.x() << ", " << _wm->ballVel.y();
        QPoint ballPosTmp = _wm->ballPos + QPoint(movement.x(), movement.y());
        //    qDebug() << "ballPos: " << ballPosTmp.x() << ", " << ballPosTmp.y();

        // Check for collisions with arena bounds
        if (ballPosTmp.x() < _wm->insideRect.left() || ballPosTmp.x() > _wm->insideRect.right()) {
            // If ball hits left or right bounds, reverse x velocity
            _wm->ballVel.setX(-_wm->ballVel.x());
        }
        if (ballPosTmp.y() < _wm->insideRect.top() || ballPosTmp.y() > _wm->insideRect.bottom()) {
            // If ball hits top or bottom bounds, reverse y velocity
            _wm->ballVel.setY(-_wm->ballVel.y());
        }


        // Check for collisions with circles
        if (false)
        {
            for (const QPoint& circleCenter : _wm->rob_Type0_pos) {
                //        qDebug() << "Circle to collide center: " << circleCenter.x() << ", " << circleCenter.y();

                // Calculate distance between ball center and circle center
                int dx = circleCenter.x() + _wm->marker0_BR.x() - ballPosTmp.x();
                int dy = circleCenter.y() + _wm->marker0_BR.y() - ballPosTmp.y();
                int distance = std::sqrt(dx * dx + dy * dy);

                // If the distance is less than the sum of the radii, collision occurs
                if (distance < (_wm->ballRad + _wm->robRad)) {
                    // Calculate reflection angle
                    double angle = std::atan2(dy, dx);
                    double reflectionAngle = 2 * angle - std::atan2(_wm->ballVel.y(), _wm->ballVel.x());

                    // Update velocity based on reflection angle
                    _wm->ballVel.setX(std::cos(reflectionAngle));
                    _wm->ballVel.setY(std::sin(reflectionAngle));

                    // Move the ball to avoid sticking in the circle
                    movement = _wm->ballSpeed * _wm->ballVel;
                    ballPosTmp = _wm->ballPos + QPoint(movement.x(), movement.y());
                    //            ballPosTmp += ballSpeed * ballVel;
                }
            }
        }

        // Ensure ball stays within arena bounds
        ballPosTmp.setX(qBound(_wm->insideRect.left(), ballPosTmp.x(), _wm->insideRect.right()));
        ballPosTmp.setY(qBound(_wm->insideRect.top(), ballPosTmp.y(), _wm->insideRect.bottom()));
        _wm->ballPos = ballPosTmp;

//        qDebug() << "AFTER : ballPos: " << _wm->ballPos.x() << ", " << _wm->ballPos.y();
    }
}

//void EnvBrain::updateTraces(QVector<QPoint> posVec)
//{
//    //    qDebug() << " hey hey! : updating trace, posVec.Size : " << posVec.size() ;
//    //    if(posVec.size()>0) {
//    //    qDebug() << " hey hey! : updating trace";
//    //    if(listInd%10==0){
//    //        _wm->rob_traces.prepend(posVec);
//    //        _wm->rob_traces.resize(nList);
//    //    }

//    //    listInd = listInd + 1;
//    //    listInd = listInd%nList;
//    //    }

//    //    cv::Mat circTemp, imgTemp;

//    //    heatMap.copyTo(circTemp);

//    //    for(int i=0; i<posVec.size(); i++)
//    //    {
//    //        cv::Point2d tmp = cv::Point2d(posVec.at(i).x(), posVec.at(i).y()) - cv::Point2d(_wm->marker0_pos.x() + _wm->marker_length, _wm->marker0_pos.y() + _wm->marker_length);
//    ////        qDebug() << "drawing circles at: " << tmp.x << ", " << tmp.y;
//    //        cv::circle(circTemp, tmp, 2, cv::Scalar(0,0,255,250), 2);
//    //    }


//    //    // the whole trace and HeatMap should be revisited once again! do we need to save it to an image? how to solve the issue with MAT type (8 is okay, 64 is not)
//    //    // Make a "real" heat map that accumulates the traces
//    //    // add a timer, so that we can control the refresh rate of the traces

//    //    circTemp.copyTo(heatMap);
//    //    float alphaForget = 0.01;
//    //    cv::addWeighted(circTemp, alphaForget, heatMap, 0.99-alphaForget, 0, heatMap);
//    ////    cv::imshow("heatMap", heatMap);
//    //    cv::imwrite("heatmap.png", heatMap);

//    //    //    _wm->heatMap = QPixmap::fromImage(QImage((unsigned char*) heatMap.data, heatMap.cols, heatMap.rows, QImage::Format_RGBA64));
//}

/**
 * @brief Periodically refreshes environment state, heatmap, and visualization objects.
 *
 * Called on a timer, updates robot positions, heatmap accumulation, centroid, and visualization elements.
 */
void EnvBrain::refresh()
{
    QVector<QPoint> tempPosVec = _wm->kiloPosVec;

    QVector<int> dist2Cent; // to draw circles rel 2 the center of the field
    int maxDist2Cent = 0, minDist2Cent = 2000000;

    heatMap.copyTo(circTemp);

    QPointF tempCentroid(0,0);

    QPoint tmpRelVec;
    for( int i=0; i<tempPosVec.size(); i++)
    {
        tmpRelVec = tempPosVec.at(i) + _wm->marker0_BR - _wm->expFieldRect.center();

        int dist2centTemp = (int) std::sqrt(QPoint::dotProduct(tmpRelVec,tmpRelVec));
        dist2Cent.push_back(dist2centTemp); // Maybe it is not necessary to store all the distances (if we only take min and max)

        if(dist2centTemp < minDist2Cent)
            minDist2Cent = dist2centTemp;
        if(dist2centTemp > maxDist2Cent)
            maxDist2Cent = dist2centTemp;

        tempCentroid = tempCentroid + tempPosVec.at(i);

        if(true) // It should be calculating the heatmap **in the background** even if it is not being shown atm. By doing it continuously it keeps track of the heatmap
            //        if(_wm->drawHeatMap)
        {
            // Update HeatMap
            cv::Point2d tmp = cv::Point2d(tempPosVec.at(i).x(), tempPosVec.at(i).y());

            // // ToDo: In the following, use user-defined "heat-map color" instead
            //            cv::circle(circTemp, tmp, trace_rad, cv::Scalar(0,0,255,250), cv::FILLED); // ORIGINAL // RED
            //            cv::circle(circTemp, tmp, trace_rad, cv::Scalar(0,255,255,250), cv::FILLED); // ORIGINAL // YELLOW
            //                        cv::circle(circTemp, tmp, trace_rad, cv::Scalar(0,255,0,250), cv::FILLED); // ORIGINAL // Green

            cv::Scalar tempColor = cv::Scalar(0,255,255,250);

            if(_wm->drawWithColors && _wm->kiloColor.size() && i<_wm->kiloColor.size())
                tempColor = cv::Scalar(_wm->kiloColor.at(i)[0]/2, _wm->kiloColor.at(i)[1]/2, _wm->kiloColor.at(i)[2]/2, 255);

            cv::circle(circTemp, tmp, trace_rad, tempColor, cv::FILLED);

            //            qDebug() << "KiloColor at " << i  << ": " << _wm->kiloColor.at(i)[0] << ", " << _wm->kiloColor.at(i)[1] << ", " << _wm->kiloColor.at(i)[2];

        }
    }

    // update centroid
    if(tempPosVec.size()>0)
        tempCentroid = tempCentroid/float(tempPosVec.size());

    //    _wm->centroid = tempCentroid;
    _wm->centroid = QPoint(tempCentroid.x(), tempCentroid.y()) + _wm->marker0_BR;

    // Drawing circles for the contour capturing scenario: works only for radial distributions!
    if(_wm->drawColCircles)
    {
        wmCircle tmpCircle;
        _wm->circles2Draw.clear();
        tmpCircle.pos = _wm->expFieldRect.center();
        tmpCircle.r = minDist2Cent;
        _wm->circles2Draw.push_back(tmpCircle);

        tmpCircle.r = maxDist2Cent;
        _wm->circles2Draw.push_back(tmpCircle);
    }

    if(true) // check the comment above!
        //    if(_wm->drawHeatMap) //
    {
        circTemp.copyTo(heatMap);

        //        cv::GaussianBlur(heatMap,heatMap, cv::Size(11,11), 1.0);

        //        float alphaForget = 0.0001;
        ////        cv::addWeighted(circTemp, alphaForget, heatMap, 0.995-alphaForget, 0, heatMap); // ORG
        //        cv::addWeighted(circTemp, alphaForget, heatMap, 0.998-alphaForget, 0, heatMap); // ORG

        // Faster decay
        float alphaForget = 0.0001;
        //        cv::addWeighted(circTemp, alphaForget, heatMap, 0.995-alphaForget, 0, heatMap); // ORG with 64FC

        cv::addWeighted(circTemp, alphaForget, heatMap, 0.998-alphaForget, -0.5, heatMap); // without tail
        //        cv::addWeighted(circTemp, alphaForget, heatMap, 0.996-alphaForget, -0.0, heatMap); // with tail


        //        // Calculation using GPU
        //        cv::cuda::GpuMat circTempGPU; // Using Cuda GPU
        //        circTempGPU.upload(circTemp);
        //        cv::cuda::addWeighted(circTempGPU, alphaForget, heatMap, 0.995-alphaForget, 0, heatMap);

        heatMap.copyTo(_wm->heatMap);

        //        cv::imwrite("heatmap.png", heatMap);


    }


    update_objects_to_draw();

}

/**
 * @brief Adds spatial noise to the arena image.
 *
 * Applies random noise to each tile of the arena image and updates the processed image for visualization.
 */
void EnvBrain::addNoise()
{

    // if _wm->expFieldType is NULL_BRUSH then make an empty arenaImage that is fully transparent as arenaImage
    //    if (_wm->expFieldType == NULL_BRUSH)
    //        arenaImage = QImage(_wm->expFieldRect.width(), _wm->expFieldRect.height(), QImage::Format_RGB16);
    //    else
    arenaImage = _wm->arenaImg.toImage();

    int nTilesNoise = _wm->noiseTileNo;
    cv::Mat1d tempNoise(nTilesNoise, nTilesNoise);

    cv::randu(tempNoise, -_wm->noiseStrength, _wm->noiseStrength);
    cv::randn(tempNoise, 0, _wm->noiseStrength);

    for (int i=0; i<arenaImage.width(); i++)
    {
        for (int j=0; j<arenaImage.width(); j++)
        {
            QColor tmpColor = arenaImage.pixelColor(i,j);
            int rndNoise = 255*tempNoise.at<double>(i*nTilesNoise/arenaImage.width(),j*nTilesNoise/arenaImage.height());
            QColor noiseColor = QColor::fromRgb(MAX(MIN(tmpColor.red() + rndNoise,255),0), MAX(MIN(tmpColor.green() + rndNoise,255),0), MAX(MIN(tmpColor.blue() + rndNoise,255),0));
            arenaImage.setPixelColor(i,j, noiseColor);
        }
    }

    _wm->arenaProcessedImg = QPixmap::fromImage(arenaImage);

}
