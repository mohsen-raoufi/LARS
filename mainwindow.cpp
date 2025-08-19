#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <opencv2/aruco.hpp>

/**
 * @brief Main constructor for the MainWindow class.
 *
 * Initializes the GUI, sets up the camera environment, tracking modules, and the arena window.
 * Handles conditional compilation for different camera types, UI setup, and initial state definitions.
 * Assumes a multi-screen setup; positions main window on primary screen and maximizes it.
 */
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    // Move the main window to the top-left corner of the primary screen
    // Set main window on the specific screen
    this->move(QGuiApplication::screens().at(0)->geometry().topLeft()- this->rect().topLeft());
    this->showMaximized();
    // Set up all UI elements defined in the .ui file
    ui->setupUi(this);

    // Ensure the window is deleted properly on close to avoid memory leaks
    // close the application when the GUI is closed
    this->setAttribute(Qt::WA_DeleteOnClose);

    // Timer used for internal periodic tasks (e.g., camera refresh, GUI updates)
    // Initial Definitions
    timer = new QTimer();
    //    joyStick_Timer = new QTimer();
    test_eval_timer = new QTimer(); // for evaluation

    // Create a secondary window (arena view) to render the experiment scene
    arenaWindow = new ArenaWindow(nullptr, &wm, "LARS ARENA WINDOW");
    //    arenaWindow2 = new ArenaWindow(nullptr, &wm, "ARENA WINDOW 2"); // Secondary Window is optional!


    // Initialize environment processing logic (e.g., heatmaps, simulation states)
    // instantiating the envBrain to calculate the environment processes
    envBrain = new EnvBrain(&this->wm);

    // Apply the main window's palette settings to the central widget
    ui->centralWidget->setPalette(this->palette());

    // Initial Parameters & Variables

    // Initialize UI widgets, sliders, signal-slot connections, and setup logic
    // // Initialization of UI
    uiInitialization();

    // Output the camera backend type (for debug)
#ifdef USE_PYLON
    qDebug() << "Using Pylon Camera!";
#else
    qDebug() << "Using V4L2 Camera!";
#endif

    //    initializePlot(ui->customPlot); // If we want to plot something!

    // Save just from Cam!
    if(ui->fromVid_rButton->isChecked())
        ui->saveVid_button->setEnabled(false);

    // Get the GUI canvas size for later use in image scaling
    GUIQSize = ui->outputLabel->size();
    qDebug() << "GUI size: " << GUIQSize.width() << ", " << GUIQSize.height();

    FPS = ui->FPS_comboBox->currentText().toInt();
    rotIndex = ui->Rotate_ComboBox->currentIndex();

    /**
     * @brief Initialize the marker detection containers.
     *
     * Ensures that marker data is in a known default state to avoid crashes if detection fails.
     */
    detectedMarker temp;
    temp.BoundingRect = QRect(0,0,0,0);
    detectedMarkersList.clear();
    for (int i=0; i < 4; ++i){
        temp.id = i;
        detectedMarkersList.insert(i, temp);

        detectedMarkerCenterList.insert(i, QPoint(0,0));
    }

    // Default identity matrix for perspective transformation (Arena-to-Camera)
    // Just some initial values so that if no marker was detected the program does not crash
    mapA2C = cv::Mat::eye(3,3, 1);
    mapC2A = cv::Mat::eye(3,3, 1);

    // Clear and initialize the heatmap matrix with a black image
    this->resetHeatMap();
}


/**
 * @brief Destructor for MainWindow.
 *
 * Cleans up allocated resources including UI and camera handles.
 * Prevents memory leaks and ensures a clean shutdown.
 */
MainWindow::~MainWindow()
{
    qDebug() << "********* closing windows ... *********";

    // delete external calls
    //    delete python_call_process;

    // Delete the arena window (secondary visualization)
    arenaWindow->close();
    arenaWindow->hide();
    delete arenaWindow;
    qDebug() << "Arena Window is closed!";
    // Delete the UI components created with setupUi()
    delete ui;
}

/**
 * @brief Logs Kilobot (or other robots) positions and LED colors to the log file.
 *
 * This function is used when only position and LED color are needed per robot.
 * Each entry includes timestamp, robot index, position (x, y), and LED color.
 */
void MainWindow::logToFile_PosLED(QVector<Kilobot *> kiloVec)
{
    log_stream << elapsedTimer.elapsed();
    for (int i = 0; i < kiloVec.size(); ++i){
        log_stream << "\t" << i << "\t" << kiloVec[i]->getPosition().x() << "\t" << kiloVec[i]->getPosition().y() << "\t" << kiloVec[i]->getLedColour();
    }
    log_stream << endl;
}

void MainWindow::logToFile_FPS(QVector<QPoint> posVec)
{
    // remove the "FPS = " from the text and convert it to int
    int FPS_extracted = ui->error_label->text().remove("FPS = ").toInt();
    log_stream << FPS_extracted << "\t" << elapsedTimer.elapsed();

    for (int i = 0; i < posVec.size(); ++i){
        log_stream << "\t" << i << "\t" << posVec[i].x() << "\t" << posVec[i].y() ;
    }

    // add the noise strength at the end of the line
//        log_stream << "\t" << ui->noiseStrenght_label->text().toInt();
//        log_stream << "\t" << ui->noiseTiles_slider->value();


//    log_stream << "\t" << ui->genExp_TextEdit->text().toInt();

    // add the brightness of the enviornment at the end of the line
//    log_stream << "\t" << ui->V_label->text().toInt();


    // //// latency test
    log_stream << "\t" << wm.ballPos.x() << "\t" << wm.ballPos.y() << "\t" << ui->sliderRandom1->value() << "\t" << ui->robRendRad_slider->value();
    // add the value of the sliderRandom1 as the robot speed


    log_stream << endl;
}

/**
 * @brief Logs Kilobot (or other robots) positions, LED colors, and velocities to the log file.
 *
 * Useful for full behavioral logging. Each entry includes timestamp, robot index,
 * position (x, y), LED color, and velocity vector (vx, vy).
 */
void MainWindow::logToFile(QVector<Kilobot *> kiloVec)
{
    log_stream << elapsedTimer.elapsed();
    for (int i = 0; i < kiloVec.size(); ++i){
        log_stream << "\t" << i << "\t" << kiloVec[i]->getPosition().x() << "\t" << kiloVec[i]->getPosition().y() << "\t" << kiloVec[i]->getLedColour()
                   << "\t" << kiloVec[i]->getVelocity().x() << "\t" << kiloVec[i]->getVelocity().y() ;
    }
    log_stream << endl;
}

/**
 * @brief Logs raw position data (without robot metadata) to the log file.
 *
 * Used for simpler tracking or external agents not using full Kilobot objects.
 * Each entry includes timestamp, index, and position (x, y).
 */
void MainWindow::logToFile(QVector<QPoint> posVec)
{
    log_stream << elapsedTimer.elapsed();
    for (int i = 0; i < posVec.size(); ++i){
        log_stream << "\t" << i << "\t" << posVec[i].x() << "\t" << posVec[i].y() ;
    }
    log_stream << endl;
}

/**
 * @brief Slot triggered when the capturing button is clicked.
 *
 * Starts or stops camera or video capture based on UI state. Initializes the
 * capture source (camera or video), configures size parameters, and resets the heatmap.
 * Also updates the UI text and button label accordingly.
 */
