#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <opencv2/aruco.hpp>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{

    // Set main window on the specific screen
    this->move(QGuiApplication::screens().at(0)->geometry().topLeft()- this->rect().topLeft());
    this->showMaximized();
    ui->setupUi(this);

    // close the application when the GUI is closed
    this->setAttribute(Qt::WA_DeleteOnClose);

    // Initial Definitions
    timer = new QTimer();
    //    joyStick_Timer = new QTimer();

    arenaWindow = new ArenaWindow(nullptr, &wm, "LARS ARENA WINDOW");
//    arenaWindow2 = new ArenaWindow(nullptr, &wm, "ARENA WINDOW 2"); // Secondary Window is optional!


    // instantiating the envBrain to calculate the environment processes
    envBrain = new EnvBrain(&this->wm);

    ui->centralWidget->setPalette(this->palette());

    // Initial Parameters & Variables

    // // Initialization of UI
    uiInitialization();

#ifdef USE_PYLON
    qDebug() << "Using Pylon Camera!";
#else
    qDebug() << "Using V4L2 Camera!";
#endif

    //    initializePlot(ui->customPlot); // If we want to plot something!

    // Save just from Cam!
    if(ui->fromVid_rButton->isChecked())
        ui->saveVid_button->setEnabled(false);

    GUIQSize = ui->outputLabel->size();
    qDebug() << "GUI size: " << GUIQSize.width() << ", " << GUIQSize.height();

    FPS = ui->FPS_comboBox->currentText().toInt();
    rotIndex = ui->Rotate_ComboBox->currentIndex();

    detectedMarker temp;
    temp.BoundingRect = QRect(0,0,0,0);
    detectedMarkersList.clear();
    for (int i=0; i < 4; ++i){
        temp.id = i;
        detectedMarkersList.insert(i, temp);

        detectedMarkerCenterList.insert(i, QPoint(0,0));
    }

    // Just some initial values so that if no marker was detected the program does not crash
    mapA2C = cv::Mat::eye(3,3, 1);
    mapC2A = cv::Mat::eye(3,3, 1);

    this->resetHeatMap();
}


MainWindow::~MainWindow()
{
    qDebug() << "********* closing windows ... *********";
    arenaWindow->close();
    arenaWindow->hide();
    delete arenaWindow;
    qDebug() << "Arena Window is closed!";
    delete ui;
}

void MainWindow::logToFile_PosLED(QVector<Kilobot *> kiloVec)
{
    log_stream << elapsedTimer.elapsed();
    for (int i = 0; i < kiloVec.size(); ++i){
        log_stream << "\t" << i << "\t" << kiloVec[i]->getPosition().x() << "\t" << kiloVec[i]->getPosition().y() << "\t" << kiloVec[i]->getLedColour();
    }
    log_stream << endl;
}

void MainWindow::logToFile(QVector<Kilobot *> kiloVec)
{
    log_stream << elapsedTimer.elapsed();
    for (int i = 0; i < kiloVec.size(); ++i){
        log_stream << "\t" << i << "\t" << kiloVec[i]->getPosition().x() << "\t" << kiloVec[i]->getPosition().y() << "\t" << kiloVec[i]->getLedColour()
                   << "\t" << kiloVec[i]->getVelocity().x() << "\t" << kiloVec[i]->getVelocity().y() ;
    }
    log_stream << endl;
}

void MainWindow::logToFile(QVector<QPoint> posVec)
{
    log_stream << elapsedTimer.elapsed();
    for (int i = 0; i < posVec.size(); ++i){
        log_stream << "\t" << i << "\t" << posVec[i].x() << "\t" << posVec[i].y() ;
    }
    log_stream << endl;
}

void MainWindow::on_capturing_button_clicked()
{
    if(ui->useARKCap_CheckBox->isChecked()) {
        if(ui->fromCam_rButton->isChecked())//fromCam)
        {
            if(ui->capturing_button->isChecked()){
                qDebug() << "capturing button is checked!";
                bool capOpenedBool = this->kbtracker.RUNcapture();

                if(capOpenedBool) {
                    qDebug() << " Openning Camera ...";
                    qDebug() << "Camera opened successfully: " << capOpenedBool;
                    FPS = ui->FPS_comboBox->currentText().toInt();
                    srcStr = "Camera";
                }
                else if(ui->fromVid_rButton->isChecked()) //(fromFile)
                {
                    srcStr = "Video File";
                }
                ui->capturing_button->setText("Disconnect Camera");
                fullCapSize = this->kbtracker.getImageSize();
                capSize = cv::Size(fullCapSize.width(), fullCapSize.height());

                // In case crop is not pressed, sizeInCap should be defined!
                sizeInCap = QSize(fullCapSize);

                resetHeatMap();

                //        // New edits:
                //        cap.set(cv::CAP_PROP_AUTOFOCUS, false);
                //        cv::Size orgSize = cv::Size(cap.get(cv::CAP_PROP_FRAME_WIDTH),cap.get(cv::CAP_PROP_FRAME_HEIGHT));
                //        capSize = cv::Size(MIN(cap.get(cv::CAP_PROP_FRAME_WIDTH),maxCapSize.width),MIN(cap.get(cv::CAP_PROP_FRAME_HEIGHT),maxCapSize.height));
                //        xGUIScale = double(GUISize.width)/double(capSize.width);
                //        yGUIScale = double(GUISize.height)/double(capSize.height);
                //        qDebug() << " Org. Frame Size : [ " << orgSize.width << " ," << orgSize.height<< "], Cap Size: [" << capSize.width << " ," << capSize.height << " ] , Scale : [ " << xGUIScale << ", " << yGUIScale << " ]" ;//<<std::endl;
                ui->textOut->setText(srcStr + " is Opened Successfully ");
            }
            else {
                qDebug() << "Please note that the HeatMap won't work if you restart capturing! :)"; // TODO
                this->kbtracker.LOOPstartstop(1);
                this->kbtracker.stopExperiment();
                ui->capturing_button->setText("Connect to Camera");
            }
        }
    }
    else
        qDebug() << "This feature is not yet ready! \nPlease check use VRK cam!";

}

void MainWindow::convertInt2HexStr(int input, std::string &output)
{

    if(input<10)
        output = std::to_string(input);
    else
    {
        switch (input) {
        case 10:
            output = "A";
            break;
        case 11:
            output = "B";
            break;
        case 12:
            output = "C";
            break;
        case 13:
            output = "D";
            break;
        case 14:
            output = "E";
            break;
        case 15:
            output = "F";
            break;
        default:
            break;
        }
    }
}

void MainWindow::showImage(cv::Mat frame)
{
    frame.copyTo(currentFrame); // MOHSEN: check if I am using "current frame somewhere else"
    emit imageRawReceived(frame);

    if(!frame.empty())
    {
        cvtColor(frame,frame,cv::COLOR_BGR2RGB);

        // TO DO: Process the image and add whatever you want, graphical stuff on the QImage....
        drawKilobots(frame);

        //        qDebug() << "cap size: " << capSize.width << ", " << capSize.height;


        //        qDebug() << "FRAME SIZE: " << frame.cols << ", " << frame.rows << "type: " << frame.type() << ",\t HEAT Map: " << wm.heatMap.type();

        //        if(wm.drawHeatMap)
        //        {
        //            addWeighted(frame, 0.5, wm.heatMap, 0.5, 0.0, frame);
        //        }

        // TO DO: Complete this, find the bugs, and make it nicer!
        //        if(frame.size>0)
        //        {
        //            //            qDebug() << "FRAME SIZE: " << frame.cols << ", " << frame.rows << "type: " << frame.type() << ",\t HEAT Map: " << wm.heatMap.type();
        //            cv::Mat tmpHeatMap, tmp;
        //            cv::resize(wm.heatMap, tmpHeatMap, Size(frame.cols, frame.rows));

        //            ////            imshow("heatMap: ", tmpHeatMap);

        //            tmpHeatMap.convertTo(tmp, frame.type());
        //            cvtColor(tmp, tmp, cv::COLOR_BGRA2RGB);


        //            addWeighted(frame, 0.5, tmp, 0.5, 0.0, frame);
        //            ////            qDebug() << "frame size: " << frame.cols << ", " << frame.rows << " || heatMap size: " << wm.heatMap.cols << ", " << wm.heatMap.rows << " || temp Size: " <<
        //            ////                        tmp.cols << ", " << tmp.rows;

        //            ////            imshow("Temp:", tmp);
        //        }


        QImage QIm((uchar*)frame.data, frame.cols, frame.rows, frame.step, QImage::Format_RGB888);
        QImage QImScaled = QIm.scaledToWidth(ui->outputLabel->width());


        ui->outputLabel->setPixmap(QPixmap::fromImage(QImScaled));

        cvtColor(frame,frame,cv::COLOR_RGB2BGR);
        emit imageProcReady(frame);

        //        ui->graphicsView->scene()->addPixmap(QPixmap::fromImage(QIm.scaledToWidth(ui->outputLabel->width())));
    }
}


void MainWindow::writeSettings()
{
    // THESE ARE TO DOs!
    QSettings settings("SCIoI", "P27 VRK ver1.1");

    settings.beginGroup("MainWindow");
    settings.setValue("size", size());
    settings.setValue("hue", ui->V_slider->value());
    settings.endGroup();
}

void MainWindow::readSettings()
{
    QSettings settings("SCIoI", "P27 VRK ver1.1");

    settings.beginGroup("MainWindow");
    //    resize(settings.value("size"));
    qDebug() << settings.value("hue").toInt();
    //    on_V_slider_actionTriggered(settings.value("hue"));
    settings.endGroup();
}

void MainWindow::myDebug(QString string)
{
    ui->textOut->setText(string);
}

void MainWindow::getKilos(QVector<Kilobot *> kiloVec)
{
    if(kiloVec.size()>0){
        this->kiloVector = kiloVec;
        //        this->kiloList = this->kiloVector.toList();
        wm.rob_Type0_pos.clear();
        wm.rob_toEnlight.clear();

        int idToTrig = ui->TrigID_comboBox->currentIndex()-ui_trigID_zero;
        for (int i=0; i<kiloVec.size(); i++)
        {
            QPoint tmp = mapPoint(QPoint(kiloVec.at(i)->getPosition().x(), kiloVec.at(i)->getPosition().y()), mapC2A)-wm.marker0_BR;
            //            qDebug() << "Kilobot #: " << i << ", was detected at: " << kiloVec.at(i)->getPosition().x() << ", " <<  kiloVec.at(i)->getPosition().y() <<
            //                        ", and the mapped Point is at: " << tmp.x() << ", " <<
            //                        tmp.y();


            //            qDebug() << "Center is: " << wm.expFieldRect.center().x() << ", " << wm.expFieldRect.center().y();
            //            qDebug() << "M1 BR is: " << wm.marker0_BR.x() << ", " << wm.marker0_BR.y();

            wm.rob_Type0_pos.append(tmp);//mapPoint(QPoint(kiloVec.at(i)->getPosition().x(), kiloVec.at(i)->getPosition().y()), mapC2A)-wm.marker0_BR);
            if(idToTrig==-ui_trigID_zero)
                wm.rob_toEnlight.append(true);
            else if(idToTrig==i)
                wm.rob_toEnlight.append(true);
            else
                wm.rob_toEnlight.append(false);
        }


        // if draw traces
        QVector<QPoint> tempVec, tempVec2;
        for (int i=0; i<kiloVec.size(); i++)
        {
            tempVec.append(wm.rob_Type0_pos.at(i));//mapPoint(QPoint(kiloVec.at(i)->getPosition().x(), kiloVec.at(i)->getPosition().y()), mapC2A));
            tempVec2.append(kiloVec.at(i)->getPosition().toPoint());
        }
        this->kiloPosVec = tempVec;
        wm.kiloPosVecOnFrame = tempVec2;


        emit kilobotPosVecReady(tempVec);// - wm.marker0_pos + QPoint(wm.marker_length, wm.marker_length) );

        wm.kiloPosVec = tempVec;

        if(listInd%10==0){
            wm.rob_traces.prepend(tempVec);
            wm.rob_traces.resize(nList);
        }
    }
    else{
        //        qDebug() << "Qlist is empty";
    }

    //    qDebug() << "I have kilobots here!, the population is: " << kiloVec.size();
}

