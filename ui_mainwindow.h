/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.15.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtGui/QIcon>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QFormLayout>
#include <QtWidgets/QFrame>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QRadioButton>
#include <QtWidgets/QSlider>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QTabWidget>
#include <QtWidgets/QTextEdit>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>
#include "qcustomplot.h"

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QAction *actionExit;
    QAction *actionOpen;
    QAction *actionSave;
    QAction *actionExit_2;
    QAction *actionOpen_2;
    QAction *actionSave_2;
    QAction *actionExit_3;
    QWidget *centralWidget;
    QFrame *line;
    QFrame *line_12;
    QFrame *frame;
    QLabel *outputLabel;
    QLabel *error_label;
    QCustomPlot *customPlot;
    QTextEdit *textOut;
    QTextEdit *nonImpt;
    QTabWidget *tabWidget;
    QWidget *input_tab;
    QRadioButton *fromVid_rButton;
    QRadioButton *fromCam_rButton;
    QFrame *line_11;
    QPushButton *capturing_button;
    QWidget *layoutWidget_17;
    QHBoxLayout *horizontalLayout_Rotation_Select_2;
    QCheckBox *RotateCheckBox;
    QComboBox *Rotate_ComboBox;
    QWidget *layoutWidget_18;
    QHBoxLayout *horizontalLayout_CameraNoSelect_2;
    QLabel *cam_label_4;
    QComboBox *cam_comboBox;
    QWidget *layoutWidget_19;
    QHBoxLayout *horizontalLayout_21;
    QLabel *cam_label_5;
    QComboBox *FPS_comboBox;
    QWidget *layoutWidget_20;
    QGridLayout *gridLayout_7;
    QPushButton *saveSetting_pushButton;
    QPushButton *loadSetting_pushButton;
    QWidget *layoutWidget_21;
    QHBoxLayout *horizontalLayout_22;
    QCheckBox *debugAV_CheckBox;
    QCheckBox *debug_CheckBox;
    QCheckBox *useARKCap_CheckBox;
    QFrame *line_21;
    QWidget *layoutWidget_22;
    QVBoxLayout *verticalLayout_12;
    QHBoxLayout *horizontalLayout_23;
    QLabel *label_23;
    QPushButton *saveVid_button;
    QPushButton *open_set_button;
    QLineEdit *filePath_user;
    QPushButton *refresh_pushButton;
    QPushButton *crop_pushButton;
    QPushButton *detectMarker_pushButton;
    QSlider *markerWidth_Slider;
    QLabel *markerWidth_label;
    QPushButton *writeLog_button;
    QFrame *line_2;
    QComboBox *logType_comboBox;
    QLabel *label_28;
    QWidget *layoutWidget;
    QHBoxLayout *horizontalLayout_31;
    QRadioButton *env1_rButton;
    QRadioButton *env2_rButton;
    QRadioButton *env3_rButton;
    QRadioButton *env4_rButton;
    QLabel *label_22;
    QFrame *line_22;
    QFrame *line_23;
    QPushButton *detectKilobots_pushButton;
    QPushButton *startTracking_pushButton;
    QPushButton *ohc_connect;
    QWidget *layoutWidget1;
    QGridLayout *gridLayout_6;
    QLabel *cropTLTextLabel;
    QLabel *cropszTextLabel;
    QWidget *layoutWidget2;
    QGridLayout *gridLayout_5;
    QLineEdit *cropTL_xTextEdit;
    QLineEdit *cropTL_yTextEdit;
    QLineEdit *cropsz_wTextEdit;
    QLineEdit *cropsz_hTextEdit;
    QWidget *layoutWidget3;
    QGridLayout *gridLayout_8;
    QCheckBox *show_HM;
    QCheckBox *draw_bots;
    QCheckBox *show_ids;
    QCheckBox *drawBoundary_CheckBox;
    QCheckBox *show_vel;
    QCheckBox *draw_bots_colors;
    QTabWidget *tabWidget_2;
    QWidget *Kilobot_tab;
    QGroupBox *groupBox_2;
    QRadioButton *ohc_run;
    QRadioButton *ohc_reset;
    QRadioButton *ohc_sleep;
    QRadioButton *ohc_volt;
    QRadioButton *ohc_stop;
    QWidget *layoutWidget4;
    QGridLayout *gridLayout_4;
    QPushButton *ohc_set_prog;
    QPushButton *ohc_upload_prog;
    QPushButton *sendBatch_pushButton;
    QPushButton *calibrate_pushButton;
    QWidget *tab_2;
    QPushButton *test_eval_pushButton;
    QWidget *Camera_tab;
    QPushButton *AFSens_Norm_pushButton;
    QLabel *label_27;
    QPushButton *AFSens_Low_pushButton;
    QPushButton *WhiteBal_Auto_pushButton;
    QLabel *label_29;
    QLabel *label_30;
    QPushButton *AE_Auto_pushButton;
    QPushButton *AE_Manual_pushButton;
    QLabel *label_33;
    QPushButton *CamBright_Up_pushButton;
    QPushButton *CamBright_Down_pushButton;
    QPushButton *CamBright_Reset_pushButton;
    QFrame *line_35;
    QSlider *tempVal_SlideBar;
    QLabel *tempVal_Value;
    QLabel *nonImpt2;
    QWidget *colorWidget;
    QFrame *frame_2;
    QGroupBox *groupBox_3;
    QWidget *verticalLayoutWidget_3;
    QVBoxLayout *verticalLayout_3;
    QHBoxLayout *horizontalLayout_16;
    QVBoxLayout *verticalLayout_11;
    QPushButton *gradientExpField_pushButton;
    QPushButton *imageExpField_pushButton;
    QPushButton *videoExpField_pushButton;
    QPushButton *nullExpField_pushButton;
    QPushButton *generateExpField_pushButton;
    QSpacerItem *horizontalSpacer_3;
    QHBoxLayout *horizontalLayout_5;
    QVBoxLayout *verticalLayout_13;
    QSpacerItem *verticalSpacer_3;
    QPushButton *shuffleImageExpField_pushButton;
    QSpacerItem *verticalSpacer_2;
    QSpacerItem *verticalSpacer_8;
    QComboBox *generate_comboBox;
    QVBoxLayout *verticalLayout_20;
    QSpacerItem *verticalSpacer_5;
    QRadioButton *noise_radioButton;
    QSpacerItem *verticalSpacer_4;
    QSpacerItem *verticalSpacer_7;
    QLineEdit *genExp_TextEdit;
    QHBoxLayout *horizontalLayout_11;
    QLineEdit *arenaImage_TextEdit;
    QPushButton *openImageField_pushButton;
    QGroupBox *groupBox_5;
    QWidget *verticalLayoutWidget;
    QVBoxLayout *verticalLayout_5;
    QHBoxLayout *horizontalLayout_35;
    QLabel *label_34;
    QSlider *noiseFreq_slider;
    QLabel *noiseFreq_label;
    QHBoxLayout *horizontalLayout_29;
    QLabel *label_31;
    QSlider *noiseTiles_slider;
    QLabel *noTiles_label;
    QHBoxLayout *horizontalLayout_34;
    QLabel *label_32;
    QSlider *noiseStrength_slider;
    QLabel *noiseStrenght_label;
    QFrame *frame_4;
    QWidget *verticalLayoutWidget_2;
    QVBoxLayout *verticalLayout_19;
    QHBoxLayout *horizontalLayout_10;
    QCheckBox *debug_tracker;
    QGridLayout *gridLayout;
    QHBoxLayout *horizontalLayout_4;
    QLabel *label_42;
    QSlider *maxDispl_slider;
    QLabel *maxDispl_label;
    QHBoxLayout *horizontalLayout_8;
    QLabel *label_43;
    QSlider *EFWL_slider;
    QLabel *EFWL_label;
    QHBoxLayout *horizontalLayout_9;
    QLabel *label_50;
    QSlider *smoothnessFact_slider;
    QLabel *smoothnessFact_label;
    QFrame *line_19;
    QVBoxLayout *verticalLayout_9;
    QFrame *line_16;
    QVBoxLayout *verticalLayout_2;
    QLabel *label_17;
    QLabel *label_44;
    QVBoxLayout *verticalLayout;
    QHBoxLayout *horizontalLayout_12;
    QLabel *label_15;
    QSlider *cannyThresh_slider;
    QLabel *cannyThresh_label;
    QHBoxLayout *horizontalLayout_13;
    QLabel *label_18;
    QSlider *houghAcc_slider;
    QLabel *houghAcc_label;
    QHBoxLayout *horizontalLayout_14;
    QLabel *label_16;
    QSlider *kbMin_slider;
    QLabel *kbMin_label;
    QHBoxLayout *horizontalLayout_15;
    QLabel *label_14;
    QSlider *kbMax_slider;
    QLabel *kbMax_label;
    QFrame *line_18;
    QLabel *label_45;
    QHBoxLayout *horizontalLayout_6;
    QCheckBox *red_checkBox;
    QCheckBox *green_checkBox;
    QCheckBox *blue_checkBox;
    QVBoxLayout *verticalLayout_4;
    QHBoxLayout *horizontalLayout_18;
    QLabel *label_36;
    QSlider *cannyThreshLED_slider;
    QLabel *cannyThreshLED_label;
    QHBoxLayout *horizontalLayout_19;
    QLabel *label_37;
    QSlider *houghAccLED_slider;
    QLabel *houghAccLED_label;
    QHBoxLayout *horizontalLayout_20;
    QLabel *label_38;
    QSlider *kbMinLED_slider;
    QLabel *kbMinLED_label;
    QHBoxLayout *horizontalLayout_27;
    QLabel *label_39;
    QSlider *kbMaxLED_slider;
    QLabel *kbMaxLED_label;
    QVBoxLayout *verticalLayout_8;
    QHBoxLayout *horizontalLayout;
    QLabel *label_46;
    QSlider *lowRLED_slider;
    QLabel *lowRLED_label;
    QSlider *hiRLED_slider;
    QLabel *hiRLED_label;
    QHBoxLayout *horizontalLayout_2;
    QLabel *label_47;
    QSlider *lowGLED_slider;
    QLabel *lowGLED_label;
    QSlider *hiGLED_slider;
    QLabel *hiGLED_label;
    QHBoxLayout *horizontalLayout_3;
    QLabel *label_48;
    QSlider *lowBLED_slider;
    QLabel *lowBLED_label;
    QSlider *hiBLED_slider;
    QLabel *hiBLED_label;
    QLabel *label_6;
    QLabel *label;
    QFrame *frame_5;
    QWidget *gridLayoutWidget;
    QGridLayout *gridLayout_2;
    QGridLayout *gridLayout_9;
    QSpacerItem *verticalSpacer;
    QPushButton *resetHMap_pushButton;
    QPushButton *fitRect_pushButton;
    QPushButton *fromImage_pushButton;
    QPushButton *resetTrace_pushButton;
    QCheckBox *drawBall;
    QVBoxLayout *verticalLayout_10;
    QCheckBox *drawTrace_CheckBox;
    QCheckBox *drawHeatMap_CheckBox;
    QCheckBox *drawRobCircles_CheckBox;
    QCheckBox *drawColCircles_CheckBox;
    QCheckBox *draw_network;
    QCheckBox *draw_centroid;
    QCheckBox *draw_voronoii;
    QCheckBox *draw_spatial_netw;
    QFrame *frame_3;
    QWidget *layoutWidget_24;
    QVBoxLayout *verticalLayout_15;
    QVBoxLayout *verticalLayout_16;
    QHBoxLayout *horizontalLayout_24;
    QLabel *label_40;
    QLabel *label_24;
    QLabel *label_25;
    QLabel *label_26;
    QHBoxLayout *horizontalLayout_25;
    QLabel *H_label;
    QLabel *S_label;
    QLabel *V_label;
    QLabel *A_label;
    QHBoxLayout *horizontalLayout_26;
    QSlider *H_slider;
    QSlider *S_slider;
    QSlider *V_slider;
    QSlider *A_slider;
    QWidget *layoutWidget5;
    QVBoxLayout *verticalLayout_14;
    QPushButton *red_pushButton;
    QPushButton *blue_pushButton;
    QPushButton *green_pushButton;
    QPushButton *white_pushButton;
    QPushButton *black_pushButton;
    QPushButton *userRed_pushButton;
    QPushButton *userBlue_pushButton;
    QPushButton *seaBlue_pushButton;
    QGroupBox *groupBox;
    QWidget *layoutWidget6;
    QVBoxLayout *verticalLayout_7;
    QRadioButton *radioButton;
    QRadioButton *radioButton_2;
    QRadioButton *radioButton_4;
    QRadioButton *radioButton_3;
    QLabel *label_49;
    QWidget *layoutWidget7;
    QHBoxLayout *horizontalLayout_30;
    QSlider *robRendRad_slider;
    QLabel *V_label_2;
    QGroupBox *groupBox_4;
    QWidget *layoutWidget_7;
    QVBoxLayout *verticalLayout_18;
    QPushButton *gradientRob_pushButton;
    QPushButton *solidRob_pushButton;
    QPushButton *nullRob_pushButton;
    QWidget *layoutWidget8;
    QVBoxLayout *verticalLayout_17;
    QHBoxLayout *horizontalLayout_32;
    QLabel *label_2;
    QSlider *sliderRandom0;
    QLabel *sliderRand0_label;
    QHBoxLayout *horizontalLayout_33;
    QLabel *label_3;
    QSlider *sliderRandom1;
    QLabel *sliderRand1_label;
    QFrame *line_17;
    QWidget *horizontalLayoutWidget;
    QHBoxLayout *horizontalLayout_17;
    QPushButton *fullScreen_pushButton;
    QPushButton *ArenaWindow_button;
    QLabel *cam_label_6;
    QComboBox *screen_comboBox;
    QWidget *layoutWidget9;
    QGridLayout *gridLayout_10;
    QLabel *label_51;
    QSpacerItem *horizontalSpacer;
    QComboBox *TrigID_comboBox;
    QWidget *layoutWidget10;
    QGridLayout *gridLayout_11;
    QPushButton *initPoints_pushButton;
    QComboBox *initPoints_comboBox;
    QLabel *label_4;
    QLabel *label_5;
    QWidget *layoutWidget11;
    QFormLayout *formLayout_2;
    QWidget *layoutWidget12;
    QFormLayout *formLayout_3;
    QButtonGroup *buttonGroupPaintObject;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QString::fromUtf8("MainWindow"));
        MainWindow->setEnabled(true);
        MainWindow->resize(1714, 990);
        MainWindow->setMouseTracking(false);
        MainWindow->setAcceptDrops(false);
        actionExit = new QAction(MainWindow);
        actionExit->setObjectName(QString::fromUtf8("actionExit"));
        actionOpen = new QAction(MainWindow);
        actionOpen->setObjectName(QString::fromUtf8("actionOpen"));
        actionOpen->setCheckable(false);
        actionSave = new QAction(MainWindow);
        actionSave->setObjectName(QString::fromUtf8("actionSave"));
        actionExit_2 = new QAction(MainWindow);
        actionExit_2->setObjectName(QString::fromUtf8("actionExit_2"));
        actionOpen_2 = new QAction(MainWindow);
        actionOpen_2->setObjectName(QString::fromUtf8("actionOpen_2"));
        actionSave_2 = new QAction(MainWindow);
        actionSave_2->setObjectName(QString::fromUtf8("actionSave_2"));
        actionExit_3 = new QAction(MainWindow);
        actionExit_3->setObjectName(QString::fromUtf8("actionExit_3"));
        centralWidget = new QWidget(MainWindow);
        centralWidget->setObjectName(QString::fromUtf8("centralWidget"));
        line = new QFrame(centralWidget);
        line->setObjectName(QString::fromUtf8("line"));
        line->setGeometry(QRect(660, 5, 20, 971));
        line->setLineWidth(2);
        line->setFrameShape(QFrame::VLine);
        line->setFrameShadow(QFrame::Sunken);
        line_12 = new QFrame(centralWidget);
        line_12->setObjectName(QString::fromUtf8("line_12"));
        line_12->setGeometry(QRect(8, 660, 660, 20));
        line_12->setLineWidth(2);
        line_12->setFrameShape(QFrame::HLine);
        line_12->setFrameShadow(QFrame::Sunken);
        frame = new QFrame(centralWidget);
        frame->setObjectName(QString::fromUtf8("frame"));
        frame->setGeometry(QRect(5, 4, 1701, 981));
        frame->setFrameShape(QFrame::StyledPanel);
        frame->setFrameShadow(QFrame::Raised);
        outputLabel = new QLabel(frame);
        outputLabel->setObjectName(QString::fromUtf8("outputLabel"));
        outputLabel->setEnabled(true);
        outputLabel->setGeometry(QRect(10, 10, 640, 640));
        outputLabel->setMouseTracking(true);
        outputLabel->setAcceptDrops(true);
        outputLabel->setStyleSheet(QString::fromUtf8("border-image: url(:/Files/LARS_Logo.png) 0 0 0 0 stretch stretch;"));
        outputLabel->setFrameShape(QFrame::Panel);
        outputLabel->setFrameShadow(QFrame::Plain);
        outputLabel->setLineWidth(2);
        outputLabel->setMargin(-1);
        error_label = new QLabel(frame);
        error_label->setObjectName(QString::fromUtf8("error_label"));
        error_label->setGeometry(QRect(30, 30, 431, 20));
        error_label->setStyleSheet(QString::fromUtf8("color: rgb(252, 175, 62);"));
        customPlot = new QCustomPlot(frame);
        customPlot->setObjectName(QString::fromUtf8("customPlot"));
        customPlot->setGeometry(QRect(330, 700, 321, 261));
        customPlot->setStyleSheet(QString::fromUtf8("background-color: rgb(221, 254, 255);"));
        textOut = new QTextEdit(frame);
        textOut->setObjectName(QString::fromUtf8("textOut"));
        textOut->setGeometry(QRect(10, 700, 311, 261));
        textOut->setFrameShape(QFrame::StyledPanel);
        textOut->setFrameShadow(QFrame::Raised);
        textOut->setReadOnly(true);
        nonImpt = new QTextEdit(frame);
        nonImpt->setObjectName(QString::fromUtf8("nonImpt"));
        nonImpt->setGeometry(QRect(10, 670, 81, 31));
        nonImpt->setFrameShape(QFrame::NoFrame);
        nonImpt->setReadOnly(true);
        tabWidget = new QTabWidget(frame);
        tabWidget->setObjectName(QString::fromUtf8("tabWidget"));
        tabWidget->setGeometry(QRect(673, 30, 351, 941));
        QFont font;
        font.setPointSize(9);
        font.setStrikeOut(false);
        font.setKerning(true);
        tabWidget->setFont(font);
        tabWidget->setCursor(QCursor(Qt::ArrowCursor));
        input_tab = new QWidget();
        input_tab->setObjectName(QString::fromUtf8("input_tab"));
        fromVid_rButton = new QRadioButton(input_tab);
        fromVid_rButton->setObjectName(QString::fromUtf8("fromVid_rButton"));
        fromVid_rButton->setGeometry(QRect(10, 10, 107, 25));
        QFont font1;
        font1.setPointSize(12);
        font1.setStrikeOut(false);
        font1.setKerning(true);
        fromVid_rButton->setFont(font1);
        fromVid_rButton->setChecked(false);
        fromCam_rButton = new QRadioButton(input_tab);
        fromCam_rButton->setObjectName(QString::fromUtf8("fromCam_rButton"));
        fromCam_rButton->setGeometry(QRect(200, 10, 107, 25));
        fromCam_rButton->setFont(font1);
        fromCam_rButton->setChecked(true);
        line_11 = new QFrame(input_tab);
        line_11->setObjectName(QString::fromUtf8("line_11"));
        line_11->setGeometry(QRect(0, -5, 341, 20));
        line_11->setFrameShape(QFrame::HLine);
        line_11->setFrameShadow(QFrame::Sunken);
        capturing_button = new QPushButton(input_tab);
        capturing_button->setObjectName(QString::fromUtf8("capturing_button"));
        capturing_button->setGeometry(QRect(30, 104, 191, 41));
        QFont font2;
        font2.setPointSize(13);
        font2.setBold(true);
        font2.setUnderline(false);
        font2.setStrikeOut(false);
        font2.setKerning(true);
        capturing_button->setFont(font2);
        capturing_button->setCheckable(true);
        layoutWidget_17 = new QWidget(input_tab);
        layoutWidget_17->setObjectName(QString::fromUtf8("layoutWidget_17"));
        layoutWidget_17->setGeometry(QRect(160, 70, 170, 29));
        horizontalLayout_Rotation_Select_2 = new QHBoxLayout(layoutWidget_17);
        horizontalLayout_Rotation_Select_2->setSpacing(6);
        horizontalLayout_Rotation_Select_2->setContentsMargins(11, 11, 11, 11);
        horizontalLayout_Rotation_Select_2->setObjectName(QString::fromUtf8("horizontalLayout_Rotation_Select_2"));
        horizontalLayout_Rotation_Select_2->setContentsMargins(0, 0, 0, 0);
        RotateCheckBox = new QCheckBox(layoutWidget_17);
        RotateCheckBox->setObjectName(QString::fromUtf8("RotateCheckBox"));

        horizontalLayout_Rotation_Select_2->addWidget(RotateCheckBox);

        Rotate_ComboBox = new QComboBox(layoutWidget_17);
        Rotate_ComboBox->addItem(QString());
        Rotate_ComboBox->addItem(QString());
        Rotate_ComboBox->addItem(QString());
        Rotate_ComboBox->setObjectName(QString::fromUtf8("Rotate_ComboBox"));

        horizontalLayout_Rotation_Select_2->addWidget(Rotate_ComboBox);

        layoutWidget_18 = new QWidget(input_tab);
        layoutWidget_18->setObjectName(QString::fromUtf8("layoutWidget_18"));
        layoutWidget_18->setGeometry(QRect(10, 40, 145, 29));
        horizontalLayout_CameraNoSelect_2 = new QHBoxLayout(layoutWidget_18);
        horizontalLayout_CameraNoSelect_2->setSpacing(6);
        horizontalLayout_CameraNoSelect_2->setContentsMargins(11, 11, 11, 11);
        horizontalLayout_CameraNoSelect_2->setObjectName(QString::fromUtf8("horizontalLayout_CameraNoSelect_2"));
        horizontalLayout_CameraNoSelect_2->setContentsMargins(0, 0, 0, 0);
        cam_label_4 = new QLabel(layoutWidget_18);
        cam_label_4->setObjectName(QString::fromUtf8("cam_label_4"));

        horizontalLayout_CameraNoSelect_2->addWidget(cam_label_4);

        cam_comboBox = new QComboBox(layoutWidget_18);
        cam_comboBox->addItem(QString());
        cam_comboBox->addItem(QString());
        cam_comboBox->addItem(QString());
        cam_comboBox->addItem(QString());
        cam_comboBox->setObjectName(QString::fromUtf8("cam_comboBox"));
        cam_comboBox->setEnabled(true);

        horizontalLayout_CameraNoSelect_2->addWidget(cam_comboBox);

        layoutWidget_19 = new QWidget(input_tab);
        layoutWidget_19->setObjectName(QString::fromUtf8("layoutWidget_19"));
        layoutWidget_19->setGeometry(QRect(10, 70, 141, 29));
        horizontalLayout_21 = new QHBoxLayout(layoutWidget_19);
        horizontalLayout_21->setSpacing(6);
        horizontalLayout_21->setContentsMargins(11, 11, 11, 11);
        horizontalLayout_21->setObjectName(QString::fromUtf8("horizontalLayout_21"));
        horizontalLayout_21->setContentsMargins(0, 0, 0, 0);
        cam_label_5 = new QLabel(layoutWidget_19);
        cam_label_5->setObjectName(QString::fromUtf8("cam_label_5"));

        horizontalLayout_21->addWidget(cam_label_5);

        FPS_comboBox = new QComboBox(layoutWidget_19);
        FPS_comboBox->addItem(QString());
        FPS_comboBox->addItem(QString());
        FPS_comboBox->addItem(QString());
        FPS_comboBox->addItem(QString());
        FPS_comboBox->addItem(QString());
        FPS_comboBox->setObjectName(QString::fromUtf8("FPS_comboBox"));
        FPS_comboBox->setEnabled(true);
        FPS_comboBox->setEditable(false);

        horizontalLayout_21->addWidget(FPS_comboBox);

        layoutWidget_20 = new QWidget(input_tab);
        layoutWidget_20->setObjectName(QString::fromUtf8("layoutWidget_20"));
        layoutWidget_20->setGeometry(QRect(10, 758, 321, 25));
        gridLayout_7 = new QGridLayout(layoutWidget_20);
        gridLayout_7->setSpacing(6);
        gridLayout_7->setContentsMargins(11, 11, 11, 11);
        gridLayout_7->setObjectName(QString::fromUtf8("gridLayout_7"));
        gridLayout_7->setContentsMargins(0, 0, 0, 0);
        saveSetting_pushButton = new QPushButton(layoutWidget_20);
        saveSetting_pushButton->setObjectName(QString::fromUtf8("saveSetting_pushButton"));

        gridLayout_7->addWidget(saveSetting_pushButton, 0, 0, 1, 1);

        loadSetting_pushButton = new QPushButton(layoutWidget_20);
        loadSetting_pushButton->setObjectName(QString::fromUtf8("loadSetting_pushButton"));

        gridLayout_7->addWidget(loadSetting_pushButton, 0, 1, 1, 1);

        layoutWidget_21 = new QWidget(input_tab);
        layoutWidget_21->setObjectName(QString::fromUtf8("layoutWidget_21"));
        layoutWidget_21->setGeometry(QRect(160, 40, 171, 31));
        horizontalLayout_22 = new QHBoxLayout(layoutWidget_21);
        horizontalLayout_22->setSpacing(6);
        horizontalLayout_22->setContentsMargins(11, 11, 11, 11);
        horizontalLayout_22->setObjectName(QString::fromUtf8("horizontalLayout_22"));
        horizontalLayout_22->setContentsMargins(0, 0, 0, 0);
        debugAV_CheckBox = new QCheckBox(layoutWidget_21);
        debugAV_CheckBox->setObjectName(QString::fromUtf8("debugAV_CheckBox"));
        debugAV_CheckBox->setChecked(true);

        horizontalLayout_22->addWidget(debugAV_CheckBox);

        debug_CheckBox = new QCheckBox(layoutWidget_21);
        debug_CheckBox->setObjectName(QString::fromUtf8("debug_CheckBox"));
        debug_CheckBox->setChecked(true);

        horizontalLayout_22->addWidget(debug_CheckBox);

        useARKCap_CheckBox = new QCheckBox(input_tab);
        useARKCap_CheckBox->setObjectName(QString::fromUtf8("useARKCap_CheckBox"));
        useARKCap_CheckBox->setGeometry(QRect(230, 112, 111, 21));
        useARKCap_CheckBox->setChecked(true);
        line_21 = new QFrame(input_tab);
        line_21->setObjectName(QString::fromUtf8("line_21"));
        line_21->setGeometry(QRect(3, 446, 341, 20));
        line_21->setFrameShape(QFrame::HLine);
        line_21->setFrameShadow(QFrame::Sunken);
        layoutWidget_22 = new QWidget(input_tab);
        layoutWidget_22->setObjectName(QString::fromUtf8("layoutWidget_22"));
        layoutWidget_22->setGeometry(QRect(10, 844, 321, 60));
        verticalLayout_12 = new QVBoxLayout(layoutWidget_22);
        verticalLayout_12->setSpacing(6);
        verticalLayout_12->setContentsMargins(11, 11, 11, 11);
        verticalLayout_12->setObjectName(QString::fromUtf8("verticalLayout_12"));
        verticalLayout_12->setContentsMargins(0, 0, 0, 0);
        horizontalLayout_23 = new QHBoxLayout();
        horizontalLayout_23->setSpacing(6);
        horizontalLayout_23->setObjectName(QString::fromUtf8("horizontalLayout_23"));
        label_23 = new QLabel(layoutWidget_22);
        label_23->setObjectName(QString::fromUtf8("label_23"));

        horizontalLayout_23->addWidget(label_23);

        saveVid_button = new QPushButton(layoutWidget_22);
        saveVid_button->setObjectName(QString::fromUtf8("saveVid_button"));
        saveVid_button->setEnabled(true);
        saveVid_button->setCheckable(true);

        horizontalLayout_23->addWidget(saveVid_button);

        open_set_button = new QPushButton(layoutWidget_22);
        open_set_button->setObjectName(QString::fromUtf8("open_set_button"));

        horizontalLayout_23->addWidget(open_set_button);


        verticalLayout_12->addLayout(horizontalLayout_23);

        filePath_user = new QLineEdit(layoutWidget_22);
        filePath_user->setObjectName(QString::fromUtf8("filePath_user"));
        filePath_user->setEnabled(false);
        filePath_user->setFocusPolicy(Qt::StrongFocus);
        filePath_user->setAcceptDrops(true);
        filePath_user->setAutoFillBackground(false);
        filePath_user->setStyleSheet(QString::fromUtf8("background-color: rgb(180, 180, 180); color: rgb(0, 0, 0);\n"
""));
        filePath_user->setFrame(true);
        filePath_user->setDragEnabled(true);
        filePath_user->setClearButtonEnabled(true);

        verticalLayout_12->addWidget(filePath_user);

        refresh_pushButton = new QPushButton(input_tab);
        refresh_pushButton->setObjectName(QString::fromUtf8("refresh_pushButton"));
        refresh_pushButton->setEnabled(false);
        refresh_pushButton->setGeometry(QRect(230, 140, 91, 27));
        QIcon icon;
        icon.addFile(QString::fromUtf8(":/images/refresh.png"), QSize(), QIcon::Normal, QIcon::On);
        refresh_pushButton->setIcon(icon);
        crop_pushButton = new QPushButton(input_tab);
        crop_pushButton->setObjectName(QString::fromUtf8("crop_pushButton"));
        crop_pushButton->setGeometry(QRect(210, 180, 91, 51));
        QFont font3;
        font3.setPointSize(9);
        font3.setBold(true);
        font3.setStrikeOut(false);
        font3.setKerning(true);
        crop_pushButton->setFont(font3);
        crop_pushButton->setIcon(icon);
        crop_pushButton->setCheckable(true);
        detectMarker_pushButton = new QPushButton(input_tab);
        detectMarker_pushButton->setObjectName(QString::fromUtf8("detectMarker_pushButton"));
        detectMarker_pushButton->setGeometry(QRect(30, 276, 181, 51));
        QFont font4;
        font4.setPointSize(11);
        font4.setBold(true);
        font4.setStrikeOut(false);
        font4.setKerning(true);
        detectMarker_pushButton->setFont(font4);
        detectMarker_pushButton->setIcon(icon);
        detectMarker_pushButton->setCheckable(false);
        markerWidth_Slider = new QSlider(input_tab);
        markerWidth_Slider->setObjectName(QString::fromUtf8("markerWidth_Slider"));
        markerWidth_Slider->setGeometry(QRect(30, 431, 271, 20));
        markerWidth_Slider->setMaximum(200);
        markerWidth_Slider->setPageStep(2);
        markerWidth_Slider->setValue(50);
        markerWidth_Slider->setOrientation(Qt::Horizontal);
        markerWidth_label = new QLabel(input_tab);
        markerWidth_label->setObjectName(QString::fromUtf8("markerWidth_label"));
        markerWidth_label->setGeometry(QRect(304, 428, 17, 18));
        writeLog_button = new QPushButton(input_tab);
        writeLog_button->setObjectName(QString::fromUtf8("writeLog_button"));
        writeLog_button->setEnabled(true);
        writeLog_button->setGeometry(QRect(120, 810, 101, 23));
        writeLog_button->setCheckable(true);
        line_2 = new QFrame(input_tab);
        line_2->setObjectName(QString::fromUtf8("line_2"));
        line_2->setGeometry(QRect(102, 808, 3, 61));
        line_2->setFrameShape(QFrame::VLine);
        line_2->setFrameShadow(QFrame::Sunken);
        logType_comboBox = new QComboBox(input_tab);
        logType_comboBox->addItem(QString());
        logType_comboBox->addItem(QString());
        logType_comboBox->addItem(QString());
        logType_comboBox->addItem(QString());
        logType_comboBox->setObjectName(QString::fromUtf8("logType_comboBox"));
        logType_comboBox->setGeometry(QRect(230, 810, 101, 26));
        label_28 = new QLabel(input_tab);
        label_28->setObjectName(QString::fromUtf8("label_28"));
        label_28->setGeometry(QRect(240, 790, 71, 24));
        QFont font5;
        font5.setPointSize(7);
        font5.setStrikeOut(false);
        font5.setKerning(true);
        label_28->setFont(font5);
        layoutWidget = new QWidget(input_tab);
        layoutWidget->setObjectName(QString::fromUtf8("layoutWidget"));
        layoutWidget->setGeometry(QRect(40, 240, 273, 28));
        horizontalLayout_31 = new QHBoxLayout(layoutWidget);
        horizontalLayout_31->setSpacing(6);
        horizontalLayout_31->setContentsMargins(11, 11, 11, 11);
        horizontalLayout_31->setObjectName(QString::fromUtf8("horizontalLayout_31"));
        horizontalLayout_31->setContentsMargins(0, 0, 0, 0);
        env1_rButton = new QRadioButton(layoutWidget);
        env1_rButton->setObjectName(QString::fromUtf8("env1_rButton"));
        env1_rButton->setFont(font1);
        env1_rButton->setChecked(true);

        horizontalLayout_31->addWidget(env1_rButton);

        env2_rButton = new QRadioButton(layoutWidget);
        env2_rButton->setObjectName(QString::fromUtf8("env2_rButton"));
        env2_rButton->setFont(font1);
        env2_rButton->setChecked(false);

        horizontalLayout_31->addWidget(env2_rButton);

        env3_rButton = new QRadioButton(layoutWidget);
        env3_rButton->setObjectName(QString::fromUtf8("env3_rButton"));
        env3_rButton->setFont(font1);
        env3_rButton->setChecked(false);

        horizontalLayout_31->addWidget(env3_rButton);

        env4_rButton = new QRadioButton(layoutWidget);
        env4_rButton->setObjectName(QString::fromUtf8("env4_rButton"));
        env4_rButton->setFont(font1);
        env4_rButton->setChecked(false);

        horizontalLayout_31->addWidget(env4_rButton);

        label_22 = new QLabel(input_tab);
        label_22->setObjectName(QString::fromUtf8("label_22"));
        label_22->setGeometry(QRect(34, 418, 64, 18));
        line_22 = new QFrame(input_tab);
        line_22->setObjectName(QString::fromUtf8("line_22"));
        line_22->setGeometry(QRect(3, 777, 341, 20));
        line_22->setFrameShape(QFrame::HLine);
        line_22->setFrameShadow(QFrame::Sunken);
        line_23 = new QFrame(input_tab);
        line_23->setObjectName(QString::fromUtf8("line_23"));
        line_23->setGeometry(QRect(3, 744, 341, 20));
        line_23->setFrameShape(QFrame::HLine);
        line_23->setFrameShadow(QFrame::Sunken);
        detectKilobots_pushButton = new QPushButton(input_tab);
        detectKilobots_pushButton->setObjectName(QString::fromUtf8("detectKilobots_pushButton"));
        detectKilobots_pushButton->setGeometry(QRect(39, 462, 271, 31));
        QFont font6;
        font6.setPointSize(12);
        font6.setBold(true);
        font6.setStrikeOut(false);
        font6.setKerning(true);
        detectKilobots_pushButton->setFont(font6);
        startTracking_pushButton = new QPushButton(input_tab);
        startTracking_pushButton->setObjectName(QString::fromUtf8("startTracking_pushButton"));
        startTracking_pushButton->setGeometry(QRect(39, 497, 271, 51));
        QFont font7;
        font7.setPointSize(14);
        font7.setBold(true);
        font7.setStrikeOut(false);
        font7.setKerning(true);
        startTracking_pushButton->setFont(font7);
        startTracking_pushButton->setStyleSheet(QString::fromUtf8("background-color: rgb(35, 37, 37);\n"
"color: rgb(255, 255, 255);"));
        startTracking_pushButton->setCheckable(false);
        startTracking_pushButton->setChecked(false);
        startTracking_pushButton->setFlat(false);
        ohc_connect = new QPushButton(input_tab);
        ohc_connect->setObjectName(QString::fromUtf8("ohc_connect"));
        ohc_connect->setGeometry(QRect(38, 552, 273, 22));
        layoutWidget1 = new QWidget(input_tab);
        layoutWidget1->setObjectName(QString::fromUtf8("layoutWidget1"));
        layoutWidget1->setGeometry(QRect(30, 180, 55, 61));
        gridLayout_6 = new QGridLayout(layoutWidget1);
        gridLayout_6->setSpacing(6);
        gridLayout_6->setContentsMargins(11, 11, 11, 11);
        gridLayout_6->setObjectName(QString::fromUtf8("gridLayout_6"));
        gridLayout_6->setContentsMargins(0, 0, 0, 0);
        cropTLTextLabel = new QLabel(layoutWidget1);
        cropTLTextLabel->setObjectName(QString::fromUtf8("cropTLTextLabel"));

        gridLayout_6->addWidget(cropTLTextLabel, 0, 0, 1, 1);

        cropszTextLabel = new QLabel(layoutWidget1);
        cropszTextLabel->setObjectName(QString::fromUtf8("cropszTextLabel"));

        gridLayout_6->addWidget(cropszTextLabel, 1, 0, 1, 1);

        layoutWidget2 = new QWidget(input_tab);
        layoutWidget2->setObjectName(QString::fromUtf8("layoutWidget2"));
        layoutWidget2->setGeometry(QRect(90, 180, 111, 60));
        gridLayout_5 = new QGridLayout(layoutWidget2);
        gridLayout_5->setSpacing(6);
        gridLayout_5->setContentsMargins(11, 11, 11, 11);
        gridLayout_5->setObjectName(QString::fromUtf8("gridLayout_5"));
        gridLayout_5->setContentsMargins(0, 0, 0, 0);
        cropTL_xTextEdit = new QLineEdit(layoutWidget2);
        cropTL_xTextEdit->setObjectName(QString::fromUtf8("cropTL_xTextEdit"));
        cropTL_xTextEdit->setEnabled(true);
        cropTL_xTextEdit->setFocusPolicy(Qt::StrongFocus);
        cropTL_xTextEdit->setAcceptDrops(true);
        cropTL_xTextEdit->setAutoFillBackground(false);
        cropTL_xTextEdit->setStyleSheet(QString::fromUtf8("background-color: rgb(255, 255, 255); \n"
"color: rgb(0, 0, 0);\n"
""));
        cropTL_xTextEdit->setFrame(true);
        cropTL_xTextEdit->setDragEnabled(true);
        cropTL_xTextEdit->setClearButtonEnabled(false);

        gridLayout_5->addWidget(cropTL_xTextEdit, 0, 0, 1, 1);

        cropTL_yTextEdit = new QLineEdit(layoutWidget2);
        cropTL_yTextEdit->setObjectName(QString::fromUtf8("cropTL_yTextEdit"));
        cropTL_yTextEdit->setEnabled(true);
        cropTL_yTextEdit->setFocusPolicy(Qt::StrongFocus);
        cropTL_yTextEdit->setAcceptDrops(true);
        cropTL_yTextEdit->setAutoFillBackground(false);
        cropTL_yTextEdit->setStyleSheet(QString::fromUtf8("background-color: rgb(255, 255, 255); \n"
"color: rgb(0, 0, 0);\n"
""));
        cropTL_yTextEdit->setFrame(true);
        cropTL_yTextEdit->setDragEnabled(true);
        cropTL_yTextEdit->setClearButtonEnabled(false);

        gridLayout_5->addWidget(cropTL_yTextEdit, 0, 1, 1, 1);

        cropsz_wTextEdit = new QLineEdit(layoutWidget2);
        cropsz_wTextEdit->setObjectName(QString::fromUtf8("cropsz_wTextEdit"));
        cropsz_wTextEdit->setEnabled(true);
        cropsz_wTextEdit->setFocusPolicy(Qt::StrongFocus);
        cropsz_wTextEdit->setAcceptDrops(true);
        cropsz_wTextEdit->setAutoFillBackground(false);
        cropsz_wTextEdit->setStyleSheet(QString::fromUtf8("background-color: rgb(255, 255, 255); \n"
"color: rgb(0, 0, 0);\n"
""));
        cropsz_wTextEdit->setFrame(true);
        cropsz_wTextEdit->setDragEnabled(true);
        cropsz_wTextEdit->setClearButtonEnabled(false);

        gridLayout_5->addWidget(cropsz_wTextEdit, 1, 0, 1, 1);

        cropsz_hTextEdit = new QLineEdit(layoutWidget2);
        cropsz_hTextEdit->setObjectName(QString::fromUtf8("cropsz_hTextEdit"));
        cropsz_hTextEdit->setEnabled(true);
        cropsz_hTextEdit->setFocusPolicy(Qt::StrongFocus);
        cropsz_hTextEdit->setAcceptDrops(true);
        cropsz_hTextEdit->setAutoFillBackground(false);
        cropsz_hTextEdit->setStyleSheet(QString::fromUtf8("background-color: rgb(255, 255, 255); \n"
"color: rgb(0, 0, 0);\n"
""));
        cropsz_hTextEdit->setFrame(true);
        cropsz_hTextEdit->setDragEnabled(true);
        cropsz_hTextEdit->setClearButtonEnabled(false);

        gridLayout_5->addWidget(cropsz_hTextEdit, 1, 1, 1, 1);

        layoutWidget3 = new QWidget(input_tab);
        layoutWidget3->setObjectName(QString::fromUtf8("layoutWidget3"));
        layoutWidget3->setGeometry(QRect(220, 270, 107, 158));
        gridLayout_8 = new QGridLayout(layoutWidget3);
        gridLayout_8->setSpacing(6);
        gridLayout_8->setContentsMargins(11, 11, 11, 11);
        gridLayout_8->setObjectName(QString::fromUtf8("gridLayout_8"));
        gridLayout_8->setContentsMargins(0, 0, 0, 0);
        show_HM = new QCheckBox(layoutWidget3);
        show_HM->setObjectName(QString::fromUtf8("show_HM"));
        show_HM->setChecked(false);

        gridLayout_8->addWidget(show_HM, 1, 0, 1, 1);

        draw_bots = new QCheckBox(layoutWidget3);
        draw_bots->setObjectName(QString::fromUtf8("draw_bots"));
        draw_bots->setChecked(true);

        gridLayout_8->addWidget(draw_bots, 2, 0, 1, 1);

        show_ids = new QCheckBox(layoutWidget3);
        show_ids->setObjectName(QString::fromUtf8("show_ids"));
        show_ids->setChecked(true);

        gridLayout_8->addWidget(show_ids, 6, 0, 1, 1);

        drawBoundary_CheckBox = new QCheckBox(layoutWidget3);
        drawBoundary_CheckBox->setObjectName(QString::fromUtf8("drawBoundary_CheckBox"));
        drawBoundary_CheckBox->setChecked(true);

        gridLayout_8->addWidget(drawBoundary_CheckBox, 0, 0, 1, 1);

        show_vel = new QCheckBox(layoutWidget3);
        show_vel->setObjectName(QString::fromUtf8("show_vel"));
        show_vel->setChecked(false);

        gridLayout_8->addWidget(show_vel, 4, 0, 1, 1);

        draw_bots_colors = new QCheckBox(input_tab);
        draw_bots_colors->setObjectName(QString::fromUtf8("draw_bots_colors"));
        draw_bots_colors->setGeometry(QRect(124, 336, 89, 21));
        draw_bots_colors->setChecked(false);
        tabWidget_2 = new QTabWidget(input_tab);
        tabWidget_2->setObjectName(QString::fromUtf8("tabWidget_2"));
        tabWidget_2->setGeometry(QRect(12, 576, 315, 175));
        Kilobot_tab = new QWidget();
        Kilobot_tab->setObjectName(QString::fromUtf8("Kilobot_tab"));
        groupBox_2 = new QGroupBox(Kilobot_tab);
        groupBox_2->setObjectName(QString::fromUtf8("groupBox_2"));
        groupBox_2->setGeometry(QRect(28, -2, 121, 119));
        ohc_run = new QRadioButton(groupBox_2);
        ohc_run->setObjectName(QString::fromUtf8("ohc_run"));
        ohc_run->setGeometry(QRect(10, 20, 100, 20));
        ohc_reset = new QRadioButton(groupBox_2);
        ohc_reset->setObjectName(QString::fromUtf8("ohc_reset"));
        ohc_reset->setGeometry(QRect(10, 40, 100, 20));
        ohc_sleep = new QRadioButton(groupBox_2);
        ohc_sleep->setObjectName(QString::fromUtf8("ohc_sleep"));
        ohc_sleep->setGeometry(QRect(10, 60, 100, 20));
        ohc_volt = new QRadioButton(groupBox_2);
        ohc_volt->setObjectName(QString::fromUtf8("ohc_volt"));
        ohc_volt->setGeometry(QRect(10, 80, 100, 20));
        ohc_volt->setChecked(false);
        ohc_stop = new QRadioButton(groupBox_2);
        ohc_stop->setObjectName(QString::fromUtf8("ohc_stop"));
        ohc_stop->setGeometry(QRect(10, 100, 100, 20));
        ohc_stop->setChecked(true);
        layoutWidget4 = new QWidget(Kilobot_tab);
        layoutWidget4->setObjectName(QString::fromUtf8("layoutWidget4"));
        layoutWidget4->setGeometry(QRect(162, 20, 131, 93));
        gridLayout_4 = new QGridLayout(layoutWidget4);
        gridLayout_4->setSpacing(6);
        gridLayout_4->setContentsMargins(11, 11, 11, 11);
        gridLayout_4->setObjectName(QString::fromUtf8("gridLayout_4"));
        gridLayout_4->setContentsMargins(0, 0, 0, 0);
        ohc_set_prog = new QPushButton(layoutWidget4);
        ohc_set_prog->setObjectName(QString::fromUtf8("ohc_set_prog"));

        gridLayout_4->addWidget(ohc_set_prog, 0, 0, 1, 1);

        ohc_upload_prog = new QPushButton(layoutWidget4);
        ohc_upload_prog->setObjectName(QString::fromUtf8("ohc_upload_prog"));

        gridLayout_4->addWidget(ohc_upload_prog, 1, 0, 1, 1);

        sendBatch_pushButton = new QPushButton(layoutWidget4);
        sendBatch_pushButton->setObjectName(QString::fromUtf8("sendBatch_pushButton"));

        gridLayout_4->addWidget(sendBatch_pushButton, 2, 0, 1, 1);

        calibrate_pushButton = new QPushButton(Kilobot_tab);
        calibrate_pushButton->setObjectName(QString::fromUtf8("calibrate_pushButton"));
        calibrate_pushButton->setEnabled(true);
        calibrate_pushButton->setGeometry(QRect(26, 118, 269, 26));
        tabWidget_2->addTab(Kilobot_tab, QString());
        tab_2 = new QWidget();
        tab_2->setObjectName(QString::fromUtf8("tab_2"));
        tabWidget_2->addTab(tab_2, QString());
        test_eval_pushButton = new QPushButton(input_tab);
        test_eval_pushButton->setObjectName(QString::fromUtf8("test_eval_pushButton"));
        test_eval_pushButton->setGeometry(QRect(32, 388, 181, 27));
        test_eval_pushButton->setFont(font4);
        test_eval_pushButton->setIcon(icon);
        test_eval_pushButton->setCheckable(false);
        tabWidget->addTab(input_tab, QString());
        Camera_tab = new QWidget();
        Camera_tab->setObjectName(QString::fromUtf8("Camera_tab"));
        AFSens_Norm_pushButton = new QPushButton(Camera_tab);
        AFSens_Norm_pushButton->setObjectName(QString::fromUtf8("AFSens_Norm_pushButton"));
        AFSens_Norm_pushButton->setGeometry(QRect(131, 76, 80, 23));
        label_27 = new QLabel(Camera_tab);
        label_27->setObjectName(QString::fromUtf8("label_27"));
        label_27->setGeometry(QRect(10, 80, 91, 16));
        AFSens_Low_pushButton = new QPushButton(Camera_tab);
        AFSens_Low_pushButton->setObjectName(QString::fromUtf8("AFSens_Low_pushButton"));
        AFSens_Low_pushButton->setGeometry(QRect(240, 76, 80, 23));
        WhiteBal_Auto_pushButton = new QPushButton(Camera_tab);
        WhiteBal_Auto_pushButton->setObjectName(QString::fromUtf8("WhiteBal_Auto_pushButton"));
        WhiteBal_Auto_pushButton->setGeometry(QRect(131, 140, 80, 23));
        label_29 = new QLabel(Camera_tab);
        label_29->setObjectName(QString::fromUtf8("label_29"));
        label_29->setGeometry(QRect(10, 143, 101, 16));
        label_30 = new QLabel(Camera_tab);
        label_30->setObjectName(QString::fromUtf8("label_30"));
        label_30->setGeometry(QRect(10, 202, 101, 16));
        AE_Auto_pushButton = new QPushButton(Camera_tab);
        AE_Auto_pushButton->setObjectName(QString::fromUtf8("AE_Auto_pushButton"));
        AE_Auto_pushButton->setGeometry(QRect(131, 199, 80, 23));
        AE_Manual_pushButton = new QPushButton(Camera_tab);
        AE_Manual_pushButton->setObjectName(QString::fromUtf8("AE_Manual_pushButton"));
        AE_Manual_pushButton->setGeometry(QRect(240, 199, 80, 23));
        label_33 = new QLabel(Camera_tab);
        label_33->setObjectName(QString::fromUtf8("label_33"));
        label_33->setGeometry(QRect(10, 250, 71, 16));
        CamBright_Up_pushButton = new QPushButton(Camera_tab);
        CamBright_Up_pushButton->setObjectName(QString::fromUtf8("CamBright_Up_pushButton"));
        CamBright_Up_pushButton->setGeometry(QRect(130, 270, 80, 23));
        CamBright_Down_pushButton = new QPushButton(Camera_tab);
        CamBright_Down_pushButton->setObjectName(QString::fromUtf8("CamBright_Down_pushButton"));
        CamBright_Down_pushButton->setGeometry(QRect(240, 270, 80, 23));
        CamBright_Reset_pushButton = new QPushButton(Camera_tab);
        CamBright_Reset_pushButton->setObjectName(QString::fromUtf8("CamBright_Reset_pushButton"));
        CamBright_Reset_pushButton->setGeometry(QRect(20, 270, 80, 23));
        line_35 = new QFrame(Camera_tab);
        line_35->setObjectName(QString::fromUtf8("line_35"));
        line_35->setGeometry(QRect(0, 940, 345, 5));
        line_35->setFrameShape(QFrame::HLine);
        line_35->setFrameShadow(QFrame::Sunken);
        tempVal_SlideBar = new QSlider(Camera_tab);
        tempVal_SlideBar->setObjectName(QString::fromUtf8("tempVal_SlideBar"));
        tempVal_SlideBar->setEnabled(true);
        tempVal_SlideBar->setGeometry(QRect(40, 50, 250, 10));
        QFont font8;
        font8.setPointSize(8);
        font8.setStrikeOut(false);
        font8.setKerning(true);
        tempVal_SlideBar->setFont(font8);
        tempVal_SlideBar->setMouseTracking(true);
        tempVal_SlideBar->setMinimum(0);
        tempVal_SlideBar->setMaximum(500);
        tempVal_SlideBar->setSingleStep(1);
        tempVal_SlideBar->setPageStep(1);
        tempVal_SlideBar->setValue(300);
        tempVal_SlideBar->setOrientation(Qt::Horizontal);
        tempVal_Value = new QLabel(Camera_tab);
        tempVal_Value->setObjectName(QString::fromUtf8("tempVal_Value"));
        tempVal_Value->setGeometry(QRect(295, 44, 31, 20));
        tempVal_Value->setFont(font8);
        nonImpt2 = new QLabel(Camera_tab);
        nonImpt2->setObjectName(QString::fromUtf8("nonImpt2"));
        nonImpt2->setGeometry(QRect(34, 35, 101, 20));
        nonImpt2->setFont(font8);
        tabWidget->addTab(Camera_tab, QString());
        colorWidget = new QWidget(frame);
        colorWidget->setObjectName(QString::fromUtf8("colorWidget"));
        colorWidget->setGeometry(QRect(1320, 40, 331, 931));
        frame_2 = new QFrame(colorWidget);
        frame_2->setObjectName(QString::fromUtf8("frame_2"));
        frame_2->setGeometry(QRect(9, 9, 311, 921));
        frame_2->setFrameShape(QFrame::StyledPanel);
        frame_2->setFrameShadow(QFrame::Raised);
        groupBox_3 = new QGroupBox(frame_2);
        groupBox_3->setObjectName(QString::fromUtf8("groupBox_3"));
        groupBox_3->setGeometry(QRect(11, 0, 291, 233));
        verticalLayoutWidget_3 = new QWidget(groupBox_3);
        verticalLayoutWidget_3->setObjectName(QString::fromUtf8("verticalLayoutWidget_3"));
        verticalLayoutWidget_3->setGeometry(QRect(4, 18, 285, 211));
        verticalLayout_3 = new QVBoxLayout(verticalLayoutWidget_3);
        verticalLayout_3->setSpacing(6);
        verticalLayout_3->setContentsMargins(11, 11, 11, 11);
        verticalLayout_3->setObjectName(QString::fromUtf8("verticalLayout_3"));
        verticalLayout_3->setContentsMargins(0, 0, 0, 0);
        horizontalLayout_16 = new QHBoxLayout();
        horizontalLayout_16->setSpacing(6);
        horizontalLayout_16->setObjectName(QString::fromUtf8("horizontalLayout_16"));
        verticalLayout_11 = new QVBoxLayout();
        verticalLayout_11->setSpacing(6);
        verticalLayout_11->setObjectName(QString::fromUtf8("verticalLayout_11"));
        gradientExpField_pushButton = new QPushButton(verticalLayoutWidget_3);
        gradientExpField_pushButton->setObjectName(QString::fromUtf8("gradientExpField_pushButton"));
        gradientExpField_pushButton->setStyleSheet(QString::fromUtf8(""));
        gradientExpField_pushButton->setCheckable(true);

        verticalLayout_11->addWidget(gradientExpField_pushButton);

        imageExpField_pushButton = new QPushButton(verticalLayoutWidget_3);
        imageExpField_pushButton->setObjectName(QString::fromUtf8("imageExpField_pushButton"));
        imageExpField_pushButton->setStyleSheet(QString::fromUtf8(""));
        imageExpField_pushButton->setCheckable(true);

        verticalLayout_11->addWidget(imageExpField_pushButton);

        videoExpField_pushButton = new QPushButton(verticalLayoutWidget_3);
        videoExpField_pushButton->setObjectName(QString::fromUtf8("videoExpField_pushButton"));
        videoExpField_pushButton->setStyleSheet(QString::fromUtf8(""));
        videoExpField_pushButton->setCheckable(true);

        verticalLayout_11->addWidget(videoExpField_pushButton);

        nullExpField_pushButton = new QPushButton(verticalLayoutWidget_3);
        nullExpField_pushButton->setObjectName(QString::fromUtf8("nullExpField_pushButton"));
        nullExpField_pushButton->setStyleSheet(QString::fromUtf8(""));
        nullExpField_pushButton->setCheckable(true);

        verticalLayout_11->addWidget(nullExpField_pushButton);

        generateExpField_pushButton = new QPushButton(verticalLayoutWidget_3);
        generateExpField_pushButton->setObjectName(QString::fromUtf8("generateExpField_pushButton"));
        generateExpField_pushButton->setStyleSheet(QString::fromUtf8(""));
        generateExpField_pushButton->setCheckable(false);

        verticalLayout_11->addWidget(generateExpField_pushButton);


        horizontalLayout_16->addLayout(verticalLayout_11);

        horizontalSpacer_3 = new QSpacerItem(20, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_16->addItem(horizontalSpacer_3);

        horizontalLayout_5 = new QHBoxLayout();
        horizontalLayout_5->setSpacing(6);
        horizontalLayout_5->setObjectName(QString::fromUtf8("horizontalLayout_5"));
        verticalLayout_13 = new QVBoxLayout();
        verticalLayout_13->setSpacing(6);
        verticalLayout_13->setObjectName(QString::fromUtf8("verticalLayout_13"));
        verticalSpacer_3 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout_13->addItem(verticalSpacer_3);

        shuffleImageExpField_pushButton = new QPushButton(verticalLayoutWidget_3);
        shuffleImageExpField_pushButton->setObjectName(QString::fromUtf8("shuffleImageExpField_pushButton"));
        QFont font9;
        font9.setPointSize(10);
        shuffleImageExpField_pushButton->setFont(font9);
        shuffleImageExpField_pushButton->setStyleSheet(QString::fromUtf8(""));

        verticalLayout_13->addWidget(shuffleImageExpField_pushButton);

        verticalSpacer_2 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout_13->addItem(verticalSpacer_2);

        verticalSpacer_8 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout_13->addItem(verticalSpacer_8);

        generate_comboBox = new QComboBox(verticalLayoutWidget_3);
        generate_comboBox->addItem(QString());
        generate_comboBox->addItem(QString());
        generate_comboBox->addItem(QString());
        generate_comboBox->addItem(QString());
        generate_comboBox->addItem(QString());
        generate_comboBox->setObjectName(QString::fromUtf8("generate_comboBox"));

        verticalLayout_13->addWidget(generate_comboBox);


        horizontalLayout_5->addLayout(verticalLayout_13);

        verticalLayout_20 = new QVBoxLayout();
        verticalLayout_20->setSpacing(6);
        verticalLayout_20->setObjectName(QString::fromUtf8("verticalLayout_20"));
        verticalSpacer_5 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout_20->addItem(verticalSpacer_5);

        noise_radioButton = new QRadioButton(verticalLayoutWidget_3);
        noise_radioButton->setObjectName(QString::fromUtf8("noise_radioButton"));
        noise_radioButton->setFont(font9);
        noise_radioButton->setStyleSheet(QString::fromUtf8(""));
        noise_radioButton->setChecked(false);

        verticalLayout_20->addWidget(noise_radioButton);

        verticalSpacer_4 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout_20->addItem(verticalSpacer_4);

        verticalSpacer_7 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout_20->addItem(verticalSpacer_7);

        genExp_TextEdit = new QLineEdit(verticalLayoutWidget_3);
        genExp_TextEdit->setObjectName(QString::fromUtf8("genExp_TextEdit"));
        genExp_TextEdit->setEnabled(true);
        QSizePolicy sizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(genExp_TextEdit->sizePolicy().hasHeightForWidth());
        genExp_TextEdit->setSizePolicy(sizePolicy);
        genExp_TextEdit->setFocusPolicy(Qt::StrongFocus);
        genExp_TextEdit->setAcceptDrops(true);
        genExp_TextEdit->setAutoFillBackground(false);
        genExp_TextEdit->setStyleSheet(QString::fromUtf8("background-color: rgb(255, 255, 255); \n"
"color: rgb(0, 0, 0);\n"
""));
        genExp_TextEdit->setFrame(true);
        genExp_TextEdit->setDragEnabled(true);
        genExp_TextEdit->setClearButtonEnabled(false);

        verticalLayout_20->addWidget(genExp_TextEdit);


        horizontalLayout_5->addLayout(verticalLayout_20);


        horizontalLayout_16->addLayout(horizontalLayout_5);


        verticalLayout_3->addLayout(horizontalLayout_16);

        horizontalLayout_11 = new QHBoxLayout();
        horizontalLayout_11->setSpacing(6);
        horizontalLayout_11->setObjectName(QString::fromUtf8("horizontalLayout_11"));
        arenaImage_TextEdit = new QLineEdit(verticalLayoutWidget_3);
        arenaImage_TextEdit->setObjectName(QString::fromUtf8("arenaImage_TextEdit"));
        arenaImage_TextEdit->setEnabled(true);
        arenaImage_TextEdit->setFocusPolicy(Qt::StrongFocus);
        arenaImage_TextEdit->setAcceptDrops(true);
        arenaImage_TextEdit->setAutoFillBackground(false);
        arenaImage_TextEdit->setStyleSheet(QString::fromUtf8("background-color: rgb(255, 255, 255); \n"
"color: rgb(0, 0, 0);\n"
""));
        arenaImage_TextEdit->setFrame(true);
        arenaImage_TextEdit->setDragEnabled(true);
        arenaImage_TextEdit->setClearButtonEnabled(false);

        horizontalLayout_11->addWidget(arenaImage_TextEdit);

        openImageField_pushButton = new QPushButton(verticalLayoutWidget_3);
        openImageField_pushButton->setObjectName(QString::fromUtf8("openImageField_pushButton"));
        openImageField_pushButton->setFont(font9);
        openImageField_pushButton->setStyleSheet(QString::fromUtf8(""));

        horizontalLayout_11->addWidget(openImageField_pushButton);


        verticalLayout_3->addLayout(horizontalLayout_11);

        groupBox_5 = new QGroupBox(frame_2);
        groupBox_5->setObjectName(QString::fromUtf8("groupBox_5"));
        groupBox_5->setGeometry(QRect(10, 236, 291, 111));
        verticalLayoutWidget = new QWidget(groupBox_5);
        verticalLayoutWidget->setObjectName(QString::fromUtf8("verticalLayoutWidget"));
        verticalLayoutWidget->setGeometry(QRect(2, 24, 287, 83));
        verticalLayout_5 = new QVBoxLayout(verticalLayoutWidget);
        verticalLayout_5->setSpacing(6);
        verticalLayout_5->setContentsMargins(11, 11, 11, 11);
        verticalLayout_5->setObjectName(QString::fromUtf8("verticalLayout_5"));
        verticalLayout_5->setContentsMargins(0, 0, 0, 0);
        horizontalLayout_35 = new QHBoxLayout();
        horizontalLayout_35->setSpacing(6);
        horizontalLayout_35->setObjectName(QString::fromUtf8("horizontalLayout_35"));
        label_34 = new QLabel(verticalLayoutWidget);
        label_34->setObjectName(QString::fromUtf8("label_34"));

        horizontalLayout_35->addWidget(label_34);

        noiseFreq_slider = new QSlider(verticalLayoutWidget);
        noiseFreq_slider->setObjectName(QString::fromUtf8("noiseFreq_slider"));
        noiseFreq_slider->setMinimum(1);
        noiseFreq_slider->setMaximum(2000);
        noiseFreq_slider->setSingleStep(10);
        noiseFreq_slider->setValue(1000);
        noiseFreq_slider->setOrientation(Qt::Horizontal);

        horizontalLayout_35->addWidget(noiseFreq_slider);

        noiseFreq_label = new QLabel(verticalLayoutWidget);
        noiseFreq_label->setObjectName(QString::fromUtf8("noiseFreq_label"));

        horizontalLayout_35->addWidget(noiseFreq_label);


        verticalLayout_5->addLayout(horizontalLayout_35);

        horizontalLayout_29 = new QHBoxLayout();
        horizontalLayout_29->setSpacing(6);
        horizontalLayout_29->setObjectName(QString::fromUtf8("horizontalLayout_29"));
        label_31 = new QLabel(verticalLayoutWidget);
        label_31->setObjectName(QString::fromUtf8("label_31"));

        horizontalLayout_29->addWidget(label_31);

        noiseTiles_slider = new QSlider(verticalLayoutWidget);
        noiseTiles_slider->setObjectName(QString::fromUtf8("noiseTiles_slider"));
        noiseTiles_slider->setMinimum(1);
        noiseTiles_slider->setMaximum(200);
        noiseTiles_slider->setValue(40);
        noiseTiles_slider->setOrientation(Qt::Horizontal);

        horizontalLayout_29->addWidget(noiseTiles_slider);

        noTiles_label = new QLabel(verticalLayoutWidget);
        noTiles_label->setObjectName(QString::fromUtf8("noTiles_label"));

        horizontalLayout_29->addWidget(noTiles_label);


        verticalLayout_5->addLayout(horizontalLayout_29);

        horizontalLayout_34 = new QHBoxLayout();
        horizontalLayout_34->setSpacing(6);
        horizontalLayout_34->setObjectName(QString::fromUtf8("horizontalLayout_34"));
        label_32 = new QLabel(verticalLayoutWidget);
        label_32->setObjectName(QString::fromUtf8("label_32"));

        horizontalLayout_34->addWidget(label_32);

        noiseStrength_slider = new QSlider(verticalLayoutWidget);
        noiseStrength_slider->setObjectName(QString::fromUtf8("noiseStrength_slider"));
        noiseStrength_slider->setMinimum(0);
        noiseStrength_slider->setMaximum(100);
        noiseStrength_slider->setValue(20);
        noiseStrength_slider->setOrientation(Qt::Horizontal);

        horizontalLayout_34->addWidget(noiseStrength_slider);

        noiseStrenght_label = new QLabel(verticalLayoutWidget);
        noiseStrenght_label->setObjectName(QString::fromUtf8("noiseStrenght_label"));

        horizontalLayout_34->addWidget(noiseStrenght_label);


        verticalLayout_5->addLayout(horizontalLayout_34);

        frame_4 = new QFrame(frame_2);
        frame_4->setObjectName(QString::fromUtf8("frame_4"));
        frame_4->setGeometry(QRect(10, 370, 291, 549));
        frame_4->setFrameShape(QFrame::StyledPanel);
        frame_4->setFrameShadow(QFrame::Raised);
        verticalLayoutWidget_2 = new QWidget(frame_4);
        verticalLayoutWidget_2->setObjectName(QString::fromUtf8("verticalLayoutWidget_2"));
        verticalLayoutWidget_2->setGeometry(QRect(4, 2, 283, 545));
        verticalLayout_19 = new QVBoxLayout(verticalLayoutWidget_2);
        verticalLayout_19->setSpacing(6);
        verticalLayout_19->setContentsMargins(11, 11, 11, 11);
        verticalLayout_19->setObjectName(QString::fromUtf8("verticalLayout_19"));
        verticalLayout_19->setContentsMargins(0, 0, 0, 0);
        horizontalLayout_10 = new QHBoxLayout();
        horizontalLayout_10->setSpacing(6);
        horizontalLayout_10->setObjectName(QString::fromUtf8("horizontalLayout_10"));
        debug_tracker = new QCheckBox(verticalLayoutWidget_2);
        debug_tracker->setObjectName(QString::fromUtf8("debug_tracker"));
        debug_tracker->setChecked(false);

        horizontalLayout_10->addWidget(debug_tracker);


        verticalLayout_19->addLayout(horizontalLayout_10);

        gridLayout = new QGridLayout();
        gridLayout->setSpacing(6);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        horizontalLayout_4 = new QHBoxLayout();
        horizontalLayout_4->setSpacing(6);
        horizontalLayout_4->setObjectName(QString::fromUtf8("horizontalLayout_4"));
        label_42 = new QLabel(verticalLayoutWidget_2);
        label_42->setObjectName(QString::fromUtf8("label_42"));

        horizontalLayout_4->addWidget(label_42);

        maxDispl_slider = new QSlider(verticalLayoutWidget_2);
        maxDispl_slider->setObjectName(QString::fromUtf8("maxDispl_slider"));
        maxDispl_slider->setMinimum(0);
        maxDispl_slider->setMaximum(300);
        maxDispl_slider->setValue(120);
        maxDispl_slider->setOrientation(Qt::Horizontal);

        horizontalLayout_4->addWidget(maxDispl_slider);

        maxDispl_label = new QLabel(verticalLayoutWidget_2);
        maxDispl_label->setObjectName(QString::fromUtf8("maxDispl_label"));

        horizontalLayout_4->addWidget(maxDispl_label);


        gridLayout->addLayout(horizontalLayout_4, 0, 0, 1, 1);

        horizontalLayout_8 = new QHBoxLayout();
        horizontalLayout_8->setSpacing(6);
        horizontalLayout_8->setObjectName(QString::fromUtf8("horizontalLayout_8"));
        label_43 = new QLabel(verticalLayoutWidget_2);
        label_43->setObjectName(QString::fromUtf8("label_43"));

        horizontalLayout_8->addWidget(label_43);

        EFWL_slider = new QSlider(verticalLayoutWidget_2);
        EFWL_slider->setObjectName(QString::fromUtf8("EFWL_slider"));
        EFWL_slider->setMinimum(0);
        EFWL_slider->setMaximum(100);
        EFWL_slider->setValue(50);
        EFWL_slider->setOrientation(Qt::Horizontal);

        horizontalLayout_8->addWidget(EFWL_slider);

        EFWL_label = new QLabel(verticalLayoutWidget_2);
        EFWL_label->setObjectName(QString::fromUtf8("EFWL_label"));

        horizontalLayout_8->addWidget(EFWL_label);


        gridLayout->addLayout(horizontalLayout_8, 1, 0, 1, 1);

        horizontalLayout_9 = new QHBoxLayout();
        horizontalLayout_9->setSpacing(6);
        horizontalLayout_9->setObjectName(QString::fromUtf8("horizontalLayout_9"));
        label_50 = new QLabel(verticalLayoutWidget_2);
        label_50->setObjectName(QString::fromUtf8("label_50"));

        horizontalLayout_9->addWidget(label_50);

        smoothnessFact_slider = new QSlider(verticalLayoutWidget_2);
        smoothnessFact_slider->setObjectName(QString::fromUtf8("smoothnessFact_slider"));
        smoothnessFact_slider->setMinimum(0);
        smoothnessFact_slider->setMaximum(100);
        smoothnessFact_slider->setValue(70);
        smoothnessFact_slider->setOrientation(Qt::Horizontal);

        horizontalLayout_9->addWidget(smoothnessFact_slider);

        smoothnessFact_label = new QLabel(verticalLayoutWidget_2);
        smoothnessFact_label->setObjectName(QString::fromUtf8("smoothnessFact_label"));

        horizontalLayout_9->addWidget(smoothnessFact_label);


        gridLayout->addLayout(horizontalLayout_9, 2, 0, 1, 1);


        verticalLayout_19->addLayout(gridLayout);

        line_19 = new QFrame(verticalLayoutWidget_2);
        line_19->setObjectName(QString::fromUtf8("line_19"));
        line_19->setStyleSheet(QString::fromUtf8(""));
        line_19->setFrameShape(QFrame::HLine);
        line_19->setFrameShadow(QFrame::Sunken);

        verticalLayout_19->addWidget(line_19);

        verticalLayout_9 = new QVBoxLayout();
        verticalLayout_9->setSpacing(6);
        verticalLayout_9->setObjectName(QString::fromUtf8("verticalLayout_9"));
        line_16 = new QFrame(verticalLayoutWidget_2);
        line_16->setObjectName(QString::fromUtf8("line_16"));
        line_16->setFrameShape(QFrame::HLine);
        line_16->setFrameShadow(QFrame::Sunken);

        verticalLayout_9->addWidget(line_16);

        verticalLayout_2 = new QVBoxLayout();
        verticalLayout_2->setSpacing(6);
        verticalLayout_2->setObjectName(QString::fromUtf8("verticalLayout_2"));
        label_17 = new QLabel(verticalLayoutWidget_2);
        label_17->setObjectName(QString::fromUtf8("label_17"));
        QSizePolicy sizePolicy1(QSizePolicy::Fixed, QSizePolicy::Fixed);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(label_17->sizePolicy().hasHeightForWidth());
        label_17->setSizePolicy(sizePolicy1);

        verticalLayout_2->addWidget(label_17);

        label_44 = new QLabel(verticalLayoutWidget_2);
        label_44->setObjectName(QString::fromUtf8("label_44"));
        QFont font10;
        font10.setBold(true);
        label_44->setFont(font10);

        verticalLayout_2->addWidget(label_44);


        verticalLayout_9->addLayout(verticalLayout_2);

        verticalLayout = new QVBoxLayout();
        verticalLayout->setSpacing(6);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        horizontalLayout_12 = new QHBoxLayout();
        horizontalLayout_12->setSpacing(6);
        horizontalLayout_12->setObjectName(QString::fromUtf8("horizontalLayout_12"));
        label_15 = new QLabel(verticalLayoutWidget_2);
        label_15->setObjectName(QString::fromUtf8("label_15"));

        horizontalLayout_12->addWidget(label_15);

        cannyThresh_slider = new QSlider(verticalLayoutWidget_2);
        cannyThresh_slider->setObjectName(QString::fromUtf8("cannyThresh_slider"));
        cannyThresh_slider->setMinimum(5);
        cannyThresh_slider->setMaximum(200);
        cannyThresh_slider->setValue(61);
        cannyThresh_slider->setOrientation(Qt::Horizontal);

        horizontalLayout_12->addWidget(cannyThresh_slider);

        cannyThresh_label = new QLabel(verticalLayoutWidget_2);
        cannyThresh_label->setObjectName(QString::fromUtf8("cannyThresh_label"));

        horizontalLayout_12->addWidget(cannyThresh_label);


        verticalLayout->addLayout(horizontalLayout_12);

        horizontalLayout_13 = new QHBoxLayout();
        horizontalLayout_13->setSpacing(6);
        horizontalLayout_13->setObjectName(QString::fromUtf8("horizontalLayout_13"));
        label_18 = new QLabel(verticalLayoutWidget_2);
        label_18->setObjectName(QString::fromUtf8("label_18"));

        horizontalLayout_13->addWidget(label_18);

        houghAcc_slider = new QSlider(verticalLayoutWidget_2);
        houghAcc_slider->setObjectName(QString::fromUtf8("houghAcc_slider"));
        houghAcc_slider->setMinimum(1);
        houghAcc_slider->setMaximum(100);
        houghAcc_slider->setValue(18);
        houghAcc_slider->setOrientation(Qt::Horizontal);

        horizontalLayout_13->addWidget(houghAcc_slider);

        houghAcc_label = new QLabel(verticalLayoutWidget_2);
        houghAcc_label->setObjectName(QString::fromUtf8("houghAcc_label"));

        horizontalLayout_13->addWidget(houghAcc_label);


        verticalLayout->addLayout(horizontalLayout_13);

        horizontalLayout_14 = new QHBoxLayout();
        horizontalLayout_14->setSpacing(6);
        horizontalLayout_14->setObjectName(QString::fromUtf8("horizontalLayout_14"));
        label_16 = new QLabel(verticalLayoutWidget_2);
        label_16->setObjectName(QString::fromUtf8("label_16"));

        horizontalLayout_14->addWidget(label_16);

        kbMin_slider = new QSlider(verticalLayoutWidget_2);
        kbMin_slider->setObjectName(QString::fromUtf8("kbMin_slider"));
        kbMin_slider->setMinimum(1);
        kbMin_slider->setMaximum(75);
        kbMin_slider->setValue(5);
        kbMin_slider->setOrientation(Qt::Horizontal);

        horizontalLayout_14->addWidget(kbMin_slider);

        kbMin_label = new QLabel(verticalLayoutWidget_2);
        kbMin_label->setObjectName(QString::fromUtf8("kbMin_label"));

        horizontalLayout_14->addWidget(kbMin_label);


        verticalLayout->addLayout(horizontalLayout_14);

        horizontalLayout_15 = new QHBoxLayout();
        horizontalLayout_15->setSpacing(6);
        horizontalLayout_15->setObjectName(QString::fromUtf8("horizontalLayout_15"));
        label_14 = new QLabel(verticalLayoutWidget_2);
        label_14->setObjectName(QString::fromUtf8("label_14"));

        horizontalLayout_15->addWidget(label_14);

        kbMax_slider = new QSlider(verticalLayoutWidget_2);
        kbMax_slider->setObjectName(QString::fromUtf8("kbMax_slider"));
        kbMax_slider->setMinimum(2);
        kbMax_slider->setMaximum(75);
        kbMax_slider->setValue(16);
        kbMax_slider->setOrientation(Qt::Horizontal);

        horizontalLayout_15->addWidget(kbMax_slider);

        kbMax_label = new QLabel(verticalLayoutWidget_2);
        kbMax_label->setObjectName(QString::fromUtf8("kbMax_label"));

        horizontalLayout_15->addWidget(kbMax_label);


        verticalLayout->addLayout(horizontalLayout_15);


        verticalLayout_9->addLayout(verticalLayout);

        line_18 = new QFrame(verticalLayoutWidget_2);
        line_18->setObjectName(QString::fromUtf8("line_18"));
        line_18->setStyleSheet(QString::fromUtf8(""));
        line_18->setFrameShape(QFrame::HLine);
        line_18->setFrameShadow(QFrame::Sunken);

        verticalLayout_9->addWidget(line_18);

        label_45 = new QLabel(verticalLayoutWidget_2);
        label_45->setObjectName(QString::fromUtf8("label_45"));
        QSizePolicy sizePolicy2(QSizePolicy::Minimum, QSizePolicy::Minimum);
        sizePolicy2.setHorizontalStretch(0);
        sizePolicy2.setVerticalStretch(0);
        sizePolicy2.setHeightForWidth(label_45->sizePolicy().hasHeightForWidth());
        label_45->setSizePolicy(sizePolicy2);
        label_45->setFont(font10);

        verticalLayout_9->addWidget(label_45);

        horizontalLayout_6 = new QHBoxLayout();
        horizontalLayout_6->setSpacing(6);
        horizontalLayout_6->setObjectName(QString::fromUtf8("horizontalLayout_6"));
        red_checkBox = new QCheckBox(verticalLayoutWidget_2);
        red_checkBox->setObjectName(QString::fromUtf8("red_checkBox"));
        red_checkBox->setChecked(true);

        horizontalLayout_6->addWidget(red_checkBox);

        green_checkBox = new QCheckBox(verticalLayoutWidget_2);
        green_checkBox->setObjectName(QString::fromUtf8("green_checkBox"));
        green_checkBox->setEnabled(true);
        green_checkBox->setChecked(false);

        horizontalLayout_6->addWidget(green_checkBox);

        blue_checkBox = new QCheckBox(verticalLayoutWidget_2);
        blue_checkBox->setObjectName(QString::fromUtf8("blue_checkBox"));
        blue_checkBox->setChecked(true);

        horizontalLayout_6->addWidget(blue_checkBox);


        verticalLayout_9->addLayout(horizontalLayout_6);

        verticalLayout_4 = new QVBoxLayout();
        verticalLayout_4->setSpacing(6);
        verticalLayout_4->setObjectName(QString::fromUtf8("verticalLayout_4"));
        horizontalLayout_18 = new QHBoxLayout();
        horizontalLayout_18->setSpacing(6);
        horizontalLayout_18->setObjectName(QString::fromUtf8("horizontalLayout_18"));
        label_36 = new QLabel(verticalLayoutWidget_2);
        label_36->setObjectName(QString::fromUtf8("label_36"));

        horizontalLayout_18->addWidget(label_36);

        cannyThreshLED_slider = new QSlider(verticalLayoutWidget_2);
        cannyThreshLED_slider->setObjectName(QString::fromUtf8("cannyThreshLED_slider"));
        cannyThreshLED_slider->setMinimum(5);
        cannyThreshLED_slider->setMaximum(200);
        cannyThreshLED_slider->setValue(61);
        cannyThreshLED_slider->setOrientation(Qt::Horizontal);

        horizontalLayout_18->addWidget(cannyThreshLED_slider);

        cannyThreshLED_label = new QLabel(verticalLayoutWidget_2);
        cannyThreshLED_label->setObjectName(QString::fromUtf8("cannyThreshLED_label"));

        horizontalLayout_18->addWidget(cannyThreshLED_label);


        verticalLayout_4->addLayout(horizontalLayout_18);

        horizontalLayout_19 = new QHBoxLayout();
        horizontalLayout_19->setSpacing(6);
        horizontalLayout_19->setObjectName(QString::fromUtf8("horizontalLayout_19"));
        label_37 = new QLabel(verticalLayoutWidget_2);
        label_37->setObjectName(QString::fromUtf8("label_37"));

        horizontalLayout_19->addWidget(label_37);

        houghAccLED_slider = new QSlider(verticalLayoutWidget_2);
        houghAccLED_slider->setObjectName(QString::fromUtf8("houghAccLED_slider"));
        houghAccLED_slider->setMinimum(1);
        houghAccLED_slider->setMaximum(100);
        houghAccLED_slider->setValue(18);
        houghAccLED_slider->setOrientation(Qt::Horizontal);

        horizontalLayout_19->addWidget(houghAccLED_slider);

        houghAccLED_label = new QLabel(verticalLayoutWidget_2);
        houghAccLED_label->setObjectName(QString::fromUtf8("houghAccLED_label"));

        horizontalLayout_19->addWidget(houghAccLED_label);


        verticalLayout_4->addLayout(horizontalLayout_19);

        horizontalLayout_20 = new QHBoxLayout();
        horizontalLayout_20->setSpacing(6);
        horizontalLayout_20->setObjectName(QString::fromUtf8("horizontalLayout_20"));
        label_38 = new QLabel(verticalLayoutWidget_2);
        label_38->setObjectName(QString::fromUtf8("label_38"));

        horizontalLayout_20->addWidget(label_38);

        kbMinLED_slider = new QSlider(verticalLayoutWidget_2);
        kbMinLED_slider->setObjectName(QString::fromUtf8("kbMinLED_slider"));
        kbMinLED_slider->setMinimum(1);
        kbMinLED_slider->setMaximum(25);
        kbMinLED_slider->setValue(5);
        kbMinLED_slider->setOrientation(Qt::Horizontal);

        horizontalLayout_20->addWidget(kbMinLED_slider);

        kbMinLED_label = new QLabel(verticalLayoutWidget_2);
        kbMinLED_label->setObjectName(QString::fromUtf8("kbMinLED_label"));

        horizontalLayout_20->addWidget(kbMinLED_label);


        verticalLayout_4->addLayout(horizontalLayout_20);

        horizontalLayout_27 = new QHBoxLayout();
        horizontalLayout_27->setSpacing(6);
        horizontalLayout_27->setObjectName(QString::fromUtf8("horizontalLayout_27"));
        label_39 = new QLabel(verticalLayoutWidget_2);
        label_39->setObjectName(QString::fromUtf8("label_39"));

        horizontalLayout_27->addWidget(label_39);

        kbMaxLED_slider = new QSlider(verticalLayoutWidget_2);
        kbMaxLED_slider->setObjectName(QString::fromUtf8("kbMaxLED_slider"));
        kbMaxLED_slider->setMinimum(2);
        kbMaxLED_slider->setMaximum(25);
        kbMaxLED_slider->setValue(16);
        kbMaxLED_slider->setOrientation(Qt::Horizontal);

        horizontalLayout_27->addWidget(kbMaxLED_slider);

        kbMaxLED_label = new QLabel(verticalLayoutWidget_2);
        kbMaxLED_label->setObjectName(QString::fromUtf8("kbMaxLED_label"));

        horizontalLayout_27->addWidget(kbMaxLED_label);


        verticalLayout_4->addLayout(horizontalLayout_27);


        verticalLayout_9->addLayout(verticalLayout_4);

        verticalLayout_8 = new QVBoxLayout();
        verticalLayout_8->setSpacing(6);
        verticalLayout_8->setObjectName(QString::fromUtf8("verticalLayout_8"));
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setSpacing(6);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        label_46 = new QLabel(verticalLayoutWidget_2);
        label_46->setObjectName(QString::fromUtf8("label_46"));

        horizontalLayout->addWidget(label_46);

        lowRLED_slider = new QSlider(verticalLayoutWidget_2);
        lowRLED_slider->setObjectName(QString::fromUtf8("lowRLED_slider"));
        lowRLED_slider->setMinimum(0);
        lowRLED_slider->setMaximum(100);
        lowRLED_slider->setValue(1);
        lowRLED_slider->setOrientation(Qt::Horizontal);

        horizontalLayout->addWidget(lowRLED_slider);

        lowRLED_label = new QLabel(verticalLayoutWidget_2);
        lowRLED_label->setObjectName(QString::fromUtf8("lowRLED_label"));

        horizontalLayout->addWidget(lowRLED_label);

        hiRLED_slider = new QSlider(verticalLayoutWidget_2);
        hiRLED_slider->setObjectName(QString::fromUtf8("hiRLED_slider"));
        hiRLED_slider->setMinimum(0);
        hiRLED_slider->setMaximum(100);
        hiRLED_slider->setValue(61);
        hiRLED_slider->setOrientation(Qt::Horizontal);

        horizontalLayout->addWidget(hiRLED_slider);

        hiRLED_label = new QLabel(verticalLayoutWidget_2);
        hiRLED_label->setObjectName(QString::fromUtf8("hiRLED_label"));

        horizontalLayout->addWidget(hiRLED_label);


        verticalLayout_8->addLayout(horizontalLayout);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setSpacing(6);
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        label_47 = new QLabel(verticalLayoutWidget_2);
        label_47->setObjectName(QString::fromUtf8("label_47"));

        horizontalLayout_2->addWidget(label_47);

        lowGLED_slider = new QSlider(verticalLayoutWidget_2);
        lowGLED_slider->setObjectName(QString::fromUtf8("lowGLED_slider"));
        lowGLED_slider->setMinimum(0);
        lowGLED_slider->setMaximum(100);
        lowGLED_slider->setValue(61);
        lowGLED_slider->setOrientation(Qt::Horizontal);

        horizontalLayout_2->addWidget(lowGLED_slider);

        lowGLED_label = new QLabel(verticalLayoutWidget_2);
        lowGLED_label->setObjectName(QString::fromUtf8("lowGLED_label"));

        horizontalLayout_2->addWidget(lowGLED_label);

        hiGLED_slider = new QSlider(verticalLayoutWidget_2);
        hiGLED_slider->setObjectName(QString::fromUtf8("hiGLED_slider"));
        hiGLED_slider->setMinimum(0);
        hiGLED_slider->setMaximum(100);
        hiGLED_slider->setValue(61);
        hiGLED_slider->setOrientation(Qt::Horizontal);

        horizontalLayout_2->addWidget(hiGLED_slider);

        hiGLED_label = new QLabel(verticalLayoutWidget_2);
        hiGLED_label->setObjectName(QString::fromUtf8("hiGLED_label"));

        horizontalLayout_2->addWidget(hiGLED_label);


        verticalLayout_8->addLayout(horizontalLayout_2);

        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setSpacing(6);
        horizontalLayout_3->setObjectName(QString::fromUtf8("horizontalLayout_3"));
        label_48 = new QLabel(verticalLayoutWidget_2);
        label_48->setObjectName(QString::fromUtf8("label_48"));

        horizontalLayout_3->addWidget(label_48);

        lowBLED_slider = new QSlider(verticalLayoutWidget_2);
        lowBLED_slider->setObjectName(QString::fromUtf8("lowBLED_slider"));
        lowBLED_slider->setMinimum(0);
        lowBLED_slider->setMaximum(100);
        lowBLED_slider->setValue(61);
        lowBLED_slider->setOrientation(Qt::Horizontal);

        horizontalLayout_3->addWidget(lowBLED_slider);

        lowBLED_label = new QLabel(verticalLayoutWidget_2);
        lowBLED_label->setObjectName(QString::fromUtf8("lowBLED_label"));

        horizontalLayout_3->addWidget(lowBLED_label);

        hiBLED_slider = new QSlider(verticalLayoutWidget_2);
        hiBLED_slider->setObjectName(QString::fromUtf8("hiBLED_slider"));
        hiBLED_slider->setMinimum(0);
        hiBLED_slider->setMaximum(100);
        hiBLED_slider->setValue(61);
        hiBLED_slider->setOrientation(Qt::Horizontal);

        horizontalLayout_3->addWidget(hiBLED_slider);

        hiBLED_label = new QLabel(verticalLayoutWidget_2);
        hiBLED_label->setObjectName(QString::fromUtf8("hiBLED_label"));

        horizontalLayout_3->addWidget(hiBLED_label);


        verticalLayout_8->addLayout(horizontalLayout_3);


        verticalLayout_9->addLayout(verticalLayout_8);


        verticalLayout_19->addLayout(verticalLayout_9);

        label_6 = new QLabel(frame_2);
        label_6->setObjectName(QString::fromUtf8("label_6"));
        label_6->setGeometry(QRect(12, 344, 276, 31));
        label_6->setFont(font10);
        label = new QLabel(frame);
        label->setObjectName(QString::fromUtf8("label"));
        label->setGeometry(QRect(1330, 0, 276, 31));
        label->setFont(font10);
        frame_5 = new QFrame(frame);
        frame_5->setObjectName(QString::fromUtf8("frame_5"));
        frame_5->setGeometry(QRect(1030, 50, 293, 921));
        frame_5->setFrameShape(QFrame::StyledPanel);
        frame_5->setFrameShadow(QFrame::Raised);
        gridLayoutWidget = new QWidget(frame_5);
        gridLayoutWidget->setObjectName(QString::fromUtf8("gridLayoutWidget"));
        gridLayoutWidget->setGeometry(QRect(6, 70, 281, 238));
        gridLayout_2 = new QGridLayout(gridLayoutWidget);
        gridLayout_2->setSpacing(6);
        gridLayout_2->setContentsMargins(11, 11, 11, 11);
        gridLayout_2->setObjectName(QString::fromUtf8("gridLayout_2"));
        gridLayout_2->setContentsMargins(0, 0, 0, 0);
        gridLayout_9 = new QGridLayout();
        gridLayout_9->setSpacing(6);
        gridLayout_9->setObjectName(QString::fromUtf8("gridLayout_9"));
        verticalSpacer = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        gridLayout_9->addItem(verticalSpacer, 4, 0, 1, 1);

        resetHMap_pushButton = new QPushButton(gridLayoutWidget);
        resetHMap_pushButton->setObjectName(QString::fromUtf8("resetHMap_pushButton"));
        QFont font11;
        font11.setPointSize(9);
        resetHMap_pushButton->setFont(font11);

        gridLayout_9->addWidget(resetHMap_pushButton, 1, 0, 1, 1);

        fitRect_pushButton = new QPushButton(gridLayoutWidget);
        fitRect_pushButton->setObjectName(QString::fromUtf8("fitRect_pushButton"));

        gridLayout_9->addWidget(fitRect_pushButton, 3, 0, 1, 1);

        fromImage_pushButton = new QPushButton(gridLayoutWidget);
        fromImage_pushButton->setObjectName(QString::fromUtf8("fromImage_pushButton"));
        fromImage_pushButton->setCheckable(true);

        gridLayout_9->addWidget(fromImage_pushButton, 2, 0, 1, 1);

        resetTrace_pushButton = new QPushButton(gridLayoutWidget);
        resetTrace_pushButton->setObjectName(QString::fromUtf8("resetTrace_pushButton"));
        resetTrace_pushButton->setFont(font11);

        gridLayout_9->addWidget(resetTrace_pushButton, 0, 0, 1, 1);

        drawBall = new QCheckBox(gridLayoutWidget);
        drawBall->setObjectName(QString::fromUtf8("drawBall"));

        gridLayout_9->addWidget(drawBall, 5, 0, 1, 1);


        gridLayout_2->addLayout(gridLayout_9, 0, 0, 1, 1);

        verticalLayout_10 = new QVBoxLayout();
        verticalLayout_10->setSpacing(6);
        verticalLayout_10->setObjectName(QString::fromUtf8("verticalLayout_10"));
        drawTrace_CheckBox = new QCheckBox(gridLayoutWidget);
        drawTrace_CheckBox->setObjectName(QString::fromUtf8("drawTrace_CheckBox"));

        verticalLayout_10->addWidget(drawTrace_CheckBox);

        drawHeatMap_CheckBox = new QCheckBox(gridLayoutWidget);
        drawHeatMap_CheckBox->setObjectName(QString::fromUtf8("drawHeatMap_CheckBox"));

        verticalLayout_10->addWidget(drawHeatMap_CheckBox);

        drawRobCircles_CheckBox = new QCheckBox(gridLayoutWidget);
        drawRobCircles_CheckBox->setObjectName(QString::fromUtf8("drawRobCircles_CheckBox"));
        drawRobCircles_CheckBox->setChecked(false);

        verticalLayout_10->addWidget(drawRobCircles_CheckBox);

        drawColCircles_CheckBox = new QCheckBox(gridLayoutWidget);
        drawColCircles_CheckBox->setObjectName(QString::fromUtf8("drawColCircles_CheckBox"));
        drawColCircles_CheckBox->setChecked(false);

        verticalLayout_10->addWidget(drawColCircles_CheckBox);

        draw_network = new QCheckBox(gridLayoutWidget);
        draw_network->setObjectName(QString::fromUtf8("draw_network"));
        draw_network->setEnabled(true);
        draw_network->setChecked(false);

        verticalLayout_10->addWidget(draw_network);

        draw_centroid = new QCheckBox(gridLayoutWidget);
        draw_centroid->setObjectName(QString::fromUtf8("draw_centroid"));
        draw_centroid->setEnabled(true);
        draw_centroid->setChecked(false);

        verticalLayout_10->addWidget(draw_centroid);

        draw_voronoii = new QCheckBox(gridLayoutWidget);
        draw_voronoii->setObjectName(QString::fromUtf8("draw_voronoii"));
        draw_voronoii->setEnabled(true);
        draw_voronoii->setChecked(false);

        verticalLayout_10->addWidget(draw_voronoii);

        draw_spatial_netw = new QCheckBox(gridLayoutWidget);
        draw_spatial_netw->setObjectName(QString::fromUtf8("draw_spatial_netw"));
        draw_spatial_netw->setEnabled(true);
        draw_spatial_netw->setChecked(false);

        verticalLayout_10->addWidget(draw_spatial_netw);


        gridLayout_2->addLayout(verticalLayout_10, 0, 1, 1, 1);

        frame_3 = new QFrame(frame_5);
        frame_3->setObjectName(QString::fromUtf8("frame_3"));
        frame_3->setGeometry(QRect(4, 416, 285, 497));
        frame_3->setFrameShape(QFrame::StyledPanel);
        frame_3->setFrameShadow(QFrame::Raised);
        layoutWidget_24 = new QWidget(frame_3);
        layoutWidget_24->setObjectName(QString::fromUtf8("layoutWidget_24"));
        layoutWidget_24->setGeometry(QRect(12, 6, 158, 231));
        verticalLayout_15 = new QVBoxLayout(layoutWidget_24);
        verticalLayout_15->setSpacing(6);
        verticalLayout_15->setContentsMargins(11, 11, 11, 11);
        verticalLayout_15->setObjectName(QString::fromUtf8("verticalLayout_15"));
        verticalLayout_15->setSizeConstraint(QLayout::SetDefaultConstraint);
        verticalLayout_15->setContentsMargins(0, 0, 0, 0);
        verticalLayout_16 = new QVBoxLayout();
        verticalLayout_16->setSpacing(6);
        verticalLayout_16->setObjectName(QString::fromUtf8("verticalLayout_16"));
        horizontalLayout_24 = new QHBoxLayout();
        horizontalLayout_24->setSpacing(6);
        horizontalLayout_24->setObjectName(QString::fromUtf8("horizontalLayout_24"));
        label_40 = new QLabel(layoutWidget_24);
        label_40->setObjectName(QString::fromUtf8("label_40"));
        label_40->setAutoFillBackground(false);
        label_40->setStyleSheet(QString::fromUtf8(""));
        label_40->setAlignment(Qt::AlignCenter);

        horizontalLayout_24->addWidget(label_40);

        label_24 = new QLabel(layoutWidget_24);
        label_24->setObjectName(QString::fromUtf8("label_24"));
        label_24->setAutoFillBackground(false);
        label_24->setStyleSheet(QString::fromUtf8(""));
        label_24->setAlignment(Qt::AlignCenter);

        horizontalLayout_24->addWidget(label_24);

        label_25 = new QLabel(layoutWidget_24);
        label_25->setObjectName(QString::fromUtf8("label_25"));
        label_25->setAutoFillBackground(false);
        label_25->setStyleSheet(QString::fromUtf8(""));
        label_25->setAlignment(Qt::AlignCenter);

        horizontalLayout_24->addWidget(label_25);

        label_26 = new QLabel(layoutWidget_24);
        label_26->setObjectName(QString::fromUtf8("label_26"));
        label_26->setAutoFillBackground(false);
        label_26->setStyleSheet(QString::fromUtf8(""));
        label_26->setAlignment(Qt::AlignCenter);

        horizontalLayout_24->addWidget(label_26);


        verticalLayout_16->addLayout(horizontalLayout_24);

        horizontalLayout_25 = new QHBoxLayout();
        horizontalLayout_25->setSpacing(6);
        horizontalLayout_25->setObjectName(QString::fromUtf8("horizontalLayout_25"));
        H_label = new QLabel(layoutWidget_24);
        H_label->setObjectName(QString::fromUtf8("H_label"));
        H_label->setAutoFillBackground(false);
        H_label->setStyleSheet(QString::fromUtf8(""));
        H_label->setAlignment(Qt::AlignCenter);

        horizontalLayout_25->addWidget(H_label);

        S_label = new QLabel(layoutWidget_24);
        S_label->setObjectName(QString::fromUtf8("S_label"));
        S_label->setAutoFillBackground(false);
        S_label->setStyleSheet(QString::fromUtf8(""));
        S_label->setAlignment(Qt::AlignCenter);

        horizontalLayout_25->addWidget(S_label);

        V_label = new QLabel(layoutWidget_24);
        V_label->setObjectName(QString::fromUtf8("V_label"));
        V_label->setAutoFillBackground(false);
        V_label->setStyleSheet(QString::fromUtf8(""));
        V_label->setAlignment(Qt::AlignCenter);

        horizontalLayout_25->addWidget(V_label);

        A_label = new QLabel(layoutWidget_24);
        A_label->setObjectName(QString::fromUtf8("A_label"));
        A_label->setAutoFillBackground(false);
        A_label->setStyleSheet(QString::fromUtf8(""));
        A_label->setAlignment(Qt::AlignCenter);

        horizontalLayout_25->addWidget(A_label);


        verticalLayout_16->addLayout(horizontalLayout_25);


        verticalLayout_15->addLayout(verticalLayout_16);

        horizontalLayout_26 = new QHBoxLayout();
        horizontalLayout_26->setSpacing(6);
        horizontalLayout_26->setObjectName(QString::fromUtf8("horizontalLayout_26"));
        H_slider = new QSlider(layoutWidget_24);
        H_slider->setObjectName(QString::fromUtf8("H_slider"));
        H_slider->setAutoFillBackground(false);
        H_slider->setStyleSheet(QString::fromUtf8(""));
        H_slider->setMaximum(359);
        H_slider->setOrientation(Qt::Vertical);

        horizontalLayout_26->addWidget(H_slider);

        S_slider = new QSlider(layoutWidget_24);
        S_slider->setObjectName(QString::fromUtf8("S_slider"));
        S_slider->setAutoFillBackground(false);
        S_slider->setStyleSheet(QString::fromUtf8(""));
        S_slider->setMaximum(255);
        S_slider->setValue(0);
        S_slider->setOrientation(Qt::Vertical);

        horizontalLayout_26->addWidget(S_slider);

        V_slider = new QSlider(layoutWidget_24);
        V_slider->setObjectName(QString::fromUtf8("V_slider"));
        V_slider->setAutoFillBackground(false);
        V_slider->setStyleSheet(QString::fromUtf8(""));
        V_slider->setMaximum(255);
        V_slider->setValue(100);
        V_slider->setOrientation(Qt::Vertical);

        horizontalLayout_26->addWidget(V_slider);

        A_slider = new QSlider(layoutWidget_24);
        A_slider->setObjectName(QString::fromUtf8("A_slider"));
        A_slider->setAutoFillBackground(false);
        A_slider->setStyleSheet(QString::fromUtf8(""));
        A_slider->setMaximum(100);
        A_slider->setValue(100);
        A_slider->setOrientation(Qt::Vertical);

        horizontalLayout_26->addWidget(A_slider);


        verticalLayout_15->addLayout(horizontalLayout_26);

        layoutWidget5 = new QWidget(frame_3);
        layoutWidget5->setObjectName(QString::fromUtf8("layoutWidget5"));
        layoutWidget5->setGeometry(QRect(188, 6, 82, 252));
        verticalLayout_14 = new QVBoxLayout(layoutWidget5);
        verticalLayout_14->setSpacing(6);
        verticalLayout_14->setContentsMargins(11, 11, 11, 11);
        verticalLayout_14->setObjectName(QString::fromUtf8("verticalLayout_14"));
        verticalLayout_14->setContentsMargins(0, 0, 0, 0);
        red_pushButton = new QPushButton(layoutWidget5);
        red_pushButton->setObjectName(QString::fromUtf8("red_pushButton"));
        red_pushButton->setStyleSheet(QString::fromUtf8("background-color: red;"));

        verticalLayout_14->addWidget(red_pushButton);

        blue_pushButton = new QPushButton(layoutWidget5);
        blue_pushButton->setObjectName(QString::fromUtf8("blue_pushButton"));
        blue_pushButton->setStyleSheet(QString::fromUtf8("background-color: rgb(114, 159, 207);; \n"
"color: rgb(46, 52, 54);"));

        verticalLayout_14->addWidget(blue_pushButton);

        green_pushButton = new QPushButton(layoutWidget5);
        green_pushButton->setObjectName(QString::fromUtf8("green_pushButton"));
        green_pushButton->setStyleSheet(QString::fromUtf8("background-color: green;\n"
"color: rgb(46, 52, 54);"));

        verticalLayout_14->addWidget(green_pushButton);

        white_pushButton = new QPushButton(layoutWidget5);
        white_pushButton->setObjectName(QString::fromUtf8("white_pushButton"));
        white_pushButton->setStyleSheet(QString::fromUtf8("background-color: rgb(255, 255, 255);\n"
"color: rgb(46, 52, 54);"));

        verticalLayout_14->addWidget(white_pushButton);

        black_pushButton = new QPushButton(layoutWidget5);
        black_pushButton->setObjectName(QString::fromUtf8("black_pushButton"));
        black_pushButton->setStyleSheet(QString::fromUtf8("background-color: rgb(0, 0, 0);\n"
"color: rgb(255, 255, 255);"));

        verticalLayout_14->addWidget(black_pushButton, 0, Qt::AlignRight);

        userRed_pushButton = new QPushButton(layoutWidget5);
        userRed_pushButton->setObjectName(QString::fromUtf8("userRed_pushButton"));
        userRed_pushButton->setStyleSheet(QString::fromUtf8("background-color: rgb(108, 24, 24);"));

        verticalLayout_14->addWidget(userRed_pushButton);

        userBlue_pushButton = new QPushButton(layoutWidget5);
        userBlue_pushButton->setObjectName(QString::fromUtf8("userBlue_pushButton"));
        userBlue_pushButton->setStyleSheet(QString::fromUtf8("background-color: rgb(32, 74, 135);"));

        verticalLayout_14->addWidget(userBlue_pushButton);

        seaBlue_pushButton = new QPushButton(layoutWidget5);
        seaBlue_pushButton->setObjectName(QString::fromUtf8("seaBlue_pushButton"));
        seaBlue_pushButton->setStyleSheet(QString::fromUtf8("background-color: rgb(0, 105, 108);"));

        verticalLayout_14->addWidget(seaBlue_pushButton);

        groupBox = new QGroupBox(frame_3);
        groupBox->setObjectName(QString::fromUtf8("groupBox"));
        groupBox->setGeometry(QRect(10, 290, 151, 121));
        layoutWidget6 = new QWidget(groupBox);
        layoutWidget6->setObjectName(QString::fromUtf8("layoutWidget6"));
        layoutWidget6->setGeometry(QRect(3, 25, 144, 116));
        verticalLayout_7 = new QVBoxLayout(layoutWidget6);
        verticalLayout_7->setSpacing(6);
        verticalLayout_7->setContentsMargins(11, 11, 11, 11);
        verticalLayout_7->setObjectName(QString::fromUtf8("verticalLayout_7"));
        verticalLayout_7->setContentsMargins(0, 0, 0, 0);
        radioButton = new QRadioButton(layoutWidget6);
        buttonGroupPaintObject = new QButtonGroup(MainWindow);
        buttonGroupPaintObject->setObjectName(QString::fromUtf8("buttonGroupPaintObject"));
        buttonGroupPaintObject->addButton(radioButton);
        radioButton->setObjectName(QString::fromUtf8("radioButton"));
        radioButton->setChecked(true);

        verticalLayout_7->addWidget(radioButton);

        radioButton_2 = new QRadioButton(layoutWidget6);
        buttonGroupPaintObject->addButton(radioButton_2);
        radioButton_2->setObjectName(QString::fromUtf8("radioButton_2"));

        verticalLayout_7->addWidget(radioButton_2);

        radioButton_4 = new QRadioButton(layoutWidget6);
        buttonGroupPaintObject->addButton(radioButton_4);
        radioButton_4->setObjectName(QString::fromUtf8("radioButton_4"));

        verticalLayout_7->addWidget(radioButton_4);

        radioButton_3 = new QRadioButton(layoutWidget6);
        buttonGroupPaintObject->addButton(radioButton_3);
        radioButton_3->setObjectName(QString::fromUtf8("radioButton_3"));

        verticalLayout_7->addWidget(radioButton_3);

        label_49 = new QLabel(frame_3);
        label_49->setObjectName(QString::fromUtf8("label_49"));
        label_49->setGeometry(QRect(10, 248, 71, 18));
        label_49->setAutoFillBackground(false);
        label_49->setStyleSheet(QString::fromUtf8(""));
        label_49->setAlignment(Qt::AlignCenter);
        layoutWidget7 = new QWidget(frame_3);
        layoutWidget7->setObjectName(QString::fromUtf8("layoutWidget7"));
        layoutWidget7->setGeometry(QRect(20, 266, 249, 21));
        horizontalLayout_30 = new QHBoxLayout(layoutWidget7);
        horizontalLayout_30->setSpacing(6);
        horizontalLayout_30->setContentsMargins(11, 11, 11, 11);
        horizontalLayout_30->setObjectName(QString::fromUtf8("horizontalLayout_30"));
        horizontalLayout_30->setContentsMargins(0, 0, 0, 0);
        robRendRad_slider = new QSlider(layoutWidget7);
        robRendRad_slider->setObjectName(QString::fromUtf8("robRendRad_slider"));
        robRendRad_slider->setMinimum(0);
        robRendRad_slider->setMaximum(300);
        robRendRad_slider->setPageStep(1);
        robRendRad_slider->setValue(50);
        robRendRad_slider->setOrientation(Qt::Horizontal);

        horizontalLayout_30->addWidget(robRendRad_slider);

        V_label_2 = new QLabel(layoutWidget7);
        V_label_2->setObjectName(QString::fromUtf8("V_label_2"));
        V_label_2->setAutoFillBackground(false);
        V_label_2->setStyleSheet(QString::fromUtf8(""));
        V_label_2->setAlignment(Qt::AlignCenter);

        horizontalLayout_30->addWidget(V_label_2);

        groupBox_4 = new QGroupBox(frame_3);
        groupBox_4->setObjectName(QString::fromUtf8("groupBox_4"));
        groupBox_4->setGeometry(QRect(162, 290, 113, 121));
        layoutWidget_7 = new QWidget(groupBox_4);
        layoutWidget_7->setObjectName(QString::fromUtf8("layoutWidget_7"));
        layoutWidget_7->setGeometry(QRect(20, 24, 82, 95));
        verticalLayout_18 = new QVBoxLayout(layoutWidget_7);
        verticalLayout_18->setSpacing(6);
        verticalLayout_18->setContentsMargins(11, 11, 11, 11);
        verticalLayout_18->setObjectName(QString::fromUtf8("verticalLayout_18"));
        verticalLayout_18->setContentsMargins(0, 0, 0, 0);
        gradientRob_pushButton = new QPushButton(layoutWidget_7);
        gradientRob_pushButton->setObjectName(QString::fromUtf8("gradientRob_pushButton"));
        gradientRob_pushButton->setStyleSheet(QString::fromUtf8(""));

        verticalLayout_18->addWidget(gradientRob_pushButton);

        solidRob_pushButton = new QPushButton(layoutWidget_7);
        solidRob_pushButton->setObjectName(QString::fromUtf8("solidRob_pushButton"));
        solidRob_pushButton->setStyleSheet(QString::fromUtf8(""));

        verticalLayout_18->addWidget(solidRob_pushButton);

        nullRob_pushButton = new QPushButton(layoutWidget_7);
        nullRob_pushButton->setObjectName(QString::fromUtf8("nullRob_pushButton"));
        nullRob_pushButton->setStyleSheet(QString::fromUtf8(""));
        nullRob_pushButton->setCheckable(true);

        verticalLayout_18->addWidget(nullRob_pushButton);

        layoutWidget8 = new QWidget(frame_3);
        layoutWidget8->setObjectName(QString::fromUtf8("layoutWidget8"));
        layoutWidget8->setGeometry(QRect(10, 430, 271, 48));
        verticalLayout_17 = new QVBoxLayout(layoutWidget8);
        verticalLayout_17->setSpacing(6);
        verticalLayout_17->setContentsMargins(11, 11, 11, 11);
        verticalLayout_17->setObjectName(QString::fromUtf8("verticalLayout_17"));
        verticalLayout_17->setContentsMargins(0, 0, 0, 0);
        horizontalLayout_32 = new QHBoxLayout();
        horizontalLayout_32->setSpacing(6);
        horizontalLayout_32->setObjectName(QString::fromUtf8("horizontalLayout_32"));
        label_2 = new QLabel(layoutWidget8);
        label_2->setObjectName(QString::fromUtf8("label_2"));

        horizontalLayout_32->addWidget(label_2);

        sliderRandom0 = new QSlider(layoutWidget8);
        sliderRandom0->setObjectName(QString::fromUtf8("sliderRandom0"));
        sliderRandom0->setMaximum(1000);
        sliderRandom0->setValue(380);
        sliderRandom0->setOrientation(Qt::Horizontal);

        horizontalLayout_32->addWidget(sliderRandom0);

        sliderRand0_label = new QLabel(layoutWidget8);
        sliderRand0_label->setObjectName(QString::fromUtf8("sliderRand0_label"));

        horizontalLayout_32->addWidget(sliderRand0_label);


        verticalLayout_17->addLayout(horizontalLayout_32);

        horizontalLayout_33 = new QHBoxLayout();
        horizontalLayout_33->setSpacing(6);
        horizontalLayout_33->setObjectName(QString::fromUtf8("horizontalLayout_33"));
        label_3 = new QLabel(layoutWidget8);
        label_3->setObjectName(QString::fromUtf8("label_3"));

        horizontalLayout_33->addWidget(label_3);

        sliderRandom1 = new QSlider(layoutWidget8);
        sliderRandom1->setObjectName(QString::fromUtf8("sliderRandom1"));
        sliderRandom1->setMaximum(500);
        sliderRandom1->setValue(200);
        sliderRandom1->setOrientation(Qt::Horizontal);

        horizontalLayout_33->addWidget(sliderRandom1);

        sliderRand1_label = new QLabel(layoutWidget8);
        sliderRand1_label->setObjectName(QString::fromUtf8("sliderRand1_label"));

        horizontalLayout_33->addWidget(sliderRand1_label);


        verticalLayout_17->addLayout(horizontalLayout_33);

        line_17 = new QFrame(frame_3);
        line_17->setObjectName(QString::fromUtf8("line_17"));
        line_17->setGeometry(QRect(0, 412, 291, 20));
        line_17->setFrameShape(QFrame::HLine);
        line_17->setFrameShadow(QFrame::Sunken);
        horizontalLayoutWidget = new QWidget(frame_5);
        horizontalLayoutWidget->setObjectName(QString::fromUtf8("horizontalLayoutWidget"));
        horizontalLayoutWidget->setGeometry(QRect(4, 6, 285, 40));
        horizontalLayout_17 = new QHBoxLayout(horizontalLayoutWidget);
        horizontalLayout_17->setSpacing(6);
        horizontalLayout_17->setContentsMargins(11, 11, 11, 11);
        horizontalLayout_17->setObjectName(QString::fromUtf8("horizontalLayout_17"));
        horizontalLayout_17->setContentsMargins(0, 0, 0, 0);
        fullScreen_pushButton = new QPushButton(horizontalLayoutWidget);
        fullScreen_pushButton->setObjectName(QString::fromUtf8("fullScreen_pushButton"));
        QSizePolicy sizePolicy3(QSizePolicy::Minimum, QSizePolicy::Expanding);
        sizePolicy3.setHorizontalStretch(0);
        sizePolicy3.setVerticalStretch(0);
        sizePolicy3.setHeightForWidth(fullScreen_pushButton->sizePolicy().hasHeightForWidth());
        fullScreen_pushButton->setSizePolicy(sizePolicy3);
        fullScreen_pushButton->setFont(font11);

        horizontalLayout_17->addWidget(fullScreen_pushButton);

        ArenaWindow_button = new QPushButton(horizontalLayoutWidget);
        ArenaWindow_button->setObjectName(QString::fromUtf8("ArenaWindow_button"));
        sizePolicy3.setHeightForWidth(ArenaWindow_button->sizePolicy().hasHeightForWidth());
        ArenaWindow_button->setSizePolicy(sizePolicy3);
        ArenaWindow_button->setFont(font11);
        ArenaWindow_button->setStyleSheet(QString::fromUtf8(""));
        ArenaWindow_button->setCheckable(true);

        horizontalLayout_17->addWidget(ArenaWindow_button);

        cam_label_6 = new QLabel(horizontalLayoutWidget);
        cam_label_6->setObjectName(QString::fromUtf8("cam_label_6"));

        horizontalLayout_17->addWidget(cam_label_6);

        screen_comboBox = new QComboBox(horizontalLayoutWidget);
        screen_comboBox->addItem(QString());
        screen_comboBox->addItem(QString());
        screen_comboBox->addItem(QString());
        screen_comboBox->setObjectName(QString::fromUtf8("screen_comboBox"));

        horizontalLayout_17->addWidget(screen_comboBox);

        layoutWidget9 = new QWidget(frame_5);
        layoutWidget9->setObjectName(QString::fromUtf8("layoutWidget9"));
        layoutWidget9->setGeometry(QRect(26, 372, 241, 29));
        gridLayout_10 = new QGridLayout(layoutWidget9);
        gridLayout_10->setSpacing(6);
        gridLayout_10->setContentsMargins(11, 11, 11, 11);
        gridLayout_10->setObjectName(QString::fromUtf8("gridLayout_10"));
        gridLayout_10->setContentsMargins(0, 0, 0, 0);
        label_51 = new QLabel(layoutWidget9);
        label_51->setObjectName(QString::fromUtf8("label_51"));

        gridLayout_10->addWidget(label_51, 0, 0, 1, 1);

        horizontalSpacer = new QSpacerItem(80, 20, QSizePolicy::Fixed, QSizePolicy::Minimum);

        gridLayout_10->addItem(horizontalSpacer, 0, 1, 1, 1);

        TrigID_comboBox = new QComboBox(layoutWidget9);
        TrigID_comboBox->addItem(QString());
        TrigID_comboBox->setObjectName(QString::fromUtf8("TrigID_comboBox"));

        gridLayout_10->addWidget(TrigID_comboBox, 0, 2, 1, 1);

        layoutWidget10 = new QWidget(frame_5);
        layoutWidget10->setObjectName(QString::fromUtf8("layoutWidget10"));
        layoutWidget10->setGeometry(QRect(44, 336, 201, 28));
        gridLayout_11 = new QGridLayout(layoutWidget10);
        gridLayout_11->setSpacing(6);
        gridLayout_11->setContentsMargins(11, 11, 11, 11);
        gridLayout_11->setObjectName(QString::fromUtf8("gridLayout_11"));
        gridLayout_11->setContentsMargins(0, 0, 0, 0);
        initPoints_pushButton = new QPushButton(layoutWidget10);
        initPoints_pushButton->setObjectName(QString::fromUtf8("initPoints_pushButton"));
        initPoints_pushButton->setCheckable(true);

        gridLayout_11->addWidget(initPoints_pushButton, 0, 0, 1, 1);

        initPoints_comboBox = new QComboBox(layoutWidget10);
        initPoints_comboBox->addItem(QString());
        initPoints_comboBox->addItem(QString());
        initPoints_comboBox->addItem(QString());
        initPoints_comboBox->addItem(QString());
        initPoints_comboBox->setObjectName(QString::fromUtf8("initPoints_comboBox"));

        gridLayout_11->addWidget(initPoints_comboBox, 0, 1, 1, 1);

        label_4 = new QLabel(frame);
        label_4->setObjectName(QString::fromUtf8("label_4"));
        label_4->setGeometry(QRect(1034, 0, 287, 31));
        label_4->setFont(font10);
        label_5 = new QLabel(frame);
        label_5->setObjectName(QString::fromUtf8("label_5"));
        label_5->setGeometry(QRect(676, 0, 189, 31));
        label_5->setFont(font10);
        frame_5->raise();
        nonImpt->raise();
        outputLabel->raise();
        error_label->raise();
        customPlot->raise();
        textOut->raise();
        tabWidget->raise();
        colorWidget->raise();
        label->raise();
        label_4->raise();
        label_5->raise();
        layoutWidget11 = new QWidget(centralWidget);
        layoutWidget11->setObjectName(QString::fromUtf8("layoutWidget11"));
        layoutWidget11->setGeometry(QRect(0, 0, 2, 2));
        formLayout_2 = new QFormLayout(layoutWidget11);
        formLayout_2->setSpacing(6);
        formLayout_2->setContentsMargins(11, 11, 11, 11);
        formLayout_2->setObjectName(QString::fromUtf8("formLayout_2"));
        formLayout_2->setContentsMargins(0, 0, 0, 0);
        layoutWidget12 = new QWidget(centralWidget);
        layoutWidget12->setObjectName(QString::fromUtf8("layoutWidget12"));
        layoutWidget12->setGeometry(QRect(0, 0, 2, 2));
        formLayout_3 = new QFormLayout(layoutWidget12);
        formLayout_3->setSpacing(6);
        formLayout_3->setContentsMargins(11, 11, 11, 11);
        formLayout_3->setObjectName(QString::fromUtf8("formLayout_3"));
        formLayout_3->setContentsMargins(0, 0, 0, 0);
        MainWindow->setCentralWidget(centralWidget);
        layoutWidget->raise();
        layoutWidget->raise();
        frame->raise();
        line->raise();
        line_12->raise();
#if QT_CONFIG(shortcut)
        label_40->setBuddy(V_slider);
        label_24->setBuddy(H_slider);
        label_25->setBuddy(S_slider);
        label_26->setBuddy(V_slider);
        label_49->setBuddy(H_slider);
#endif // QT_CONFIG(shortcut)

        retranslateUi(MainWindow);
        QObject::connect(V_slider, SIGNAL(sliderMoved(int)), V_label, SLOT(setNum(int)));
        QObject::connect(S_slider, SIGNAL(sliderMoved(int)), S_label, SLOT(setNum(int)));
        QObject::connect(H_slider, SIGNAL(sliderMoved(int)), H_label, SLOT(setNum(int)));
        QObject::connect(cannyThreshLED_slider, SIGNAL(sliderMoved(int)), cannyThreshLED_label, SLOT(setNum(int)));
        QObject::connect(houghAccLED_slider, SIGNAL(sliderMoved(int)), houghAccLED_label, SLOT(setNum(int)));
        QObject::connect(kbMaxLED_slider, SIGNAL(sliderMoved(int)), kbMaxLED_label, SLOT(setNum(int)));
        QObject::connect(cannyThresh_slider, SIGNAL(sliderMoved(int)), cannyThresh_label, SLOT(setNum(int)));
        QObject::connect(houghAcc_slider, SIGNAL(sliderMoved(int)), houghAcc_label, SLOT(setNum(int)));
        QObject::connect(kbMax_slider, SIGNAL(sliderMoved(int)), kbMax_label, SLOT(setNum(int)));
        QObject::connect(kbMin_slider, SIGNAL(sliderMoved(int)), kbMin_label, SLOT(setNum(int)));
        QObject::connect(kbMinLED_slider, SIGNAL(sliderMoved(int)), kbMinLED_label, SLOT(setNum(int)));
        QObject::connect(lowRLED_slider, SIGNAL(sliderMoved(int)), lowRLED_label, SLOT(setNum(int)));
        QObject::connect(hiRLED_slider, SIGNAL(sliderMoved(int)), hiRLED_label, SLOT(setNum(int)));
        QObject::connect(lowGLED_slider, SIGNAL(sliderMoved(int)), lowGLED_label, SLOT(setNum(int)));
        QObject::connect(hiGLED_slider, SIGNAL(sliderMoved(int)), hiGLED_label, SLOT(setNum(int)));
        QObject::connect(lowBLED_slider, SIGNAL(sliderMoved(int)), lowBLED_label, SLOT(setNum(int)));
        QObject::connect(hiBLED_slider, SIGNAL(sliderMoved(int)), hiBLED_label, SLOT(setNum(int)));
        QObject::connect(A_slider, SIGNAL(sliderMoved(int)), A_label, SLOT(setNum(int)));
        QObject::connect(maxDispl_slider, SIGNAL(sliderMoved(int)), maxDispl_label, SLOT(setNum(int)));
        QObject::connect(EFWL_slider, SIGNAL(sliderMoved(int)), EFWL_label, SLOT(setNum(int)));
        QObject::connect(robRendRad_slider, SIGNAL(sliderMoved(int)), V_label_2, SLOT(setNum(int)));
        QObject::connect(smoothnessFact_slider, SIGNAL(sliderMoved(int)), smoothnessFact_label, SLOT(setNum(int)));
        QObject::connect(markerWidth_Slider, SIGNAL(sliderMoved(int)), markerWidth_label, SLOT(setNum(int)));
        QObject::connect(sliderRandom0, SIGNAL(valueChanged(int)), sliderRand0_label, SLOT(setNum(int)));
        QObject::connect(sliderRandom1, SIGNAL(valueChanged(int)), sliderRand1_label, SLOT(setNum(int)));
        QObject::connect(noiseStrength_slider, SIGNAL(valueChanged(int)), noiseStrenght_label, SLOT(setNum(int)));
        QObject::connect(noiseTiles_slider, SIGNAL(valueChanged(int)), noTiles_label, SLOT(setNum(int)));
        QObject::connect(noiseFreq_slider, SIGNAL(valueChanged(int)), noiseFreq_label, SLOT(setNum(int)));

        tabWidget->setCurrentIndex(0);
        Rotate_ComboBox->setCurrentIndex(1);
        FPS_comboBox->setCurrentIndex(1);
        logType_comboBox->setCurrentIndex(3);
        tabWidget_2->setCurrentIndex(0);
        generate_comboBox->setCurrentIndex(2);
        screen_comboBox->setCurrentIndex(2);


        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "LARS @ SCIoI", nullptr));
        actionExit->setText(QCoreApplication::translate("MainWindow", "Exit", nullptr));
        actionOpen->setText(QCoreApplication::translate("MainWindow", "Open", nullptr));
        actionSave->setText(QCoreApplication::translate("MainWindow", "Save", nullptr));
        actionExit_2->setText(QCoreApplication::translate("MainWindow", "Exit", nullptr));
        actionOpen_2->setText(QCoreApplication::translate("MainWindow", "Open", nullptr));
        actionSave_2->setText(QCoreApplication::translate("MainWindow", "Save", nullptr));
        actionExit_3->setText(QCoreApplication::translate("MainWindow", "Exit", nullptr));
        outputLabel->setText(QString());
        error_label->setText(QCoreApplication::translate("MainWindow", "Hello!", nullptr));
        textOut->setHtml(QCoreApplication::translate("MainWindow", "<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.0//EN\" \"http://www.w3.org/TR/REC-html40/strict.dtd\">\n"
"<html><head><meta name=\"qrichtext\" content=\"1\" /><meta charset=\"utf-8\" /><style type=\"text/css\">\n"
"p, li { white-space: pre-wrap; }\n"
"</style></head><body style=\" font-family:'Cantarell'; font-size:11pt; font-weight:400; font-style:normal;\">\n"
"<p align=\"center\" style=\"-qt-paragraph-type:empty; margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><br /></p>\n"
"<p align=\"center\" style=\"-qt-paragraph-type:empty; margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><br /></p>\n"
"<p align=\"center\" style=\"-qt-paragraph-type:empty; margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><br /></p>\n"
"<p align=\"center\" style=\"-qt-paragraph-type:empty; margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-"
                        "block-indent:0; text-indent:0px;\"><br /></p>\n"
"<p align=\"center\" style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" color:#d0d0d0;\">*** Science of Intelligence ***</span></p>\n"
"<p align=\"center\" style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" color:#d0d0d0;\">***** Project 27 *****</span></p>\n"
"<p align=\"center\" style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\">  <span style=\" font-family:'Courier New'; font-weight:600; color:#00ffff;\">&lt;</span>  <span style=\" font-family:'Courier New'; font-weight:600; color:#d0d0d0;\">    L    A    R    S    </span>  <span style=\" font-family:'Courier New'; font-weight:600; color:#fcfea9;\">&gt;</span></p>\n"
"<p align=\"center\" style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:"
                        "0; text-indent:0px;\"><span style=\" color:#d0d0d0;\">* Light Augmented Reality System *</span></p>\n"
"<p align=\"center\" style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" color:#d0d0d0;\">** Version: 2.2 **</span></p>\n"
"<p align=\"center\" style=\"-qt-paragraph-type:empty; margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px; color:#d0d0d0;\"><br /></p>\n"
"<p align=\"center\" style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><br /><span style=\" font-size:9pt;\">\302\251</span> <span style=\" font-size:9pt;\">Mohsen Raoufi</span></p></body></html>", nullptr));
        nonImpt->setHtml(QCoreApplication::translate("MainWindow", "<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.0//EN\" \"http://www.w3.org/TR/REC-html40/strict.dtd\">\n"
"<html><head><meta name=\"qrichtext\" content=\"1\" /><meta charset=\"utf-8\" /><style type=\"text/css\">\n"
"p, li { white-space: pre-wrap; }\n"
"</style></head><body style=\" font-family:'Cantarell'; font-size:11pt; font-weight:400; font-style:normal;\">\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-family:'Sans Serif'; font-size:9pt;\">Output:</span></p></body></html>", nullptr));
        fromVid_rButton->setText(QCoreApplication::translate("MainWindow", "Video File", nullptr));
        fromCam_rButton->setText(QCoreApplication::translate("MainWindow", "Camera", nullptr));
