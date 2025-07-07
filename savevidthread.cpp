#include "savevidthread.h"

/**
 * @file savevidthread.cpp
 * @brief Implementation of saveVidThread, a threaded video writer for saving frames using OpenCV.
 *
 * Provides methods for starting, writing, and releasing video output in a separate thread context.
 */

/**
 * @brief Constructs the saveVidThread object and initializes the video writer.
 * @param fileName Output video file path.
 * @param codec FourCC codec identifier.
 * @param FPS Frames per second for video output.
 * @param size Frame size (width, height).
 * @param isColor True if video is in color.
 */
saveVidThread::saveVidThread(cv::String fileName, int codec, int FPS, cv::Size size, bool isColor)
{
    oVideoWriter.open(fileName, codec, FPS, size, isColor);
}

/**
 * @brief Writes a video frame (cv::Mat) to the output file.
 * @param frame Video frame to save.
 */
void saveVidThread::run(cv::Mat frame)
{
    //    cv::imshow("runSave:", frame);
    oVideoWriter.write(frame);
    //    cv::waitKey(20);
}

/**
 * @brief Converts a QImage frame to cv::Mat and writes it to the output file.
 * @param frame QImage frame to save.
 */
void saveVidThread::run(QImage frame)
{
//    cv::Mat temp(frame.height(), frame.width(), CV_8UC3, (cv::Scalar*) frame.scanLine(0));
    temp = cv::Mat(frame.height(), frame.width(), CV_8UC3, (cv::Scalar*) frame.scanLine(0));
    oVideoWriter.write(temp);
}

/**
 * @brief Releases the video writer and any associated resources.
 */
void saveVidThread::release()
{
    oVideoWriter.release();
}

/**
 * @brief Saves a single video frame (cv::Mat) to the output file.
 * @param frame Video frame to save.
 */
void saveVidThread::saveFrame(cv::Mat frame)
{
//    std::cout << "Save Vid Thread-frame width: " << frame.cols << ", " << frame.rows << std::endl;
//    oVideoWriter.write(frame);
}
