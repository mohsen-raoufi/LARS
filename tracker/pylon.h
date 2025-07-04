#ifndef _PYLON_H_
#define _PYLON_H_

#include <opencv4/opencv2/videoio.hpp>
#include <pylon/InstantCamera.h>
#include <pylon/ImageFormatConverter.h>
#include <pylon/PylonBase.h>
#include <pylon/PylonImage.h>

class PylonVideoSource : public cv::VideoCapture {

    std::shared_ptr<Pylon::CInstantCamera> mCamera;
    bool mOpened = false;
    Pylon::CGrabResultPtr mGrabResult;
    Pylon::CImageFormatConverter mImgFormater;

    // VideoCapture interface
public:
    explicit PylonVideoSource();
    ~PylonVideoSource();

    bool isOpened() const;
    void release();
    bool retrieve(cv::OutputArray image, int flag = 0);
    bool open(int index, int apiPreference = cv::CAP_ANY );

    void readAllParameterValues();

    void writeParameterValues();//VarList* varList);

private:
    // freq should always be 125 MHz for Basler-ace-1300-75gc
        int camera_frequency = 125e6;
        int* v_camera_id;
//        VarDouble* v_framerate;
//        VarInt* v_balance_ratio_red;
//        VarInt* v_balance_ratio_green;
//        VarInt* v_balance_ratio_blue;
//        VarBool* v_auto_gain;
//        VarInt* v_gain;
//        VarBool* v_gamma_enable;
//        VarDouble* v_gamma;
//        VarDouble* v_black_level;
//        VarBool* v_auto_exposure;
//        VarDouble* v_manual_exposure;
//        VarStringEnum* v_color_mode;

        void resetCamera(unsigned int new_id);
        bool _stopCapture();
        bool _buildCamera();

    // A slight blur helps to reduce noise and improve color recognition.
    #ifdef OPENCV
        static const double blur_sigma;
        void gaussianBlur(RawImage& img);
        void contrast(RawImage& img, double factor);
        void sharpen(RawImage& img);
    #endif


};

#endif
