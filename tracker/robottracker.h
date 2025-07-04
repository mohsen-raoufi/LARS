/*!
 * Kilobottracker.h
 *
 *  Rewritten on: April 2022
 *  Author: Mohsen Raoufi
 */

#ifndef ROBOTTRACKER_H
#define ROBOTTRACKER_H
#include <ios>
#include <vector>

#define USE_CUDA true
using namespace std;

// OpenCV 3 :
#include <opencv2/highgui.hpp>
#include <opencv2/video.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/videostab.hpp>
#include <opencv2/features2d.hpp>
//#include <opencv2/stitching.hpp>
#include <opencv2/opencv.hpp>
#include <opencv2/core/core.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/videoio.hpp>
#include <opencv2/core/ocl.hpp>
#include <opencv2/cudaarithm.hpp>
#include <opencv2/cudaimgproc.hpp>
#include <opencv2/cudafilters.hpp>
#include <opencv2/cudafeatures2d.hpp>
#include <opencv2/cudawarping.hpp>

#ifdef USE_CUDA
#define MAT_TYPE cuda::GpuMat
#define CV_NS cv::cuda::
#else
#define MAT_TYPE UMat
#define CV_NS cv::
#endif

// allow easy addressing of OpenCV functions
using namespace cv;

// Qt base include
#include <QObject>
#include <QPoint>
#include <QPixmap>

// for thread buffer communication
#include <QSemaphore>
#include <QTimer>
#include <QElapsedTimer>
#include <QTime>
//#include <QColor>
#include <QDebug>

#include "Kilobot/kilobot.h"

// buffers and semaphores
struct srcBuffer {
    MAT_TYPE full_warped_image;
};

#define BUFF_SIZE 2

#define IM_WIDTH 1920 //960 //  2304
#define IM_HEIGHT 1200 // 600 // 1536

//#define IDENTIFY_TIMEOUT 10
#define IDENTIFY_TIMEOUT 1

enum srcDataType {
    IMAGES,
    VIDEO,
    CAMERA
};

enum trackerType {
    NO_TRACK,
    CIRCLES_NAIVE,
    CIRCLES_LOCAL,
    MY_HAPPY_OTHER_TRACKER,
    MORFI_TRACKER
};

struct indexPair {
    int a;
    int b;
};

struct kiloLight {
    lightColour col;
    Point pos;
};

enum experimentType {
    IDENTIFY,
    ID_ASSIGNMENT,
    CALIBRATION,
    USER_EXP,
    VRK_EXP,
    M_EXP
};

// DRAWABLES:
struct drawnCircle {
    Point pos;
    int r;
    QColor col;
    int thickness;
    std::string text;
    bool transparent;
};

struct drawnLine {
    std::vector<Point> pos;
    QColor col;
    int thickness;
    std::string text;
    bool transparent;
};

class acquireThread;
//class KilobotExperiment;

/*!
 * \brief The KilobotTracker class
 *
 * This class contains the code that tracks Kilobots in the live camera or offline video feeds.
 *
 */
class KilobotTracker : public QObject
{
    Q_OBJECT

public:
    explicit KilobotTracker(QPoint smallImageSize = QPoint(300,300), QObject *parent = 0);
    ~KilobotTracker();


//    KilobotExperiment * expt; // Mohsen: do we need EXPERIMENT here?

    int dummyVar2000 = 2000; // MOHSEN! << just to check what is this value!

    //Default tracking parameters and identification parameters
#ifdef FOR_KILOBOT
//    int kbMinSize = 5;//3;
//    int kbMaxSize = 16;//22;
//    int houghAcc = 19; // 27;
//    int cannyThresh = 61; //40;

//    int kbMinSize = 10;//8;//10;//3;
//    int kbMaxSize = 17;//12;//18;//22;
//    int houghAcc = 9;//13;//12; // 27;
//    int cannyThresh = 119;//90;//112; //40;

    // Kilobots
    int kbMinSize = 12;
    int kbMaxSize = 17;
//    int kbBigMinSize = 25;
//    int kbBigMaxSize = 40;
    int houghAcc = 12;//13;//12; // 27;
    int cannyThresh = 129;//90;//112; //40;

//    // THYMIOS
//    int kbMinSize = 18;
//    int kbMaxSize = 29;
//    int houghAcc = 25;//13;//12; // 27;
//    int cannyThresh = 131;//90;//112; //40;

