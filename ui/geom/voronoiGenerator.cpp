#include "voronoiGenerator.h"
#include <boost/polygon/voronoi.hpp>

#include <QPoint>


using namespace boost::polygon;


voronoiGenerator::voronoiGenerator() {
}


void voronoiGenerator::generateVoronoi(const QList<QPoint>& qPoints, voronoi_diagram<double>& vd) {
    std::vector<point_data<int>> boostPoints;
    for (const auto& qPoint : qPoints) {
        boostPoints.push_back(point_data<int>(qPoint.x(), qPoint.y()));
    }

    // Clear the existing diagram data before constructing a new diagram
    vd.clear();

    construct_voronoi(boostPoints.begin(), boostPoints.end(), &vd);
}

QPoint voronoiGenerator::findIntersection(const QLineF& line, double rectX, double rectY, double width, double height) {
    QRectF rect(rectX, rectY, width, height);
    QPointF intersectionPoint;

    // Define the lines for each edge of the rectangle
    QLineF topLine(rect.topLeft(), rect.topRight());
    QLineF bottomLine(rect.bottomLeft(), rect.bottomRight());
    QLineF leftLine(rect.topLeft(), rect.bottomLeft());
    QLineF rightLine(rect.topRight(), rect.bottomRight());

    // Check for intersections with each side of the rectangle
    QLineF::IntersectType intersectType;

    intersectType = line.intersect(topLine, &intersectionPoint);
    if (intersectType == QLineF::BoundedIntersection) return intersectionPoint.toPoint();

    intersectType = line.intersect(bottomLine, &intersectionPoint);
    if (intersectType == QLineF::BoundedIntersection) return intersectionPoint.toPoint();

    intersectType = line.intersect(leftLine, &intersectionPoint);
    if (intersectType == QLineF::BoundedIntersection) return intersectionPoint.toPoint();

    intersectType = line.intersect(rightLine, &intersectionPoint);
    if (intersectType == QLineF::BoundedIntersection) return intersectionPoint.toPoint();

    // If no intersection found or an unbounded intersection, handle appropriately
    // This might involve returning a default value or handling an error
    return QPoint();
}

void voronoiGenerator::update_points(const QList<QPoint> &points)
{
    point_data_.clear();
    for (const auto& qPoint : points) {
        point_type p(qPoint.x(), qPoint.y());
        point_data_.push_back(p);

    }
}

void voronoiGenerator::old_voronoi_plot()
{
    //        // 1st version
    //        int itk = 0;
    //        int midPntCtr = 0;
    //        for (boost::polygon::voronoi_diagram<double>::const_edge_iterator it = vd.edges().begin(); it != vd.edges().end(); ++it) {
    //            itk++;

    //            const boost::polygon::voronoi_edge<double>& edge = *it;
    //            if (edge.is_finite()) {
    //                QPointF start(edge.vertex0()->x(), edge.vertex0()->y());
    //                QPointF end(edge.vertex1()->x(), edge.vertex1()->y());
    //                painter.drawLine(start, end);
    //                //            qDebug() << "HEY THERE, Drawing the Voronoii Line #" << itk << " from: " << start->x() << ", " << start->y() << " to " << end->x() << ", " << end->y();
    //            }
    //            else {
    //                continue;
    //                painter.setPen(*pen_network);

    //                //                continue;
    //                // Handle infinite edges
    //                //                QRectF bounds = _wm->insideRect;

    //                //                bounds.moveTopLeft(QPoint(-_wm->insideRect.topLeft().x()/2, -_wm->insideRect.topLeft().y()/2));
    //                const boost::polygon::voronoi_vertex<double>* vertex = edge.vertex0() ? edge.vertex0() : edge.vertex1();
    //                if (!vertex) continue; // Skip if no vertex is associated with the edge

    //                QPointF knownPoint(vertex->x(), vertex->y());

    //                painter.drawEllipse(knownPoint, 5, 5);

    //                int index = edge.cell()->source_index();
    //                int twinIndex = edge.twin()->cell()->source_index();
    //                QPointF site = _wm->rob_Type0_pos[index];
    //                QPointF twinSite = _wm->rob_Type0_pos[twinIndex];
    //                QPointF midPoint = (site + twinSite) / 2.0;
    //                midPntCtr++;


    //                painter.drawEllipse(midPoint, 5, 5);

    //                //                // V1: Perpendicular to the direction of the connecting line between two sites
    //                //                QPointF direction = (twinSite - site);
    //                //                direction = QPointF(-direction.y(), direction.x()); // Perpendicular to the edge
    //                //                QPointF scndPoint = QPointF(knownPoint.x() + direction.x(), knownPoint.y() + direction.y());



    //                // V2: from the known point toward the midpoint! -->> Second point is the midpoint!!!
    //                QPointF direction = (midPoint - knownPoint);


    //                // Normalize the direction
    //                qreal length = sqrt(direction.x() * direction.x() + direction.y() * direction.y());
    //                if (length == 0) continue; // Avoid division by zero
    //                direction /= length;


    //                //                painter.setBrush(*brush_initPoints);
    //                //                painter.setBrush(Qt::NoBrush);
    //                //                painter.setPen(*pen_circ2Draw);
    //                //                painter.drawEllipse(scndPoint, 5, 5);


    //                // Calculate intersection and draw
    //                //                voronoiGenerator::calculateIntersection(midpoint, direction, bounds);
    //                //                QPointF intersection = VoronoiiGen.findIntersection(QLineF(midpoint, knownPoint), bounds.left(), bounds.top(), bounds.width(), bounds.height());


    //                QPointF intersection = VoronoiiGen.calculateIntersection(midPoint, direction, bounds); //  voronoiGenerator::calculateIntersection(midpoint, direction, bounds);

    //                //                QPointF intersection = VoronoiiGen.calculateIntersectionII(knownPoint, midPoint, bounds);

    //                painter.drawEllipse(intersection, 5, 5);

    //                qDebug() << "It# " << itk << ", Known: " << knownPoint.x() << ", " <<  knownPoint.y() << ", MidPoint #" << midPntCtr << ": " << midPoint.x() << ", " << midPoint.y() << ", Intersect: " << intersection.x() << ", " << intersection.y();
    //                painter.drawLine(knownPoint, intersection);

    //                painter.drawLine(bounds.topLeft(), bounds.bottomLeft());
    //                painter.drawLine(bounds.bottomLeft(), bounds.bottomRight());
    //                painter.drawLine(bounds.bottomRight(), bounds.topRight());
    //                painter.drawLine(bounds.topRight(), bounds.topLeft());

    //            }
    //        }
}

