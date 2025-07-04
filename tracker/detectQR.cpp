#include "detectQR.h"
#include <QDebug>

DetectQR::DetectQR(cv::Mat frame)
{
    qDebug() << "Detect QR Object is defined";
    frame.copyTo(currentFrame);
}

DetectQR::~DetectQR()
{
//    delete this;
}

void DetectQR::runDetectQR()
{
    std::vector<decodedObject> decodedObjects;

    // Find and decode barcodes and QR codes
    decode(currentFrame, decodedObjects);

    // Display location
    display(currentFrame, decodedObjects);

    // Inform GUI thread of new frame (QImage)
//    emit newFrame(frame);

    qDebug() << "QR Detection finished!";
}

//void DetectQR::run()
//{

//}

void DetectQR::decode(Mat &im, std::vector<decodedObject> &decodedObjects)
{
    // Create zbar scanner
    zbar::ImageScanner scanner;

    // Configure scanner
    scanner.set_config(zbar::ZBAR_NONE, zbar::ZBAR_CFG_ENABLE, 1);

    // Convert image to grayscale
    Mat imGray, frmCopy, mask0;
    //    cv::cvtColor(currentFrame, frmCopy, cv::COLOR_BGR2HSV);
    ////    cv::inRange(frmCopy, cv::Scalar(0, 50, 50), cv::Scalar(10, 255, 255), mask0);
    //    cv::inRange(frmCopy, cv::Scalar(0, 50, 50), cv::Scalar(250, 255, 255), mask0);
    ////    imshow("hey", mask0);
    ////    waitKey(10);
    ////    imGray = currentFrame.clone();
    //    cv::bitwise_and(currentFrame, currentFrame, imGray, mask0);
    ////    imGray
    ////    imshow("hey", imGray);
    ////    cvtColor(mask0, imGray, cv::COLOR_HSV2BGR);
    ////    cvtColor(mask0, mask0, cv::COLOR_BGR2GRAY);
    //    cvtColor(imGray, imGray, cv::COLOR_BGR2GRAY);

    cvtColor(currentFrame, imGray, cv::COLOR_BGR2GRAY);

    // Wrap image data in a zbar image
    zbar::Image image(im.cols, im.rows, "Y800", (uchar *)imGray.data, im.cols * im.rows);

    // Scan the image for barcodes and QRCodes
    int n = scanner.scan(image);
    QList<decodedObject> detectedObjectList;
    // Print results
    for(zbar::Image::SymbolIterator symbol = image.symbol_begin(); symbol != image.symbol_end(); ++symbol)
    {
        decodedObject obj;


        obj.type = symbol->get_type_name();
        obj.data = symbol->get_data();

        // Print type and data
        std::cout << "Type : " << obj.type << std::endl;
        std::cout << "Data : " << obj.data << std::endl << std::endl;

        // Obtain location
        for(int i = 0; i< symbol->get_location_size(); i++)
        {
            obj.location.push_back(Point(symbol->get_location_x(i),symbol->get_location_y(i)));
        }

        decodedObjects.push_back(obj);
    }

}

void DetectQR::decodePub(Mat &im, std::vector<decodedObject> &decodedObjects)
{
    qDebug() << "I got here! tracking QR ...";
    // Create zbar scanner
    zbar::ImageScanner scanner;

    // Configure scanner
    scanner.set_config(zbar::ZBAR_NONE, zbar::ZBAR_CFG_ENABLE, 1);

    // Convert image to grayscale
    Mat imGray, frmCopy, mask0;
    //    cv::cvtColor(currentFrame, frmCopy, cv::COLOR_BGR2HSV);
    ////    cv::inRange(frmCopy, cv::Scalar(0, 50, 50), cv::Scalar(10, 255, 255), mask0);
    //    cv::inRange(frmCopy, cv::Scalar(0, 50, 50), cv::Scalar(250, 255, 255), mask0);
    ////    imshow("hey", mask0);
    ////    waitKey(10);
    ////    imGray = currentFrame.clone();
    //    cv::bitwise_and(currentFrame, currentFrame, imGray, mask0);
    ////    imGray
    ////    imshow("hey", imGray);
    ////    cvtColor(mask0, imGray, cv::COLOR_HSV2BGR);
    ////    cvtColor(mask0, mask0, cv::COLOR_BGR2GRAY);
    //    cvtColor(imGray, imGray, cv::COLOR_BGR2GRAY);

    cvtColor(currentFrame, imGray, cv::COLOR_BGR2GRAY);

    // Wrap image data in a zbar image
    zbar::Image image(im.cols, im.rows, "Y800", (uchar *)imGray.data, im.cols * im.rows);

    // Scan the image for barcodes and QRCodes
    int n = scanner.scan(image);
    QList<decodedObject> detectedObjectList;
    // Print results
    for(zbar::Image::SymbolIterator symbol = image.symbol_begin(); symbol != image.symbol_end(); ++symbol)
    {
        decodedObject obj;


        obj.type = symbol->get_type_name();
        obj.data = symbol->get_data();

        // Print type and data
        std::cout << "Type : " << obj.type << std::endl;
        std::cout << "Data : " << obj.data << std::endl << std::endl;

        // Obtain location
        for(int i = 0; i< symbol->get_location_size(); i++)
        {
            obj.location.push_back(Point(symbol->get_location_x(i),symbol->get_location_y(i)));
        }

        decodedObjects.push_back(obj);
    }

}

void DetectQR::display(Mat &im, std::vector<decodedObject>&decodedObjects)
{
    // Display barcode and QR code location
    // Loop over all decoded objects
    for(int i = 0; i < decodedObjects.size(); i++)
    {
        std::vector<Point> points = decodedObjects[i].location;
        std::vector<Point> hull;

        // If the points do not form a quad, find convex hull
        if(points.size() > 4)
            convexHull(points, hull);
        else
            hull = points;

        // Number of points in the convex hull
        int n = hull.size();

        for(int j = 0; j < n; j++)
        {
            line(im, hull[j], hull[ (j+1) % n], Scalar(255,0,0), 3);
        }

    }
    currentFrame = im.clone();
}