void MainWindow::getDrawnCircles(QVector<drawnCircle> circsToDraw)
{
    this->circlsToDraw.clear();
    this->circlsToDraw = circsToDraw;
}

void MainWindow::drawOverlay(Mat &frame)
{
    // MOHSEN: probably not needed! :)
    //    cvtColor(frame, frame, cv::COLOR_RGB2GRAY);
    QVector < drawnCircle > alphaCircles;
    for (int i = 0; i < this->circlsToDraw.size(); ++i) {

        if (this->circlsToDraw[i].transparent) {
            alphaCircles.push_back(this->circlsToDraw[i]);
        }
        else{
            //            qDebug() << "MOHSEN: circle: " << i << " is not transparent!, Pos: " << this->circlsToDraw[i].pos.x << ", " << this->circlsToDraw[i].pos.y;
            cv::circle(frame,this->circlsToDraw[i].pos, this->circlsToDraw[i].r,
                       Scalar(this->circlsToDraw[i].col.red(),this->circlsToDraw[i].col.green(),this->circlsToDraw[i].col.blue()),
                       this->circlsToDraw[i].thickness);

            if (!this->circlsToDraw[i].text.empty()){
                cv::putText(frame, this->circlsToDraw[i].text,
                            this->circlsToDraw[i].pos+Point(-15,10) , //+Point(this->circsToDraw[i].r,-this->circsToDraw[i].r),
                            FONT_HERSHEY_DUPLEX, 1,
                            Scalar(this->circlsToDraw[i].col.red(),this->circlsToDraw[i].col.green(),this->circlsToDraw[i].col.blue()), 2, 8);
            }
        }
    }

    //    QVector < drawnLine > alphaLines;
    //    for (int i = 0; i < this->linesToDraw.size(); ++i) {

    //        if (this->linesToDraw[i].transparent) {
    //            alphaLines.push_back(this->linesToDraw[i]);
    //        } else{
    //            cv::polylines(display, this->linesToDraw[i].pos, false,
    //                          Scalar(this->linesToDraw[i].col.red(),this->linesToDraw[i].col.green(),this->linesToDraw[i].col.blue()),
    //                          this->linesToDraw[i].thickness, LINE_8, 0 );

    //            if (!this->linesToDraw[i].text.empty()){
    //                cv::putText(display, this->linesToDraw[i].text,
    //                            this->linesToDraw[i].pos[0]+Point(-15,10) , //+Point(this->circsToDraw[i].r,-this->circsToDraw[i].r),
    //                        FONT_HERSHEY_DUPLEX, 1,
    //                        Scalar(this->linesToDraw[i].col.red(),this->linesToDraw[i].col.green(),this->linesToDraw[i].col.blue()), 2, 8);
    //            }
    //        }
    //    }

    if (!alphaCircles.empty()) { // || !alphaLines.empty() ){
        cv::Mat overlay;
        frame.copyTo(overlay);
        for (int i = 0; i < alphaCircles.size(); ++i) {
            cv::circle(overlay,alphaCircles[i].pos, 100, //alphaCircles[i].r,
                       Scalar(alphaCircles[i].col.red(),alphaCircles[i].col.green(),alphaCircles[i].col.blue()),
                       alphaCircles[i].thickness);

            if (!alphaCircles[i].text.empty()){
                cv::putText(overlay, alphaCircles[i].text,
                            alphaCircles[i].pos+Point(-15,10) , //+Point(this->circsToDraw[i].r,-this->circsToDraw[i].r),
                            FONT_HERSHEY_DUPLEX, 1,
                            Scalar(alphaCircles[i].col.red(),alphaCircles[i].col.green(),alphaCircles[i].col.blue()), 2, 8);
            }
        }
        /*
        for (int i = 0; i < alphaLines.size(); ++i) {
            cv::polylines(display, alphaLines[i].pos, false,
                          Scalar(alphaLines[i].col.red(),alphaLines[i].col.green(),alphaLines[i].col.blue()),
                          alphaLines[i].thickness, LINE_8, 0 );

            if (!alphaLines[i].text.empty()){
                cv::putText(display, alphaLines[i].text,
                            alphaLines[i].pos[0]+Point(-15,10) , //+Point(this->circsToDraw[i].r,-this->circsToDraw[i].r),
                        FONT_HERSHEY_DUPLEX, 1,
                        Scalar(alphaLines[i].col.red(),alphaLines[i].col.green(),alphaLines[i].col.blue()), 2, 8);
            }
        }
        */
        //        double alpha = 0.2;
        //        cv::addWeighted(frame, 1.0-alpha, overlay, alpha , 0.0, frame);
    }

}

void MainWindow::drawKilobots(Mat &frame)
{
    // we add overlay circles and orientation */
    if(this->kiloVector.size()>0)
    {
        if(ui->show_HM->isChecked())//true) // draw heatmap on GUI
            drawHeatMapOnGUI(frame);

        wm.kiloColor.clear();

        for (int i = 0; i < this->kiloVector.size(); ++i) {
            //cv::circle(display,Point(kilos[i]->getPosition().x(),kilos[i]->getPosition().y()),10,Scalar(0,255,0),2);
            Scalar rgbColor(255,255,255);

            if(ui->draw_bots_colors->isChecked()){
                switch (kiloVector[i]->getLedColour()){
                case OFF:{
                    break;
                }
                case RED:{
                    rgbColor[0] = 255;
                    rgbColor[1] = 0;
                    rgbColor[2] = 0;
                    break;
                }
                case GREEN:{
                    rgbColor[0] = 0;
                    rgbColor[1] = 255;
                    rgbColor[2] = 0;
                    break;
                }
                case BLUE:{
                    rgbColor[0] = 0;
                    rgbColor[1] = 0;
                    rgbColor[2] = 255;
                    break;
                }
                }
            }
            else{
                rgbColor = Scalar(255,255,255);
            }

            wm.kiloColor.append(rgbColor);

            if(ui->draw_bots->isChecked())
                cv::circle(frame,Point(kiloVector[i]->getPosition().x(),kiloVector[i]->getPosition().y()),kbtracker.kbMinSize,rgbColor,2);

            // TO DO: add some transparency to the circles, something like a weighted add, so that the circles are transparent!

            if (ui->show_vel->isChecked()){//this->t_type & ROT){
                Point center(round(kiloVector[i]->getPosition().x()), round(kiloVector[i]->getPosition().y()));
                QLineF currVel = QLineF(QPointF(0,0),this->kiloVector[i]->getVelocity());
                //            currVel.setLength(currVel.length()*10.0f+50.0f);
                currVel.setLength(currVel.length()*1.0f+5.0f);
                QPointF hdQpt = currVel.p2() + this->kiloVector[i]->getPosition();
                Point heading(hdQpt.x(), hdQpt.y());
                line(frame, center, heading, rgbColor, 6);
            }

            if (ui->show_ids->isChecked()) {
                int offset = kbtracker.kbMinSize;
                putText(frame, QString::number(this->kiloVector[i]->getID()).toStdString(), Point(kiloVector[i]->getPosition().x(),kiloVector[i]->getPosition().y()-offset), FONT_HERSHEY_SIMPLEX, 0.6, rgbColor, 2);
            }
        }

    }
}

void MainWindow::drawHeatMapOnGUI(Mat &frame)
{
    cv::Mat circTemp;

    //    qDebug() << "frame size: " << frame.cols << ", " << frame.rows;

    heatMapOnFrame.copyTo(circTemp);

    for( int i=0; i<this->kiloVector.size(); i++)
    {
        QPointF tmpPos = this->kiloVector.at(i)->getPosition();

        if(true) //_wm->drawHeatMap)
        {
            // Update HeatMap
            cv::Point2d tmp = cv::Point2d(tmpPos.x(), tmpPos.y());
            //            cv::circle(circTemp, tmp, 5, cv::Scalar(255*1000,0,0), 7);
            //            cv::circle(circTemp, tmp, 5, cv::Scalar(255*1000,0,0), 7); // >>
            //            cv::circle(circTemp, tmp, 5, cv::Scalar(0*1000,0,0), 7);
            //            cv::circle(circTemp, tmp, 5, cv::Scalar(255*1000), 7);

            int HMIntensity = 255*1000;
            cv::Scalar colorHeatMap = cv::Scalar(0,255,255);

            if(ui->draw_bots_colors->isChecked()){

                switch (kiloVector[i]->getLedColour()){
                case OFF:{
                    break;
                }
                case RED:{
                    colorHeatMap[0] = HMIntensity;
                    break;
                }
                case GREEN:{
                    colorHeatMap[1] = HMIntensity;
                    break;
                }
                case BLUE:{
                    colorHeatMap[2] = HMIntensity;
                    break;
                }
                }
            }

            cv::circle(circTemp, tmp, 5, colorHeatMap, 7);
        }
    }

    float alphaForget = 0.001;
    cv::addWeighted(circTemp, alphaForget, heatMapOnFrame, 0.99-alphaForget, 0, heatMapOnFrame);

    //    // add weighted the Heatmap on the frame
    cv::Mat finImg, tmpFrame;
    heatMapOnFrame.copyTo(finImg);
    finImg.convertTo(finImg, frame.type());
    frame.copyTo(tmpFrame);

//    cv::imshow("heatMap on Frame:", heatMapOnFrame);

    //    qDebug() << "frame types in heatmap: tmpFrame: " << tmpFrame.type() << ", finImg: " << finImg.type() << ", frame: " << frame.type();

    try {
        //        cv::addWeighted(tmpFrame, 0.5, finImg, 0.5, 0, frame);
        cv::addWeighted(tmpFrame, 0.8, finImg, 0.5, 0, frame);
        //        frame.convertTo(frame, -1, 1.6, 40); // Increase contrast
    } catch (...) {
        //        cv::imshow("tmpFrame:", tmpFrame);
        //        cv::imshow("finImg:", finImg);
        //        cv::imshow("frame:", frame);
        qDebug() << "something went wrong here! Check me Please! BTW, I am reseting HeatMap";
        resetHeatMap();
    }

}

