
// Qt
#include <QtCore>
// OpenCV
#include <opencv2/opencv.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/objdetect.hpp>

#include <zbar.h>

using namespace cv;

typedef struct
{
    std::string type;
    std::string data;
    std::vector <Point> location;
} decodedObject;


class DetectQR : public QThread
{
    Q_OBJECT
public:
    explicit DetectQR(cv::Mat frame);
    ~DetectQR();
    void runDetectQR();

private:
    //        QImage frame;
    cv::Mat currentFrame;
protected:
    //        void run();

private slots:
    void decode(Mat &im, std::vector<decodedObject>&decodedObjects);
    void display(Mat &im, std::vector<decodedObject>&decodedObjects);

public slots:
    void decodePub(Mat &im, std::vector<decodedObject>&decodedObjects);
};


