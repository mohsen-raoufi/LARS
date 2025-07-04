#include "savevidthread.h"

saveVidThread::saveVidThread(cv::String fileName, int codec, int FPS, cv::Size size, bool isColor)
{
    oVideoWriter.open(fileName, codec, FPS, size, isColor);
}

void saveVidThread::run(cv::Mat frame)
{
    //    cv::imshow("runSave:", frame);
    oVideoWriter.write(frame);
    //    cv::waitKey(20);
}

void saveVidThread::run(QImage frame)
{
//    cv::Mat temp(frame.height(), frame.width(), CV_8UC3, (cv::Scalar*) frame.scanLine(0));
    temp = cv::Mat(frame.height(), frame.width(), CV_8UC3, (cv::Scalar*) frame.scanLine(0));
    oVideoWriter.write(temp);
}

void saveVidThread::release()
{
    oVideoWriter.release();
}

void saveVidThread::saveFrame(cv::Mat frame)
{
//    std::cout << "Save Vid Thread-frame width: " << frame.cols << ", " << frame.rows << std::endl;
//    oVideoWriter.write(frame);
}
