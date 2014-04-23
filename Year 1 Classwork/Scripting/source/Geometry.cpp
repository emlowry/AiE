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
#include <iostream>

bool SegmentCircleIntersect( const LineSegment& ac_roSegment,
                             const Circle& ac_roCircle )
{
    // get vector from start of segment to end of segment and from start of
    // segment to center of circle
    Point segV( ac_roSegment.point2.x - ac_roSegment.point1.x,
                ac_roSegment.point2.y - ac_roSegment.point1.y );
    Point circV( ac_roCircle.location.x - ac_roSegment.point1.x,
                 ac_roCircle.location.y - ac_roSegment.point1.y );

    // if distance from either end of segment to center of circle is less than
    // radius of circle, return true
    float segLenSq = segV.x*segV.x + segV.y*segV.y;
    float circDist1Sq = circV.x*circV.x + circV.y*circV.y;
    float radSq = ac_roCircle.radius*ac_roCircle.radius;
    if( circDist1Sq <= radSq )
    {
        return true;
    }
    float circDist2Sq = ( circV.x - segV.x )*( circV.x - segV.x ) +
                        ( circV.y - segV.y )*( circV.y - segV.y );
    if( circDist2Sq <= radSq )
    {
        return true;
    }

    // distance from center of circle to nearest point on line containing
    // segment, multiplied by segment length and squared, must be less than or
    // equal to square of product of segment length and circle radius
    float perp = segV.x*circV.y - segV.y*circV.x;
    if( perp*perp > segLenSq * radSq )
    {
        return false;
    }

    // half the length of area of line containing segment that intersects with
    // circle, multiplied by segment length
    float intersect = std::sqrt( segLenSq*radSq - perp*perp );

    // distance from start of segment to point on line containing segment
    // nearest to center of circle, multiplied by segment length
    float parallel = segV.x*circV.x + segV.y*circV.y;

    // parallel distance must be within [-intersect, segment length + intersect]
    return ( -intersect <= parallel && parallel <= segLenSq + intersect );
}

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

float RayCircleDistance( const Ray& ac_roRay, const Circle& ac_roCircle )
{
    
    Point circV( ac_roCircle.location.x - ac_roRay.location.x,
                 ac_roCircle.location.y - ac_roRay.location.y );

    // If ray starts inside circle, return 0
    float rayLenSq = ac_roRay.direction.x*ac_roRay.direction.x +
                     ac_roRay.direction.y*ac_roRay.direction.y;
    float circDistSq = circV.x*circV.x + circV.y*circV.y;
    float radSq = ac_roCircle.radius*ac_roCircle.radius;
    if( circDistSq <= radSq )
    {
        return 0;
    }

    // distance from start of ray to point on ray nearest to center of circle,
    // multiplied by ray direction vector magnitude, must be greater than zero
    float parallel = ac_roRay.direction.x*circV.x + ac_roRay.direction.y*circV.y;
    if ( parallel < 0 )
    {
        return -1;
    }

    // distance from center of circle to nearest point on ray, multiplied by ray
    // direction vector magnitude, must be less than or equal to product of ray
    // direction vector magnitude and circle radius
    float perp = ac_roRay.direction.x*circV.y - ac_roRay.direction.y*circV.x;
    if( perp*perp > rayLenSq * radSq )
    {
        return -1;
    }

    // length of area of line containing ray that intersects with circle,
    // multiplied by ray direction vector magnitude, minus half the length of the
    // segment of the line containing the ray that intersects the circle is the
    // distance from the start of the ray to the edge of the circle
    return ( parallel - std::sqrt( rayLenSq*radSq - perp*perp ) ) / std::sqrt( rayLenSq );
}

float RaySquareDistance( const Ray& ac_roRay, const Square& ac_roSquare )
{
    // if ray starts inside square, return 0 (meaning already inside)
    if( PointInSquare( ac_roRay.location, ac_roSquare ) )
    {
        return 0;
    }

    // if ray has no direction, return -1 (meaning no intersection)
    if( ( 0.0f == ac_roRay.direction.x && 0.0f == ac_roRay.direction.y ) )
    {
        return -1;
    }

    // minimum discovered distance
    float fResult = -1;

    // check each edge of the square
    LineSegment oEdges[4];
    ac_roSquare.Edges( oEdges[0], oEdges[1], oEdges[2], oEdges[3] );
    for each( LineSegment oSegment in oEdges )
    {
        float fDistance = RaySegmentDistance( ac_roRay, oSegment );
        if ( -1 != fDistance && fDistance < fResult )
        {
            fResult = fDistance;
        }
    }

    return fResult;
}

float RaySegmentDistance( const Ray& ac_roRay, const LineSegment& ac_roSegment )
{
    float fMag = std::sqrt( ac_roRay.direction.x*ac_roRay.direction.x +
                            ac_roRay.direction.y*ac_roRay.direction.y );
    Ray oRay( ac_roRay.location, Point( ac_roRay.direction.x / fMag,
                                        ac_roRay.direction.y / fMag ) );
    float denominator = ( ac_roSegment.point2.y - ac_roSegment.point1.y ) * oRay.direction.x -
                        ( ac_roSegment.point2.x - ac_roSegment.point1.x ) * oRay.direction.y;
    if( 0.0f == denominator )
    {
        return false;
    }
    float u1 = ( ac_roSegment.point2.x - ac_roSegment.point1.x ) *
               ( oRay.location.y - ac_roSegment.point1.y ) -
               ( ac_roSegment.point2.y - ac_roSegment.point1.y ) *
               ( oRay.location.x - ac_roSegment.point1.x );
    u1 /= denominator;
    float u2 = oRay.direction.x * ( oRay.location.y - ac_roSegment.point1.y ) -
               oRay.direction.y * ( oRay.location.x - ac_roSegment.point1.x );
    u2 /= denominator;
    return ( 0.0f <= u1 && 0.0f <= u2 && 1.0f >= u2 ? u1 : -1 );
}