void MainWindow::findMarkerRect()
{
    //    qDebug() << "Finding the markers rect, with n Rects: " << detectedMarkersList.size();
    if(detectedMarkersList.size() == 4){ // This condition is dummy now! the size of the list is fixed! :)
        QPoint M0TL_C, M1TL_C, M2TL_C, M3TL_C, M0BR_C, M3BR_C, M1TR_C, M2BL_C;
        M0TL_C = detectedMarkersList.at(0).BoundingRect.topLeft();
        M1TL_C = detectedMarkersList.at(1).BoundingRect.topLeft();
        M2TL_C = detectedMarkersList.at(2).BoundingRect.topLeft();
        M3TL_C = detectedMarkersList.at(3).BoundingRect.topLeft();

        M0BR_C = detectedMarkersList.at(0).BoundingRect.bottomRight();
        M3BR_C = detectedMarkersList.at(3).BoundingRect.bottomRight();
        M1TR_C = detectedMarkersList.at(1).BoundingRect.topRight();
        M2BL_C = detectedMarkersList.at(2).BoundingRect.bottomLeft();

        vector<Point2f> RectA2, RectC2;
        int markerHalfWidth = (int) (wm.marker_length/2);
        qDebug() << "marker half width: " << markerHalfWidth;
        QPoint wmMarker0C, wmMarker1C, wmMarker2C, wmMarker3C;
        QPoint markerTL2Cent = QPoint(markerHalfWidth,markerHalfWidth);
        QPoint M0C_A, M1C_A, M2C_A, M3C_A, M0C_C, M1C_C, M2C_C, M3C_C;

        M0C_C = detectedMarkerCenterList.at(0);
        M1C_C = detectedMarkerCenterList.at(1);
        M2C_C = detectedMarkerCenterList.at(2);
        M3C_C = detectedMarkerCenterList.at(3);

        wmMarker0C = wm.marker0_pos + markerTL2Cent;
        wmMarker1C = wm.marker1_pos + markerTL2Cent;
        wmMarker2C = wm.marker2_pos + markerTL2Cent;
        wmMarker3C = wm.marker3_pos + markerTL2Cent;

        RectA2.push_back(Point2f(wmMarker0C.x(), wmMarker0C.y()));
        RectA2.push_back(Point2f(wmMarker1C.x(), wmMarker1C.y()));
        RectA2.push_back(Point2f(wmMarker2C.x(), wmMarker2C.y()));
        RectA2.push_back(Point2f(wmMarker3C.x(), wmMarker3C.y()));

        RectC2.push_back(Point2f(M0C_C.x(),M0C_C.y()));
        RectC2.push_back(Point2f(M1C_C.x(),M1C_C.y()));
        RectC2.push_back(Point2f(M2C_C.x(),M2C_C.y()));
        RectC2.push_back(Point2f(M3C_C.x(),M3C_C.y()));

        //        std::cout << "RECT  A: " << RectA2 << std::endl;
        //        std::cout << "RECT  C: " << RectC2 << std::endl;

        mapA2C = getPerspectiveTransform(RectA2, RectC2);
        mapC2A = getPerspectiveTransform(RectC2, RectA2);

        QPoint M0TL_A, M1TL_A, M2TL_A, M3TL_A, M0BR_A, M3BR_A;
        M0TL_A = mapPoint(M0TL_C, mapC2A);
        M1TL_A = mapPoint(M1TL_C, mapC2A);
        M2TL_A = mapPoint(M2TL_C, mapC2A);
        M3TL_A = mapPoint(M3TL_C, mapC2A);
        M0BR_A = mapPoint(M0BR_C, mapC2A);
        M3BR_A = mapPoint(M3BR_C, mapC2A);

        M0C_A = mapPoint(M0C_C, mapC2A);
        M1C_A = mapPoint(M1C_C, mapC2A);
        M2C_A = mapPoint(M2C_C, mapC2A);
        M3C_A = mapPoint(M3C_C, mapC2A);

        wm.expFieldPoints.clear();
        wm.expFieldPoints << M0C_A << M1C_A << M3C_A << M2C_A; // to draw the rectangle through the centers of the markers

        QRect insideRect = QRect(M0BR_A,M3TL_A);
        wm.insideRect = insideRect;

        QRect outsideRet = QRect(M0TL_A,M3BR_A);
        wm.outsideRect = outsideRet;

        wm.marker0_BR = QPoint(wm.marker0_pos + QPoint(wm.marker_length, wm.marker_length));

        wm.expFieldRect = QRect(wm.marker0_BR, wm.marker3_pos);
        envBrain->resetHeatMap(); // to prevent heatmap size inconsistency

        //        if(!ui->crop_pushButton->isChecked())
        //        {
        //            cropQRect = QRect(M0TL_C, M3BR_C);
        //            cropRectDefined = true;
        //            TLInCap = cropQRect.topLeft();
        //            sizeInCap = cropQRect.size();
        //            QRect tempRect = QRect(cropQRect.topLeft(), cropQRect.size());
        //            this->kbtracker.updateCropPoints(tempRect);
        //            capSize = cv::Size(tempRect.width(), tempRect.height());
        //        }

        //        ui->cropTL_xTextEdit->setText(QString::number(M0TL_C.x()));
        //        ui->cropTL_yTextEdit->setText(QString::number(M0TL_C.y()));

        //        ui->cropsz_wTextEdit->setText(QString::number(M3BR_C.x() - M0TL_C.x()));
        //        ui->cropsz_hTextEdit->setText(QString::number(M3BR_C.y() - M0TL_C.y()));
    }
}

void MainWindow::calibrateKilobot()
{
    calib->show();

}

void MainWindow::on_fromVid_rButton_clicked()
{
    //    ui->save_set_button->setEnabled(false);
}

void MainWindow::on_fromCam_rButton_clicked()
{
    //    ui->save_set_button->setEnabled(true);
}

void MainWindow::rot90(cv::Mat &matImage, int rotflag)
{
    // 0 = 90CW,  1 = 180,  2 = 90 CCW
    if (rotflag == 0){
        transpose(matImage, matImage);
        flip(matImage, matImage,1); //transpose+flip(1)=CW
    } else if (rotflag ==1){
        flip(matImage, matImage,-1);    //flip(-1)=180
    } else if (rotflag == 2) {
        transpose(matImage, matImage);
        flip(matImage, matImage,0); //transpose+flip(0)=CCW
    }else { //if not 1,2,3:
        std::cout  << "Unknown rotation flag(" << rotflag << ")" <<std::endl;
    }

}

void MainWindow::mouseReleaseEvent(QMouseEvent *event)
{
    if(isValidPlaceForSelect(event->x(), event->y()))
    {
        qDebug() << "Event : [ " << event->x() << ", " << event->y() << " ]";
        qDebug() << "Rubber band TopLeft is set at: " << rubberBand->x() << ", " << rubberBand->y();
        qDebug() << "Rubber band size is set at: " << rubberBand->size().width() << ", " << rubberBand->size().height();

        ui->cropTL_xTextEdit->setText(QString::number(rubberBand->x()));
        ui->cropTL_yTextEdit->setText(QString::number(rubberBand->y()));
        ui->cropsz_wTextEdit->setText(QString::number(rubberBand->width()));
        ui->cropsz_hTextEdit->setText(QString::number(rubberBand->height()));

        cropQRect = QRect(rubberBand->x(), rubberBand->y(), rubberBand->width(), rubberBand->height());
        qDebug() << "Crop Rect TopLeft is set at: " << cropQRect.topLeft().x() << ", " << cropQRect.topLeft().y();

        rubberBand->close();
    }
    else
        qDebug() << "check this condition!";
}


//bool MainWindow::eventFilter(QObject *obj, QEvent *event)
//{
//    if (event->type() == QEvent::MouseButtonPress || event->type() == QEvent::MouseMove || event->type() == QEvent::MouseButtonRelease)
//    {
//        if(mouseButtonClicked)
//        {
//            return QMainWindow::eventFilter(obj, event);
//        }
//        else
//        {
//            qDebug()<<"Select a mode!";
//        }
//    }
//    else
//    {
//        // pass the event on to the parent class
//        return QMainWindow::eventFilter(obj, event);
//    }
//}

void MainWindow::mousePressEvent(QMouseEvent *event)
{

    if(isValidPlaceForSelect(event->x(),event->y()))
    {
        std::cout << "Event : [ " << event->x() << ", " << event->y() << " ]" <<std::endl;
        origin = event->pos() - mouseBias;
        rubberBand->setGeometry(QRect(origin, QSize()));
        rubberBand->show();
    }
}

void MainWindow::mouseMoveEvent(QMouseEvent *event)
{

    if(isValidPlaceForSelect(event->x(),event->y()))
    {
        qDebug() << "Mouse moves to : " << event->x() << ", " << event->y();
        rubberBand->setGeometry(QRect(origin, event->pos() - mouseBias));//.normalized());
    }
    else
    {
        rubberBand->hide();
        firstPointSelectedIsValid = false;
    }
}

bool MainWindow::isValidPlaceForSelect(int x, int y)
{
    bool isValid = false ;
    isValid = ui->outputLabel->rect().contains(x-mouseBias.x(),y-mouseBias.y());
    qDebug() << "isvalid: " << isValid;
    return isValid;
}

void MainWindow::on_open_set_button_clicked()
{
    // TO DO: the whole open/read/write/save Setting ...
    QString fileAddress = QFileDialog::getOpenFileName(this,tr("Select Setting File"), "/home/p27/Kilobot_Materials/savedData/", tr("All Files (*.*)"));
    ui->filePath_user->setText(fileAddress);
}

void MainWindow::on_Rotate_ComboBox_activated(const QString &arg1)
{
    rotIndex = ui->Rotate_ComboBox->currentIndex();
    QString str = QString::number(rotIndex);
    ui->textOut->setText(str);
}

void MainWindow::on_saveVid_button_clicked()
{
    bool saveProcVidBool = true;

    if(ui->saveVid_button->isChecked())
    {
        on_writeLog_button_clicked(false);
        this->ui->writeLog_button->setChecked(false);
        on_writeLog_button_clicked(true);
        this->ui->writeLog_button->setChecked(true);


        //    QString fileAddressBase = QFileDialog::getSaveFileName(this,tr("Select Processed File"), "/home/p27/Kilobot_Materials/savedData", tr("All Files (*.*)"));
        QString dateStrng = QDateTime::currentDateTime().toString("yyyy_MM_dd__hh_mm");
        QString fileAddressBase = ui->filePath_user->text() + dateStrng + "_Video" ;
        //    cam_timer->start();
        QString fileAddress = fileAddressBase + ".mkv";
        qDebug() << "Processed Video will Save to File: " <<  fileAddress;
        ui->textOut->setText("Processed Video will Save to File : \n" + fileAddress);
        boolSaveVideoFile = true;
        int codec = cv::VideoWriter::fourcc('X', '2', '6', '4');


        //        sRawVidThrd = new saveVidThread(fileAddress.toStdString(), codec, 250, capSize, true);
        sRawVidThrd = new saveVidThread(fileAddress.toStdString(), codec, 100, capSize, true);
        connect(this, SIGNAL(imageRawReceived(cv::Mat)), this->sRawVidThrd, SLOT(run(cv::Mat)));
        sRawVidThrd->start(QThread::LowestPriority);

        procSize = cv::Size(sizeInCap.width(), sizeInCap.height());
        fileAddress = fileAddressBase + "_Proc.mkv";
        //        sProcVidThrd = new saveVidThread(fileAddress.toStdString(), codec, 250, procSize, true);

        if(saveProcVidBool)
        {
            sProcVidThrd = new saveVidThread(fileAddress.toStdString(), codec, 100, procSize, true);

            qDebug() << "Saving video with cap size: " << capSize.width << ", " << capSize.height << " ||| procSize: " << procSize.width << ", " << procSize.height;

            connect(this, SIGNAL(imageProcReady(cv::Mat)), this->sProcVidThrd, SLOT(run(cv::Mat)));
            sProcVidThrd->start(QThread::LowestPriority);
        }
    }
    else
    {
        on_writeLog_button_clicked(false);
        this->ui->writeLog_button->setChecked(false);

        disconnect(this, SIGNAL(imageRawReceived(cv::Mat)), this->sRawVidThrd, SLOT(run(cv::Mat)));
        sRawVidThrd->release();
        sRawVidThrd->quit();

        if(saveProcVidBool)
            sProcVidThrd->release();



        //                sProcVidThrd->release();
    }


}

