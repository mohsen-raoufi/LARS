#include "voronoi_diagram.h"

Voronoi_Diagram::Voronoi_Diagram()
{
}

QList<Vector2D> Voronoi_Diagram::calculate(QList<Vector2D> in_points)
{
    //consider some points
    std::vector<Point_2> points;
    for(int i=0;i<in_points.size();i++)
    {
        points.push_back(Point_2(in_points.at(i).x,in_points.at(i).y));
    }

    Delaunay_triangulation_2 dt2;
    //insert points into the triangulation
    dt2.insert(points.begin(),points.end());
    //construct a rectangle
    Iso_rectangle_2 bbox(Field::MinX,Field::MinY,Field::MaxX,Field::MaxY);
    Cropped_voronoi_from_delaunay vor(bbox);
    //extract the cropped Voronoi diagram
    dt2.draw_dual(vor);
    //print the cropped Voronoi diagram as segments
    std::stringstream ss;

    QList<Vector2D> out;
    wm->voronoi.clear();

    for(int i=0;i<vor.m_cropped_vd.size();i++)
    {
        Segment_2 tmp = vor.m_cropped_vd.at(i);
        Point_2 start = tmp.vertex(0) , end = tmp.vertex(1);
        Vector2D first(floor(start.x()),floor(start.y())) , second(floor(end.x()),floor(end.y()));

        if( !out.contains(first) )
        {
            if( wm->kn->IsInsideField(first) )
                 out.append(first);
        }

        if( !out.contains(second) )
        {
            if( wm->kn->IsInsideField(second) )
               out.append(second);
        }

        Segment2D seg(first,second);
        wm->voronoi.append(seg);
    }

    return out;
}

void Voronoi_Diagram::setWorldModel(WorldModel *wm)
{
    this->wm = wm;
}