void MainWindow::on_capturing_button_clicked()
{
    ui->outputLabel->setStyleSheet("");
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

/**
 * @brief Converts an integer (0–15) to its hexadecimal string representation.
 *
 * Used for displaying or logging compact hex values from numeric inputs.
 * Modifies the output string passed by reference.
 */
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

/**
 * @brief Displays the input image on the GUI and emits image signals.
 *
 * Converts the input OpenCV frame to RGB, calls drawKilobots to render annotations,
 * then displays the result in the GUI label. Emits signals before and after processing.
 */
void MainWindow::showImage(cv::Mat frame)
{
    frame.copyTo(currentFrame); // MOHSEN: check if I am using "current frame somewhere else"
    emit imageRawReceived(frame);

    if(!frame.empty())
    {
        cvtColor(frame,frame,cv::COLOR_BGR2RGB);

        // TO DO: Process the image and add whatever you want, graphical stuff on the QImage....
        drawKilobots(frame);

        QImage QIm((uchar*)frame.data, frame.cols, frame.rows, frame.step, QImage::Format_RGB888);
        QImage QImScaled = QIm.scaledToWidth(ui->outputLabel->width());


        ui->outputLabel->setPixmap(QPixmap::fromImage(QImScaled));

        cvtColor(frame,frame,cv::COLOR_RGB2BGR);
        emit imageProcReady(frame);

        //        ui->graphicsView->scene()->addPixmap(QPixmap::fromImage(QIm.scaledToWidth(ui->outputLabel->width())));
    }
}


/**
 * @brief Writes user settings (e.g., window size, hue value) to disk.
 *
 * Saves GUI state to persistent storage under "SCIoI" application group.
 * Currently includes window size and slider value.
 */
void MainWindow::writeSettings()
{
    // THESE ARE TO DOs!
    QSettings settings("SCIoI", "P27 VRK ver1.1");

    settings.beginGroup("MainWindow");
    settings.setValue("size", size());
    settings.setValue("hue", ui->V_slider->value());
    settings.endGroup();
}

/**
 * @brief Reads saved user settings from disk.
 *
 * Loads GUI state from previous session. Only the hue value is currently used.
 * Resize and slider re-trigger are present as commented-out TODOs.
 */
void MainWindow::readSettings()
{
    QSettings settings("SCIoI", "P27 VRK ver1.1");

    settings.beginGroup("MainWindow");
    //    resize(settings.value("size"));
    qDebug() << settings.value("hue").toInt();
    //    on_V_slider_actionTriggered(settings.value("hue"));
    settings.endGroup();
}

/**
 * @brief Utility function to display debug messages in the GUI text output.
 *
 * Allows internal status or error messages to be shown to the user via the interface.
 */
void MainWindow::myDebug(QString string)
{
    ui->textOut->setText(string);
}

/**
 * @brief Processes received robot data and updates internal state.
 *
 * Accepts a list of Kilobots (or other robot instances), maps their positions into arena coordinates,
 * and updates internal world model data (positions, traces, and which robots should be enlightened).
 * Emits kilobot position vector for downstream modules.
 */
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

/**
 * @brief Receives a list of drawn circles to overlay on the video frame.
 *
 * Used to annotate the GUI with circular visual indicators (e.g., targets, zones).
 */
void MainWindow::getDrawnCircles(QVector<drawnCircle> circsToDraw)
{
    this->circlsToDraw.clear();
    this->circlsToDraw = circsToDraw;
}

/**
 * @brief Draws graphical overlays (like circles and optional labels) on top of a frame.
 *
 * Handles both transparent and opaque overlays based on `drawnCircle` data.
 * Supports future extensions for drawn lines (currently commented out).
 */
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

/**
 * @brief Renders Kilobots (or other robots) on the video frame.
 *
 * Displays robot positions as colored circles, optionally with velocity vectors and IDs.
 * Heatmap and color options depend on GUI checkboxes. This function integrates robot state,
 * visual encoding, and conditional overlays.
 */
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
            else{ // if not showing the color based on the LED
                rgbColor = Scalar(255,255,255); // white
                rgbColor = Scalar(255, 174, 0); // orange
            }

            wm.kiloColor.append(rgbColor);

            if(ui->draw_bots->isChecked())
                cv::circle(frame,Point(kiloVector[i]->getPosition().x(),kiloVector[i]->getPosition().y()),kbtracker.kbMaxSize,rgbColor,2);

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
                int offset = kbtracker.kbMaxSize + 5;
                putText(frame, QString::number(this->kiloVector[i]->getID()).toStdString(), Point(kiloVector[i]->getPosition().x(),kiloVector[i]->getPosition().y()-offset), FONT_HERSHEY_SIMPLEX, 0.6, rgbColor, 2);
            }
        }

    }
}

/**
 * @brief Draws and updates a heatmap based on robot positions.
 *
 * For each Kilobot (or robot), draws a colored circle on a heatmap layer using the robot's LED color.
 * This overlay is then blended with the GUI video feed to visualize collective activity over time.
 */
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

/**
 * @brief Detects and maps marker positions between camera and arena coordinates.
 *
 * Uses bounding rectangles and centers of four detected markers to compute perspective transforms
 * (camera-to-arena and arena-to-camera). Updates the experimental field boundaries accordingly.
 */
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

/**
 * @brief Opens the calibration window for Kilobots.
 */
void MainWindow::calibrateKilobot()
{
    calib->show();

}

/**
 * @brief Slot triggered when 'From Video' radio button is selected.
 *
 * Currently only used for toggling UI elements (partially implemented).
 */
void MainWindow::on_fromVid_rButton_clicked()
{
    //    ui->save_set_button->setEnabled(false);
}

/**
 * @brief Slot triggered when 'From Camera' radio button is selected.
 *
 * Currently only used for toggling UI elements (partially implemented).
 */
void MainWindow::on_fromCam_rButton_clicked()
{
    //    ui->save_set_button->setEnabled(true);
}

/**
 * @brief Rotates the input image based on the specified flag.
 *
 * Flags:
 * 0 = 90° clockwise
 * 1 = 180°
 * 2 = 90° counterclockwise
 */
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

/**
 * @brief Handles mouse release events used for defining a cropping region.
 *
 * If the mouse position is valid, captures the rubber band (selection box) position
 * and updates UI elements and internal cropping rectangle accordingly.
 */
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

/**
 * @brief Handles mouse press events to start drawing a selection box.
 *
 * If the press occurs within a valid area, initializes a rubber band rectangle at the cursor position.
 */
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

/**
 * @brief Handles mouse movement while drawing a selection box.
 *
 * Updates the geometry of the rubber band rectangle or hides it if the area is invalid.
 */
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

/**
 * @brief Checks whether the given (x,y) position is within the allowed area for selection.
 *
 * Selection is limited to the region inside the output display label, accounting for mouse bias.
 */
bool MainWindow::isValidPlaceForSelect(int x, int y)
{
    bool isValid = false ;
    isValid = ui->outputLabel->rect().contains(x-mouseBias.x(),y-mouseBias.y());
    qDebug() << "isvalid: " << isValid;
    return isValid;
}

/**
 * @brief Opens a file dialog for selecting a settings file.
 *
 * The chosen file path is displayed in the user interface for further use.
 */
void MainWindow::on_open_set_button_clicked()
{
    // TO DO: the whole open/read/write/save Setting ...
    QString fileAddress = QFileDialog::getOpenFileName(this,tr("Select Setting File"), "/home/p27/Kilobot_Materials/savedData/", tr("All Files (*.*)"));
    ui->filePath_user->setText(fileAddress);
}

/**
 * @brief Updates the rotation index based on user selection.
 *
 * Also updates a text output label to show the selected index.
 */
void MainWindow::on_Rotate_ComboBox_activated(const QString &arg1)
{
    rotIndex = ui->Rotate_ComboBox->currentIndex();
    QString str = QString::number(rotIndex);
    ui->textOut->setText(str);
}

/**
 * @brief Starts or stops saving of raw and processed video streams.
 *
 * If the button is checked, initializes video writers and starts saving based on the current settings.
 * Otherwise, stops and releases video writer threads and related connections.
 */