void voronoiGenerator::set_brect(QRectF Rect)
{
//    const point_data& point1(Rect.topLeft().x(), Rect.topLeft().y());
    point_type tl(Rect.topLeft().x(), Rect.topLeft().y());
    point_type br(Rect.bottomRight().x(), Rect.bottomRight().y());
    point_type wh(Rect.width(), Rect.height());
    boost::polygon::set_points(brect_, tl, wh);
}


QPointF voronoiGenerator::calculateIntersection(const QPointF& point, const QPointF& direction, const QRectF& bounds) {
    std::vector<QPointF> intersections;

    // Calculate line equation parameters: y = mx + b
    double m = direction.y() / direction.x();
    double b = point.y() - m * point.x();

    // Avoid division by zero for vertical lines
    if (std::isfinite(m)) {
        // Top boundary (y = bounds.top())
        double xTop = (bounds.top() - b) / m;
        if (xTop >= bounds.left() && xTop <= bounds.right()) {
            intersections.push_back(QPointF(xTop, bounds.top()));
        }

        // Bottom boundary (y = bounds.bottom())
        double xBottom = (bounds.bottom() - b) / m;
        if (xBottom >= bounds.left() && xBottom <= bounds.right()) {
            intersections.push_back(QPointF(xBottom, bounds.bottom()));
        }
    }

    // Left boundary (x = bounds.left()), calculate y directly
    double yLeft = m * bounds.left() + b;
    if (yLeft >= bounds.top() && yLeft <= bounds.bottom()) {
        intersections.push_back(QPointF(bounds.left(), yLeft));
    }

    // Right boundary (x = bounds.right()), calculate y directly
    double yRight = m * bounds.right() + b;
    if (yRight >= bounds.top() && yRight <= bounds.bottom()) {
        intersections.push_back(QPointF(bounds.right(), yRight));
    }

    // Find the closest intersection point to the original point
    QPointF closestIntersection = point; // Default to start point if no intersection found
    double minDistance = std::numeric_limits<double>::max();

    for (const auto& intersection : intersections) {
        double dx = point.x() - intersection.x();
        double dy = point.y() - intersection.y();
        double distance = sqrt(dx * dx + dy * dy);

        // Ensure the intersection is in the direction of the vector
        QPointF diff = intersection - point;
        bool inDirection = (direction.x() * diff.x() + direction.y() * diff.y()) > 0;

        if (distance < minDistance && inDirection) {
            closestIntersection = intersection;
            minDistance = distance;
        }
    }

    return closestIntersection;
}


