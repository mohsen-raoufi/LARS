#include "arenaWindow.h"
#include "ui_arenaWindow.h"

#include <QDebug>

#include <QtQml/QQmlEngine>
//#include <QtQuick/QQuickView>
#include <QtQuick>

#include <QPushButton>

ArenaWindow::ArenaWindow(QWidget *parent, WorldModel *wm, QString title) :
    QMainWindow(parent),
    ui(new Ui::ArenaWindow)
{
    _wm = wm;
    ui->setupUi(this);

    setWindowTitle(title);

    this->setWindowFlags(Qt::WindowMinimizeButtonHint);
    this->setWindowFlags(Qt::WindowSystemMenuHint);
    this->setWindowFlags(Qt::WindowCloseButtonHint);

    _renderArea = new RenderArea(wm);

    this->ui->gridRender->addWidget(_renderArea);


//    gif_anim = new QLabel();
//    movie = new QMovie(":/Files/SCIoI_Logo.png");//:/Files/scioiNet.gif");
//    gif_anim->setMovie(movie);
//    movie->start();
//    proxy = sceneGif.addWidget(gif_anim);
//    gif_anim->setGeometry(0,0,100,100);

    //    showFullScreen();
    //    show();
    //    update();
    //    qDebug() << "is full scrn: " << isFullScreen();
    //    qDebug() << "UI ARENA width: " << ui->centralwidget->rect().width() << ", wind size: " << this->rect().width();
    //    ui->graphicsView->setGeometry(ui->centralwidget->rect());

    //    scene = new QGraphicsScene(this);
    //    ui->graphicsView->setScene(scene);

    //    ui->graphicsView->move(ui->graphicsView->rect().topLeft()-QGuiApplication::screens().at(0)->geometry().topLeft());
    //    ui->graphicsView->resize(QGuiApplication::screens().at(0)->geometry().size());

    //    qDebug() << "UI ARENA width: " << ui->graphicsView->rect().width() << ", Screen: " << QGuiApplication::screens().at(0)->geometry().width() << ", " << QGuiApplication::screens().at(0)->geometry().height();
    //    qDebug() << "UI ARENA width: " << ui->graphicsView->rect().width() << ", Central: " << this->geometry().width();
    //    ui->graphicsView->resize(this->geometry().size());

    show();



    //    ////    QQmlEngine engine;
    //    QQuickView view;
    //    view.setSource(QUrl::fromLocalFile(":qrCode.qml"));
    //    QObject *object = view.rootObject();
    //    //    if(object)
    //    //        qDebug() << "hoy hoy!!";
    //    //    object->set
    //    ////    QObject *rect = o
    //    ///
    //    //    QQmlEngine engine;
    //    //    QQmlComponent component(&engine, QUrl::fromLocalFile(":qrCode.qml"));
    //    //    QObject *object = component.create();
    //    QObject *qrCodeTL = object->findChild<QObject*>("qr_TopLeft");

    //    QObject *rect = object->findChild<QObject*>("rect");
    //    if(rect)
    //        rect->setProperty("color", "red");

    //    view.update();
    //    view.show();

    //    object->setProperty("x",100);

    //    delete object;

    update();

    // remove the bottom black status bar
    this->statusBar()->hide();
}

ArenaWindow::~ArenaWindow()
{
    delete ui;
}

void ArenaWindow::toggleFullScreen(bool goFullScreen)
{
//    qDebug() << "Arena Window: " << ui->centralwidget->rect().width();
    isFullScreen() ? showNormal() : showFullScreen();
    //    isFullScreen() ? ui->VVal_label->setGeometry(620, 170, 67, 19) : ui->VVal_label->setGeometry(820, 170, 67, 19);
    this->show();
    //    update();
//    qDebug() << "Arena Window: " << ui->centralwidget->rect().width();
}

void ArenaWindow::mousePressEvent(QMouseEvent* ev)
{
    qDebug() << "mouse press event at ARENA: " << ev->pos().x() << ", " << ev->pos().y();
    if(mouseVer==1){
        ms_x = ev->pos().x();
        ms_y = ev->pos().y();
        qDebug() << "Mouse is at [" << ms_x << ", " << ms_y << "]";
        if(ev->buttons() == Qt::LeftButton){
            //            ui->graphicsView->setGeometry(ms_x, ms_y, ui->graphicsView->width(), ui->graphicsView->height()); // Change this line, maybe
            mouseGrab = false;
        }
        else if (ev->buttons() == Qt::RightButton) {
            int tmpx, tmpy;
            //            tmpx = ui->graphicsView->x();
            //            tmpy = ui->graphicsView->y();
            //            ui->graphicsView->setGeometry(tmpx, tmpy, abs(ms_x-tmpx), abs(ms_y-tmpy));
        }
    }
    else if(mouseVer==2){
        if (ev->button() == Qt::LeftButton) {
            if(~this->isDragged){
                ms_x = ev->pos().x();
                ms_y = ev->pos().y();
                //                ui->graphicsView->setGeometry(ms_x, ms_y, 10, 10); // 10 is a temp value
            }
            this->isDragged = true;
            this->setMouseTracking(true);
            emit moving(QPoint(ev->localPos().x(),ev->localPos().y()));
            ev->accept();
        }
    }

}

void ArenaWindow::mouseMoveEvent(QMouseEvent *ev)
{
    if (this->isDragged) {
        int tmpx, tmpy;
        tmpx = 0;//ui->graphicsView->x();
        tmpy = 0;//ui->graphicsView->y();
        //        ui->graphicsView->setGeometry(tmpx, tmpy, abs(ev->pos().x()-tmpx), abs(ev->pos().y()-tmpy)); // later make a slot and connect moving(QPoint) to this line
        //        ui->graphicsView->setGeometry(ms_x, ms_y, ui->graphicsView->width(), ui->graphicsView->height());
        emit moving(QPoint(ev->localPos().x(),ev->localPos().y()));
    }
    ev->accept();
}

void ArenaWindow::mouseReleaseEvent(QMouseEvent *ev)
{
    if (ev->button() == Qt::LeftButton) {
        this->isDragged = false;
        emit this->moveDone();
        this->setMouseTracking(false);
        ev->accept();
    }
}