void MainWindow::uiInitialization()
{
    /// initialize openPath
    QString styleSheetStr = "background-color: rgb(255, 255, 255); color: rgb(0, 0, 0);";
    ui->filePath_user->setStyleSheet(styleSheetStr);
    ui->filePath_user->setDisabled(false);

    bg_color.setHsv(ui->H_slider->value(), ui->S_slider->value(), ui->V_slider->value());

    screensList = QGuiApplication::screens();

    // openArena
    int screenIndex = screensList.size() - 1;
    arenaWindow->move(screensList.at(screenIndex)->geometry().topRight() - arenaWindow->frameGeometry().topRight());
    //    arenaWindow2->move(QGuiApplication::screens().at(0)->geometry().topRight() - arenaWindow->frameGeometry().topRight());

    ui->ArenaWindow_button->setText("Close Arena");
    ui->ArenaWindow_button->setChecked(true);
    on_fullScreen_pushButton_clicked();
    on_fitRect_pushButton_clicked();
    arenaWindow->show();

    // Initializing Slider Values by default Values

    DebugAv = ui->debugAV_CheckBox->isChecked();
    boolDebug = ui->debug_CheckBox->isChecked();

    rubberBand = new QRubberBand(QRubberBand::Rectangle, this->ui->outputLabel);
    mouseBias = QPoint(ui->outputLabel->x(), ui->outputLabel->y()) + QPoint(ui->frame->x(), ui->frame->y());

    // Robot Tracker Initialization
    //show default settings on the GUI
    ui->kbMax_slider->setValue(this->kbtracker.kbMaxSize);
    ui->kbMin_slider->setValue(this->kbtracker.kbMinSize);
    ui->houghAcc_slider->setValue(this->kbtracker.houghAcc);
    ui->cannyThresh_slider->setValue(this->kbtracker.cannyThresh);

    ui->kbMaxLED_slider->setValue(this->kbtracker.kbLEDMaxSize);
    ui->kbMinLED_slider->setValue(this->kbtracker.kbLEDMinSize);
    ui->houghAccLED_slider->setValue(this->kbtracker.LEDhoughAcc);
    ui->cannyThreshLED_slider->setValue(this->kbtracker.LEDcannyThresh);

    ui->maxDispl_slider->setValue((int) this->kbtracker.morfiTrack_maxDisplacement*10);
    ui->EFWL_slider->setValue((int) this->kbtracker.EFWL*10);
    ui->smoothnessFact_slider->setValue((int) (this->kbtracker.smooth_fact*100));

    ui->lowRLED_slider->setValue(100*this->kbtracker.redLThreshold);
    ui->lowGLED_slider->setValue(100*this->kbtracker.greenLThreshold);
    ui->lowBLED_slider->setValue(100*this->kbtracker.blueLThreshold);
    ui->hiRLED_slider->setValue(100*this->kbtracker.redHThreshold);
    ui->hiGLED_slider->setValue(100*this->kbtracker.greenHThreshold);
    ui->hiBLED_slider->setValue(100*this->kbtracker.blueHThreshold);

    // updating sliders on the GUI
    updateSliders();

    // Connecting signals and slots
    connect(&this->kbtracker, SIGNAL(capturedImage(cv::Mat)), this, SLOT(showImage(cv::Mat)));
    connect(&this->kbtracker, SIGNAL(errorMessage(QString)), ui->error_label, SLOT(setText(QString)));
    //    connect(ui->refresh, SIGNAL(clicked(bool)), &this->kbtracker,SLOT(RefreshDisplayedImage()));


    connect(&this->kbtracker, SIGNAL(kiloList(QVector<Kilobot*>)), this, SLOT(getKilos(QVector<Kilobot*>)));
    //    connect(&this->kbtracker, SIGNAL(circlesToDrawSig(QVector<drawnCircle>)), this, SLOT(getDrawnCircles(QVector<drawnCircle>)));


    // TO the ENV.
    //    connect(this, SIGNAL(kilobotPosVecReady(QVector<QPoint>)), this->envBrain, SLOT(updateTraces(QVector<QPoint>))); // we use a timer inside envBrain to update the traces, instead of a signal
    connect(ui->resetHMap_pushButton, SIGNAL(clicked(bool)), this->envBrain, SLOT(resetHeatMap()));
    connect(ui->resetHMap_pushButton, SIGNAL(clicked(bool)), this, SLOT(resetHeatMap()));


    // TO OverHeadController
    connect(ui->ohc_connect, SIGNAL(clicked(bool)), &this->ohc, SLOT(toggleConnection()));
    connect(ui->ohc_reset, SIGNAL(toggled(bool)), &this->ohc, SLOT(resetKilobots()));
    connect(ui->ohc_sleep, SIGNAL(toggled(bool)), &this->ohc, SLOT(sleepKilobots()));
    connect(ui->ohc_run, SIGNAL(toggled(bool)), &this->ohc, SLOT(runKilobots()));
    connect(ui->ohc_stop, SIGNAL(toggled(bool)), &this->ohc, SLOT(stopSending()));
    connect(ui->ohc_volt, SIGNAL(toggled(bool)), &this->ohc, SLOT(checkVoltage()));
    connect(ui->ohc_set_prog, SIGNAL(clicked(bool)), &this->ohc, SLOT(chooseProgramFile()));
    connect(ui->ohc_upload_prog, SIGNAL(clicked(bool)), &this->ohc, SLOT(uploadProgram()));
    connect(ui->sendBatch_pushButton, SIGNAL(pressed()), &this->ohc, SLOT(sendBatch())); // MOHSEN

    connect(this,SIGNAL(sendKiloMessage(kilobot_message)), &this->ohc, SLOT(signalKilobot(kilobot_message))); // MOHSEN

    // From OHC
    connect(&this->ohc,SIGNAL(setStopButton(bool)),ui->ohc_stop,SLOT(setChecked(bool)));
    connect(&this->ohc,SIGNAL(errorMessage(QString)), ui->error_label, SLOT(setText(QString)));


    // TO DO: FOR KILOBOT STUFF
//    connect(ui->calibrate_pushButton, SIGNAL(clicked(bool)), this, SLOT(calibrateKilobot())); // NOT WORKING YET!

    // Kilobot Tracker sliders connections
    connect(ui->houghAcc_slider, SIGNAL(valueChanged(int)), &this->kbtracker, SLOT(setHoughAcc(int)));
    connect(ui->cannyThresh_slider, SIGNAL(valueChanged(int)), &this->kbtracker, SLOT(setCannyThresh(int)));
    connect(ui->kbMax_slider, SIGNAL(valueChanged(int)), &this->kbtracker, SLOT(setKbMax(int)));
    connect(ui->kbMin_slider, SIGNAL(valueChanged(int)), &this->kbtracker, SLOT(setKbMin(int)));

    connect(ui->houghAccLED_slider, SIGNAL(valueChanged(int)), &this->kbtracker, SLOT(setLEDHoughAcc(int)));
    connect(ui->cannyThreshLED_slider, SIGNAL(valueChanged(int)), &this->kbtracker, SLOT(setLEDCannyThresh(int)));
    connect(ui->kbMaxLED_slider, SIGNAL(valueChanged(int)), &this->kbtracker, SLOT(setKbLMax(int)));
    connect(ui->kbMinLED_slider, SIGNAL(valueChanged(int)), &this->kbtracker, SLOT(setKbLMin(int)));

    connect(ui->lowRLED_slider, SIGNAL(valueChanged(int)), &this->kbtracker, SLOT(setLowRLED(int)));
    connect(ui->lowGLED_slider, SIGNAL(valueChanged(int)), &this->kbtracker, SLOT(setLowGLED(int)));
    connect(ui->lowBLED_slider, SIGNAL(valueChanged(int)), &this->kbtracker, SLOT(setLowBLED(int)));
    connect(ui->hiRLED_slider, SIGNAL(valueChanged(int)), &this->kbtracker, SLOT(setHiRLED(int)));
    connect(ui->hiGLED_slider, SIGNAL(valueChanged(int)), &this->kbtracker, SLOT(setHiGLED(int)));
    connect(ui->hiBLED_slider, SIGNAL(valueChanged(int)), &this->kbtracker, SLOT(setHiBLED(int)));

    //    connect(ui->arena_height_x_slider, SIGNAL(valueChanged(int)), &this->kbtracker, SLOT(setHeightXSlider(int)));
    //    connect(ui->arena_height_y_slider, SIGNAL(valueChanged(int)), &this->kbtracker, SLOT(setHeightYSlider(int)));

    connect(ui->refresh_pushButton, SIGNAL(clicked(bool)), &this->kbtracker,SLOT(RefreshDisplayedImage()));

    // Connect color buttons in GUI
    connect(ui->black_pushButton, &QPushButton::clicked, [this]() { QString txt = ui->black_pushButton->text(); qDebug() << "clicked : " << txt; updateColors(txt); clicked(txt); });
    connect(ui->blue_pushButton, &QPushButton::clicked, [this]() { QString txt = ui->blue_pushButton->text(); qDebug() << "clicked : " << txt; updateColors(txt); clicked(txt); });
    connect(ui->red_pushButton, &QPushButton::clicked, [this]() { QString txt = ui->red_pushButton->text(); qDebug() << "clicked : " << txt; updateColors(txt); clicked(txt); });
    connect(ui->green_pushButton, &QPushButton::clicked, [this]() { QString txt = ui->green_pushButton->text(); qDebug() << "clicked : " << txt; updateColors(txt); clicked(txt); });
    connect(ui->white_pushButton, &QPushButton::clicked, [this]() { QString txt = ui->white_pushButton->text(); qDebug() << "clicked : " << txt; updateColors(txt); clicked(txt); });

    connect(ui->gradientExpField_pushButton, &QPushButton::clicked, [this]() { wm.expFieldType = GRADIENT;});
    connect(ui->imageExpField_pushButton, &QPushButton::clicked, [this]() { wm.expFieldType = IMAGE;});
    connect(ui->nullExpField_pushButton, &QPushButton::clicked, [this]() { wm.expFieldType = NULL_BRUSH;});

    connect(ui->gradientRob_pushButton, &QPushButton::clicked, [this]() { wm.robBrushType = GRADIENT;});
    connect(ui->solidRob_pushButton, &QPushButton::clicked, [this]() { wm.robBrushType = SOLID;});
    connect(ui->nullRob_pushButton, &QPushButton::clicked, [this]() { wm.robBrushType = NULL_BRUSH;});

    // Render Arena
    connect(ui->H_slider, SIGNAL(valueChanged(int)), this, SLOT(updateColors()));
    connect(ui->V_slider, SIGNAL(valueChanged(int)), this, SLOT(updateColors()));
    connect(ui->S_slider, SIGNAL(valueChanged(int)), this, SLOT(updateColors()));
    connect(ui->A_slider, SIGNAL(valueChanged(int)), this, SLOT(updateColors()));

    // Manual Calibration Widget
    calib = new CalibWindow("Calibration Values", this);
    connect(calib, SIGNAL(calibUID(int)), this, SLOT(calibUID(int)));
    connect(calib, SIGNAL(calibLeft(int)), this, SLOT(calibLeft(int)));
    connect(calib, SIGNAL(calibRight(int)), this, SLOT(calibRight(int)));
    connect(calib, SIGNAL(calibStraight(int)), this, SLOT(calibStraight(int)));
    connect(calib, SIGNAL(calibStop()), this, SLOT(calibStop()));
    connect(calib, SIGNAL(calibSave()), this, SLOT(calibSave()));

    connect(ui->black_pushButton, SIGNAL(objectNameChanged(QString)), this, SLOT(updateColors(QString)));

    updateColors();

    wm.setFieldSize(QGuiApplication::screens().at(screenIndex)->geometry().size());
    qDebug() << "Field Size set to: " << wm.fieldSize.width() << ", " << wm.fieldSize.height();

#ifdef FOR_KILOBOT
    // shrink the field size so that the margins of the demonstratore are in the shade
    wm.setFieldSize(wm.fieldSize-QSize(825,0));
#else
    // shrink the field size so that the wood margins are in the shade
    wm.setFieldSize(wm.fieldSize-QSize(290,190));
#endif


    // setting initial values of some parameters in the WM
    wm.arenaImg = QPixmap(":/Files/arena_01.png");

    wm.drawNetwork = ui->draw_network->isChecked();

    procQSize = ui->outputLabel->size(); // for saving the processed video, this would
    procSize = cv::Size(procQSize.width(), procQSize.height());

    elapsedTimer.start();
}