    int kbLEDMinSize = kbMinSize/7;//3;
    int kbLEDMaxSize = kbMinSize*10/7;//22; << !!
    int LEDhoughAcc = houghAcc; // 27;
    int LEDcannyThresh = cannyThresh; //40;


#else
    // THYMIOS on Floor
//    int kbMinSize = 33;
//    int kbMaxSize = 44;
//    int houghAcc = 23;//13;//12; // 27;
//    int cannyThresh = 131;//90;//112; //40;

//    int kbLEDMinSize = kbMinSize/7;//3;
//    int kbLEDMaxSize = kbMinSize*10/7;//22; << !!
//    int LEDhoughAcc = houghAcc; // 27;
//    int LEDcannyThresh = cannyThresh; //40;


    // THYMIOS on Floor/ half Resolution
    int kbMinSize = 14;
    int kbMaxSize = 26;
    int houghAcc = 23;//13;//12; // 27;
    int cannyThresh = 115;//90;//112; //40;

//    int kbLEDMinSize = kbMinSize/7;//3;
//    int kbLEDMaxSize = kbMinSize*10/7;//22; << !!

    int kbLEDMinSize = kbMinSize; // For Thymios
    int kbLEDMaxSize = kbMaxSize; // For Thymios
    int LEDhoughAcc = houghAcc; // 27;
    int LEDcannyThresh = cannyThresh; //40;

#endif

    int maxIDtoCheck = 100;
    uint manualID;


    float morfiTrack_maxDisplacement = 12.0;
    float EFWL = 2.0; // Expansion Factor for search When Lost
    float smooth_fact = 0.5; // for updating positions of kilobots

    // camera parameters
    int height_x_adj = 10;
    int height_y_adj = 10;

    //Default color threshold detection parameters
    float redLThreshold = 1.0; // 0.75;     //0.6
    float redHThreshold = 0.0;
    float greenLThreshold = 1.0; // 0.56;
    float greenHThreshold = 0.0; // 0.75;
    float blueLThreshold = 0.65;
    float blueHThreshold = 0.0;

    QList<Vec3f> detectedCircles;

    bool debugBool = false;//true;//false;
    bool drawDebugBool = false; //true;


signals:
    /*!
     * \brief errorMessage
     * Qt signal to update the UI message QLabel
     */
    void errorMessage(QString);

    void setStitchedImage(QPixmap);

    void capturedImage(cv::Mat);

    void identifyKilo(uint8_t);

    void broadcastMessage(kilobot_broadcast);

    void clearMsgQueue();

    void startExperiment(bool);

    void stopExperiment();

    void toggleExpButton(int);

    void activateExpButtons(int);

    void setRuntimeIdentificationLock(bool);

    void kiloList(QVector<Kilobot *>);

    void circlesToDrawSig(QVector < drawnCircle >);


public slots:
    /*!
     * \brief startLoop
     * This slot is the target of the timeout on the QTimer tick, and fetches warped images from the thread buffers and
     * stitches them
     */
    void LOOPstartstop(int stage);

    /*!
     * \brief iterateTracker
     * Use the existing feature matches to stitch the images and track the kilobots
     */
    void LOOPiterate();

    /*!
     * \brief loadCalibration
     * Load the calibration matrices from an OpenCV FileStorage format
     */
    void SETUPloadCalibration();


    // MOHSEN
    bool RUNcapture();

    /*!
     * \brief findKilobots
     * Find the locations of Kilobots in the stitched image
     */
    void SETUPfindKilobots();

    /*!
     * \brief identifyKilobots
     * Find out what IDs the Kilobots have
     */
    void identifyKilobots();


    // MOHSEN

    void updateCropPoints(QRect cropRect);

    QSize getImageSize();

//    void drawOverlayPub(Mat &);

//    void getCircles(QVector < drawnCircle >);



    // drawing slots
    void drawCircle(QPointF pos, float r, QColor col, int thickness = 2, std::string text ="", bool transparent = false) {
        int r_int = r;
        this->circsToDraw.push_back(drawnCircle {Point(pos.x(),pos.y()), r_int, col, thickness, text, transparent});
    }

    void drawLine(std::vector<cv::Point> pos, QColor col, int thickness = 2, std::string text ="", bool transparent = false) {
        this->linesToDraw.push_back(drawnLine {pos, col, thickness, text, transparent});
    }

    void clearDrawings() {
        this->circsToDraw.clear();
        this->linesToDraw.clear();
    }

    void drawCircleOnRecordedImage(QPointF pos, float r, QColor col, int thickness = 2, std::string text = "") {
        int r_int = r;
        this->circsToDrawFinal.push_back(drawnCircle {Point(pos.x(),pos.y()), r_int, col, thickness, text});
    }

    void clearDrawingsOnRecordedImage() {
        this->circsToDrawFinal.clear();
    }