#if QT_CONFIG(tooltip)
        capturing_button->setToolTip(QCoreApplication::translate("MainWindow", "<html><head/><body><p>Connect to Camera</p></body></html>", "toolTip"));
#endif // QT_CONFIG(tooltip)
#if QT_CONFIG(statustip)
        capturing_button->setStatusTip(QString());
#endif // QT_CONFIG(statustip)
#if QT_CONFIG(whatsthis)
        capturing_button->setWhatsThis(QCoreApplication::translate("MainWindow", "<html><head/><body><p>Connect me to camera</p></body></html>", "dis whats this"));
#endif // QT_CONFIG(whatsthis)
        capturing_button->setText(QCoreApplication::translate("MainWindow", "Connect to Camera", "hey hey"));
        RotateCheckBox->setText(QCoreApplication::translate("MainWindow", "Rotate (CW)", nullptr));
        Rotate_ComboBox->setItemText(0, QCoreApplication::translate("MainWindow", "90", nullptr));
        Rotate_ComboBox->setItemText(1, QCoreApplication::translate("MainWindow", "180", nullptr));
        Rotate_ComboBox->setItemText(2, QCoreApplication::translate("MainWindow", "270", nullptr));

        cam_label_4->setText(QCoreApplication::translate("MainWindow", "Camera No. :  ", nullptr));
        cam_comboBox->setItemText(0, QCoreApplication::translate("MainWindow", "-1", nullptr));
        cam_comboBox->setItemText(1, QCoreApplication::translate("MainWindow", "0", nullptr));
        cam_comboBox->setItemText(2, QCoreApplication::translate("MainWindow", "1", nullptr));
        cam_comboBox->setItemText(3, QCoreApplication::translate("MainWindow", "2", nullptr));

        cam_label_5->setText(QCoreApplication::translate("MainWindow", "FPS :", nullptr));
        FPS_comboBox->setItemText(0, QCoreApplication::translate("MainWindow", "15", nullptr));
        FPS_comboBox->setItemText(1, QCoreApplication::translate("MainWindow", "25", nullptr));
        FPS_comboBox->setItemText(2, QCoreApplication::translate("MainWindow", "45", nullptr));
        FPS_comboBox->setItemText(3, QCoreApplication::translate("MainWindow", "60", nullptr));
        FPS_comboBox->setItemText(4, QCoreApplication::translate("MainWindow", "120", nullptr));

        FPS_comboBox->setCurrentText(QCoreApplication::translate("MainWindow", "25", nullptr));
        saveSetting_pushButton->setText(QCoreApplication::translate("MainWindow", "Save Settings", nullptr));
        loadSetting_pushButton->setText(QCoreApplication::translate("MainWindow", "Load Settings", nullptr));
        debugAV_CheckBox->setText(QCoreApplication::translate("MainWindow", "Debug Video", nullptr));
        debug_CheckBox->setText(QCoreApplication::translate("MainWindow", "Debug", nullptr));
        useARKCap_CheckBox->setText(QCoreApplication::translate("MainWindow", "use ARK cap", nullptr));
        label_23->setText(QCoreApplication::translate("MainWindow", "File Path:", nullptr));
        saveVid_button->setText(QCoreApplication::translate("MainWindow", "Save Vid", nullptr));
        open_set_button->setText(QCoreApplication::translate("MainWindow", "Open", nullptr));
        filePath_user->setText(QCoreApplication::translate("MainWindow", "/home/p27/Kilobot_Materials/savedData/eval_test_s", nullptr));
        refresh_pushButton->setText(QCoreApplication::translate("MainWindow", "refresh", nullptr));
        crop_pushButton->setText(QCoreApplication::translate("MainWindow", "CROP", nullptr));