void MainWindow::plotData(QCustomPlot *customPlot, double value)
{
    static QTime time(QTime::currentTime());
    double key = time.elapsed()/1000.0; // time elapsed since start of demo, by seconds
    //    customPlot->graph(0)->addData(key,tempVal);
    customPlot->xAxis->setRange(key, 3, Qt::AlignRight);
    customPlot->replot();
}

void MainWindow::initializePlot(QCustomPlot *customPlot)
{
    // Initializing Plot
    customPlot->addGraph(); // for precision error
    customPlot->addGraph(); // for trueness error

    QSharedPointer<QCPAxisTickerTime> timeTicker(new QCPAxisTickerTime);
    timeTicker->setTimeFormat("%h:%m:%s");
    customPlot->xAxis->setTicker(timeTicker);
    customPlot->axisRect()->setupFullAxesBox();
    customPlot->yAxis->setRange(-0.5, 0.5);


    customPlot->graph(0)->setName("Err Prec");
    customPlot->graph(0)->setPen(QColor(0, 0, 255, 255));
    customPlot->graph(0)->setLineStyle(QCPGraph::lsNone);
    customPlot->graph(0)->setScatterStyle(QCPScatterStyle(QCPScatterStyle::ssCircle, 4));

    customPlot->graph(1)->setName("Err True");
    customPlot->graph(1)->setPen(QColor(255, 0, 255, 255));
    customPlot->graph(1)->setLineStyle(QCPGraph::lsNone);
    customPlot->graph(1)->setScatterStyle(QCPScatterStyle(QCPScatterStyle::ssCircle, 2));

    customPlot->legend->setVisible(true);
    //    customPlot->axisRect()->insetLayout()->setInsetAlignment(0, Qt::AlignTop|Qt::AlignLeft);

    customPlot->axisRect()->setAutoMargins(QCP::msLeft | QCP::msTop | QCP::msBottom);
    customPlot->axisRect()->setMargins(QMargins(0,0,200,0));
    customPlot->axisRect()->insetLayout()->setInsetPlacement(0, QCPLayoutInset::ipFree);
    customPlot->axisRect()->insetLayout()->setInsetRect(0, QRectF(1.1,0,0.1,0.1));
}

void MainWindow::resetHeatMap()
{
    //    cv::Mat tempHM(capSize.height, capSize.width, CV_16UC1, cv::Scalar(0)); // MOHSEN !! check why it is the reverse, height & Width
    //    cv::Mat tempHM(capSize.height, capSize.width, CV_64FC1, cv::Scalar(0)); // MOHSEN !! check why it is the reverse, height & Width
    //    cv::Mat tempHM(capSize.height, capSize.width, CV_64FC3, cv::Scalar(0,0,0)); // MOHSEN !! check why it is the reverse, height & Width
    //        cv::Mat tempHM(capSize.height, capSize.width, CV_64FC4, cv::Scalar(0,0,0,0)); // MOHSEN !! check why it is the reverse, height & Width

    cv::Mat tempHM(capSize.height, capSize.width, CV_32FC3, cv::Scalar(0,0,0));
    //    cv::Mat tempHM(capSize.height, capSize.width, CV_8UC3, cv::Scalar(0,0,0)); // ToDo: use a lighter Mat type for heatmap on frame
    tempHM.copyTo(this->heatMapOnFrame);
}

void MainWindow::on_debug_CheckBox_clicked()
{
    DebugAv = ui->debugAV_CheckBox->isChecked();
}


//void MainWindow::on_save_var_button_clicked()
//{
//    std::ofstream dataFile;
//    QString fileStr;
//    fileStr = QDateTime::currentDateTime().toString("yy_MM_dd___hh_mm");
//    fileStr = "/home/" + fileStr + "_tmp" + QString::number(ui->zoomSpeedGainEnCheckBox->isChecked()) + ".txt";
//    dataFile.open(fileStr.toStdString());
//    //    GainFile << ui->tempVal->value() << "\n";
//    dataFile.close();
//}


//void MainWindow::on_load_var_button_clicked()
//{
//    QString fileAddress = QFileDialog::getOpenFileName(this,tr("Select DATA File"), "/home/p27/Kilobot_Materials/savedData/", tr("Text Files (*.txt)"));

//    std::ifstream inputFile(fileAddress.toStdString());
//    std::string line;
//    int var[5], count = 0; // change this line accordingly
//    while (std::getline(inputFile, line))
//    {
//        std::istringstream ss(line);

//        ss >> var[count];
//        std::cout << var[count] <<std::endl;
//        count++;
//    }
//    inputFile.close();

//    //    ui->tempVal->setValue(var[0]);

//}

void MainWindow::SendKeyBoardData(int key)
{
    qDebug() << " Key board : " << key;
    std::string usrCmd;
    if(prevKeyBoard!=key)
    {
    }

    switch (key) {
    case 87: // W
    {
        qDebug() << "w or JoyStick up Pressed";
        // Forward
        kilobot_broadcast msg;
        msg.type = 1;
        ohc.broadcastMessage(msg);
        qDebug() << "Sending Forward Message to the kilobot ...";
        break;
    }
    case 65: // A
    {
        qDebug() << "a or JoyStick left Pressed";
        // Left
        kilobot_broadcast msg;
        msg.type = 2;
        ohc.broadcastMessage(msg);
        qDebug() << "Sending Left Message to the kilobot ...";
        break;
    }
    case 68: // D
    {
        qDebug() << "d or JoyStick right Pressed";
        // Right
        kilobot_broadcast msg;
        msg.type = 3;
        ohc.broadcastMessage(msg);
        qDebug() << "Sending Right Message to the kilobot ...";
        break;
    }
    case 83: // S
    {
        qDebug() << "s or JoyStick down Pressed";
        // Stop
        kilobot_broadcast msg;
        msg.type = 4;
        ohc.broadcastMessage(msg);
        qDebug() << "Sending STOP Message to the kilobot ...";
        break;
    }
        // Presenter keys
    case 66: // presenter: mid bottom
    {
        // Stop
        kilobot_broadcast msg;
        msg.type = 4;
        ohc.broadcastMessage(msg);
        qDebug() << "Sending STOP Message to the kilobot ...";
        break;
    }
    case 16777238: // presenter: Left
    {
        // Forward
        kilobot_broadcast msg;
        msg.type = 1;
        ohc.broadcastMessage(msg);
        qDebug() << "Sending Forward Message to the kilobot ...";
        break;
    }
    case 16777239: // presenter: Right
    {
        // Right
        kilobot_broadcast msg;
        msg.type = 3;
        ohc.broadcastMessage(msg);
        qDebug() << "Sending Right Message to the kilobot ...";
        break;
    }

    case 86: // v  / R1 JoyStick
    {
        qDebug() << "v or JoyStick R1 Pressed";
        ui->V_slider->setValue(ui->V_slider->value() + 10);
        //        ui->white_pushButton->clicked();
        break;
    }
    case 67: // c  / R2 JoyStick
    {
        qDebug() << "c or JoyStick R2 Pressed";
        ui->V_slider->setValue(ui->V_slider->value() - 10);
        //        ui->black_pushButton->clicked();
        break;
    }
    case 88: // x / L1 JoyStick
    {
        qDebug() << "x or JoyStick L1 Pressed";
        ohc.stopSending();
        break;
    }
    case 90: // z / L2 JoyStick
    {
        qDebug() << "z or JoyStick L2 Pressed";
        ohc.sleepKilobots();
        break;
    }

    case 78: // n / + JoyStick
    {
        qDebug() << "n or JoyStick +/start Pressed";
        ohc.runKilobots();
        break;
    }
    case 77: // m / - JoyStick
    {
        qDebug() << "m or JoyStick -/reset Pressed";
        ohc.resetKilobots();
        break;
    }

        //    case 48: // 0 / start JoyStick
        //    {
        //        qDebug() << "0 or JoyStick start Pressed";
        //        ohc.stopSending();
        //        break;
        //    }




    case 73: // i  / X JoyStick
    {
        qDebug() << "i or JoyStick X Pressed";
        ui->black_pushButton->clicked();
        //        ui->V_slider->setValue(ui->V_slider->value() + 10);
        break;
    }
        //    case 74: // j  / left arrow JoyStick
        //    {
        //        qDebug() << "k or JoyStick down Pressed";
        //        ui->V_slider->setValue(ui->V_slider->value() - 10);
        //        break;
        //    }
    case 75: // k  / Y JoyStick
    {
        qDebug() << "k or JoyStick Y Pressed";
        ui->drawHeatMap_CheckBox->click();
        //        ui->drawHeatMap_CheckBox->toggle();
        //        qDebug() << "k or JoyStick right Pressed";
        //        ui->shuffleImageExpField_pushButton->clicked();
        break;
    }
    case 82: // r  / right joystick click JoyStick
    {
        qDebug() << "r or JoyStick Right Click Pressed";
        ui->resetHMap_pushButton->clicked();
        resetHeatMap();
        break;
    }
    case 76: // l  / A JoyStick
    {
        qDebug() << "l or JoyStick A Pressed";
        ui->shuffleImageExpField_pushButton->clicked();
        break;
    }


    case 50: // 2 / down JS JoyStick
    {
        qDebug() << "2 or JoyStick down JS Pressed";
        wm.marker0_pos.setY(wm.marker0_pos.y() + 10);
        //        ui->cropTL_yTextEdit->setText(QString::number(ui->cropTL_yTextEdit->text().toInt()+10));
        update_wmMarkers();
        break;
    }
    case 56: // 8 / up JS JoyStick
    {
        qDebug() << "8 or JoyStick up JS Pressed";
        wm.marker0_pos.setY(wm.marker0_pos.y() - 10);
        //        ui->cropTL_yTextEdit->setText(QString::number(ui->cropTL_yTextEdit->text().toInt()-10));
        update_wmMarkers();
        break;
    }
    case 52: // 4 / left JS JoyStick
    {
        qDebug() << "4 or JoyStick left JS Pressed";
        wm.marker0_pos.setX(wm.marker0_pos.x() - 10);
        //        ui->cropTL_xTextEdit->setText(QString::number(ui->cropTL_xTextEdit->text().toInt()-10));
        update_wmMarkers();
        break;
    }
    case 54: // 6 / right JS JoyStick
    {
        qDebug() << "6 or JoyStick right JS Pressed";
        wm.marker0_pos.setX(wm.marker0_pos.x() + 10);
        //        ui->cropTL_xTextEdit->setText(QString::number(ui->cropTL_xTextEdit->text().toInt()+10));
        update_wmMarkers();
        break;
    }
        //    case 56: // 8 / 4/sq JoyStick
        //    {
        //        qDebug() << "?? or JoyStick 4/sq Pressed";
        ////        ui->drawHeatMap_CheckBox->toggle();
        //    }
        //    case 52: // 4 / 4/sq JoyStick
        //    {
        //        qDebug() << "??? or JoyStick 4/sq Pressed";
        ////        ui->drawHeatMap_CheckBox->toggle();
        //    }
        //    case 52: // 4 / 4/sq JoyStick
        //    {
        //        qDebug() << "? or JoyStick 4/sq Pressed";
        ////        ui->drawHeatMap_CheckBox->toggle();
        //    }

    case 51: // 3 / 3/B JoyStick
    {
        qDebug() << "3 or JoyStick 3/B Pressed";
        switch (wm.expFieldType){
        case GRADIENT:
            wm.expFieldType = IMAGE;
            break;
        case IMAGE:
            wm.expFieldType = SOLID;
            break;
        case SOLID:
            wm.expFieldType = NULL_BRUSH;
            break;
        case NULL_BRUSH:
            wm.expFieldType = GRADIENT;
            break;
        default:
            wm.expFieldType = GRADIENT;
            break;
        }
        break;
    }

    default:
    {
        usrCmd = "Null";
        break;
    }
    }

    prevKeyBoard = key;
}