    void saveImage(QString file) {
        if (!finalImageCol.empty()) {
            // before saving I draw what I need to draw on the FinalImage
            for (int i = 0; i < this->circsToDrawFinal.size(); ++i) {
                cv::circle(finalImageCol,this->circsToDrawFinal[i].pos, this->circsToDrawFinal[i].r,
                           Scalar(this->circsToDrawFinal[i].col.blue(),this->circsToDrawFinal[i].col.green(),this->circsToDrawFinal[i].col.red(),0.5),
                           this->circsToDrawFinal[i].thickness);
            }
            cv::imwrite(file.toStdString(),finalImageCol);
        }
    }

    void saveVideoFrames(QString file, unsigned int numofframes) {
        savecamerasframes = true;
        savecamerasframesdir=file;
        numberofframes=numofframes;
    }

    // accessors - docs not required??
    void setSourceType(bool val) {if (val) this->srcType = CAMERA; else this->srcType = VIDEO;}

    void setKbMin(int val){this->kbMinSize = val;}
    void setKbMax(int val) {this->kbMaxSize = val;}

//    void setKbBigMin(int val){this->kbBigMinSize = val;}
//    void setKbBigMax(int val) {this->kbBigMaxSize = val;}

    void setCannyThresh(int val) {this->cannyThresh = val;}
    void setHoughAcc(int val) {this->houghAcc = val;}

    void setKbLMin(int val){this->kbLEDMinSize = val;}
    void setKbLMax(int val) {this->kbLEDMaxSize = val;}
    void setLEDCannyThresh(int val) {this->LEDcannyThresh = val;}
    void setLEDHoughAcc(int val) {this->LEDhoughAcc = val;}


    void setLowRLED(int val){this->redLThreshold = (double) val/100.0;}// qDebug() << "value: " << this->redLThreshold;}
    void setLowGLED(int val) {this->greenLThreshold = (double) val/100.0;}
    void setLowBLED(int val) {this->blueLThreshold = (double) val/100.0;}
    void setHiRLED(int val){this->redHThreshold = (double) val/100.0;}
    void setHiGLED(int val) {this->greenHThreshold = (double) val/100.0;}
    void setHiBLED(int val) {this->blueHThreshold = (double) val/100.0;}


    void setHeightXSlider(int val) {this->height_x_adj = val;}
    void setHeightYSlider(int val) {this->height_y_adj = val;}

    void manuallyassignID(QPoint position);

    /*!
     * \brief setVideoDir
     * \param dir
     * Set the path to video files for tracking
     */
    void setVideoDir(QString dir) {this->videoPath = dir;}

    void updateKilobotStates();

    void getInitialKilobotStates();

    void setTrackingType(int t_type) {this->t_type = t_type;}
    void updateExperimentBroadcastingState(bool BroadcastingState)
    {
        experimentIsBroadcasting=BroadcastingState;
    }

    /*!
     * \brief showIds
     * \param toggle
     *
     * Accessor to allow drawing of KiloBot IDs
     */
    void showIds(bool toggle) {this->showIDs = toggle;}
    void detectred(bool toggle) {this->m_detectred = toggle;}
    void detectgreen(bool toggle) {this->m_detectgreen = toggle;}
    void detectblue(bool toggle) {this->m_detectblue = toggle;}
    void manualIDassignment(bool toggle) {this->m_assignIDmanually = toggle;}
    void enableRuntimeIdentification(bool toggle) {this->m_runtimeIDenabled = toggle;}


    void maxIDtoTry(QString maxIdStr) {this->maxIDtoCheck = maxIdStr.toInt();}
    void setManualID(QString manID) {this->manualID = manID.toUInt();}
    void setFlipangle(double angle);

    /*!
     * \brief RefreshDisplayedImage
     * Refresh the displayed image on the GUI
     */
    void RefreshDisplayedImage();

private:

    // PRIVATE METHODS


    /*!
     * \brief trackKilobots
     * The method used to contain the tracking algorithm for one timestep
     */
    void trackKilobots();

    /*!
     * \brief setupStitcher
     * Setup required after loading the calibration data
     */
    void SETUPstitcher();

    /*!
     * \brief showMat
     * Convert a Mat for display and send it as a QPixmap via the setStichedImage signal
     */
    void showMat(Mat &);