#if QT_CONFIG(tooltip)
        detectMarker_pushButton->setToolTip(QString());
#endif // QT_CONFIG(tooltip)
        detectMarker_pushButton->setText(QCoreApplication::translate("MainWindow", "Detect Markers", nullptr));
        markerWidth_label->setText(QCoreApplication::translate("MainWindow", "50", nullptr));
        writeLog_button->setText(QCoreApplication::translate("MainWindow", "Write Log", nullptr));
        logType_comboBox->setItemText(0, QCoreApplication::translate("MainWindow", "Pos, Vec, LED", nullptr));
        logType_comboBox->setItemText(1, QCoreApplication::translate("MainWindow", "Pos", nullptr));
        logType_comboBox->setItemText(2, QCoreApplication::translate("MainWindow", "Pos, LED", nullptr));
        logType_comboBox->setItemText(3, QCoreApplication::translate("MainWindow", "Pos, FPS", nullptr));

        label_28->setText(QCoreApplication::translate("MainWindow", "Log Type:", nullptr));
        env1_rButton->setText(QCoreApplication::translate("MainWindow", "env 1", nullptr));
        env2_rButton->setText(QCoreApplication::translate("MainWindow", "env 2", nullptr));
        env3_rButton->setText(QCoreApplication::translate("MainWindow", "env 3", nullptr));
        env4_rButton->setText(QCoreApplication::translate("MainWindow", "demo", nullptr));
        label_22->setText(QCoreApplication::translate("MainWindow", "Marker Size", nullptr));