void MainWindow::keyPressEvent(QKeyEvent *key)
{
    SendKeyBoardData(key->key());
}

//void MainWindow::on_JoyStick_button_pressed()
//{
//    ui->JoyStick_button->setChecked(~ui->JoyStick_button->isChecked());
//    if(ui->JoyStick_button->isChecked())
//    {
//        /// Start JoyStick Commanding
//        joyStick_Timer->start(1);
//        connect(joyStick_Timer,SIGNAL(timeout()),this,SLOT(joyStick_timeout()));
//        ui->JoyStick_button->setText("Stop JoyStick");

//    }
//    else
//    {
//        /// Stop JoyStick Commanding
//        ui->JoyStick_button->setText("Start JoyStick");
//        disconnect(joyStick_Timer,SIGNAL(timeout()),this,SLOT(joyStick_timeout()));
//    }

//}

void MainWindow::on_ArenaWindow_button_clicked()
{
    if(ui->ArenaWindow_button->isChecked()){
        arenaWindow->show();
        arenaWindow->move(QGuiApplication::screens().at(ui->screen_comboBox->currentIndex())->geometry().topRight() - arenaWindow->frameGeometry().topRight());
        ui->ArenaWindow_button->setText("Close Arena");
    }
    else {
        arenaWindow->close();
        ui->ArenaWindow_button->setText("Open Arena");
    }
}

void MainWindow::updateColors()
{
    //    qDebug() << "updating for checked ID: " << ui->buttonGroupPaintObject->checkedId();
    switch (ui->buttonGroupPaintObject->checkedId()) {
    case -2: // Background Color : // Mohsen: check this later, why IDs are like that!
        //        ui->buttonGroupPaintObject->
        //        qDebug() << "updating background color!, alpha: " << ((double)0.01)*((double)ui->A_slider->value());
        wm.setFieldColor(QColor::fromHsv(ui->H_slider->value(), ui->S_slider->value(), ui->V_slider->value()));
        //        wm.setFieldColor(QColor::fromHsvF(ui->H_slider->value(), ui->S_slider->value(), ui->V_slider->value(), ((double)0.01)*((double)ui->A_slider->value())));
        break;
    case -3: // Robot Custom 1
        //        qDebug() << "updating Robot Custom color!";
        wm.setRobotCustomColor(QColor::fromHsv(ui->H_slider->value(), ui->S_slider->value(), ui->V_slider->value()));
        //        wm.setRobotCustomColor(QColor::fromHsvF(ui->H_slider->value(), ui->S_slider->value(), ui->V_slider->value(), ((double)0.01)*((double)ui->A_slider->value())));
        break;
    case -4: // Robot Custom PEN
        //        qDebug() << "updating Robot Custom PEN!";
        wm.setRobotCustomColor(QColor::fromHsv(ui->H_slider->value(), ui->S_slider->value(), ui->V_slider->value()));
        //        wm.setRobotCustomColor(QColor::fromHsvF(ui->H_slider->value(), ui->S_slider->value(), ui->V_slider->value(), ((double)0.01)*((double)ui->A_slider->value())));
        break;
    default:
        break;
    }


    //    bg_color.setHsv(ui->H_slider->value(), ui->S_slider->value(), ui->V_slider->value());
    //        arenaWindow->changeScreenBG(bg_color);
}

void MainWindow::updateColors(QString colorString)
{
    //    qDebug() << "hey! I am here updating color: " << colorString;
    QColor temp(colorString);
    ui->H_slider->setValue(temp.hue());
    ui->S_slider->setValue(temp.saturation());
    ui->V_slider->setValue(temp.value());
    updateSliders();
    updateColors();
}

void MainWindow::on_userRed_pushButton_clicked()
{
    QColor temp;
    temp.setHsv(0, 254, 130);
    ui->H_slider->setValue(temp.hue());
    ui->S_slider->setValue(temp.saturation());
    ui->V_slider->setValue(temp.value());
    updateSliders();
    updateColors();
}

void MainWindow::on_userBlue_pushButton_clicked()
{
    QColor temp;
    temp.setHsv(230, 254, 164);
    ui->H_slider->setValue(temp.hue());
    ui->S_slider->setValue(temp.saturation());
    ui->V_slider->setValue(temp.value());
    updateSliders();
    updateColors();
}

void MainWindow::on_fullScreen_pushButton_clicked()
{
    arenaWindow->toggleFullScreen(true);
    this->raise();
    //    arenaWindow->isFullScreen() ? arenaWindow->showNormal() : arenaWindow->showFullScreen();
}

//void MainWindow::on_moveRect_pushButton_clicked()
//{
//    arenaWindow->changeSceneRect(QRect(100,100,100,100));
//}

void MainWindow::on_fitRect_pushButton_clicked()
{
    ui->fitRect_pushButton->setEnabled(false);
    //    arenaWindow->fitSceneRect();
}

void MainWindow::on_fromImage_pushButton_clicked()
{
    ui->fromImage_pushButton->setEnabled(false);
    //    if(ui->fromImage_pushButton->isChecked()){
    //        QPixmap pic("../Files/Arena_01.png");
    //        arenaWindow->setFromImage(pic);
    //        ui->fromImage_pushButton->setText("Clean Image");
    //    }
    //    else{
    //        arenaWindow->removePic();
    //        ui->fromImage_pushButton->setText("Load Image");
    //    }
}

void MainWindow::updateSliders()
{
    ui->H_label->setNum(ui->H_slider->value());
    ui->S_label->setNum(ui->S_slider->value());
    ui->V_label->setNum(ui->V_slider->value());


    ui->kbMax_label->setNum(ui->kbMax_slider->value());
    ui->kbMin_label->setNum(ui->kbMin_slider->value());
    ui->houghAcc_label->setNum(ui->houghAcc_slider->value());
    ui->cannyThresh_label->setNum(ui->cannyThresh_slider->value());

    ui->kbMaxLED_label->setNum(ui->kbMaxLED_slider->value());
    ui->kbMinLED_label->setNum(ui->kbMinLED_slider->value());
    ui->houghAccLED_label->setNum(ui->houghAccLED_slider->value());
    ui->cannyThreshLED_label->setNum(ui->cannyThreshLED_slider->value());


    ui->lowRLED_label->setNum(ui->lowRLED_slider->value());
    ui->lowGLED_label->setNum(ui->lowGLED_slider->value());
    ui->lowBLED_label->setNum(ui->lowBLED_slider->value());
    ui->hiRLED_label->setNum(ui->hiRLED_slider->value());
    ui->hiGLED_label->setNum(ui->hiGLED_slider->value());
    ui->hiBLED_label->setNum(ui->hiBLED_slider->value());
}

void MainWindow::on_saveSetting_pushButton_clicked()
{
    writeSettings();
}

void MainWindow::on_loadSetting_pushButton_clicked()
{
    readSettings();
}

void MainWindow::on_startTracking_pushButton_clicked()
{
    //    ui->startTracking_pushButton->isChecked() ? ui->startTracking_pushButton->setText("Stop Tracking") : ui->startTracking_pushButton->setText("Start Tracking");
    update_startTracking_pushBotton();

    this->kbtracker.LOOPstartstop(1);//1); // change this later ... // 3 : USER Experiment It's better to use (1) as input :)

    ui->startTracking_pushButton->isChecked() ? ui->crop_pushButton->setEnabled(false) : ui->crop_pushButton->setEnabled(true);
}

void MainWindow::update_startTracking_pushBotton()
{
    ui->startTracking_pushButton->isChecked() ? ui->startTracking_pushButton->setText("Stop Tracking") : ui->startTracking_pushButton->setText("Start Tracking");
}

void MainWindow::on_detectKilobots_pushButton_clicked()
{
    this->kbtracker.SETUPfindKilobots();

    qDebug() << "#" << kiloVector.size() << " Kilobots are detected!!";
    if(kiloVector.size()>0) // I already added id number 0 in the default of comboBox
    {
        ui->TrigID_comboBox->clear();
        ui->TrigID_comboBox->addItem("All");
        ui->TrigID_comboBox->addItem("None");
        ui->TrigID_comboBox->addItem("Mx. Centrall");

        ui_trigID_zero = 3;                 // set this to the number of other items added to the list

        for(int i=0; i<kiloVector.size(); i++)
        {
            ui->TrigID_comboBox->addItem(QString::number(i));
        }
        ui->TrigID_comboBox->setCurrentIndex(0);

    }

    if(ui->startTracking_pushButton->isCheckable())
    {
        ui->startTracking_pushButton->setChecked(false);
        update_startTracking_pushBotton();
    }
    else
        ui->startTracking_pushButton->setCheckable(true);

    qDebug() << "detection done!";

    //    detectedCircles = this->kbtracker.detectedCircles;

    //    for( size_t i = 0; i < detectedCircles.size(); i++ )
    //    {
    //        Point center(cvRound(detectedCircles[i][0]), cvRound(detectedCircles[i][1]));
    //        int radius = cvRound(detectedCircles[i][2]);
    //        // draw the circle center
    //        //circle( result, center, 3, Scalar(0,255,0), -1, 8, 0 );
    //        // draw the circle outline

    //        circle(frame, center, radius, Scalar(0,0,255), 3, 8, 0 );
    //        putText(frame, to_string(i), center-Point(0,33), FONT_HERSHEY_PLAIN, 3.5, Scalar(0,0,255), 3);
    //    }
}

