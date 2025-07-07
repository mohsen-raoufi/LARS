#**
 * @file savevid_thread.cpp
 * @brief Implementation of SaveVid_Thread, a threaded video writer for saving frames using OpenCV.
 *
 * Provides functionality for starting, writing, and configuring video output in a separate thread context.
 */
#include "savevid_thread.h"
#include <QtCore>

#include <QDebug>
/**
 * @brief Constructs the SaveVid_Thread object and initializes the video writer.
 * @param fileName Output video file path.
 * @param codec FourCC codec identifier.
 * @param FPS Frames per second for video output.
 * @param size Frame size (width, height).
 * @param isColor True if video is in color.
 */
SaveVid_Thread::SaveVid_Thread(cv::String fileName, int codec, int FPS, cv::Size size, bool isColor)
{
    oVideoWriter.open(fileName, codec, FPS, size, isColor);
}

/**
 * @brief Runs the thread function: displays and writes a video frame.
 * @param frame Video frame to display and save.
 */
void SaveVid_Thread::run(cv::Mat frame)
{
    cv::imshow("runSave:", frame);
    oVideoWriter.write(frame);
}

/**
 * @brief Saves a single video frame to the output file.
 * @param frame Video frame to save.
 */
void SaveVid_Thread::saveFrame(cv::Mat frame)
{
    oVideoWriter.write(frame);
}

/**
 * @brief Configures the video writer with new parameters.
 * @param fileName Output video file path.
 * @param codec FourCC codec identifier.
 * @param FPS Frames per second.
 * @param size Frame size (width, height).
 * @param isColor True if video is in color.
 */
void SaveVid_Thread::setVideoWriter(cv::String fileName, int codec, int FPS, cv::Size size, bool isColor)
{
    oVideoWriter.open(fileName, codec, FPS, size, isColor);
}