#if QT_CONFIG(tooltip)
        detectKilobots_pushButton->setToolTip(QString());
#endif // QT_CONFIG(tooltip)
        detectKilobots_pushButton->setText(QCoreApplication::translate("MainWindow", "Detect Robots", nullptr));
#if QT_CONFIG(tooltip)
        startTracking_pushButton->setToolTip(QString());
#endif // QT_CONFIG(tooltip)
        startTracking_pushButton->setText(QCoreApplication::translate("MainWindow", "Start Tracking", nullptr));
        ohc_connect->setText(QCoreApplication::translate("MainWindow", "Connect OHC", nullptr));
        cropTLTextLabel->setText(QCoreApplication::translate("MainWindow", "Crop TL:", nullptr));
        cropszTextLabel->setText(QCoreApplication::translate("MainWindow", "Crop size:", nullptr));
        cropTL_xTextEdit->setText(QCoreApplication::translate("MainWindow", "152", nullptr));
        cropTL_yTextEdit->setText(QCoreApplication::translate("MainWindow", "129", nullptr));
        cropsz_wTextEdit->setText(QCoreApplication::translate("MainWindow", "335", nullptr));
        cropsz_hTextEdit->setText(QCoreApplication::translate("MainWindow", "329", nullptr));
        show_HM->setText(QCoreApplication::translate("MainWindow", "show HM", nullptr));
        draw_bots->setText(QCoreApplication::translate("MainWindow", "draw Bots", nullptr));
        show_ids->setText(QCoreApplication::translate("MainWindow", "show IDs", nullptr));
        drawBoundary_CheckBox->setText(QCoreApplication::translate("MainWindow", "draw boundary", nullptr));
        show_vel->setText(QCoreApplication::translate("MainWindow", "show vel", nullptr));
        draw_bots_colors->setText(QCoreApplication::translate("MainWindow", "with colors", nullptr));
        groupBox_2->setTitle(QCoreApplication::translate("MainWindow", "Command", nullptr));
        ohc_run->setText(QCoreApplication::translate("MainWindow", "Run", nullptr));
        ohc_reset->setText(QCoreApplication::translate("MainWindow", "Reset", nullptr));
        ohc_sleep->setText(QCoreApplication::translate("MainWindow", "Sleep", nullptr));
        ohc_volt->setText(QCoreApplication::translate("MainWindow", "Voltage", nullptr));
        ohc_stop->setText(QCoreApplication::translate("MainWindow", "None", nullptr));
        ohc_set_prog->setText(QCoreApplication::translate("MainWindow", "[select file]", nullptr));
        ohc_upload_prog->setText(QCoreApplication::translate("MainWindow", "Upload", nullptr));
        sendBatch_pushButton->setText(QCoreApplication::translate("MainWindow", "Send", nullptr));
        calibrate_pushButton->setText(QCoreApplication::translate("MainWindow", "Start Motors Calibration", nullptr));
        tabWidget_2->setTabText(tabWidget_2->indexOf(Kilobot_tab), QCoreApplication::translate("MainWindow", "Kilobot", nullptr));
        tabWidget_2->setTabText(tabWidget_2->indexOf(tab_2), QCoreApplication::translate("MainWindow", "Thymio", nullptr));
