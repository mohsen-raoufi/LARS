#ifndef ARENAWINDOW_H
#define ARENAWINDOW_H

#include <QMainWindow>

// Mohsen
#include <QGraphicsScene>
#include <QMouseEvent>
#include <QGraphicsSceneMouseEvent>
#include <QEvent>


#include <QPainter>

#include "ui/renderarea.h"
#include "ui/worldmodel.h"

#include <QGridLayout>

namespace Ui {
class ArenaWindow;
}

class ArenaWindow : public QMainWindow
{
    Q_OBJECT

public:
//    explicit ArenaWindow( WorldModel *wm = nullptr);
    explicit ArenaWindow(QWidget *parent = nullptr, WorldModel* wm = nullptr, QString title = "Arena Window");
    ~ArenaWindow();


//    void changeScreenBG(QColor color);
    void toggleFullScreen(bool goFullScreen);
//    void changeSceneRect(QRect rect);
//    void fitSceneRect();
//    void setFromImage(QPixmap pics);
    void toggleGrabMouse(bool isGrab);
//    void drawPoint(QPoint pnt);
//    void removePic();

    RenderArea *_renderArea;
//    void paintEvent(QPaintEvent *);

private slots:


public slots:
//    void refresh();
//    void paintEvent(QPaintEvent *);

private:
    Ui::ArenaWindow *ui;

    QGraphicsScene *scene;

    QGridLayout *testGrid;

    WorldModel* _wm;

//    void mouseMoveEvent(QMouseEvent *ev);

    void mousePressEvent(QMouseEvent *ev);
    void mouseMoveEvent(QMouseEvent *ev);
    void mouseReleaseEvent(QMouseEvent *ev);

//    void leaveEvent(QEvent *);
    int ms_x, ms_y;
    bool mouseGrab = true;
    int mouseVer = 2; // ver1: rightclick > leftclick, ver2: drag and drop
    bool isDragged = false;


    // User Interface
//    QBrush *brush_tmp;
//    QBrush brush_tmp2;

//    QBrush *brush_field ,*brush_goals, *brush_ball, *brush_yrobot,*brush_brobot,*brush_test,
//    *brush_astarNode, *brush_astarResult ,*brush_marking ,*brush_debug , *brush_pass;
//    QTimer _timer;

signals:
//    void mouse_pressed();
    void mouse_Pos();
//    void mouse_Left();

    void moving(QPoint);
    void moveDone();
};

#endif // ARENAWINDOW_H
