#include "worldmodel.h"

WorldModel::WorldModel()
{
    time = 0;

    expFieldRect = QRect(marker0_pos + QPoint(marker_length,marker_length), marker3_pos);

    qDebug() << "BALL INITIAL POS: " << ballPos.x() << ", " << ballPos.y();
}

void WorldModel::setFieldColor(QColor color)
{
    this->fieldCol = color;
}

void WorldModel::setFieldSize(QSize size)
{
    this->fieldSize = size;
}

void WorldModel::setRobotCustomColor(QColor color)
{
    this->brush_robotCustom_0->setStyle(Qt::SolidPattern);
    this->brush_robotCustom_0->setColor(color);
}

void WorldModel::setNullRobotCustomBrush(bool boolNullBrush)
{
    qDebug() << "Toggling Robot Brush, nullBrush: " << boolNullBrush;
    this->boolNullBrushForRobots = boolNullBrush;
}

//void WorldModel::create_empty_graph(QList<QPoint> points)
//{
////    for (const QPoint &point : points) {
////        boost::add_vertex(point, robot_graph);
////    }
//}

void WorldModel::setFieldColorHSV(int H, int S, int V)
{
    this->fieldCol = QColor::fromHsv(H,S,V);
}