#if QT_CONFIG(tooltip)
        test_eval_pushButton->setToolTip(QString());
#endif // QT_CONFIG(tooltip)
        test_eval_pushButton->setText(QCoreApplication::translate("MainWindow", "test evalution", nullptr));
        tabWidget->setTabText(tabWidget->indexOf(input_tab), QCoreApplication::translate("MainWindow", "Input", nullptr));
        AFSens_Norm_pushButton->setText(QCoreApplication::translate("MainWindow", "Normal", nullptr));
        label_27->setText(QCoreApplication::translate("MainWindow", "AF Sensitivity :", nullptr));
        AFSens_Low_pushButton->setText(QCoreApplication::translate("MainWindow", "Low", nullptr));
        WhiteBal_Auto_pushButton->setText(QCoreApplication::translate("MainWindow", "once", nullptr));
        label_29->setText(QCoreApplication::translate("MainWindow", "White Balance :", nullptr));
        label_30->setText(QCoreApplication::translate("MainWindow", "Auto Exposure :", nullptr));
        AE_Auto_pushButton->setText(QCoreApplication::translate("MainWindow", "Auto", nullptr));
        AE_Manual_pushButton->setText(QCoreApplication::translate("MainWindow", "Manual", nullptr));
        label_33->setText(QCoreApplication::translate("MainWindow", "Cam Bright:", nullptr));
        CamBright_Up_pushButton->setText(QCoreApplication::translate("MainWindow", "Up", nullptr));
        CamBright_Down_pushButton->setText(QCoreApplication::translate("MainWindow", "Down", nullptr));
        CamBright_Reset_pushButton->setText(QCoreApplication::translate("MainWindow", "Reset", nullptr));
