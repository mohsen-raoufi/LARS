#ifndef MAINWINDOW_H
#define MAINWINDOW_H

/**
 * @file mainwindow.h
 * @brief Main window class for the LARS GUI, managing UI events, robot tracking, video, and arena controls.
 *
 * This class handles all primary GUI logic and interfaces with hardware controllers, tracking, and experimental logic.
 */

#include <QMainWindow>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/opencv.hpp>
#include <opencv2/video.hpp>
//#include <opencv2/videoio.hpp>
#include <opencv2/imgcodecs.hpp>
//#include <opencv2/tracking.hpp>
#include <iostream>
#include <fstream>

#include <QTimer>
#include <QMouseEvent>
#include <QRubberBand>
#include <QFileDialog>
#include <QDebug>

//#include <QElapsedTimer>
#include <QThread>

#include <stdio.h>
#include <stdlib.h>

#include "etc/publicvars.h"
#include "qcustomplot.h"

//#include <stdexcept>

//#include "savevid_thread.h"
#include "savevidthread.h"

#include "tracker/robottracker.h"
#include "Kilobot/kilobotoverheadcontroller.h"
//#include "Kilobot/kilobotexperiment.h"
//#include "Kilobot/kilobotcalibrate.h"

#include "arenaWindow.h"
#include "ui/renderarea.h"
#include "ui/worldmodel.h"

#include "envbrain.h"

typedef struct
{
    QRect BoundingRect;
    int id;
} detectedMarker;


#define PAGE_SIZE 128
#define PACKET_HEADER 0x55
#define PACKET_SIZE   PAGE_SIZE+4

enum {
    PACKET_STOP,
    PACKET_LEDTOGGLE,
    PACKET_FORWARDMSG,
    PACKET_FORWARDRAWMSG,
    PACKET_BOOTPAGE
};

typedef enum {
    NORMAL = 0,
    GPS,
    SPECIAL = 0x80,
    BOOT = 0x80,
    BOOTPGM_PAGE,
    BOOTPGM_SIZE,
    RESET,
    SLEEP,
    WAKEUP,
    CHARGE,
    VOLTAGE,
    RUN,
    READUID,
    CALIB
} message_type_t;


enum {
    CALIB_SAVE,
    CALIB_UID,
    CALIB_TURN_LEFT,
    CALIB_TURN_RIGHT,
    CALIB_STRAIGHT
};

#pragma pack(1)
typedef  struct  __attribute__((__packed__)) {
    uint8_t mode;
    uint16_t uid;
    uint8_t turn_left;
    uint8_t turn_right;
    uint8_t straight_left;
    uint8_t straight_right;
    uint16_t unused;
} calibmsg_t;


namespace Ui {
class MainWindow;
}

/**
 * @brief Main application window for the LARS system.
 *
 * Handles all GUI events, robot tracking, data logging, and interface to the overhead controller.
 */
class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    /**
     * @brief Constructs the main application window.
     * @param parent Pointer to parent widget (default nullptr).
     */
    explicit MainWindow(QWidget *parent = 0);
    /**
     * @brief Destructor for MainWindow.
     */
    ~MainWindow();

    WorldModel wm;

private slots:

    void logToFile(QVector<Kilobot *> kiloVec);
    void logToFile(QVector<QPoint> posVec);
    void logToFile_PosLED(QVector<Kilobot *> kiloVec);

    void on_capturing_button_clicked();

    void convertInt2HexStr(int input, std::string &output);

    void showImage(cv::Mat frame);

    void writeSettings();

    void readSettings();

    void myDebug(QString string);

    void getKilos(QVector<Kilobot *> kiloVec);

    void getDrawnCircles(QVector <drawnCircle> circsToDraw);

    void drawOverlay(Mat &frame);

    void drawKilobots(Mat &frame);

    void drawHeatMapOnGUI(Mat &frame);

    void findMarkerRect();

    /// @name Calibration Slots
    /// @{
    void calibrateKilobot();

    void calibUID(int);
    void calibLeft(int);
    void calibRight(int);
    void calibStraight(int);
    void calibSave();
    void calibStop();
    /// @}

    void on_fromVid_rButton_clicked();

    void on_fromCam_rButton_clicked();

    void rot90(cv::Mat &matImage, int rotflag);

    //-------Mouse Functions---------
    //    bool eventFilter(QObject *obj, QEvent *event);

    void mousePressEvent(QMouseEvent *event) override;

    void mouseMoveEvent(QMouseEvent *event) override;

    void mouseReleaseEvent(QMouseEvent *event) override;

    bool isValidPlaceForSelect(int x, int y);

    // ...

    void on_open_set_button_clicked();

    void on_Rotate_ComboBox_activated(const QString &arg1);

    void on_saveVid_button_clicked();

    void uiInitialization();

    void plotData(QCustomPlot *customPlot, double value);

    void initializePlot(QCustomPlot *customPlot);

    void resetHeatMap();

    /// @name GUI Slots
    /// @{
    // -------------------------------------------------------------------------------------------
    // GUI Functions

    void update_wmMarkers();

    void on_debug_CheckBox_clicked();

//    void on_save_var_button_clicked();

//    void on_load_var_button_clicked();

    void SendKeyBoardData(int key);

    void keyPressEvent(QKeyEvent *key) override;