void MainWindow::on_saveVid_button_clicked()
{
    bool saveProcVidBool = false; // true;//

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

/**
 * @brief Initialize UI elements and connect signals and slots.
 *
 * Sets initial UI states, configures sliders and buttons, connects UI elements to their
 * respective handlers using Qt's signal/slot mechanism. Also initializes logging paths
 * and camera source selection.
 */
void MainWindow::uiInitialization()
{
    // === UI ELEMENT SETUP AND INITIALIZATION ===
    // Set initial appearance and interactivity for the file path text box.
    /// initialize openPath
    QString styleSheetStr = "background-color: rgb(255, 255, 255); color: rgb(0, 0, 0);";
    ui->filePath_user->setStyleSheet(styleSheetStr);
    ui->filePath_user->setDisabled(false);

    // Set initial background color based on current HSV slider values.
    bg_color.setHsv(ui->H_slider->value(), ui->S_slider->value(), ui->V_slider->value());

    // Get list of available screens and use the last one to position arena window.
    screensList = QGuiApplication::screens();

    // === OPEN ARENA SETUP ===
    // Position and show the arena window on an external screen.
    int screenIndex = screensList.size() - 1;
    arenaWindow->move(screensList.at(screenIndex)->geometry().topRight() - arenaWindow->frameGeometry().topRight());
    //    arenaWindow2->move(QGuiApplication::screens().at(0)->geometry().topRight() - arenaWindow->frameGeometry().topRight());

    ui->ArenaWindow_button->setText("Close Arena");
    ui->ArenaWindow_button->setChecked(true);
    // Trigger default fullscreen and fitting options for the arena display.
    on_fullScreen_pushButton_clicked();
    on_fitRect_pushButton_clicked();
    arenaWindow->show();

    // Initializing Slider Values by default Values

    DebugAv = ui->debugAV_CheckBox->isChecked();
    boolDebug = ui->debug_CheckBox->isChecked();

    // Setup for mouse selection tool (rubber band) for cropping or selection.
    rubberBand = new QRubberBand(QRubberBand::Rectangle, this->ui->outputLabel);
    mouseBias = QPoint(ui->outputLabel->x(), ui->outputLabel->y()) + QPoint(ui->frame->x(), ui->frame->y());

    // === ROBOT TRACKER INITIALIZATION ===
    // Load default tracking parameters into sliders for user interface.
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

    // Apply these values to ensure slider values are reflected in the UI correctly.
    // updating sliders on the GUI
    updateSliders();

    // === SIGNAL-SLOT CONNECTIONS ===
    // Connections from tracker to GUI for displaying images and messages.
    connect(&this->kbtracker, SIGNAL(capturedImage(cv::Mat)), this, SLOT(showImage(cv::Mat)));
    connect(&this->kbtracker, SIGNAL(errorMessage(QString)), ui->error_label, SLOT(setText(QString)));
    //    connect(ui->refresh, SIGNAL(clicked(bool)), &this->kbtracker,SLOT(RefreshDisplayedImage()));

    connect(&this->kbtracker, SIGNAL(kiloList(QVector<Kilobot*>)), this, SLOT(getKilos(QVector<Kilobot*>)));
    //    connect(&this->kbtracker, SIGNAL(circlesToDrawSig(QVector<drawnCircle>)), this, SLOT(getDrawnCircles(QVector<drawnCircle>)));

    // --- To ENVIRONMENT MODULE ---
    //    connect(this, SIGNAL(kilobotPosVecReady(QVector<QPoint>)), this->envBrain, SLOT(updateTraces(QVector<QPoint>))); // we use a timer inside envBrain to update the traces, instead of a signal
    connect(ui->resetHMap_pushButton, SIGNAL(clicked(bool)), this->envBrain, SLOT(resetHeatMap()));
    connect(ui->resetHMap_pushButton, SIGNAL(clicked(bool)), this, SLOT(resetHeatMap()));

    // --- To OVERHEAD CONTROLLER MODULE ---
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

    // Signals emitted from OverheadController to update GUI elements.
    connect(&this->ohc,SIGNAL(setStopButton(bool)),ui->ohc_stop,SLOT(setChecked(bool)));
    connect(&this->ohc,SIGNAL(errorMessage(QString)), ui->error_label, SLOT(setText(QString)));

    // --- TRACKER PARAMETER SLIDERS ---
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

    // --- COLOR PICKING BUTTONS ---
    // Connect color buttons in GUI
    connect(ui->black_pushButton, &QPushButton::clicked, [this]() { QString txt = ui->black_pushButton->text(); qDebug() << "clicked : " << txt; updateColors(txt); clicked(txt); });
    connect(ui->blue_pushButton, &QPushButton::clicked, [this]() { QString txt = ui->blue_pushButton->text(); qDebug() << "clicked : " << txt; updateColors(txt); clicked(txt); });
    connect(ui->red_pushButton, &QPushButton::clicked, [this]() { QString txt = ui->red_pushButton->text(); qDebug() << "clicked : " << txt; updateColors(txt); clicked(txt); });
    connect(ui->green_pushButton, &QPushButton::clicked, [this]() { QString txt = ui->green_pushButton->text(); qDebug() << "clicked : " << txt; updateColors(txt); clicked(txt); });
    connect(ui->white_pushButton, &QPushButton::clicked, [this]() { QString txt = ui->white_pushButton->text(); qDebug() << "clicked : " << txt; updateColors(txt); clicked(txt); });

    // --- EXPERIMENT FIELD TYPE SELECTION ---
    connect(ui->gradientExpField_pushButton, &QPushButton::clicked, [this]() { wm.expFieldType = GRADIENT;});
    connect(ui->imageExpField_pushButton, &QPushButton::clicked, [this]() { wm.expFieldType = IMAGE;});
    connect(ui->videoExpField_pushButton, &QPushButton::clicked, [this]() { wm.expFieldType = BR_VIDEO;});
    connect(ui->nullExpField_pushButton, &QPushButton::clicked, [this]() { wm.expFieldType = NULL_BRUSH;});

    // --- ROBOT BRUSH TYPE SELECTION ---
    connect(ui->gradientRob_pushButton, &QPushButton::clicked, [this]() { wm.robBrushType = GRADIENT;});
    connect(ui->solidRob_pushButton, &QPushButton::clicked, [this]() { wm.robBrushType = SOLID;});
    connect(ui->nullRob_pushButton, &QPushButton::clicked, [this]() { wm.robBrushType = NULL_BRUSH;});

    // --- ARENA RENDER COLOR SLIDERS ---
    // Render Arena
    connect(ui->H_slider, SIGNAL(valueChanged(int)), this, SLOT(updateColors()));
    connect(ui->V_slider, SIGNAL(valueChanged(int)), this, SLOT(updateColors()));
    connect(ui->S_slider, SIGNAL(valueChanged(int)), this, SLOT(updateColors()));
    connect(ui->A_slider, SIGNAL(valueChanged(int)), this, SLOT(updateColors()));

    // --- MANUAL CALIBRATION CONNECTIONS ---
    // Create and connect calibration window for manual robot tuning.
    calib = new CalibWindow("Calibration Values", this);
    connect(calib, SIGNAL(calibUID(int)), this, SLOT(calibUID(int)));
    connect(calib, SIGNAL(calibLeft(int)), this, SLOT(calibLeft(int)));
    connect(calib, SIGNAL(calibRight(int)), this, SLOT(calibRight(int)));
    connect(calib, SIGNAL(calibStraight(int)), this, SLOT(calibStraight(int)));
    connect(calib, SIGNAL(calibStop()), this, SLOT(calibStop()));
    connect(calib, SIGNAL(calibSave()), this, SLOT(calibSave()));

    connect(ui->black_pushButton, SIGNAL(objectNameChanged(QString)), this, SLOT(updateColors(QString)));

    // Trigger one-time color update at startup using current button states.
    updateColors();

    // Set the world model field size based on screen geometry (adapted for platform).
    wm.setFieldSize(QGuiApplication::screens().at(screenIndex)->geometry().size());
    qDebug() << "Field Size set to: " << wm.fieldSize.width() << ", " << wm.fieldSize.height();

#ifdef FOR_KILOBOT
    // shrink the field size so that the margins of the demonstratore are in the shade
    wm.setFieldSize(wm.fieldSize-QSize(825,0));
#else
    // shrink the field size so that the wood margins are in the shade
    wm.setFieldSize(wm.fieldSize-QSize(290,190));
#endif

    // === WORLD MODEL INITIALIZATION ===
    // Load default arena image and apply initial render settings.
    // setting initial values of some parameters in the WM
    //    wm.arenaImg = QPixmap(":/Files/arena_01.png");
    wm.arenaImg = QPixmap(":/Files/empty_image.png");

    wm.drawNetwork = ui->draw_network->isChecked();
    wm.spatialNetwork = ui->draw_spatial_netw->isChecked();
    wm.dummy_var = ui->sliderRandom0->value();

    procQSize = ui->outputLabel->size(); // for saving the processed video, this would
    procSize = cv::Size(procQSize.width(), procQSize.height());

    ui->filePath_user->setText("/home/p27/LARS/LARS/etc/validation/media/eval_test_latency_LARS_LOG_");

    // Start main timer for tracking experiment runtime.s
    elapsedTimer.start();
}


/**
 * @brief Plots a new data point on the QCustomPlot.
 *
 * Updates the plot's x-axis range based on elapsed time and triggers a replot.
 * @param customPlot Pointer to the QCustomPlot widget to update.
 * @param value The new data value to plot (not currently used in this implementation).
 */
void MainWindow::plotData(QCustomPlot *customPlot, double value)
{
    static QTime time(QTime::currentTime());
    double key = time.elapsed()/1000.0; // time elapsed since start of demo, by seconds
    //    customPlot->graph(0)->addData(key,tempVal);
    customPlot->xAxis->setRange(key, 3, Qt::AlignRight);
    customPlot->replot();
}

/**
 * @brief Initializes the QCustomPlot for error visualization.
 *
 * Sets up two graphs ("Err Prec" and "Err True") for precision and trueness errors,
 * configures time-based x-axis, y-axis range, legend, and visual customizations for each graph.
 * Also adjusts margins and inset layout for optimal display.
 *
 * @param customPlot Pointer to the QCustomPlot widget to initialize.
 */
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

    // Graph 0: Precision error
    customPlot->graph(0)->setName("Err Prec");
    customPlot->graph(0)->setPen(QColor(0, 0, 255, 255));
    customPlot->graph(0)->setLineStyle(QCPGraph::lsNone);
    customPlot->graph(0)->setScatterStyle(QCPScatterStyle(QCPScatterStyle::ssCircle, 4));

    // Graph 1: Trueness error
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

/**
 * @brief Resets the heatmap overlay to a blank state.
 *
 * Clears the heatmap by initializing it to a black (zeroed) matrix
 * matching the current capture size. Used to restart heatmap accumulation.
 */
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

/**
 * @brief Handles the "Debug" checkbox click event.
 *
 * Updates the DebugAv state according to the debugAV_CheckBox status.
 */
void MainWindow::on_debug_CheckBox_clicked()
{
    DebugAv = ui->debugAV_CheckBox->isChecked();
}

/**
 * @brief Handles keyboard input and triggers corresponding robot and UI actions.
 *
 * Supported keys and actions:
 * - W (87), presenter Left (16777238): Move kilobot(s) forward.
 * - A (65): Move kilobot(s) left.
 * - D (68), presenter Right (16777239): Move kilobot(s) right.
 * - S (83), B (66): Stop kilobot(s).
 * - V (86): Increase V slider.
 * - C (67): Decrease V slider.
 * - X (88): Stop sending messages.
 * - Z (90): Put kilobot(s) to sleep.
 * - N (78): Run kilobot(s).
 * - M (77): Reset kilobot(s).
 * - I (73): Press black button (UI).
 * - K (75): Toggle heatmap display (UI).
 * - R (82): Reset heatmap.
 * - L (76): Shuffle image experiment field.
 * - 2 (50): Move marker0 down.
 * - 8 (56): Move marker0 up.
 * - 4 (52): Move marker0 left.
 * - 6 (54): Move marker0 right.
 * - 3 (51): Cycle experiment field type.
 *
 * @param key The integer key code received from the keyboard event.
 */
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

/**
 * @brief Override Qt key press handler.
 *
 * Handles application-level keyboard shortcuts such as quitting the app with 'Esc'.
 */
void MainWindow::keyPressEvent(QKeyEvent *key)
{
    // If 'Esc' is pressed, close the main window
    SendKeyBoardData(key->key());
}


/**
 * @brief Handles Arena window open/close button click.
 *
 * Shows or hides the Arena window and updates the button label accordingly.
 * Moves the window to the selected screen when opening.
 */
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

/**
 * @brief Updates colors for field or robots based on current GUI slider values.
 *
 * Depending on the selected object type (background, robot custom, or pen), updates color in the world model.
 */
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

/**
 * @brief Updates color sliders and field/robot color from a color string.
 *
 * Converts a given color string (e.g., from a button) to HSV slider values, then updates the world model colors.
 * @param colorString The color string (e.g., "#RRGGBB" or named color) to use.
 */
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

/**
 * @brief Sets sliders to a predefined red color and updates the interface.
 *
 * Applies a preset HSV value for red, updates sliders, and triggers color update.
 */
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

/**
 * @brief Sets sliders to a predefined blue color and updates the interface.
 *
 * Applies a preset HSV value for blue, updates sliders, and triggers color update.
 */
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

/**
 * @brief Toggles the Arena window fullscreen mode.
 *
 * Puts the Arena window into fullscreen and brings the main window to front.
 */
void MainWindow::on_fullScreen_pushButton_clicked()
{
    arenaWindow->toggleFullScreen(true);
    this->raise();
    //    arenaWindow->isFullScreen() ? arenaWindow->showNormal() : arenaWindow->showFullScreen();
}

/**
 * @brief Handles the 'Fit Rect' button click event.
 *
 * Disables the button to prevent repeated clicks. Intended to fit the scene rectangle in the arena window
 * (currently commented out).
 */
void MainWindow::on_fitRect_pushButton_clicked()
{
    ui->fitRect_pushButton->setEnabled(false);
    //    arenaWindow->fitSceneRect();
}

/**
 * @brief Handles the 'From Image' button click event.
 *
 * Disables the button to prevent repeated clicks. Intended for toggling loading/cleaning
 * of a background image in the arena window (logic currently commented out).
 */
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

/**
 * @brief Updates all slider labels with current slider values.
 *
 * Synchronizes displayed numeric values for HSV sliders, kilobot tracker sliders, and LED detection sliders.
 */
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

/**
 * @brief Handles the 'Save Setting' button click event.
 *
 * Triggers saving of GUI and user settings.
 */
void MainWindow::on_saveSetting_pushButton_clicked()
{
    writeSettings();
}

/**
 * @brief Handles the 'Load Setting' button click event.
 *
 * Loads GUI and user settings from disk.
 */
void MainWindow::on_loadSetting_pushButton_clicked()
{
    readSettings();
}

/**
 * @brief Handles the 'Start Tracking' button click event.
 *
 * Starts or stops the tracking loop and updates button/text states accordingly.
 */
void MainWindow::on_startTracking_pushButton_clicked()
{
    //    ui->startTracking_pushButton->isChecked() ? ui->startTracking_pushButton->setText("Stop Tracking") : ui->startTracking_pushButton->setText("Start Tracking");
    update_startTracking_pushBotton();

    this->kbtracker.LOOPstartstop(1);//1); // change this later ... // 3 : USER Experiment It's better to use (1) as input :)

    ui->startTracking_pushButton->isChecked() ? ui->crop_pushButton->setEnabled(false) : ui->crop_pushButton->setEnabled(true);
}

/**
 * @brief Updates the 'Start Tracking' button label.
 *
 * Changes the button text based on its checked state.
 */
void MainWindow::update_startTracking_pushBotton()
{
    ui->startTracking_pushButton->isChecked() ? ui->startTracking_pushButton->setText("Stop Tracking") : ui->startTracking_pushButton->setText("Start Tracking");
}

/**
 * @brief Handles the 'Detect Kilobots' button click event.
 *
 * Initiates kilobot detection, updates the combo box for selection, and manages start tracking button states.
 */
void MainWindow::on_detectKilobots_pushButton_clicked()
{
    dummy_detection_ready = false;
    this->kbtracker.SETUPfindKilobots();

    qDebug() << "#" << kiloVector.size() << " Robots are detected!!";
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
                ui->TrigID_comboBox->setCurrentIndex(0); // set the triger ID to None if not needed: comment this out
//        ui->TrigID_comboBox->setCurrentIndex(1); // set the triger ID to ALL to see if you detected all the robots

    }

    if(ui->startTracking_pushButton->isCheckable())
    {
        ui->startTracking_pushButton->setChecked(false);
        update_startTracking_pushBotton();
    }
    else
        ui->startTracking_pushButton->setCheckable(true);

    qDebug() << "detection done!";

    dummy_detection_ready = true;

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

/**
 * @brief Handles the crop button click event to define or clear the cropping rectangle.
 *
 * When enabled, calculates crop rectangle coordinates based on UI fields or detected markers,
 * maps cropping region between GUI, fit, and capture coordinates, and updates internal state.
 * When disabled, resets cropping to the full capture region. Always triggers an update in the tracker and resets the heatmap.
 */
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

/**
 * @brief Handles the 'Detect Marker' button click event to find ArUco markers in the current video frame.
 *
 * Processes the current frame using OpenCV's ArUco detection tools. If markers are found, their positions and bounding rectangles are extracted and
 * stored in internal lists, and details are printed for debugging. Calls findMarkerRect() to update arena mapping based on detected marker locations.
 */
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

/**
 * @brief Handles the marker width slider movement.
 *
 * Updates the world model marker length parameter according to the slider position.
 * @param position New slider value for marker width.
 */
void MainWindow::on_markerWidth_Slider_sliderMoved(int position)
{
    wm.marker_length = position;
}

/**
 * @brief Maps a QPoint using provided scale and bias.
 *
 * Applies a linear transformation to point P: scale and then bias.
 * @param P Original point.
 * @param scale 2D scaling factors.
 * @param bias 2D bias/offset to add.
 * @return Transformed QPoint.
 */
QPoint MainWindow::mapPoint(QPoint P, QVector2D scale, QVector2D bias)
{
    QPoint P2;
    P2.setX(P.x()*scale.x() + bias.x());
    P2.setY(P.y()*scale.y() + bias.y());

    return P2;
}

/**
 * @brief Maps a QPoint using a 3x3 projective transformation matrix.
 *
 * Applies a homography (projective transform) to the input point.
 * @param P Original point.
 * @param lambda 3x3 transformation matrix (homography).
 * @return Transformed QPoint.
 */
QPoint MainWindow::mapPoint(QPoint P, Matx33f lambda)
{
    cv::Point3f homogeneous = lambda * Point2f(P.x(), P.y());
    homogeneous /= homogeneous.z;
    return QPoint(homogeneous.x, homogeneous.y);
}

/**
 * @brief Maps a QPoint using a 3x3 matrix and translation vector.
 *
 * Applies an affine or rigid transform (matrix and translation) to the point.
 * @param P Original point.
 * @param rvec 3x3 transformation matrix.
 * @param tvec Translation vector.
 * @return Transformed QPoint.
 */
QPoint MainWindow::mapPoint(QPoint P, Matx33f rvec, Point3f tvec)
{
    cv::Point3f homogeneous = rvec*Point2f(P.x(), P.y())  + tvec;
    return QPoint(homogeneous.x, homogeneous.y);
}


/**
 * @brief Handles state change for the tracker debug checkbox.
 *
 * Enables or disables debug drawing in the tracker.
 * @param arg1 State change value (unused).
 */
void MainWindow::on_debug_tracker_stateChanged(int arg1)
{
    this->kbtracker.drawDebugBool = ui->debug_tracker->isChecked();
}

/**
 * @brief Handles the max displacement slider movement.
 *
 * Updates the tracker maximum allowed displacement parameter for object tracking.
 * @param position New slider value.
 */
void MainWindow::on_maxDispl_slider_sliderMoved(int position)
{
    //#ifdef FOR_KILOBOT
    //    this->kbtracker.morfiTrack_maxDisplacement = (float) position/10.0;
    //#else
    this->kbtracker.morfiTrack_maxDisplacement = (float) position/2.0;
    //#endif
}

/**
 * @brief Handles the EFWL slider movement.
 *
 * Updates the EFWL (e.g., Exponential Forgetting Window Length) parameter in the tracker.
 * @param position New slider value.
 */
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

/**
 * @brief Handles the robot rendering radius slider movement.
 *
 * Updates the robot rendering radius in the world model for visualization.
 * @param position New slider value for robot radius.
 */
void MainWindow::on_robRendRad_slider_sliderMoved(int position)
{
    wm.robRad = position;
}

/**
 * @brief Handles the smoothness factor slider movement.
 *
 * Updates the tracker smoothing parameter for object trajectories.
 * @param position New slider value.
 */
void MainWindow::on_smoothnessFact_slider_sliderMoved(int position)
{
    this->kbtracker.smooth_fact = (float) position/100.0;
}

/**
 * @brief Handles toggling of the image-based experiment field.
 *
 * Loads a background image for the experiment field if enabled.
 * @param checked True if button is checked (enabled).
 */
void MainWindow::on_imageExpField_pushButton_clicked(bool checked)
{
    wm.loadImgBackground = checked;
    ////
    //    QString address = ":/Files/" + ui->arenaImage_TextEdit->text(); // uncomment for normal behavior
    //     qDebug() << "Image loaded from: " << address;
    //     wm.arenaImg = QPixmap(address);

    //// // FOR MANUAL EVALUATION ONLY
    //    ui->arenaImage_TextEdit->setText("robot_calib_pattern_kilobot.png");
    //    QString address = "/home/p27/LARS/LARS/etc/validation/media/" + ui->arenaImage_TextEdit->text(); // for evaluation

    //// // FOR Generating EVALUATION ONLY
    QString address = ui->arenaImage_TextEdit->text(); // for evaluation
    // load the image from the address using opencv
    cv::Mat img = cv::imread(address.toStdString(), cv::IMREAD_UNCHANGED);
    // convert the image to QPixmap
    if(img.empty())
    {
        qDebug() << "Image not found at: " << address;
        return;
    }
    // convert cv::Mat to QPixmap
    QImage image = QImage((const unsigned char*)img.data, img.cols, img.rows, img.step, QImage::Format_ARGB32);
    wm.arenaImg = QPixmap::fromImage(image);

}

/**
 * @brief Handles initialization of points to draw (e.g., grid, star).
 *
 * Generates and sets up points for drawing, according to the selected mode.
 * @param checked True if button is checked (enabled).
 */
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

/**
 * @brief Handles the reset trace button click event.
 *
 * Clears the robot traces stored in the world model.
 */
void MainWindow::on_resetTrace_pushButton_clicked()
{
    wm.rob_traces.clear();
}


/**
 * @brief Stops the calibration routine.
 *
 * Currently only contains commented-out code for sending wakeup messages. Intended for future use.
 */
void MainWindow::calibStop() {
    //    if (sending) {
    //        sendMessage(WAKEUP);
    //        sendMessage(WAKEUP);
    //    }
}

/**
 * @brief Updates the positions of arena markers and the experimental field rectangle.
 *
 * Computes positions of the 4 arena markers based on the current marker0 position and arena width.
 * Also updates bottom-right marker and experiment field rectangle.
 */
void MainWindow::update_wmMarkers()
{
    wm.marker1_pos = QPoint(wm.marker0_pos.x(), wm.marker0_pos.y() + wm.arenaWidth);
    wm.marker2_pos = QPoint(wm.marker0_pos.x() + wm.arenaWidth, wm.marker0_pos.y());
    wm.marker3_pos = QPoint(wm.marker0_pos.x() + wm.arenaWidth, wm.marker0_pos.y() + wm.arenaWidth);

    wm.marker0_BR = QPoint(wm.marker0_pos + QPoint(wm.marker_length, wm.marker_length));
    wm.expFieldRect = QRect(wm.marker0_BR, wm.marker3_pos);

    qDebug() << "marker 0. pos.x: " << wm.marker0_pos.x() << ", marker 0. pos.y: " << wm.marker0_pos.y();
}

/**
 * @brief Sends a save command to the overhead controller for calibration.
 *
 * Publishes a CALIB_SAVE message via the overhead controller.
 */
void MainWindow::calibSave() {
    static calibmsg_t msg;
    msg.mode = CALIB_SAVE;
    this->ohc.sendDataMessagePub((uint8_t *)&msg, CALIB);
    //    sendDataMessage((uint8_t*)&msg, CALIB);
}

/**
 * @brief Sends a UID (unique ID) command to the overhead controller for calibration.
 *
 * Publishes a CALIB_UID message with the given UID value.
 * @param x Unique ID for calibration.
 */
void MainWindow::calibUID(int x) {
    static calibmsg_t msg;
    msg.mode = CALIB_UID;
    msg.uid = x;
    this->ohc.sendDataMessagePub((uint8_t *)&msg, CALIB);
    //    sendDataMessage((uint8_t *)&msg, CALIB);
}

/**
 * @brief Sends a left turn calibration value to the overhead controller.
 *
 * Publishes a CALIB_TURN_LEFT message with the specified left turn value.
 * @param x Left turn calibration value.
 */
void MainWindow::calibLeft(int x) {
    static calibmsg_t msg;
    msg.mode = CALIB_TURN_LEFT;
    msg.turn_left = x;
    this->ohc.sendDataMessagePub((uint8_t *)&msg, CALIB);
    //    sendDataMessage((uint8_t *)&msg, CALIB);
}

/**
 * @brief Sends a right turn calibration value to the overhead controller.
 *
 * Publishes a CALIB_TURN_RIGHT message with the specified right turn value.
 * @param x Right turn calibration value.
 */
void MainWindow::calibRight(int x) {
    static calibmsg_t msg;
    msg.mode = CALIB_TURN_RIGHT;
    msg.turn_right = x;
    this->ohc.sendDataMessagePub((uint8_t *)&msg, CALIB);
    //    sendDataMessage((uint8_t *)&msg, CALIB);
}

/**
 * @brief Sends a straight movement calibration value to the overhead controller.
 *
 * Publishes a CALIB_STRAIGHT message with left and right calibration values packed in x.
 * @param x Straight calibration value (lower and upper bytes).
 */
void MainWindow::calibStraight(int x) {
    static calibmsg_t msg;
    msg.mode = CALIB_STRAIGHT;
    msg.straight_left = x&0xFF;
    msg.straight_right = (x>>8) & 0xFF;
    this->ohc.sendDataMessagePub((uint8_t *)&msg, CALIB);
    //    sendDataMessage((uint8_t *)&msg, CALIB);
}

/**
 * @brief Handles the state change event for the 'Draw Trace' checkbox.
 *
 * Updates the drawTrace flag in the world model according to the UI checkbox.
 * @param arg1 State value (unused).
 */
void MainWindow::on_drawTrace_CheckBox_stateChanged(int arg1)
{
    wm.drawTrace = this->ui->drawTrace_CheckBox->isChecked();
}

/**
 * @brief Randomizes and loads a background image for the experimental field.
 *
 * Selects a random arena image from a set of predefined files and loads it into the world model.
 */
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

/**
 * @brief Handles the state change event for the 'Draw Boundary' checkbox.
 *
 * Updates the drawBoundary flag in the world model according to the UI checkbox.
 * @param arg1 State value (unused).
 */
void MainWindow::on_drawBoundary_CheckBox_stateChanged(int arg1)
{
    wm.drawBoundary = ui->drawBoundary_CheckBox->isChecked();
}

/**
 * @brief Handles the 'Draw Heatmap' checkbox click event.
 *
 * Updates the drawHeatMap flag in the world model according to the UI checkbox.
 */
void MainWindow::on_drawHeatMap_CheckBox_clicked()
{
    wm.drawHeatMap = ui->drawHeatMap_CheckBox->isChecked();
}

/**
 * @brief Handles the 'Draw Colored Circles' checkbox click event.
 *
 * Updates the drawColCircles flag in the world model.
 * @param checked True if the checkbox is checked.
 */
void MainWindow::on_drawColCircles_CheckBox_clicked(bool checked)
{
    wm.drawColCircles = checked;
}

/**
 * @brief Handles the 'Sea Blue' color preset button click.
 *
 * Sets the HSV sliders to a predefined 'sea blue' value and updates colors in the interface.
 */
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

/**
 * @brief Handles the 'Draw Robot Circles' checkbox click event.
 *
 * Toggles drawing of robot circles in the visualization.
 * @param checked True if the checkbox is checked (enabled).
 */
void MainWindow::on_drawRobCircles_CheckBox_clicked(bool checked)
{
    wm.drawRobCircles = checked;
}


/**
 * @brief Handles the 'Set Program' button click for the overhead controller.
 *
 * Logs an action for loading a .hex file to program the Kilobots.
 */
void MainWindow::on_ohc_set_prog_clicked()
{
    qDebug() << "loading .hex file to program Kilobots!";
}


/**
 * @brief Handles the 'Write Log' button click event.
 *
 * Starts or stops logging experiment data to a file based on the checked state.
 * Sets up file streams and connects/disconnects relevant signals for different logging modes.
 * @param checked True if logging is enabled.
 */
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

//        log_stream << "Evaluation from experiment:\t" << ui->arenaImage_TextEdit->text() << endl;

//        log_stream << "Here we added the V value (brightness) of the environment at the end of the line" << endl;

//        log_stream << "Here we added the Number of Noise Tiles at the end of the line" << endl;

//        log_stream << "Here we added the Number of robots generated in the image at the end of the line" << endl;

//        log_stream << "Here we added the speed of robots generated in the animation at the end of the line" << endl;


        log_stream << "Evaluation from experiment Latency with QT Ball" << endl;
        log_stream << "Here we added the position of the ball as well as the speed of it" << endl;

        int comboIndex = ui->logType_comboBox->currentIndex();

        switch (comboIndex) {
        case 0:{
            connect(&this->kbtracker, SIGNAL(kiloList(QVector<Kilobot*>)), this, SLOT(logToFile(QVector<Kilobot*>))); // version 1: pos, vel, LED
            qDebug() << "Writing Pos, Vel, LED into the log file, in captured coordination system.";
            log_stream << "**** Writing Pos, Vel, LED ****" << endl;
            break;
        }
        case 1:{
            connect(this, SIGNAL(kilobotPosVecReady(QVector<QPoint>)), this, SLOT(logToFile(QVector<QPoint>))); // version 2: pos
            qDebug() << "Writing Pos into the log file, in (mapped to) Arena coordination system.";
            log_stream << "**** Writing just the Pos in (mapped to) Arena coordination system ****" << endl;
            break;
        }
        case 2:{
            connect(&this->kbtracker, SIGNAL(kiloList(QVector<Kilobot*>)), this, SLOT(logToFile_PosLED(QVector<Kilobot*>))); // version 3: pos + LED
            qDebug() << "Writing Pos + LED into the log file, in captured coordination system.";
            log_stream << "**** Writing Pos + LED in captured coordination system ****" << endl;
            break;
        }
        case 3:{
            connect(this, SIGNAL(kilobotPosVecReady(QVector<QPoint>)), this, SLOT(logToFile_FPS(QVector<QPoint>))); // version 2: pos
            qDebug() << "Writing Pos into the log file, in (mapped to) Arena coordination system.";
            log_stream << "**** Writing just FPS and the Pos in (mapped to) Arena coordination system ****" << endl;
            break;
        }
        default:
            break;
        }

    }
    else
    {
        disconnect(&this->kbtracker, SIGNAL(kiloList(QVector<Kilobot*>)), this, SLOT(logToFile(QVector<Kilobot*>))); // version 1: pos, vel, LED
        disconnect(this, SIGNAL(kilobotPosVecReady(QVector<QPoint>)), this, SLOT(logToFile(QVector<QPoint>))); // version 2: pos
        disconnect(&this->kbtracker, SIGNAL(kiloList(QVector<Kilobot*>)), this, SLOT(logToFile_PosLED(QVector<Kilobot*>))); // version 3: pos + LED
        disconnect(this, SIGNAL(kilobotPosVecReady(QVector<QPoint>)), this, SLOT(logToFile_FPS(QVector<QPoint>))); // version 2: pos

        if (log_file.isOpen()){
            qDebug() << "Closing file" << log_file.fileName();
            log_file.close();
        }
    }


}