void MainWindow::on_crop_pushButton_clicked()
{

    if(ui->crop_pushButton->isChecked())
    {
        if(!cropRectDefined)//cropQRect.isEmpty())
        {
            qDebug() << "crop Rect Text edit value is: " << ui->cropTL_xTextEdit->text().toInt(); //
            cropQRect.setX(ui->cropTL_xTextEdit->text().toInt());
            cropQRect.setY(ui->cropTL_yTextEdit->text().toInt());
            cropQRect.setWidth(ui->cropsz_wTextEdit->text().toInt());
            cropQRect.setHeight(ui->cropsz_hTextEdit->text().toInt());

            //    fullCapSize = this->kbtracker.getImageSize();
            qDebug() << "full cap Size is: " << fullCapSize.width() << ", \t" << fullCapSize.height();
            qDebug() << "GUI      Size is: " << GUIQSize.width() << ", \t" << GUIQSize.height();

            // Mohsen: The size of the captured image which is fitted on the QT GUI output, here I assumed it is "resized to width":
            // so, the widths of GUI and fitCap are equal! to calculate the height, we need to consider the aspect ratio of the captured frame and scale it down
            QSize fitCapSize = QSize(GUIQSize.width(), (int) ((double)fullCapSize.height()* (double) GUIQSize.width()/(double) fullCapSize.width()));
            qDebug() << "fitCapSize : " << fitCapSize.width() << ", " << fitCapSize.height();

            int widthBiasGui2Fit = 0;
            int heightBiasGui2Fit = (int) double(0.5* (GUIQSize.height() - fitCapSize.height()));

            double widthScaleFit2Cap = (double)fullCapSize.width()/(double)fitCapSize.width();
            double heightScaleFit2Cap = (double)fullCapSize.height()/(double)fitCapSize.height();

            TLInGUI = cropQRect.topLeft();
            sizeInGUI = cropQRect.size();

            TLInFit = cropQRect.topLeft() - QPoint(widthBiasGui2Fit,heightBiasGui2Fit);
            TLInFit.setX(max(min(TLInFit.x(),fitCapSize.width()),0));
            TLInFit.setY(max(min(TLInFit.y(),fitCapSize.height()),0));

            sizeInFit = cropQRect.size();
            sizeInFit.setWidth(max(min(sizeInFit.width(),fitCapSize.width()),0));
            sizeInFit.setHeight(max(min(sizeInFit.height(),fitCapSize.height()),0));

            TLInCap = TLInFit;
            TLInCap.setX((int) (double)TLInCap.x()*(double)widthScaleFit2Cap);
            TLInCap.setY((int) (double)TLInCap.y()*(double)heightScaleFit2Cap);

            sizeInCap = sizeInFit;
            sizeInCap.setWidth((int) (double)sizeInFit.width()*(double)widthScaleFit2Cap);
            sizeInCap.setHeight((int) (double)sizeInFit.height()*(double)heightScaleFit2Cap);

            qDebug() << "heightBiasGui2Fit: " << heightBiasGui2Fit;
            qDebug() << "TOP left @ GUI: " << TLInGUI.x() << ", " << TLInGUI.y() << ", in Fit: " << TLInFit.x() << ", " << TLInFit.y() << ", in Cap: " << TLInCap.x() << ", " << TLInCap.y();
            qDebug() << "Size height @ GUI: " << sizeInGUI.height() << ", in Fit: " << sizeInFit.height() << ", in Cap: " << sizeInCap.height();

            ui->crop_pushButton->setText("UnCrop");
        }
        else // crop rect was already defined thanks to marker detection!
        {
            TLInCap = cropQRect.topLeft();
            sizeInCap = cropQRect.size();
            cropRectDefined = false;
        }
    }
    else{
        TLInCap = QPoint(0,0);
        sizeInCap = QSize(fullCapSize);
        ui->crop_pushButton->setText("Crop");
    }

    QRect tempRect = QRect(TLInCap, sizeInCap);
    this->kbtracker.updateCropPoints(tempRect);
    capSize = cv::Size(tempRect.width(), tempRect.height());
    wm.capSize = capSize; // redundant variable! TO DO: Remove it later

    this->resetHeatMap();
}

void MainWindow::on_detectMarker_pushButton_clicked()
{
    if(currentFrame.size>0)
    {
        cv::Mat inputImage;
        currentFrame.copyTo(inputImage);

        std::vector<int> ids;
        std::vector<std::vector<cv::Point2f> > corners;
        cv::Ptr<cv::aruco::Dictionary> dictionary = cv::aruco::getPredefinedDictionary(cv::aruco::DICT_6X6_250);
        cv::aruco::detectMarkers(inputImage, dictionary, corners, ids);

        cv::aruco::drawDetectedMarkers(inputImage, corners, ids);
//        cv::imshow("Markers",inputImage);
//        cv::imwrite("detected_markers.png", inputImage);

        // if at least one marker detected
        qDebug() << "Aruco Markers found!: " << ids.size();

        if (ids.size() > 0){
            //        cv::aruco::drawDetectedMarkers(inputImage, corners, ids);
            for (int indexID = 0; indexID < ids.size(); ++indexID) { // for all detected markers/IDs
                QPoint tmpCenter = QPoint(0,0);

                QPoint topLeft = QPoint(corners.at(indexID).at(0).x, corners.at(indexID).at(0).y);
                QPoint bottomRight = QPoint(corners.at(indexID).at(1).x, corners.at(indexID).at(1).y);
                for (int indexCorner = 0; indexCorner < 4; ++indexCorner) { // for all corners of each marker

                    tmpCenter = tmpCenter + QPoint(corners.at(indexID).at(indexCorner).x, corners.at(indexID).at(indexCorner).y);

                    if(topLeft.x() > corners.at(indexID).at(indexCorner).x)
                        topLeft.setX(corners.at(indexID).at(indexCorner).x);
                    if(topLeft.y() > corners.at(indexID).at(indexCorner).y)
                        topLeft.setY(corners.at(indexID).at(indexCorner).y);

                    if(bottomRight.x() < corners.at(indexID).at(indexCorner).x)
                        bottomRight.setX(corners.at(indexID).at(indexCorner).x);
                    if(bottomRight.y() < corners.at(indexID).at(indexCorner).y)
                        bottomRight.setY(corners.at(indexID).at(indexCorner).y);
                }

                detectedMarkerCenterList.replace(ids.at(indexID), QPoint( round((double)tmpCenter.x()/4.0), round((double)tmpCenter.y()/4.0)));
                detectedMarker temp;
                temp.BoundingRect = QRect(topLeft, bottomRight);
                temp.id = ids.at(indexID);
                detectedMarkersList.replace(ids.at(indexID), temp);

                qDebug() << "Marker: " << ids.at(indexID) << " is at pos: "   << corners.at(indexID).at(0).x << ", " << corners.at(indexID).at(0).y << ", \t "
                         << corners.at(indexID).at(1).x << ", " << corners.at(indexID).at(1).y << ", \t "
                         << corners.at(indexID).at(2).x << ", " << corners.at(indexID).at(2).y << ", \t "
                         << corners.at(indexID).at(3).x << ", " << corners.at(indexID).at(3).y ;//<< ", \t "
            }
            for (int indexID = 0; indexID < detectedMarkersList.size(); ++indexID) {

                qDebug() << "list of marker order says: " << detectedMarkersList.at(indexID).id << ", top left is: " << detectedMarkersList.at(indexID).BoundingRect.topLeft().x()
                         << ", " << detectedMarkersList.at(indexID).BoundingRect.topLeft().y();

                //            qDebug() << "list of marker order says: " << detectedMarkersList.at(indexID).id << ", Bottom right is: " << detectedMarkersList.at(indexID).BoundingRect.bottomRight().x()
                //                     << ", " << detectedMarkersList.at(indexID).BoundingRect.bottomRight().y();


                //            qDebug() << "list of marker order says: " << indexID << ", center is: " << detectedMarkerCenterList.at(indexID).x() << ", " << detectedMarkerCenterList.at(indexID).y();
            }
        }
        findMarkerRect();
    }


    //    else
    //    {
    //        mapA2C = cv::Mat::eye(3,3, 1);
    //    }
}

void MainWindow::on_markerWidth_Slider_sliderMoved(int position)
{
    wm.marker_length = position;
}

QPoint MainWindow::mapPoint(QPoint P, QVector2D scale, QVector2D bias)
{
    QPoint P2;
    P2.setX(P.x()*scale.x() + bias.x());
    P2.setY(P.y()*scale.y() + bias.y());

    return P2;
}

QPoint MainWindow::mapPoint(QPoint P, Matx33f lambda)
{
    cv::Point3f homogeneous = lambda * Point2f(P.x(), P.y());
    homogeneous /= homogeneous.z;
    return QPoint(homogeneous.x, homogeneous.y);
}

QPoint MainWindow::mapPoint(QPoint P, Matx33f rvec, Point3f tvec)
{
    cv::Point3f homogeneous = rvec*Point2f(P.x(), P.y())  + tvec;
    return QPoint(homogeneous.x, homogeneous.y);
}



void MainWindow::on_debug_tracker_stateChanged(int arg1)
{
    this->kbtracker.drawDebugBool = ui->debug_tracker->isChecked();
}


void MainWindow::on_maxDispl_slider_sliderMoved(int position)
{
//#ifdef FOR_KILOBOT
//    this->kbtracker.morfiTrack_maxDisplacement = (float) position/10.0;
//#else
    this->kbtracker.morfiTrack_maxDisplacement = (float) position/2.0;
//#endif
}


void MainWindow::on_EFWL_slider_sliderMoved(int position)
{
    this->kbtracker.EFWL = (float) position/10.0;
}


//void MainWindow::on_nullRob_pushButton_clicked()
//{
//    //    wm.brush_robotCustom_0 = &QBrush(Qt::NoBrush);
//    //    wm.brush_robotCustom_0 = *QBrush(Qt::NoBrush);

//    wm.setNullRobotCustomBrush(ui->nullRob_pushButton->isChecked());
//    //    wm.setRobotCustomColor(Qt::NoBrush);
//}


void MainWindow::on_robRendRad_slider_sliderMoved(int position)
{
    wm.robRad = position;
}


void MainWindow::on_smoothnessFact_slider_sliderMoved(int position)
{
    this->kbtracker.smooth_fact = (float) position/100.0;
}


void MainWindow::on_imageExpField_pushButton_clicked(bool checked)
{
    wm.loadImgBackground = checked;
    QString address = ":/Files/" + ui->arenaImage_TextEdit->text();
    qDebug() << "Image loaded from: " << address;
    wm.arenaImg = QPixmap(address);
}


void MainWindow::on_initPoints_pushButton_clicked(bool checked)
{
    if(checked)
    {
        switch (ui->initPoints_comboBox->currentIndex()) {
        case 0: // Grid
            wm.pointsToDraw = envBrain->makeGridPoints(30,30,30,30, wm.expFieldRect.topLeft());
            break;
        case 1: // Star
            wm.pointsToDraw = envBrain->makeStarPoints(5,20,10, wm.expFieldRect.center());
            wm.pointsToDraw.append(wm.expFieldRect.center());
            break;
        case 2: // Ring
            qDebug() << "Not yet written!";
            break;
        case 3: // File Read
            // TO DO: read positions from a text file
            qDebug() << "Not yet written!";
            break;
        default:
            break;
        }

        wm.drawInitPoint = true;


        qDebug() << "initial points to draw size: " << wm.pointsToDraw.size();
    }
    else
        wm.pointsToDraw.clear();
}


void MainWindow::on_resetTrace_pushButton_clicked()
{
    wm.rob_traces.clear();
}


void MainWindow::calibStop() {
    //    if (sending) {
    //        sendMessage(WAKEUP);
    //        sendMessage(WAKEUP);
    //    }
}

void MainWindow::update_wmMarkers()
{
    wm.marker1_pos = QPoint(wm.marker0_pos.x(), wm.marker0_pos.y() + wm.arenaWidth);
    wm.marker2_pos = QPoint(wm.marker0_pos.x() + wm.arenaWidth, wm.marker0_pos.y());
    wm.marker3_pos = QPoint(wm.marker0_pos.x() + wm.arenaWidth, wm.marker0_pos.y() + wm.arenaWidth);

    wm.marker0_BR = QPoint(wm.marker0_pos + QPoint(wm.marker_length, wm.marker_length));
    wm.expFieldRect = QRect(wm.marker0_BR, wm.marker3_pos);

    qDebug() << "marker 0. pos.x: " << wm.marker0_pos.x() << ", marker 0. pos.y: " << wm.marker0_pos.y();
}

void MainWindow::calibSave() {
    static calibmsg_t msg;
    msg.mode = CALIB_SAVE;
    this->ohc.sendDataMessagePub((uint8_t *)&msg, CALIB);
    //    sendDataMessage((uint8_t*)&msg, CALIB);
}
void MainWindow::calibUID(int x) {
    static calibmsg_t msg;
    msg.mode = CALIB_UID;
    msg.uid = x;
    this->ohc.sendDataMessagePub((uint8_t *)&msg, CALIB);
    //    sendDataMessage((uint8_t *)&msg, CALIB);
}
void MainWindow::calibLeft(int x) {
    static calibmsg_t msg;
    msg.mode = CALIB_TURN_LEFT;
    msg.turn_left = x;
    this->ohc.sendDataMessagePub((uint8_t *)&msg, CALIB);
    //    sendDataMessage((uint8_t *)&msg, CALIB);
}
void MainWindow::calibRight(int x) {
    static calibmsg_t msg;
    msg.mode = CALIB_TURN_RIGHT;
    msg.turn_right = x;
    this->ohc.sendDataMessagePub((uint8_t *)&msg, CALIB);
    //    sendDataMessage((uint8_t *)&msg, CALIB);
}
void MainWindow::calibStraight(int x) {
    static calibmsg_t msg;
    msg.mode = CALIB_STRAIGHT;
    msg.straight_left = x&0xFF;
    msg.straight_right = (x>>8) & 0xFF;
    this->ohc.sendDataMessagePub((uint8_t *)&msg, CALIB);
    //    sendDataMessage((uint8_t *)&msg, CALIB);
}


