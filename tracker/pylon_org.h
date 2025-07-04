#ifndef _PYLON_H_
#define _PYLON_H_

#include <opencv4/opencv2/videoio.hpp>
#include <pylon/InstantCamera.h>
#include <pylon/ImageFormatConverter.h>

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
};

#endif