/**
 * @brief Handles the "Environment 1" radio button click event.
 *
 * Sets predefined marker positions and cropping rectangle for environment 1.
 * @param checked True if the radio button is checked.
 */
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

/**
 * @brief Handles the "Environment 2" radio button click event.
 *
 * Sets predefined marker positions and cropping rectangle for environment 2.
 * @param checked True if the radio button is checked.
 */
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

/**
 * @brief Handles the "Environment 3" radio button click event.
 *
 * Sets predefined marker positions and cropping rectangle for environment 3.
 */
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

/**
 * @brief Handles the "Environment 4" radio button click event (Thymio arena).
 *
 * Sets marker positions and cropping rectangle for the largest Thymio arena.
 */
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

/**
 * @brief Opens a file dialog to select an arena image.
 *
 * Loads the selected arena image and updates the corresponding UI field.
 */
void MainWindow::on_openImageField_pushButton_clicked()
{
    //// Uncomment below for normal behavior
    //    QString fileAddress = QFileDialog::getOpenFileName(this,tr("Select Arena Image"), "/home/p27/kilobot_project/VRK/New_VRK_GUI/Files/", tr("All Files (*.*)"));
    //    ui->arenaImage_TextEdit->setText(fileAddress.mid(fileAddress.lastIndexOf("/") + 1));

    //// for evaluation only
    QString fileAddress = QFileDialog::getOpenFileName(this,tr("Select Arena Image"), "/home/p27/LARS/LARS/etc/validation/media/", tr("All Files (*.*)"));
    ui->arenaImage_TextEdit->setText(fileAddress.mid(fileAddress.lastIndexOf("/") + 1));
    wm.arenaImg = QPixmap(fileAddress);
}

