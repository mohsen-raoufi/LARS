#ifndef VORONOIGENERATOR_H
#define VORONOIGENERATOR_H

#include <vector>
#include <boost/polygon/voronoi.hpp>
#include <boost/polygon/polygon.hpp>
#include <boost/polygon/segment_concept.hpp>

#include <QList>
#include <limits>
#include <QLineF>
#include <QRectF>

#include <QDebug>

using namespace boost::polygon;


class QPoint;

class voronoiGenerator {

public:
    typedef double coordinate_type;
    typedef point_data<coordinate_type> point_type;

private:


    typedef segment_data<coordinate_type> segment_type;
    typedef rectangle_data<coordinate_type> rect_type;
    typedef voronoi_builder<int> VB;
    typedef voronoi_diagram<coordinate_type> VD;
    typedef VD::edge_type edge_type;
    typedef VD::cell_type cell_type;
    typedef VD::cell_type::source_index_type source_index_type;
    typedef VD::cell_type::source_category_type source_category_type;
    typedef VD::cell_container_type cell_container_type;
    typedef VD::cell_container_type vertex_container_type;
    typedef VD::edge_container_type edge_container_type;
    typedef VD::const_cell_iterator const_cell_iterator;
    typedef VD::const_vertex_iterator const_vertex_iterator;
    typedef VD::const_edge_iterator const_edge_iterator;

    std::vector<segment_type> segment_data_;

    rect_type brect_;
    std::vector<point_type> point_data_;

public:
    voronoiGenerator();
    static void generateVoronoi(const QList<QPoint>& points, boost::polygon::voronoi_diagram<double>& vd);
    static QPoint findIntersection(const QLineF& line, double rectX, double rectY, double width, double height);
    void update_points(const QList<QPoint>& points);

    void old_voronoi_plot();

    void set_brect(QRectF Rect);

public slots:
    QPointF calculateIntersection(const QPointF &point, const QPointF &direction, const QRectF &bounds);
    QPointF calculateIntersectionII(const QPointF& knownPoint, const QPointF& midPoint, const QRectF& bounds);
    void clip_infinite_edge(const edge_type &edge, std::vector<point_type> *clipped_edge);
    point_type retrieve_point(const cell_type &cell);

    segment_type retrieve_segment(const cell_type &cell);
};

#endif // VORONOIGENERATOR_H