void MainWindow::on_drawTrace_CheckBox_stateChanged(int arg1)
{
    wm.drawTrace = this->ui->drawTrace_CheckBox->isChecked();
}


void MainWindow::on_shuffleImageExpField_pushButton_clicked()
{
    int rnd = rand() % 8 + 1;
    QString address = ":/Files/arena_0" + QString::number(rnd) + ".png";

    //    cv::Mat tst;
    //    tst = cv::imread()
    //    QString address = ":/Files/arena_08.png";
    wm.arenaImg = QPixmap(address);
    //    imshow("test", wm.arenaImg)
}


void MainWindow::on_drawBoundary_CheckBox_stateChanged(int arg1)
{
    wm.drawBoundary = ui->drawBoundary_CheckBox->isChecked();
}


void MainWindow::on_drawHeatMap_CheckBox_clicked()
{
    wm.drawHeatMap = ui->drawHeatMap_CheckBox->isChecked();
}


void MainWindow::on_drawColCircles_CheckBox_clicked(bool checked)
{
    wm.drawColCircles = checked;
}

void MainWindow::on_seaBlue_pushButton_clicked()
{
    QColor temp;
    temp.setHsv(183, 233, 149);
    ui->H_slider->setValue(temp.hue());
    ui->S_slider->setValue(temp.saturation());
    ui->V_slider->setValue(temp.value());
    updateSliders();
    updateColors();
}

void MainWindow::on_drawRobCircles_CheckBox_clicked(bool checked)
{
    wm.drawRobCircles = checked;
}


void MainWindow::on_ohc_set_prog_clicked()
{
    qDebug() << "loading .hex file to program Kilobots!";
}


void MainWindow::on_writeLog_button_clicked(bool checked)
{
    if(checked)
    {
        QString dateStrng = QDateTime::currentDateTime().toString("yyyy_MM_dd__hh_mm");
        QString textFileStrng = ui->filePath_user->text() + dateStrng + "_log.txt" ;
        log_file.setFileName(textFileStrng);
        if ( !log_file.open(QIODevice::WriteOnly) ) { // open file
            qDebug() << "ERROR(!) in opening file" << textFileStrng;
        } else {
            qDebug () << "Log file" << log_file.fileName() << "opened.";
            log_stream.setDevice(&log_file);
        }

        log_stream << "---- Kilobot Experiment: at SCIoI, Project 27. @Mohsen Raoufi ----" << endl;
        log_stream << "Date:\t" << dateStrng << endl;
        log_stream << "Markers:\t"  << wm.marker0_pos.x() << "\t" <<  wm.marker0_pos.y() << "\t"
                   << wm.marker1_pos.x() << "\t" <<  wm.marker1_pos.y() << "\t"
                   << wm.marker2_pos.x() << "\t" <<  wm.marker2_pos.y() << "\t"
                   << wm.marker3_pos.x() << "\t" <<  wm.marker3_pos.y() << endl;
        log_stream << "Arena Size:\t"  << wm.marker3_pos.x() - wm.marker0_pos.x() << "\t" <<  wm.marker3_pos.y() - wm.marker0_pos.y() << endl;
        log_stream << "Marker width:\t" << wm.marker_length << endl;
        log_stream << "CapSize:\t"  << capSize.width << "\t" << capSize.height << endl;
        log_stream << "FrameSize:\t"  << capSize.width << "\t" << capSize.height << endl;

        if(ui->logType_comboBox->currentIndex()==0)
        {
            connect(&this->kbtracker, SIGNAL(kiloList(QVector<Kilobot*>)), this, SLOT(logToFile(QVector<Kilobot*>))); // version 1: pos, vel, LED
            qDebug() << "Writing Pos, Vel, LED into the log file, in captured coordination system.";
            log_stream << "**** Writing Pos, Vel, LED ****" << endl;
        }
        else if(ui->logType_comboBox->currentIndex()==1)
        {
            connect(this, SIGNAL(kilobotPosVecReady(QVector<QPoint>)), this, SLOT(logToFile(QVector<QPoint>))); // version 2: pos
            qDebug() << "Writing Pos into the log file, in (mapped to) Arena coordination system.";
            log_stream << "**** Writing just the Pos in (mapped to) Arena coordination system ****" << endl;
        }
        else if(ui->logType_comboBox->currentIndex()==2)
        {
            connect(&this->kbtracker, SIGNAL(kiloList(QVector<Kilobot*>)), this, SLOT(logToFile_PosLED(QVector<Kilobot*>))); // version 3: pos + LED
            qDebug() << "Writing Pos + LED into the log file, in captured coordination system.";
            log_stream << "**** Writing Pos + LED in captured coordination system ****" << endl;
        }

    }
    else
    {
        disconnect(&this->kbtracker, SIGNAL(kiloList(QVector<Kilobot*>)), this, SLOT(logToFile(QVector<Kilobot*>))); // version 1: pos, vel, LED
        disconnect(this, SIGNAL(kilobotPosVecReady(QVector<QPoint>)), this, SLOT(logToFile(QVector<QPoint>))); // version 2: pos
        disconnect(&this->kbtracker, SIGNAL(kiloList(QVector<Kilobot*>)), this, SLOT(logToFile_PosLED(QVector<Kilobot*>))); // version 3: pos + LED

        if (log_file.isOpen()){
            qDebug() << "Closing file" << log_file.fileName();
            log_file.close();
        }
    }


}

void MainWindow::on_env1_rButton_clicked(bool checked)
{
    // Markers Pos in Projected Space: set 1
    wm.arenaWidth = 500;
    wm.marker0_pos = QPoint(1190, 330);
    this->update_wmMarkers();
    //    wm.marker1_pos = QPoint(wm.marker0_pos.x(), wm.marker0_pos.y() + wm.arenaWidth);
    //    wm.marker2_pos = QPoint(wm.marker0_pos.x() + wm.arenaWidth, wm.marker0_pos.y());
    //    wm.marker3_pos = QPoint(wm.marker0_pos.x() + wm.arenaWidth, wm.marker0_pos.y() + wm.arenaWidth);


    ui->cropTL_xTextEdit->setText(QString::number(377));
    ui->cropTL_yTextEdit->setText(QString::number(146));

    ui->cropsz_wTextEdit->setText(QString::number(239));
    ui->cropsz_hTextEdit->setText(QString::number(237));
}

void MainWindow::on_env2_rButton_clicked(bool checked)
{
    // Markers Pos in Projected Space: set 2
    wm.arenaWidth = 700;
    wm.marker0_pos = QPoint(1000, 300);
    this->update_wmMarkers();

    ui->cropTL_xTextEdit->setText(QString::number(300));
    ui->cropTL_yTextEdit->setText(QString::number(133));

    ui->cropsz_wTextEdit->setText(QString::number(320));
    ui->cropsz_hTextEdit->setText(QString::number(320));
}

void MainWindow::on_env3_rButton_clicked()
{
    wm.arenaWidth = 550;
    wm.marker0_pos = QPoint(1100+50, 300);
    this->update_wmMarkers();

    ui->cropTL_xTextEdit->setText(QString::number(360));
    ui->cropTL_yTextEdit->setText(QString::number(133));

    ui->cropsz_wTextEdit->setText(QString::number(255));
    ui->cropsz_hTextEdit->setText(QString::number(255));
}

void MainWindow::on_env4_rButton_clicked()
{
    // Markers Pos in Projected Space: set 4: for Thymios
    // Largest arena for THYMIO
    wm.arenaWidth = 1350;
    wm.arenaHeight = 700;
    wm.marker0_pos = QPoint(340, 300);
    wm.marker1_pos = QPoint(wm.marker0_pos.x(), wm.marker0_pos.y() + wm.arenaHeight);
    wm.marker2_pos = QPoint(wm.marker0_pos.x() + wm.arenaWidth, wm.marker0_pos.y());
    wm.marker3_pos = QPoint(wm.marker0_pos.x() + wm.arenaWidth, wm.marker0_pos.y() + wm.arenaHeight);

    wm.marker0_BR = QPoint(wm.marker0_pos + QPoint(wm.marker_length, wm.marker_length));
    wm.expFieldRect = QRect(wm.marker0_BR, wm.marker3_pos);

    ui->cropTL_xTextEdit->setText(QString::number(29));
    ui->cropTL_yTextEdit->setText(QString::number(151));

    ui->cropsz_wTextEdit->setText(QString::number(558));
    ui->cropsz_hTextEdit->setText(QString::number(305));
}

void MainWindow::on_openImageField_pushButton_clicked()
{
    QString fileAddress = QFileDialog::getOpenFileName(this,tr("Select Arena Image"), "/home/p27/kilobot_project/VRK/New_VRK_GUI/Files/", tr("All Files (*.*)"));
    ui->arenaImage_TextEdit->setText(fileAddress.mid(fileAddress.lastIndexOf("/") + 1));
    wm.arenaImg = QPixmap(fileAddress);
}

void MainWindow::on_gradientExpField_pushButton_clicked()
{
    this->arenaWindow->_renderArea->updateGradientPainter();
}

void MainWindow::on_noiseTiles_slider_valueChanged(int value)
{
    wm.noiseTileNo = value;
}

void MainWindow::on_noiseFreq_slider_valueChanged(int value)
{
    wm.noiseTimeIntv = value;
    envBrain->updateNoiseProps(value);
}

void MainWindow::on_noiseStrength_slider_valueChanged(int value)
{
    wm.noiseStrength = (double) value/100.0;
}

void MainWindow::on_draw_network_stateChanged(int arg1)
{
    wm.drawNetwork = ui->draw_network->isChecked();
}

void MainWindow::on_sliderRandom0_valueChanged(int value)
{
    wm.dummy_var = value;
//    kbtracker.setKbBigMin(int(value/10));
    qDebug() << "Dummy Var 0 changed: " << value;
    qDebug() << "Nothing is assigned!!";
}

void MainWindow::on_noise_radioButton_clicked(bool checked)
{
    envBrain->connect_disconnect_add_noise(checked);
    if(checked)
        wm.noiseTimeIntv = ui->noiseFreq_slider->value();
    else
        wm.noiseTimeIntv = -1;
}



void MainWindow::on_draw_centroid_stateChanged(int arg1)
{
    wm.drawCentroid = ui->draw_centroid->isChecked();
}


void MainWindow::on_draw_voronoii_stateChanged(int arg1)
{
    wm.drawVoronoii = ui->draw_voronoii->isChecked();
}


void MainWindow::on_draw_bots_colors_stateChanged(int arg1)
{
    wm.drawWithColors = ui->draw_bots_colors->isChecked();
}


void MainWindow::on_sliderRandom1_valueChanged(int value)
{
    qDebug() << "Dummy Var 1 changed: " << value;
    wm.dummy_var2 = value;
//    qDebug() << "Nothing is assigned!!";
//    kbtracker.setKbBigMax(int(value/10));
}


void MainWindow::on_draw_spatial_netw_stateChanged(int arg1)
{
    wm.spatialNetwork = ui->draw_spatial_netw->isChecked();
}


void MainWindow::on_drawBall_stateChanged(int arg1)
{
    wm.drawBall = ui->drawBall->isChecked();
}