/**
 * @brief Handles the "Gradient Experiment Field" button click event.
 *
 * Triggers an update of the gradient painter in the arena window.
 */
void MainWindow::on_gradientExpField_pushButton_clicked()
{
    this->arenaWindow->_renderArea->updateGradientPainter();
}

/**
 * @brief Handles the noise tiles slider value change event.
 *
 * Updates the number of noise tiles in the world model.
 * @param value New number of noise tiles.
 */
void MainWindow::on_noiseTiles_slider_valueChanged(int value)
{
    wm.noiseTileNo = value;
}

/**
 * @brief Handles the noise frequency slider value change event.
 *
 * Updates the noise time interval in the world model and environment brain.
 * @param value New noise frequency value.
 */
void MainWindow::on_noiseFreq_slider_valueChanged(int value)
{
    wm.noiseTimeIntv = value;
    envBrain->updateNoiseProps(value);
}

/**
 * @brief Handles the noise strength slider value change event.
 *
 * Updates the noise strength parameter in the world model.
 * @param value New noise strength value.
 */
void MainWindow::on_noiseStrength_slider_valueChanged(int value)
{
    wm.noiseStrength = (double) value/100.0;
}

/**
 * @brief Handles the "Draw Network" checkbox state change event.
 *
 * Updates the drawNetwork flag in the world model.
 * @param arg1 State value (unused).
 */
