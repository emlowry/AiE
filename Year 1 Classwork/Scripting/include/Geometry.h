/******************************************************************************
 * File:               Geometry.h
 * Author:             Elizabeth Lowry
 * Date Created:       April 1, 2014
 * Description:        Declares functions for a collision detection module.
 * Last Modified:      April 1, 2014
 * Last Modification:  Creation.
 ******************************************************************************/

#ifndef GEOMETRY__H
#define GEOMETRY__H

struct Point
{
    float x, y;
    Point( float a_x = 0, float a_y = 0 ) : x( a_x ), y( a_y ) {}
};
struct LineSegment
{
    Point point1, point2;
    LineSegment( float a_x1 = 0, float a_y1 = 0,
                 float a_x2 = 0, float a_y2 = 0 )
        : point1( a_x1, a_y1 ), point2( a_x2, a_y2 ) {}
    LineSegment( const Point& ac_roPoint1, const Point& ac_roPoint2 = Point() )
        : point1( ac_roPoint1 ), point2( ac_roPoint2 ) {}
};
struct Square
{
    Point corner1, corner2;
    Square( float a_x1 = 0, float a_y1 = 0, float a_x2 = 0, float a_y2 = 0 )
        : corner1( a_x1, a_y1 ), corner2( a_x2, a_y2 ) {}
    Square( const Point& ac_roCorner1, const Point& ac_roCorner2 = Point() )
        : corner1( ac_roCorner1 ), corner2( ac_roCorner2 ) {}
    void Edges( LineSegment& a_roEdge1, LineSegment& a_roEdge2,
                LineSegment& a_roEdge3, LineSegment& a_roEdge4 ) const;
};
struct Ray
{
    Point location, direction;
    Ray( float a_xLoc = 0, float a_yLoc = 0, float a_xDir = 0, float a_yDir = 0 )
        : location( a_xLoc, a_yLoc ), direction( a_xDir, a_yDir ) {}
    Ray( const Point& ac_roLocation, const Point& ac_roDirection = Point() )
        : location( ac_roLocation ), direction( ac_roDirection ) {}
};
struct Circle
{
    Point location;
    float radius;
    Circle( float a_x = 0, float a_y = 0, float a_r = 0 )
        : location( a_x, a_y ), radius( a_r ) {}
    Circle( const Point& ac_roPoint, float a_r = 0 )
        : location( ac_roPoint ), radius( a_r ) {}
};

bool SegmentCircleIntersect( const LineSegment& ac_roSegment,
                             const Circle& ac_roCircle );
bool SegmentSquareIntersect( const LineSegment& ac_roSegment,
                             const Square& ac_roSquare );
bool SegmentsIntersect( const LineSegment& ac_roSegment1,
                        const LineSegment& ac_roSegment2 );
bool PointInSquare( const Point& ac_roPoint, const Square& ac_roSquare );
float RayCircleDistance( const Ray& ac_roRay, const Circle& ac_roCircle );
float RaySquareDistance( const Ray& ac_roRay, const Square& ac_roSquare );
float RaySegmentDistance( const Ray& ac_roRay, const LineSegment& ac_roSegment );

#endif  // GEOMETRY__H