//    void on_JoyStick_button_pressed();

    void on_ArenaWindow_button_clicked();

    void updateColors();

    void updateColors(QString colorString);

    void updateSliders();

    void on_userRed_pushButton_clicked();

    void on_userBlue_pushButton_clicked();

    void on_fullScreen_pushButton_clicked();

    void on_fitRect_pushButton_clicked();

    void on_fromImage_pushButton_clicked();


    void on_saveSetting_pushButton_clicked();

    void on_loadSetting_pushButton_clicked();

    void on_startTracking_pushButton_clicked();

    void update_startTracking_pushBotton();

    void on_detectKilobots_pushButton_clicked();


    void on_crop_pushButton_clicked();

    void on_detectMarker_pushButton_clicked();

    void on_markerWidth_Slider_sliderMoved(int position);

    void on_debug_tracker_stateChanged(int arg1);

    void on_maxDispl_slider_sliderMoved(int position);

    void on_EFWL_slider_sliderMoved(int position);

//    void on_nullRob_pushButton_clicked();

    void on_robRendRad_slider_sliderMoved(int position);

    void on_smoothnessFact_slider_sliderMoved(int position);

    void on_imageExpField_pushButton_clicked(bool checked);

    void on_initPoints_pushButton_clicked(bool checked);

    void on_resetTrace_pushButton_clicked();




    void on_drawTrace_CheckBox_stateChanged(int arg1);

    void on_shuffleImageExpField_pushButton_clicked();

    void on_drawBoundary_CheckBox_stateChanged(int arg1);

    void on_drawHeatMap_CheckBox_clicked();

    void on_drawColCircles_CheckBox_clicked(bool checked);


    // for kilobot calibration
//    void transmitKiloState(kilobot_message);

    void on_seaBlue_pushButton_clicked();

    void on_drawRobCircles_CheckBox_clicked(bool checked);

    void on_ohc_set_prog_clicked();

    void on_writeLog_button_clicked(bool checked);

    void on_env2_rButton_clicked(bool checked);

    void on_env1_rButton_clicked(bool checked);

    void on_openImageField_pushButton_clicked();

    void on_env3_rButton_clicked();

    void on_env4_rButton_clicked();

    void on_gradientExpField_pushButton_clicked();

    void on_noiseTiles_slider_valueChanged(int value);

    void on_noiseFreq_slider_valueChanged(int value);

    void on_noiseStrength_slider_valueChanged(int value);

    void on_draw_network_stateChanged(int arg1);

    void on_sliderRandom0_valueChanged(int value);

    void on_noise_radioButton_clicked(bool checked);

    void on_draw_centroid_stateChanged(int arg1);

    void on_draw_voronoii_stateChanged(int arg1);

    void on_draw_bots_colors_stateChanged(int arg1);

    void on_sliderRandom1_valueChanged(int value);

    void on_draw_spatial_netw_stateChanged(int arg1);

    void on_drawBall_stateChanged(int arg1);
    /// @}

    void on_videoExpField_pushButton_clicked(bool checked);

private:
    Ui::MainWindow *ui;

    publicVars *publicVar;

    ArenaWindow *arenaWindow, *arenaWindow2;

    EnvBrain *envBrain;

    QList<QScreen*> screensList;

    QColor bg_color;

    KilobotTracker kbtracker;
    KilobotOverheadController ohc;

    CalibWindow *calib;
    SerialConnection *serial_conn;

    saveVidThread *sRawVidThrd, *sProcVidThrd;

    QGraphicsScene *scene;


    // Store the rect and id of aruco markers
    QList<detectedMarker> detectedMarkersList;
    QList<QPoint> detectedMarkerCenterList;

    QPoint mapPoint(QPoint P, QVector2D scale, QVector2D bias);
    QPoint mapPoint(QPoint P, Matx33f lambda);
    QPoint mapPoint(QPoint P, Matx33f rvec, Point3f tvec);
    cv::Mat mapA2C, mapC2A = cv::Mat::ones(3,3, CV_8UC3);


    QFile log_file;
    QTextStream log_stream;

    //-------------------------
    bool DebugAv, boolDebug = true, FilterAv;

    int prevKeyBoard;

    bool firstPointSelectedIsValid;
    bool tl_set, br_set, paused;
    bool boolSaveVideoFile = false;
    bool capturingBool = false;

    double FPS;
    double rotIndex;
    QElapsedTimer elapsedTimer;
    QPoint origin;
    QRubberBand *rubberBand;
    QPoint mouseBias;
    QRect cropQRect;
    bool cropRectDefined = false;

    QString srcStr;
    QTimer *timer, *joyStick_Timer;
    cv::Rect cropRect;
    QSize procQSize, GUIQSize, fullCapSize;
    cv::Size capSize, procSize;
    int ui_trigID_zero = 3;

    // For cropping
    QPoint TLInGUI, TLInFit, TLInCap;
    QSize sizeInGUI, sizeInFit, sizeInCap;

    QVector <drawnCircle> circlsToDraw;
    QVector <Kilobot *> kiloVector;
    QVector<QPoint> kiloPosVec;
    QList<Vec3f> detectedCircles;

    cv::Mat currentFrame, heatMapOnFrame;

    // Traces
    int listInd = 0, nList = 1000;


signals:
    void QImageProcReady(QImage image);
    void imageProcReady(cv::Mat image);
    void imageRawReceived(cv::Mat image);
    void clicked(const QString &text);
    void broadcastMessage(kilobot_broadcast msg);
    void sendKiloMessage(kilobot_message msg);
    void kilobotPosVecReady(QVector<QPoint> posVec);

};

#endif // MAINWINDOW_H