void MainWindow::on_draw_network_stateChanged(int arg1)
{
    wm.drawNetwork = ui->draw_network->isChecked();
}

/**
 * @brief Handles the value change for a dummy/random slider.
 *
 * Updates a dummy variable in the world model. Used for testing or prototyping.
 * @param value New slider value.
 */
void MainWindow::on_sliderRandom0_valueChanged(int value)
{
    wm.dummy_var = value;
    //    kbtracker.setKbBigMin(int(value/10));
    qDebug() << "Dummy Var 0 changed: " << value;
    qDebug() << "Nothing is assigned!!";
}

/**
 * @brief Handles the noise radio button click event.
 *
 * Connects or disconnects noise addition in the environment brain. Also updates noise interval.
 * @param checked True if the radio button is checked (enabled).
 */
void MainWindow::on_noise_radioButton_clicked(bool checked)
{
    envBrain->connect_disconnect_add_noise(checked);
    if(checked)
        wm.noiseTimeIntv = ui->noiseFreq_slider->value();
    else
        wm.noiseTimeIntv = -1;
}

/**
 * @brief Handles the 'Draw Centroid' checkbox state change event.
 *
 * Updates the drawCentroid flag in the world model according to the UI checkbox.
 * @param arg1 State value (unused).
 */
void MainWindow::on_draw_centroid_stateChanged(int arg1)
{
    wm.drawCentroid = ui->draw_centroid->isChecked();
}