QPointF voronoiGenerator::calculateIntersectionII(const QPointF& knownPoint, const QPointF& midPoint, const QRectF& bounds) {
    QPointF intersect, tmpIntersect;
    std::vector<QPointF> intersections;

    QPointF direction = (midPoint - knownPoint);

    qreal length = sqrt(direction.x() * direction.x() + direction.y() * direction.y());
    if (length == 0)  {
        intersect = midPoint;
        return intersect;
    }

    // Calculate line equation parameters: y = mx + b
    double m = direction.y() / direction.x();
    double b = knownPoint.y() - m * knownPoint.x();


    // Avoid division by zero for vertical lines
    if (std::isfinite(m)) {
        // check if intersects with the top or bottom lines
        // Top boundary (y = bounds.top())
        double xTop = (bounds.top() - b) / m;
        if (xTop >= bounds.left() && xTop <= bounds.right()) {
            tmpIntersect = QPointF(xTop, bounds.top());
            if(QPointF::dotProduct(direction,(tmpIntersect-knownPoint))>0)
                intersections.push_back(tmpIntersect);
        }

        // Bottom boundary (y = bounds.bottom())
        double xBottom = (bounds.bottom() - b) / m;
        if (xBottom >= bounds.left() && xBottom <= bounds.right()) {
            tmpIntersect = QPointF(xBottom, bounds.bottom());
            if(QPointF::dotProduct(direction,(tmpIntersect-knownPoint))>0)
                intersections.push_back(tmpIntersect);
        }
    }

    // Left boundary (x = bounds.left()), calculate y directly
    double yLeft = m * bounds.left() + b;
    if (yLeft >= bounds.top() && yLeft <= bounds.bottom()) {
        //        intersections.push_back(QPointF(bounds.left(), yLeft));

        tmpIntersect = QPointF(bounds.left(), yLeft);
        if(QPointF::dotProduct(direction,(tmpIntersect-knownPoint))>0)
            intersections.push_back(tmpIntersect);
    }

    // Right boundary (x = bounds.right()), calculate y directly
    double yRight = m * bounds.right() + b;
    if (yRight >= bounds.top() && yRight <= bounds.bottom()) {
        //        intersections.push_back(QPointF(bounds.right(), yRight));

        tmpIntersect = QPointF(bounds.right(), yRight);
        if(QPointF::dotProduct(direction,(tmpIntersect-knownPoint))>0)
            intersections.push_back(tmpIntersect);
    }

    if (intersections.size()==1) {
        intersect = intersections[0];
        qDebug() << "only 1 intersection found!!";
        return intersect;
    }


    // Find the closest intersection point to the original point
    QPointF closestIntersection = knownPoint; // Default to start point if no intersection found
    double minDistance = std::numeric_limits<double>::max();

    for (const auto& intersection : intersections) {
        double dx = knownPoint.x() - intersection.x();
        double dy = knownPoint.y() - intersection.y();
        double distance = sqrt(dx * dx + dy * dy);

        // Ensure the intersection is in the direction of the vector
        QPointF diff = intersection - knownPoint;
        bool inDirection = (direction.x() * diff.x() + direction.y() * diff.y()) > 0;

        if (distance < minDistance && inDirection) {
            closestIntersection = intersection;
            minDistance = distance;
        }
    }

    return closestIntersection;
}



void voronoiGenerator::clip_infinite_edge(const edge_type& edge, std::vector<point_type>* clipped_edge) {
    const cell_type& cell1 = *edge.cell();
    const cell_type& cell2 = *edge.twin()->cell();
    point_type origin, direction;
    // Infinite edges could not be created by two segment sites.
    if (cell1.contains_point() && cell2.contains_point()) {
        point_type p1 = retrieve_point(cell1);
        point_type p2 = retrieve_point(cell2);
        origin.x((p1.x() + p2.x()) * 0.5);
        origin.y((p1.y() + p2.y()) * 0.5);
        direction.x(p1.y() - p2.y());
        direction.y(p2.x() - p1.x());
    } else {
        origin = cell1.contains_segment() ?
                    retrieve_point(cell2) :
                    retrieve_point(cell1);
        segment_type segment = cell1.contains_segment() ?
                    retrieve_segment(cell1) :
                    retrieve_segment(cell2);
        coordinate_type dx = high(segment).x() - low(segment).x();
        coordinate_type dy = high(segment).y() - low(segment).y();
        if ((low(segment) == origin) ^ cell1.contains_point()) {
            direction.x(dy);
            direction.y(-dx);
        } else {
            direction.x(-dy);
            direction.y(dx);
        }
    }
    coordinate_type side = xh(brect_) - xl(brect_);
    coordinate_type koef =
            side / (std::max)(fabs(direction.x()), fabs(direction.y()));
    if (edge.vertex0() == NULL) {
        clipped_edge->push_back(point_type(
                                    origin.x() - direction.x() * koef,
                                    origin.y() - direction.y() * koef));
    } else {
        clipped_edge->push_back(
                    point_type(edge.vertex0()->x(), edge.vertex0()->y()));
    }
    if (edge.vertex1() == NULL) {
        clipped_edge->push_back(point_type(
                                    origin.x() + direction.x() * koef,
                                    origin.y() + direction.y() * koef));
    } else {
        clipped_edge->push_back(
                    point_type(edge.vertex1()->x(), edge.vertex1()->y()));
    }
}

voronoiGenerator::point_type voronoiGenerator::retrieve_point(const cell_type &cell)
{
    source_index_type index = cell.source_index();
    source_category_type category = cell.source_category();
    if (category == SOURCE_CATEGORY_SINGLE_POINT) {
        return point_data_[index];
    }
    index -= point_data_.size();
    if (category == SOURCE_CATEGORY_SEGMENT_START_POINT) {
        return low(segment_data_[index]);
    } else {
        return high(segment_data_[index]);
    }
}


voronoiGenerator::segment_type voronoiGenerator::retrieve_segment(const cell_type& cell) {
    source_index_type index = cell.source_index() - point_data_.size();
    return segment_data_[index];
}


