#ifndef ENVBRAIN_H
#define ENVBRAIN_H

/**
 * @file envbrain.h
 * @brief Declaration of EnvBrain, environment logic module for LARS.
 *
 * Provides environment modeling, heatmap management, noise handling, and geometric utilities for the arena.
 */

#include <QObject>
#include <QtCore>
#include <QTimer>
#include <opencv2/opencv.hpp>
#include <opencv2/cudaarithm.hpp>

#include "ui/worldmodel.h"

/**
 * @brief Environment logic and utility class for the robot arena.
 *
 * Handles collective environment updates, heatmap operations, spatial noise, and geometry generation.
 */
class EnvBrain : public QObject
{
    Q_OBJECT
public:
    /**
     * @brief Constructs the EnvBrain object.
     * @param wm Pointer to the world model.
     */
    explicit EnvBrain(WorldModel *wm = nullptr);//, QObject *parent);

    /**
     * @brief Generates a grid of points within the arena.
     * @param nRows Number of rows.
     * @param nCols Number of columns.
     * @param dx Horizontal spacing between points.
     * @param dy Vertical spacing between points.
     * @param origin Top-left origin for the grid.
     * @return List of grid points.
     */
    QList<QPoint> makeGridPoints(int nRows=1, int nCols=1, int dx=10, int dy=10, QPoint origin=QPoint(0,0));
    /**
     * @brief Generates star-shaped point arrangements centered at a given origin.
     * @param nArms Number of star arms.
     * @param nLayers Number of layers (distance steps) on each arm.
     * @param d Distance between layers.
     * @param origin Center of the star.
     * @return List of star points.
     */
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
/// @name Environment update and utility slots
/// @{

    /**
     * @brief Periodically refreshes environment state and visualization.
     */
    void refresh();
    /**
     * @brief Adds spatial noise to the arena image and updates the visualization.
     */
    void addNoise();
    /**
     * @brief Resets the heatmap to its initial state.
     */
    void resetHeatMap();
    /**
     * @brief Updates the noise timer interval based on a slider/time parameter.
     * @param time_interval User-defined time interval (slider value).
     */
    void updateNoiseProps(int time_interval);
    /**
     * @brief Connects or disconnects the timer for adding noise to the environment.
     * @param connect_bool If true, connect; else disconnect.
     */
    void connect_disconnect_add_noise(bool connect_bool);
    /**
     * @brief Updates centroid of robot distribution. (Empty or placeholder)
     */
    void update_centroid();
    /**
     * @brief Updates arena objects (e.g. ball, robots) to be drawn.
     */
    void update_objects_to_draw();

/// @}

signals:

};

#endif // ENVBRAIN_H