/**
 * @brief Handles the 'Draw Voronoii' checkbox state change event.
 *
 * Updates the drawVoronoii flag in the world model according to the UI checkbox.
 * @param arg1 State value (unused).
 */
void MainWindow::on_draw_voronoii_stateChanged(int arg1)
{
    wm.drawVoronoii = ui->draw_voronoii->isChecked();
}


/**
 * @brief Handles the 'Draw Bots Colors' checkbox state change event.
 *
 * Updates the drawWithColors flag in the world model according to the UI checkbox.
 * @param arg1 State value (unused).
 */
void MainWindow::on_draw_bots_colors_stateChanged(int arg1)
{
    wm.drawWithColors = ui->draw_bots_colors->isChecked();
}


/**
 * @brief Handles the value change for a dummy/random slider (slider 1).
 *
 * Updates a second dummy variable in the world model. Used for testing or prototyping.
 * @param value New slider value.
 */
void MainWindow::on_sliderRandom1_valueChanged(int value)
{
    qDebug() << "Dummy Var 1 changed: " << value;
    wm.dummy_var2 = value;
    //    qDebug() << "Nothing is assigned!!";
    //    kbtracker.setKbBigMax(int(value/10));
}


/**
 * @brief Handles the 'Draw Spatial Network' checkbox state change event.
 *
 * Updates the spatialNetwork flag in the world model according to the UI checkbox.
 * @param arg1 State value (unused).
 */
void MainWindow::on_draw_spatial_netw_stateChanged(int arg1)
{
    wm.spatialNetwork = ui->draw_spatial_netw->isChecked();
}


/**
 * @brief Handles the 'Draw Ball' checkbox state change event.
 *
 * Updates the drawBall flag in the world model according to the UI checkbox.
 * @param arg1 State value (unused).
 */
void MainWindow::on_drawBall_stateChanged(int arg1)
{
    wm.drawBall = ui->drawBall->isChecked();
}


void MainWindow::on_videoExpField_pushButton_clicked(bool checked)
{
    if(checked){
        wm.loadvidBackground = checked;
        //    QString address = ":/Files/" + ui->arenaImage_TextEdit->text();
        //    QString address = "/home/p27/LARS/LARS/etc/validation/media/robot_animation_random_robots_kilobot_N_20.mp4";
        QString address = ui->arenaImage_TextEdit->text();
        qDebug() << "HEY !! video loaded from: " << address;
        this->arenaWindow->_renderArea->playVideo(address.toStdString());

        envBrain->resetHeatMap();
        ////    this->arenaWindow->_renderArea->
    }
}


void MainWindow::on_generateExpField_pushButton_clicked()
{
    // Example: Call Python function generate_robot_animation_random_robots with arguments
    QString pythonScript = "/home/p27/LARS/LARS/etc/validation/generate_validation_images.py";

    QProcess *python_call_process = new QProcess(this);

    connect(python_call_process, &QProcess::readyReadStandardOutput, [python_call_process]() {
        qDebug() << python_call_process->readAllStandardOutput();
    });

    connect(python_call_process, &QProcess::readyReadStandardError, [python_call_process]() {
        qDebug() << python_call_process->readAllStandardError();
    });

    int test_num = 0;
    // ////  0: GRID Positions -> image  ||  1: Random Positions -> image  || 2: Star movement single robot -> animation || 3 : Random movement N -> animation
    // //// 4: random robot (non-grid) -> image

    test_num = ui->generate_comboBox->currentIndex();

    int dummy_var = ui->genExp_TextEdit->text().toInt();

    QStringList arguments;
    QString output_str, output_path;
    int robot_width = 42/2;

    switch (test_num) {
    case 0: // 0: GRID Positions -> image
    {
        //// IMAGE : GRID POSITIONS
        QString functionName = "robot_grid";

        int N = dummy_var;
        //        robot_width = dummy_var;
        QString dateStrng = QDateTime::currentDateTime().toString("yyyy_MM_dd__hh_mm");
        output_str = "/home/p27/LARS/LARS/etc/validation/media/eval_test_" + functionName + "_N_" + QString::number(N) + "_w_" + QString::number(robot_width);
        output_path = output_str + "_img.png";
        QString log_output_path = output_str + "_log.txt";
        QString robot_image_path = "/home/p27/LARS/LARS/etc/validation/kilobot.png";
        int grid_h, grid_w;
        grid_w = int(sqrt(N));
        grid_h = int(N/grid_w);
        N = grid_h*grid_w;
        QString grid_size = QString("("+QString::number(grid_w)+","+QString::number(grid_h)+")");
        int image_w = 1000;
        QString image_size = QString("("+QString::number(image_w)+","+QString::number(image_w)+")");
        //        QString point_distance = QString("800");
        int margin = 100;
        if(grid_w==1)
            grid_w = 2;
        int point_distance_i = int((image_w - margin)/(grid_w-1));
        QString point_distance = QString::number(point_distance_i);

        arguments << pythonScript << functionName
                  << "--args"
                  << QString("robot_image_path=%1").arg(robot_image_path)
                  << QString("robot_width=%1").arg(robot_width)
                  << QString("grid_size=%1").arg(grid_size)
                  << QString("output_path=%1").arg(output_path)
                  << QString("log_output_path=%1").arg(log_output_path)
                  << QString("image_size=%1").arg(image_size)
                  << QString("point_distance=%1").arg(point_distance);

        //        ui->arenaImage_TextEdit->setText(output_path);

        connect(python_call_process, QOverload<int, QProcess::ExitStatus>::of(&QProcess::finished),
                [this, python_call_process](int exitCode, QProcess::ExitStatus exitStatus) {
            qDebug() << "Python process finished with exit code:" << exitCode
                     << "and exit status:" << (exitStatus == QProcess::NormalExit ? "NormalExit" : "CrashExit");
            python_call_process->deleteLater();  // clean up
            ui->imageExpField_pushButton->click();
        });
        break;
    }
    case 1: // 1: Random Positions -> image
    {
        //// IMAGE : RANDOM POSITIONS
        QString functionName = "random_robots";
        int N = dummy_var;
        QString dateStrng = QDateTime::currentDateTime().toString("yyyy_MM_dd__hh_mm");
        output_str = "/home/p27/LARS/LARS/etc/validation/media/eval_test_" + functionName + "_N_" + QString::number(N) + "_w_" + QString::number(robot_width);
        output_path = output_str + "_img.png";
        QString log_output_path = output_str + "_log.txt";
        QString robot_image_path = "/home/p27/LARS/LARS/etc/validation/kilobot.png";
        QString image_size = QString("(1000,1000)");

        arguments << pythonScript << functionName
                  << "--args"
                  << QString("robot_image_path=%1").arg(robot_image_path)
                  << QString("robot_width=%1").arg(robot_width)
                  << QString("num_robots=%1").arg(N)
                  << QString("output_path=%1").arg(output_path)
                  << QString("log_output_path=%1").arg(log_output_path)
                  << QString("image_size=%1").arg(image_size);

        //        ui->arenaImage_TextEdit->setText(output_path);

        connect(python_call_process, QOverload<int, QProcess::ExitStatus>::of(&QProcess::finished),
                [this, python_call_process](int exitCode, QProcess::ExitStatus exitStatus) {
            qDebug() << "Python process finished with exit code:" << exitCode
                     << "and exit status:" << (exitStatus == QProcess::NormalExit ? "NormalExit" : "CrashExit");
            python_call_process->deleteLater();  // clean up
            ui->imageExpField_pushButton->click();
        });
        break;
    }
    case 2: // 2: Star movement single robot -> animation
    {
        //// ANIMATION : STAR MOVEMENT 1 Robot
        QString functionName = "robot_traj";
        int robot_speed = dummy_var;
        //    QString dateStrng = QDateTime::currentDateTime().toString("yyyy_MM_dd__hh_mm");
        //        QString output_str
        output_str = "/home/p27/LARS/LARS/etc/validation/media/eval_test_"
                + functionName
                + "_w_" + QString::number(robot_width)
                + "_sp_" + QString::number(robot_speed);
        output_path = output_str + "_vid.mp4";
        QString log_output_path = output_str + "_log.txt";
        QString robot_image_path = "/home/p27/LARS/LARS/etc/validation/kilobot.png";
        QString image_size = QString("(500,500)");

        arguments << pythonScript << functionName
                  << "--args"
                  << QString("robot_image_path=%1").arg(robot_image_path)
                  << QString("robot_width=%1").arg(robot_width)
                  << QString("robot_speed=%1").arg(robot_speed)
                  << QString("output_path=%1").arg(output_path)
                  << QString("image_size=%1").arg(image_size)
                  << QString("log_output_path=%1").arg(log_output_path);


        connect(python_call_process, QOverload<int, QProcess::ExitStatus>::of(&QProcess::finished),
                [this, python_call_process](int exitCode, QProcess::ExitStatus exitStatus) {
            qDebug() << "Python process finished with exit code:" << exitCode
                     << "and exit status:" << (exitStatus == QProcess::NormalExit ? "NormalExit" : "CrashExit");
            python_call_process->deleteLater();  // clean up
            ui->videoExpField_pushButton->click();
            if(!ui->videoExpField_pushButton->isChecked())
                ui->videoExpField_pushButton->click();
            this->resetElapsedTimer();
        });
        break;
    }
    case 3: // 3 : Random movement N -> animation
    {
        //// ANIMATION : RANDOM MOVEMENT
        QString functionName = "robot_anim_random";
        int N = dummy_var;
        int robot_speed = 3;
        //    QString dateStrng = QDateTime::currentDateTime().toString("yyyy_MM_dd__hh_mm");
        //        QString output_str
        output_str = "/home/p27/LARS/LARS/etc/validation/media/eval_test_"
                + functionName
                + "_N_" + QString::number(N)
                + "_w_" + QString::number(robot_width)
                + "_sp_" + QString::number(robot_speed);
        output_path = output_str + "_vid.mp4";
        QString log_output_path = output_str + "_log.txt";
        QString robot_image_path = "/home/p27/LARS/LARS/etc/validation/kilobot.png";
        QString image_size = QString("(1000,1000)");

        arguments << pythonScript << functionName
                  << "--args"
                  << QString("robot_image_path=%1").arg(robot_image_path)
                  << QString("robot_width=%1").arg(robot_width)
                  << QString("num_robots=%1").arg(N)
                  << QString("robot_speed=%1").arg(robot_speed)
                  << QString("output_path=%1").arg(output_path)
                  << QString("image_size=%1").arg(image_size)
                  << QString("log_output_path=%1").arg(log_output_path);


        connect(python_call_process, QOverload<int, QProcess::ExitStatus>::of(&QProcess::finished),
                [this, python_call_process](int exitCode, QProcess::ExitStatus exitStatus) {
            qDebug() << "Python process finished with exit code:" << exitCode
                     << "and exit status:" << (exitStatus == QProcess::NormalExit ? "NormalExit" : "CrashExit");
            python_call_process->deleteLater();  // clean up
            ui->videoExpField_pushButton->click();
            this->resetElapsedTimer();
        });
        break;
    }
    case 4: // 4: random robot (grid) -> image
    {
        //// IMAGE : RANDOM ROBOTS on GRID
        QString functionName = "random_robots_grid";

        int N = dummy_var;
        QString dateStrng = QDateTime::currentDateTime().toString("yyyy_MM_dd__hh_mm");
        output_str = "/home/p27/LARS/LARS/etc/validation/media/eval_test_" + functionName + "_N_" + QString::number(N) + "_w_" + QString::number(robot_width);
        output_path = output_str + "_img.png";
        QString log_output_path = output_str + "_log.txt";
        QString robot_image_path = "/home/p27/LARS/LARS/etc/validation/kilobot.png";
        int image_w = 1000;
        QString image_size = QString("("+QString::number(image_w)+","+QString::number(image_w)+")");

        arguments << pythonScript << functionName
                  << "--args"
                  << QString("robot_image_path=%1").arg(robot_image_path)
                  << QString("robot_width=%1").arg(robot_width)
                  << QString("output_path=%1").arg(output_path)
                  << QString("log_output_path=%1").arg(log_output_path)
                  << QString("image_size=%1").arg(image_size)
                  << QString("num_robots=%1").arg(N);

        //        ui->arenaImage_TextEdit->setText(output_path);

        connect(python_call_process, QOverload<int, QProcess::ExitStatus>::of(&QProcess::finished),
                [this, python_call_process](int exitCode, QProcess::ExitStatus exitStatus) {
            qDebug() << "Python process finished with exit code:" << exitCode
                     << "and exit status:" << (exitStatus == QProcess::NormalExit ? "NormalExit" : "CrashExit");
            python_call_process->deleteLater();  // clean up
            ui->imageExpField_pushButton->click();
            update_evaluation_test(); // call the test evaluation step
        });
        break;
    }
    default:
    {
        qDebug() << "TEST NUM NOT FOUND!!";
        break;
    }
    }

    qDebug() << "Calling the python code ... ";

    ui->arenaImage_TextEdit->setText(output_path);

    QString LARS_log_file_path = output_str + "_LARS_LOG_";
    ui->filePath_user->setText(LARS_log_file_path);

    python_call_process->start("python", arguments);
    qDebug() << "Started Python process to generate robot animation with arguments.";
}