    /*!
     * \brief getKiloBotLight
     * \param channels
     * \param centreOfBox
     * \return
     * Used to detect the presence, colour, and position of a kiloBot's light and return it
     */

#ifdef USE_CUDA
    kiloLight getKiloBotLight(cuda::GpuMat  channels[3], Point centreOfBox, int index);
    kiloLight getKiloBotLightAdaptive(cuda::GpuMat  channels[3], Point centreOfBox, int index);
    void getKiloBotLights(Mat &display);
#else
    kiloLight getKiloBotLight(Mat channels[3], Point centreOfBox, int index);
    kiloLight getKiloBotLightAdaptive(Mat channels[3], Point centreOfBox, int index);
#endif

    /*!
     * \brief getKiloBotBoundingBox
     * \param index
     * \param scale
     * \return
     *
     * For a single Kilobot obtain an openCV Rect of the bounding box around the kilobot
     */
    Rect getKiloBotBoundingBox(int index, float scale);

    /*!
     * \brief launchThreads
     * Launches the threads for each of the source images
     */
    void THREADSlaunch();

    void THREADSstop();

    void identifyKilobot(int);
    void identifyKilobot(int,bool);

    void runtimeIdentify();

    void drawOverlay(Mat &);

    void getDetectedCircles();


    // INTERNAL VARIABLES
//    int t_type = POS | ADAPTIVE_LED | ROT;
    int t_type = POS | LED | ROT;

    bool experimentIsBroadcasting=false;

    Mat finalImageCol;

#ifdef USE_CUDA
    cuda::GpuMat finalImageB;
    cuda::GpuMat finalImageG;
    cuda::GpuMat finalImageR;
    cuda::GpuMat fullImages[3];

    // MOHSEN
    cuda::GpuMat fullImagesHSV[3];
    cuda::GpuMat grayImage, finalImageH, finalImageS, finalImageV;
    // make thread safe
    cuda::Stream stream;
//    cv::Mat finalCPUImage;
#else
    Mat finalImage;
    Mat fullImages[3];
#endif

    MAT_TYPE warpedImages;
    MAT_TYPE warpedMasks;
    Point corners;
    Size sizes;

    vector < Mat > Ks;
    vector < Mat > Rs;
    Point2f arenaCorners[4];
    bool haveCalibration = false;
    QTimer tick;

    acquireThread * threads = NULL;

    int time = 0;
    /*!
     * \brief smallImageSize
     * Assigned in the constructor
     */
    QPoint smallImageSize;

//    Ptr<detail::ExposureCompensator> compensator;
//    Ptr<detail::Blender> blender;

    QElapsedTimer timer;

    bool loadFirstIm = false;

    srcDataType srcType = CAMERA;
    QString videoPath;

    trackerType trackType = MORFI_TRACKER; // MORFI_TRACKER; // MY_HAPPY_OTHER_TRACKER; // CIRCLES_LOCAL;// CIRCLES_NAIVE;

    QVector < Kilobot * > kilos;

    QVector < float > kiloHeadings;

    QVector < QPointF > kiloOldPos;

    QVector < QVector < int > > exclusionTestsIndices;

    float last_time = 0.0f;

    Size fullSize;
    Point fullCorner;

    int currentID = 0;
    uint found = IDENTIFY_TIMEOUT;
    QVector < uint > foundIDs;
    QVector < int > assignedCircles;

    experimentType expType = VRK_EXP; // M_EXP;// USER_EXP; // VRK_EXP;

    Mat testAdap;

    QVector < drawnCircle > circsToDraw;
    QVector < drawnLine > linesToDraw;
    QVector < drawnCircle > circsToDrawFinal;

//    QList<Vec3f> detectedCircles;

#ifdef USE_CUDA
    Ptr<cuda::HoughCirclesDetector> hough;
    bool detectHeter = true;
    Ptr<cuda::HoughCirclesDetector> houghLarger;
    // RGB Hough
    Ptr<cuda::HoughCirclesDetector> hough2;
    cuda::GpuMat kbLocs;

    Ptr<cuda::CLAHE> clahe;
    Mat element = cv::getStructuringElement(MORPH_ELLIPSE,Size(7,7));
    Ptr<cuda::Filter> dilateFilter;
#endif

    bool showIDs = true;
    int flipangle = 0;
    bool m_detectred=true;
    bool m_detectgreen=true;
    bool m_detectblue=true;
    bool m_assignIDmanually=false;
    bool m_runtimeIDenabled=true;

    QVector <int> lost_count;

    int m_runtimeIdentificationTimer = 0;
    bool m_ongoingRuntimeIdentification = false;
    QVector <int> pendingRuntimeIdentification;
    QElapsedTimer runtimeIDtimer;

    //video saving
    bool savecamerasframes=false;
    unsigned int numberofframes;
    QString savecamerasframesdir;


};

#endif // ROBOTTRACKER_H
