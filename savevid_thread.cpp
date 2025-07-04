#include "savevid_thread.h"
#include <QtCore>

#include <QDebug>
SaveVid_Thread::SaveVid_Thread(cv::String fileName, int codec, int FPS, cv::Size size, bool isColor)
{
    oVideoWriter.open(fileName, codec, FPS, size, isColor);
}

void SaveVid_Thread::run(cv::Mat frame)
{
    cv::imshow("runSave:", frame);
    oVideoWriter.write(frame);
}

void SaveVid_Thread::saveFrame(cv::Mat frame)
{
    oVideoWriter.write(frame);
}

void SaveVid_Thread::setVideoWriter(cv::String fileName, int codec, int FPS, cv::Size size, bool isColor)
{
    oVideoWriter.open(fileName, codec, FPS, size, isColor);
}
