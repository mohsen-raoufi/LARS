#ifndef SAVEVID_THREAD_H
#define SAVEVID_THREAD_H
#include <QtCore>
#include <opencv2/opencv.hpp>
#include <opencv2/highgui.hpp>
#include <QObject>

class SaveVid_Thread : public  QThread
{
    Q_OBJECT
public:
    SaveVid_Thread(cv::String fileName, int codec, int FPS, cv::Size size, bool isColor);

private:
    cv::VideoWriter oVideoWriter;

public slots:
    void run(cv::Mat frame);
    void saveFrame(cv::Mat frame);
    void setVideoWriter(cv::String fileName, int codec, int FPS, cv::Size size, bool isColor);
};

#endif // SAVEVID_THREAD_H