void MainWindow::resetElapsedTimer()
{
    elapsedTimer.restart();
}


void MainWindow::on_V_slider_sliderReleased()
{

}


//void MainWindow::on_test_eval_pushButton_clicked(bool checked)
//{
//    if(checked)
//    {
//        if(ui->writeLog_button->isChecked())
//        {
            
//            // reduce v_val at each iteration by 2
//            // and update the V slider value
//            for (int v_val = 255; v_val >= 0; v_val -= 10) {

//                qDebug() << "V_VALUES : " << v_val;
//                ui->V_slider->setValue(v_val);

//                updateSliders();
//                updateColors();

//                for (int rep = 0; rep < 20; ++rep) {
//                    this->on_detectKilobots_pushButton_clicked();

//                    // wait as long as the dummy_detection_ready is false
//                    while(!dummy_detection_ready)
//                    {
//                        QCoreApplication::processEvents();
//                    }
//                }



//            }


//        }
//    }
//}

void MainWindow::update_evaluation_test()
{

//    int time_0 = elapsedTimer.elapsed();

//    while (elapsedTimer.elapsed()-time_0 < 2000)
//    {
//        int dummy = 0;
////        qDebug() << "ELAPSED TIME: " << elapsedTimer.elapsed()-time_0;
//    }
    for (int rep = 0; rep < 20; ++rep) {
        this->on_detectKilobots_pushButton_clicked();

        dummy_detection_ready = false;
        // wait as long as the dummy_detection_ready is false
        while(!dummy_detection_ready)
        {
            QCoreApplication::processEvents();
        }
    }

//    ui->detectKilobots_pushButton->click();


}


void MainWindow::on_test_eval_pushButton_clicked()
{

    //// Test Brightness
    //// {
//    int v_val = ui->V_slider->value();

//    if(v_val>80)
//        ui->V_slider->setValue(v_val-10);
//    else
//        ui->V_slider->setValue(v_val-2);

//    updateSliders();
//    updateColors();

    //// }



////    // Test Noise Tile Size
    //// {


    // // for detection [for tracking skip this for loop]
//    int N_reps = 50; // for detection evaluation
//    for (int rep = 0; rep < N_reps; ++rep) {
//        this->on_detectKilobots_pushButton_clicked();

//        // wait as long as the dummy_detection_ready is false
//        while(!dummy_detection_ready)
//        {
//            QCoreApplication::processEvents();
//        }
//    }


//    int N_Tile = ui->noiseTiles_slider->value();
//    ui->noiseTiles_slider->setValue(N_Tile + 10);

    //// }
    ///



//// // Test scalability
//     int N_robots = ui->genExp_TextEdit->text().toInt();
//     int next_N = N_robots + 5;
//     int w, h;
//     w = int(sqrt(float(next_N)));
//     h = ceil(float(next_N)/float(w));
//     next_N = h*w;
//     ui->genExp_TextEdit->setText(QString::number(next_N));

//     ui->generateExpField_pushButton->click();


    ui->sliderRandom1->setValue(ui->sliderRandom1->value()-5);


}


void MainWindow::on_genExp_TextEdit_editingFinished()
{
    QString path = "/home/p27/LARS/LARS/etc/validation/media/";
    QString tmp = path + "eval_test_robot_traj_w_42_sp_" + QString::number(ui->genExp_TextEdit->text().toInt());
//    eval_test_robot_traj_w_42_sp_26_vid
    ui->arenaImage_TextEdit->setText(tmp + "_vid.mp4");

    QString tmp_log_path = tmp +  "_LARS_LOG_";
    ui->filePath_user->setText(tmp_log_path);

    // ONLY FOR LATENCY EVALUATION
    wm.dummy_var3 = ui->genExp_TextEdit->text().toInt();
}

