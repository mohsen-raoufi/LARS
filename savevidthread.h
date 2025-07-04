#ifndef SAVEVIDTHREAD_H
#define SAVEVIDTHREAD_H
#include <QtCore>
#include <QImage>


#include <opencv2/opencv.hpp>
#include <opencv2/highgui.hpp>


class saveVidThread : public  QThread
{
    Q_OBJECT
public:
    saveVidThread(cv::String fileName, int codec, int FPS, cv::Size size, bool isColor);

private:
    cv::VideoWriter oVideoWriter;
    cv::Mat temp;

public slots:
    void run(cv::Mat frame);
    void run(QImage frame);
    void release();
    void saveFrame(cv::Mat frame);
};

#endif // SAVEVIDTHREAD_H
