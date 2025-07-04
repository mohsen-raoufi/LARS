#include "pylon.h"

#include <pylon/PylonIncludes.h>

static unsigned int cPylonInstances = 0;

using namespace Pylon;

PylonVideoSource::PylonVideoSource()
{
    if(cPylonInstances == 0){
        PylonInitialize();
        ++cPylonInstances;
    }
    mImgFormater.OutputPixelFormat = PixelType_BGR8packed;
}

PylonVideoSource::~PylonVideoSource()
{
    if(--cPylonInstances == 0){
        PylonTerminate();
    }
}

bool PylonVideoSource::isOpened() const
{
    return mOpened;
}

void PylonVideoSource::release()
{
    mCamera->StopGrabbing();
    mCamera.reset();
    mCamera = nullptr;
    mOpened = false;
}

bool PylonVideoSource::retrieve(cv::OutputArray image, int flag)
{
    mCamera->RetrieveResult(5000, mGrabResult, TimeoutHandling_Return );
    if(!mGrabResult->GrabSucceeded()){
        image.getMatRef() = cv::Mat();
        return false;
    }
    CPylonImage img;
    mImgFormater.Convert(img, mGrabResult);
    image.getMatRef() = cv::Mat(mGrabResult->GetHeight(), mGrabResult->GetWidth(), CV_8UC3, static_cast<uint8_t *>(img.GetBuffer()));
}

bool PylonVideoSource::open(int index, int apiPreference)
{
    auto &tlFactory = CTlFactory::GetInstance();
    DeviceInfoList_t devList;
    tlFactory.EnumerateDevices(devList);
    if(index >= devList.size()){
        mOpened = false;
    }

    try {
        mCamera = std::make_shared<CInstantCamera>( tlFactory.CreateDevice(devList.at(index)));
    } catch(std::exception &e){
        std::cout << "Exception thrown\n";
        mOpened = false;
    };


    if(mCamera){
        mCamera->StartGrabbing(); // todo: perhaps pass some integer
        mOpened = true;
    }
}