#if QT_CONFIG(tooltip)
        tempVal_SlideBar->setToolTip(QString());
#endif // QT_CONFIG(tooltip)
#if QT_CONFIG(statustip)
        tempVal_SlideBar->setStatusTip(QString());
#endif // QT_CONFIG(statustip)
#if QT_CONFIG(whatsthis)
        tempVal_SlideBar->setWhatsThis(QCoreApplication::translate("MainWindow", "extra area surrounding the target", nullptr));
#endif // QT_CONFIG(whatsthis)
#if QT_CONFIG(accessibility)
        tempVal_SlideBar->setAccessibleName(QString());
#endif // QT_CONFIG(accessibility)
        tempVal_Value->setText(QCoreApplication::translate("MainWindow", "130", nullptr));
#if QT_CONFIG(whatsthis)
        nonImpt2->setWhatsThis(QCoreApplication::translate("MainWindow", "extra area surrounding the target", nullptr));
#endif // QT_CONFIG(whatsthis)
        nonImpt2->setText(QCoreApplication::translate("MainWindow", "TempVal", nullptr));
        tabWidget->setTabText(tabWidget->indexOf(Camera_tab), QCoreApplication::translate("MainWindow", "Camera settings", nullptr));
        groupBox_3->setTitle(QCoreApplication::translate("MainWindow", "Exp. Field Type", nullptr));
        gradientExpField_pushButton->setText(QCoreApplication::translate("MainWindow", "gradient", nullptr));
        imageExpField_pushButton->setText(QCoreApplication::translate("MainWindow", "image", nullptr));
        videoExpField_pushButton->setText(QCoreApplication::translate("MainWindow", "video", nullptr));
        nullExpField_pushButton->setText(QCoreApplication::translate("MainWindow", "null", nullptr));
        generateExpField_pushButton->setText(QCoreApplication::translate("MainWindow", "generate", nullptr));
        shuffleImageExpField_pushButton->setText(QCoreApplication::translate("MainWindow", "shuffle", nullptr));
        generate_comboBox->setItemText(0, QCoreApplication::translate("MainWindow", "grid", nullptr));
        generate_comboBox->setItemText(1, QCoreApplication::translate("MainWindow", "rnd img", nullptr));
        generate_comboBox->setItemText(2, QCoreApplication::translate("MainWindow", "star ani", nullptr));
        generate_comboBox->setItemText(3, QCoreApplication::translate("MainWindow", "rnd ani", nullptr));
        generate_comboBox->setItemText(4, QCoreApplication::translate("MainWindow", "rnd img NG", nullptr));

        noise_radioButton->setText(QCoreApplication::translate("MainWindow", "noise", nullptr));
        genExp_TextEdit->setText(QCoreApplication::translate("MainWindow", "2", nullptr));
        arenaImage_TextEdit->setText(QCoreApplication::translate("MainWindow", "arena_image.png", nullptr));
        openImageField_pushButton->setText(QCoreApplication::translate("MainWindow", "Open File", nullptr));
        groupBox_5->setTitle(QCoreApplication::translate("MainWindow", "Noise Config", nullptr));
        label_34->setText(QCoreApplication::translate("MainWindow", "Time Intvl", nullptr));
        noiseFreq_label->setText(QCoreApplication::translate("MainWindow", "1000", nullptr));
        label_31->setText(QCoreApplication::translate("MainWindow", "No. Tiles", nullptr));
        noTiles_label->setText(QCoreApplication::translate("MainWindow", "40", nullptr));
        label_32->setText(QCoreApplication::translate("MainWindow", "Strength", nullptr));
        noiseStrenght_label->setText(QCoreApplication::translate("MainWindow", "20", nullptr));
        debug_tracker->setText(QCoreApplication::translate("MainWindow", "Debug Tracker", nullptr));
        label_42->setText(QCoreApplication::translate("MainWindow", "max dsplc.", nullptr));
        maxDispl_label->setText(QCoreApplication::translate("MainWindow", "60", nullptr));
        label_43->setText(QCoreApplication::translate("MainWindow", "EFWL         ", nullptr));
        EFWL_label->setText(QCoreApplication::translate("MainWindow", "50", nullptr));
        label_50->setText(QCoreApplication::translate("MainWindow", "Smthness ", nullptr));
        smoothnessFact_label->setText(QCoreApplication::translate("MainWindow", "50", nullptr));
        label_17->setText(QCoreApplication::translate("MainWindow", "Circle detection parameters:", nullptr));
        label_44->setText(QCoreApplication::translate("MainWindow", "Robot detection:", nullptr));
        label_15->setText(QCoreApplication::translate("MainWindow", "Canny:", nullptr));
        cannyThresh_label->setText(QCoreApplication::translate("MainWindow", "50", nullptr));
        label_18->setText(QCoreApplication::translate("MainWindow", "Vote", nullptr));
        houghAcc_label->setText(QCoreApplication::translate("MainWindow", "19", nullptr));
        label_16->setText(QCoreApplication::translate("MainWindow", "Min rad:", nullptr));
        kbMin_label->setText(QCoreApplication::translate("MainWindow", "14", nullptr));
        label_14->setText(QCoreApplication::translate("MainWindow", "Max rad:", nullptr));
        kbMax_label->setText(QCoreApplication::translate("MainWindow", "26", nullptr));
        label_45->setText(QCoreApplication::translate("MainWindow", "Color detection:", nullptr));
        red_checkBox->setText(QCoreApplication::translate("MainWindow", "R", nullptr));
        green_checkBox->setText(QCoreApplication::translate("MainWindow", "G", nullptr));
        blue_checkBox->setText(QCoreApplication::translate("MainWindow", "B", nullptr));
        label_36->setText(QCoreApplication::translate("MainWindow", "Canny", nullptr));
        cannyThreshLED_label->setText(QCoreApplication::translate("MainWindow", "50", nullptr));
        label_37->setText(QCoreApplication::translate("MainWindow", "Vote", nullptr));
        houghAccLED_label->setText(QCoreApplication::translate("MainWindow", "19", nullptr));
        label_38->setText(QCoreApplication::translate("MainWindow", "Min rad:", nullptr));
        kbMinLED_label->setText(QCoreApplication::translate("MainWindow", "14", nullptr));
        label_39->setText(QCoreApplication::translate("MainWindow", "Max rad:", nullptr));
        kbMaxLED_label->setText(QCoreApplication::translate("MainWindow", "26", nullptr));
        label_46->setText(QCoreApplication::translate("MainWindow", "R", nullptr));
        lowRLED_label->setText(QCoreApplication::translate("MainWindow", "50", nullptr));
        hiRLED_label->setText(QCoreApplication::translate("MainWindow", "50", nullptr));
        label_47->setText(QCoreApplication::translate("MainWindow", "G", nullptr));
        lowGLED_label->setText(QCoreApplication::translate("MainWindow", "50", nullptr));
        hiGLED_label->setText(QCoreApplication::translate("MainWindow", "50", nullptr));
        label_48->setText(QCoreApplication::translate("MainWindow", "B", nullptr));
        lowBLED_label->setText(QCoreApplication::translate("MainWindow", "50", nullptr));
        hiBLED_label->setText(QCoreApplication::translate("MainWindow", "50", nullptr));
        label_6->setText(QCoreApplication::translate("MainWindow", "Tracking Control Panel", nullptr));
        label->setText(QCoreApplication::translate("MainWindow", "Environment Control Panel", nullptr));
        resetHMap_pushButton->setText(QCoreApplication::translate("MainWindow", "Res. H.Map", nullptr));
        fitRect_pushButton->setText(QCoreApplication::translate("MainWindow", "Fit Rect", nullptr));
        fromImage_pushButton->setText(QCoreApplication::translate("MainWindow", "Load Image", nullptr));
        resetTrace_pushButton->setText(QCoreApplication::translate("MainWindow", "Res. Trace", nullptr));
        drawBall->setText(QCoreApplication::translate("MainWindow", "BALL", nullptr));
        drawTrace_CheckBox->setText(QCoreApplication::translate("MainWindow", "Trace", nullptr));
        drawHeatMap_CheckBox->setText(QCoreApplication::translate("MainWindow", "HeatMap", nullptr));
        drawRobCircles_CheckBox->setText(QCoreApplication::translate("MainWindow", "Rob. Circles", nullptr));
        drawColCircles_CheckBox->setText(QCoreApplication::translate("MainWindow", "Col. Circles", nullptr));
        draw_network->setText(QCoreApplication::translate("MainWindow", "Network", nullptr));
        draw_centroid->setText(QCoreApplication::translate("MainWindow", "Centroid", nullptr));
        draw_voronoii->setText(QCoreApplication::translate("MainWindow", "Voronoii Diagram", nullptr));
        draw_spatial_netw->setText(QCoreApplication::translate("MainWindow", "Spatial Network", nullptr));
        label_40->setText(QCoreApplication::translate("MainWindow", "H", nullptr));
        label_24->setText(QCoreApplication::translate("MainWindow", "S", nullptr));
        label_25->setText(QCoreApplication::translate("MainWindow", "V", nullptr));
        label_26->setText(QCoreApplication::translate("MainWindow", "A", nullptr));
        H_label->setText(QCoreApplication::translate("MainWindow", "H", nullptr));
        S_label->setText(QCoreApplication::translate("MainWindow", "S", nullptr));
        V_label->setText(QCoreApplication::translate("MainWindow", "V", nullptr));
        A_label->setText(QCoreApplication::translate("MainWindow", "A", nullptr));
        red_pushButton->setText(QCoreApplication::translate("MainWindow", "Red", nullptr));
        blue_pushButton->setText(QCoreApplication::translate("MainWindow", "Blue", nullptr));
        green_pushButton->setText(QCoreApplication::translate("MainWindow", "Green", nullptr));
        white_pushButton->setText(QCoreApplication::translate("MainWindow", "White", nullptr));
        black_pushButton->setText(QCoreApplication::translate("MainWindow", "Black", nullptr));
        userRed_pushButton->setText(QCoreApplication::translate("MainWindow", "u. Red", nullptr));
        userBlue_pushButton->setText(QCoreApplication::translate("MainWindow", "u. Blue", nullptr));
        seaBlue_pushButton->setText(QCoreApplication::translate("MainWindow", "Sea Blue", nullptr));
        groupBox->setTitle(QCoreApplication::translate("MainWindow", "Paint object", nullptr));
        radioButton->setText(QCoreApplication::translate("MainWindow", "Field Background", nullptr));
        radioButton_2->setText(QCoreApplication::translate("MainWindow", "Robot Custom 1", nullptr));
        radioButton_4->setText(QCoreApplication::translate("MainWindow", "Robot Pen", nullptr));
        radioButton_3->setText(QCoreApplication::translate("MainWindow", "etc", nullptr));
        label_49->setText(QCoreApplication::translate("MainWindow", "Rob Size", nullptr));
        V_label_2->setText(QCoreApplication::translate("MainWindow", "50", nullptr));
        groupBox_4->setTitle(QCoreApplication::translate("MainWindow", "Brush Type", nullptr));
        gradientRob_pushButton->setText(QCoreApplication::translate("MainWindow", "gradient", nullptr));
        solidRob_pushButton->setText(QCoreApplication::translate("MainWindow", "Solid", nullptr));
        nullRob_pushButton->setText(QCoreApplication::translate("MainWindow", "Null", nullptr));
        label_2->setText(QCoreApplication::translate("MainWindow", "Dummy Var1", nullptr));
        sliderRand0_label->setText(QCoreApplication::translate("MainWindow", "380", nullptr));
        label_3->setText(QCoreApplication::translate("MainWindow", "Dummy Var2", nullptr));
        sliderRand1_label->setText(QCoreApplication::translate("MainWindow", "200", nullptr));
        fullScreen_pushButton->setText(QCoreApplication::translate("MainWindow", "Full\n"
"Screen", nullptr));
        ArenaWindow_button->setText(QCoreApplication::translate("MainWindow", "Open\n"
"Arena", nullptr));
        cam_label_6->setText(QCoreApplication::translate("MainWindow", "Scr. No.", nullptr));
        screen_comboBox->setItemText(0, QCoreApplication::translate("MainWindow", "0", nullptr));
        screen_comboBox->setItemText(1, QCoreApplication::translate("MainWindow", "1", nullptr));
        screen_comboBox->setItemText(2, QCoreApplication::translate("MainWindow", "2", nullptr));

        label_51->setText(QCoreApplication::translate("MainWindow", "Trigerred ID:", nullptr));
        TrigID_comboBox->setItemText(0, QCoreApplication::translate("MainWindow", "0", nullptr));

        initPoints_pushButton->setText(QCoreApplication::translate("MainWindow", "Initialize Points", nullptr));
        initPoints_comboBox->setItemText(0, QCoreApplication::translate("MainWindow", "Grid", nullptr));
        initPoints_comboBox->setItemText(1, QCoreApplication::translate("MainWindow", "Star", nullptr));
        initPoints_comboBox->setItemText(2, QCoreApplication::translate("MainWindow", "Ring", nullptr));
        initPoints_comboBox->setItemText(3, QCoreApplication::translate("MainWindow", "fRead", nullptr));

        label_4->setText(QCoreApplication::translate("MainWindow", "Drawing Control Panel", nullptr));
        label_5->setText(QCoreApplication::translate("MainWindow", "Input/Output Control Panel", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
