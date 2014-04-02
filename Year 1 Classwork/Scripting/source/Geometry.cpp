/******************************************************************************
 * File:               Geometry.cpp
 * Author:             Elizabeth Lowry
 * Date Created:       April 1, 2014
 * Description:        Declares functions for a collision detection module.
 * Last Modified:      April 1, 2014
 * Last Modification:  Creation.
 ******************************************************************************/

#include "Geometry.h"
#include <algorithm>

void Square::Edges( LineSegment& a_roEdge1, LineSegment& a_roEdge2,
                    LineSegment& a_roEdge3, LineSegment& a_roEdge4 ) const
{
    a_roEdge1.point1 = a_roEdge2.point1 = corner1;
    a_roEdge3.point1 = a_roEdge4.point1 = corner2;
    a_roEdge1.point2.x = a_roEdge4.point2.x = corner1.x;
    a_roEdge1.point2.y = a_roEdge4.point2.y = corner2.y;
    a_roEdge2.point2.x = a_roEdge3.point2.x = corner2.x;
    a_roEdge2.point2.y = a_roEdge3.point2.y = corner1.y;
}

bool SegmentSquareIntersect( const LineSegment& ac_roSegment,
                             const Square& ac_roSquare )
{
    if( PointInSquare( ac_roSegment.point1, ac_roSquare ) ||
        PointInSquare( ac_roSegment.point2, ac_roSquare ) )
    {
        return true;
    }
    LineSegment oEdge1, oEdge2, oEdge3, oEdge4;
    ac_roSquare.Edges( oEdge1, oEdge2, oEdge3, oEdge4 );
    return SegmentsIntersect( ac_roSegment, oEdge1 ) ||
           SegmentsIntersect( ac_roSegment, oEdge2 ) ||
           SegmentsIntersect( ac_roSegment, oEdge3 ) ||
           SegmentsIntersect( ac_roSegment, oEdge4 );
}

bool SegmentsIntersect( const LineSegment& ac_roSegment1,
                        const LineSegment& ac_roSegment2 )
{
    float denominator = ( ac_roSegment2.point2.y - ac_roSegment2.point1.y ) *
                        ( ac_roSegment1.point2.x - ac_roSegment1.point1.x ) -
                        ( ac_roSegment2.point2.x - ac_roSegment2.point1.x ) *
                        ( ac_roSegment1.point2.y - ac_roSegment1.point1.y );
    if( 0.0f == denominator )
    {
        return false;
    }
    float u1 = ( ac_roSegment2.point2.x - ac_roSegment2.point1.x ) *
               ( ac_roSegment1.point1.y - ac_roSegment2.point1.y ) -
               ( ac_roSegment2.point2.y - ac_roSegment2.point1.y ) *
               ( ac_roSegment1.point1.x - ac_roSegment2.point1.x );
    u1 /= denominator;
    float u2 = ( ac_roSegment1.point2.x - ac_roSegment1.point1.x ) *
               ( ac_roSegment1.point1.y - ac_roSegment2.point1.y ) -
               ( ac_roSegment1.point2.y - ac_roSegment1.point1.y ) *
               ( ac_roSegment1.point1.x - ac_roSegment2.point1.x );
    u2 /= denominator;
    return 0.0f <= u1 && 1.0f >= u1 && 0.0f <= u2 && 1.0f >= u2;
}

bool PointInSquare( const Point& ac_roPoint, const Square& ac_roSquare )
{
    return ac_roPoint.x <= std::min( ac_roSquare.corner1.x, ac_roSquare.corner2.x ) &&
           ac_roPoint.x >= std::max( ac_roSquare.corner1.x, ac_roSquare.corner2.x ) &&
           ac_roPoint.y <= std::min( ac_roSquare.corner1.y, ac_roSquare.corner2.y ) &&
           ac_roPoint.y >= std::max( ac_roSquare.corner1.y, ac_roSquare.corner2.y );
}