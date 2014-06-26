/******************************************************************************
 * File:               Matrix4x4TestGroup.cpp
 * Author:             Elizabeth Lowry
 * Date Created:       January 5, 2014
 * Description:        4x4 Matrix tests.
 * Last Modified:      June 26, 2014
 * Last Modification:  Debugging.
 ******************************************************************************/

#include "Matrix4x4TestGroup.h"
#include "MathLibrary.h"
#include <sstream>

using namespace Space;
using Math::Matrix;

Matrix4x4TestGroup::Matrix4x4TestGroup()
    : UnitTestGroup("4x4 Matrix tests")
{
    AddTest( "Perspective and parallel projection", Project );
    AddTest( "HVector scale transformation", Scale );
    AddTest( "HVector rotation ", Rotate );
    AddTest( "HVector translation ", Translate );
    AddTest( "Point scale transformation", PointScale );
    AddTest( "Point rotation", PointRotate );
    AddTest( "Matrix multiplication", Multiply );
}

UnitTest::Result Matrix4x4TestGroup::Project()
{
    // Perspective projection - z-axis points toward the camera, y-axis points
    // up, and x-axis points right.  You may have to transform further to get
    // the right pixel coordinates.  After transformation, z-axis points away
    // from the camera, but x and y are the same - we've switched coordinate
    // system handedness.
    HVector3D aoPoints[6] = { HVector3D( 1, 2, -8 ),
                              HVector3D( 1, 2, -4 ),
                              HVector3D( 1, 2, -2 ),
                              HVector3D( 1, 2, -1 ),
                              HVector3D( 1, 2, 2 ),
                              HVector3D( 2, 4, -4, 2 ) };
    Transform3D oTransform = PerspectiveProjection( 2, 6, Point2D( 4, 4 ) );
    HVector3D aoExpected1[6] = { HVector3D( 0.0625, 0.125, 1.125 ),
                                 HVector3D( 0.125, 0.25, 0.75 ),
                                 HVector3D( 0.25, 0.5, 0 ),
                                 HVector3D( 0.5, 1, -1.5 ),
                                 HVector3D( -0.25, -0.5, 3 ),
                                 // In the physical world, ^this is how
                                 // holograms work.  In computer graphics,
                                 // remember to discard points "behind" the
                                 // virtual camera lens at the origin.
                                 HVector3D( 0.25, 0.5, 0 ) };
    for( unsigned int i = 0; i < 6; ++i )
    {
        if( aoPoints[i] * oTransform != aoExpected1[i] )
        {
            std::ostringstream oOut;
            oOut << "Perspective projection of " << aoPoints[i]
                 << " other than " << aoExpected1[i];
                 return UnitTest::Fail( oOut.str() );
        }
    }

    // Parallel projection
    oTransform = ParallelProjection( 2, 6, Point2D( 4, 4 ) );
    HVector3D aoExpected2[6] = { HVector3D( 0.25, 0.5, 1.5 ),
                                 HVector3D( 0.25, 0.5, 0.5 ),
                                 HVector3D( 0.25, 0.5, 0 ),
                                 HVector3D( 0.25, 0.5, -0.25 ),
                                 HVector3D( 0.25, 0.5, -1 ),
                                 HVector3D( 0.25, 0.5, 0 ) };
    for( unsigned int i = 0; i < 6; ++i )
    {
        if( aoPoints[i] * oTransform != aoExpected2[i] )
        {
            std::ostringstream oOut;
            oOut << "Parallel projection of " << aoPoints[i]
                 << " other than " << aoExpected2[i];
                 return UnitTest::Fail( oOut.str() );
        }
    }

    return UnitTest::PASS;
}

UnitTest::Result Matrix4x4TestGroup::Scale()
{
    // Scale a non-homogeneous 2D vector by a uniform factor
    HVector3D oVector( 1, 2, 3 );
    Transform3D oTransform = Scaling( 0.5 );
    oVector *= oTransform;
    if( HVector3D( 0.5, 1, 1.5 ) != oVector )
    {
        return UnitTest::Fail( "Scaling by a factor of 0.5 failed" );
    }
    oVector /= oTransform;
    if( HVector3D( 1, 2, 3 ) != oVector )
    {
        return UnitTest::Fail( "Failed to undo scaling by a factor of 0.5" );
    }

    // Scale by different factors for each direction
    oTransform = Scaling( 2, 0.5, -1 );
    oVector *= oTransform;
    if( HVector3D( 2, 1, -3 ) != oVector )
    {
        return UnitTest::Fail( "Scaling by factors of 0.5 in the x direction, 2"
                               " in the y direction, and -1 in the z direction"
                               " failed" );
    }
    oVector /= oTransform;
    if( HVector3D( 1, 2, 3 ) != oVector )
    {
        return UnitTest::Fail( "Failed to undo scaling by a factor of 0.5 in"
                               " the x direction, 2 in the y direction, and -1"
                               " in the z direction" );
    }

    // Scale by factors in each direction given by a vector
    oTransform = Scaling( oVector );
    oVector *= oTransform;
    if( HVector3D( 1, 4, 9 ) != oVector )
    {
        return UnitTest::Fail( "Scaling by a vector factor failed" );
    }
    oVector /= oTransform;
    if( HVector3D( 1, 2, 3 ) != oVector )
    {
        return UnitTest::Fail( "Failed to undo scaling by a vector factor" );
    }
    
    // Scale a non-homogeneous 2D vector about a point by a uniform factor
    oTransform = Scaling( 0.5, Point3D( 2, 1, -2 ) );
    oVector *= oTransform;
    if( HVector3D( 1.5, 1.5, 0.5 ) != oVector )
    {
        return UnitTest::Fail( "Scaling by a factor of 0.5 failed" );
    }
    oVector /= oTransform;
    if( HVector3D( 1, 2, 3 ) != oVector )
    {
        return UnitTest::Fail( "Failed to undo scaling by a factor of 0.5" );
    }

    // Scale about a point by different factors for each direction
    oTransform = Scaling( 2, 0.5, -1, Point3D( 2, 1, -2 ) );
    oVector *= oTransform;
    if( HVector3D( 0, 1.5, -7 ) != oVector )
    {
        return UnitTest::Fail( "Scaling by factors of 0.5 in the x direction, 2"
                               " in the y direction, and -1 in the z direction"
                               " failed" );
    }
    oVector /= oTransform;
    if( HVector3D( 1, 2, 3 ) != oVector )
    {
        return UnitTest::Fail( "Failed to undo scaling by a factor of 0.5 in"
                               " the x direction, 2 in the y direction, and -1"
                               " in the z direction" );
    }

    // Scale about a point by factors in each direction given by a vector
    oTransform = Scaling( oVector, Point3D( 2, 1, -2 ) );
    oVector *= oTransform;
    if( HVector3D( 1, 3, 13 ) != oVector )
    {
        return UnitTest::Fail( "Scaling by a vector factor failed" );
    }
    oVector /= oTransform;
    if( HVector3D( 1, 2, 3 ) != oVector )
    {
        return UnitTest::Fail( "Failed to undo scaling by a vector factor" );
    }
    
    return UnitTest::PASS;
}

UnitTest::Result Matrix4x4TestGroup::Rotate()
{
    // Rotate by radians
    HVector3D oVector( 1, 2, 3 );
    Transform3D oTransform = Rotation( Math::PI / 2, Point3D::Unit(0) );
    oVector *= oTransform;
    if( HVector3D( 1, -3, 2 ) != oVector )
    {
        return UnitTest::Fail( "Rotating about x-axis by pi/2 radians failed" );
    }
    oVector /= oTransform;
    if( HVector3D( 1, 2, 3 ) != oVector )
    {
        return UnitTest::Fail( "Failed to undo rotating about x-axis by pi/2 radians" );
    }
    oTransform = Rotation( Math::PI / 2, Point3D::Unit(1) );
    oVector *= oTransform;
    if( HVector3D( 3, 2, -1 ) != oVector )
    {
        return UnitTest::Fail( "Rotating about y-axis by pi/2 radians failed" );
    }
    oVector /= oTransform;
    if( HVector3D( 1, 2, 3 ) != oVector )
    {
        return UnitTest::Fail( "Failed to undo rotating about y-axis by pi/2 radians" );
    }
    oTransform = Rotation( Math::PI / 2, Point3D::Unit(2) );
    oVector *= oTransform;
    if( HVector3D( -2, 1, 3 ) != oVector )
    {
        return UnitTest::Fail( "Rotating about z-axis by pi/2 radians failed" );
    }
    oVector /= oTransform;
    if( HVector3D( 1, 2, 3 ) != oVector )
    {
        return UnitTest::Fail( "Failed to undo rotating about z-axis by pi/2 radians" );
    }
    
    // Rotate by degrees
    oTransform = DegreeRotation( 90, Point3D::Unit(0) );
    oVector *= oTransform;
    if( HVector3D( 1, -3, 2 ) != oVector )
    {
        return UnitTest::Fail( "Rotating about x-axis by 90 degrees failed" );
    }
    oVector /= oTransform;
    if( HVector3D( 1, 2, 3 ) != oVector )
    {
        return UnitTest::Fail( "Failed to undo rotating about x-axis by 90 degrees" );
    }
    oTransform = DegreeRotation( 90, Point3D::Unit(1) );
    oVector *= oTransform;
    if( HVector3D( 3, 2, -1 ) != oVector )
    {
        return UnitTest::Fail( "Rotating about y-axis by 90 degrees failed" );
    }
    oVector /= oTransform;
    if( HVector3D( 1, 2, 3 ) != oVector )
    {
        return UnitTest::Fail( "Failed to undo rotating about y-axis by 90 degrees" );
    }
    oTransform = DegreeRotation( 90, Point3D::Unit(2) );
    oVector *= oTransform;
    if( HVector3D( -2, 1, 3 ) != oVector )
    {
        return UnitTest::Fail( "Rotating about z-axis by 90 degrees failed" );
    }
    oVector /= oTransform;
    if( HVector3D( 1, 2, 3 ) != oVector )
    {
        return UnitTest::Fail( "Failed to undo rotating about z-axis by 90 degrees" );
    }
    
    // Rotate by radians about a point
    oTransform = Rotation( Math::PI / 2, Point3D::Unit(0), Point3D( 2, 1, -2 ) );
    oVector *= oTransform;
    if( HVector3D( 1, -4, -1 ) != oVector )
    {
        return UnitTest::Fail( "X-rotating about (2,1,-2) by pi/2 radians failed" );
    }
    oVector /= oTransform;
    if( HVector3D( 1, 2, 3 ) != oVector )
    {
        return UnitTest::Fail( "Failed to undo x-rotating about (2,1,-2) by pi/2 radians" );
    }
    oTransform = Rotation( Math::PI / 2, Point3D::Unit(1), Point3D( 2, 1, -2 ) );
    oVector *= oTransform;
    if( HVector3D( 7, 2, -1 ) != oVector )
    {
        return UnitTest::Fail( "Y-rotating about (2,1,-2) by pi/2 radians failed" );
    }
    oVector /= oTransform;
    if( HVector3D( 1, 2, 3 ) != oVector )
    {
        return UnitTest::Fail( "Failed to undo y-rotating about (2,1,-2) by pi/2 radians" );
    }
    oTransform = Rotation( Math::PI / 2, Point3D::Unit(2), Point3D( 2, 1, -2 ) );
    oVector *= oTransform;
    if( HVector3D( 1, 0, 3 ) != oVector )
    {
        return UnitTest::Fail( "Z-rotating about (2,1,-2) by pi/2 radians failed" );
    }
    oVector /= oTransform;
    if( HVector3D( 1, 2, 3 ) != oVector )
    {
        return UnitTest::Fail( "Failed to undo z-rotating about (2,1,-2) by pi/2 radians" );
    }
    
    // Rotate by degrees about a point
    oTransform = DegreeRotation( 90, Point3D::Unit(0), Point3D( 2, 1, -2 ) );
    oVector *= oTransform;
    if( HVector3D( 1, -4, -1 ) != oVector )
    {
        return UnitTest::Fail( "X-rotating about (2,1,-2) by 90 degrees failed" );
    }
    oVector /= oTransform;
    if( HVector3D( 1, 2, 3 ) != oVector )
    {
        return UnitTest::Fail( "Failed to undo x-rotating about (2,1,-2) by 90 degrees" );
    }
    oTransform = DegreeRotation( 90, Point3D::Unit(1), Point3D( 2, 1, -2 ) );
    oVector *= oTransform;
    if( HVector3D( 7, 2, -1 ) != oVector )
    {
        return UnitTest::Fail( "Y-rotating about (2,1,-2) by 90 degrees failed" );
    }
    oVector /= oTransform;
    if( HVector3D( 1, 2, 3 ) != oVector )
    {
        return UnitTest::Fail( "Failed to undo y-rotating about (2,1,-2) by 90 degrees" );
    }
    oTransform = DegreeRotation( 90, Point3D::Unit(2), Point3D( 2, 1, -2 ) );
    oVector *= oTransform;
    if( HVector3D( 1, 0, 3 ) != oVector )
    {
        return UnitTest::Fail( "Z-rotating about (2,1,-2) by 90 degrees failed" );
    }
    oVector /= oTransform;
    if( HVector3D( 1, 2, 3 ) != oVector )
    {
        return UnitTest::Fail( "Failed to undo z-rotating about (2,1,-2) by 90 degrees" );
    }

    return UnitTest::PASS;
}

UnitTest::Result Matrix4x4TestGroup::Translate()
{
    // translate by a given amount in each direction
    HVector3D oVector( 1, 2, 3 );
    Transform3D oTransform = Translation( -2, 2, -1 );
    oVector *= oTransform;
    if( HVector3D( -1, 4, 2 ) != oVector )
    {
        return UnitTest::Fail( "Translating -2 y, 2 x, and -1 z up failed" );
    }
    oVector /= oTransform;
    if( HVector3D( 1, 2, 3 ) != oVector )
    {
        return UnitTest::Fail( "Failed to undo translating -2 y, 2 x, and -1 z" );
    }
    
    // translate by a vector
    oTransform = Translation( Point3D( 1, -3, 2 ) );
    oVector *= oTransform;
    if( HVector3D( 2, -1, 5 ) != oVector )
    {
        return UnitTest::Fail( "Translating by (1,-3,2) failed" );
    }
    oVector /= oTransform;
    if( HVector3D( 1, 2, 3 ) != oVector )
    {
        return UnitTest::Fail( "Failed to undo translating by (1,-3,2)" );
    }
    
    // translate at a given velocity for a given amount of time
    oTransform = Translation( 0.5, Point3D( 1, 1, -2 ) );
    oVector *= oTransform;
    if( HVector3D( 1.5, 2.5, 2 ) != oVector )
    {
        return UnitTest::Fail( "Translating with velocity (1,1,-2) for 0.5 units"
                               " of time failed" );
    }
    oVector /= oTransform;
    if( HVector3D( 1, 2, 3 ) != oVector )
    {
        return UnitTest::Fail( "Failed to undo translating with velocity (1,1,-2)"
                               " for 0.5 units of time" );
    }
    
    return UnitTest::PASS;
}

UnitTest::Result Matrix4x4TestGroup::PointScale()
{
    // Scale a non-homogeneous 2D vector by a uniform factor
    Point3D oVector( 1, 2, 3 );
    PointTransform3D oTransform = PointScaling( 0.5 );
    oVector *= oTransform;
    if( Point3D( 0.5, 1, 1.5 ) != oVector )
    {
        return UnitTest::Fail( "Scaling by a factor of 0.5 failed" );
    }
    oVector /= oTransform;
    if( Point3D( 1, 2, 3 ) != oVector )
    {
        return UnitTest::Fail( "Failed to undo scaling by a factor of 0.5" );
    }

    // Scale by different factors for each direction
    oTransform = PointScaling( 2, 0.5, -1 );
    oVector *= oTransform;
    if( Point3D( 2, 1, -3 ) != oVector )
    {
        return UnitTest::Fail( "Scaling by factors of 0.5 in the x direction"
                               " and 2 in the y direction failed" );
    }
    oVector /= oTransform;
    if( Point3D( 1, 2, 3 ) != oVector )
    {
        return UnitTest::Fail( "Failed to undo scaling by a factor of 0.5 in"
                               " the x direction and 2 in the y direction" );
    }

    // Scale by factors in each direction given by a vector
    oTransform = PointScaling( oVector );
    oVector *= oTransform;
    if( Point3D( 1, 4, 9 ) != oVector )
    {
        return UnitTest::Fail( "Scaling by a vector factor failed" );
    }
    oVector /= oTransform;
    if( Point3D( 1, 2, 3 ) != oVector )
    {
        return UnitTest::Fail( "Failed to undo scaling by a vector factor" );
    }
    
    return UnitTest::PASS;
}

UnitTest::Result Matrix4x4TestGroup::PointRotate()
{
    // Rotate by radians
    Point3D oVector( 1, 2, 3 );
    PointTransform3D oTransform = PointRotation( Math::PI / 2, Point3D::Unit(0) );
    oVector *= oTransform;
    if( Point3D( 1, -3, 2 ) != oVector )
    {
        return UnitTest::Fail( "Rotating about x-axis by pi/2 radians failed" );
    }
    oVector /= oTransform;
    if( Point3D( 1, 2, 3 ) != oVector )
    {
        return UnitTest::Fail( "Failed to undo rotating about x-axis by pi/2 radians" );
    }
    oTransform = PointRotation( Math::PI / 2, Point3D::Unit(1) );
    oVector *= oTransform;
    if( Point3D( 3, 2, -1 ) != oVector )
    {
        return UnitTest::Fail( "Rotating about y-axis by pi/2 radians failed" );
    }
    oVector /= oTransform;
    if( Point3D( 1, 2, 3 ) != oVector )
    {
        return UnitTest::Fail( "Failed to undo rotating about y-axis by pi/2 radians" );
    }
    oTransform = PointRotation( Math::PI / 2, Point3D::Unit(2) );
    oVector *= oTransform;
    if( Point3D( -2, 1, 3 ) != oVector )
    {
        return UnitTest::Fail( "Rotating about z-axis by pi/2 radians failed" );
    }
    oVector /= oTransform;
    if( Point3D( 1, 2, 3 ) != oVector )
    {
        return UnitTest::Fail( "Failed to undo rotating about z-axis by pi/2 radians" );
    }

    // Rotate by degrees
    oTransform = PointDegreeRotation( 90, Point3D::Unit(0) );
    oVector *= oTransform;
    if( Point3D( 1, -3, 2 ) != oVector )
    {
        return UnitTest::Fail( "Rotating about x-axis by 90 degrees failed" );
    }
    oVector /= oTransform;
    if( Point3D( 1, 2, 3 ) != oVector )
    {
        return UnitTest::Fail( "Failed to undo rotating about x-axis by 90 degrees" );
    }
    oTransform = PointDegreeRotation( 90, Point3D::Unit(1) );
    oVector *= oTransform;
    if( Point3D( 3, 2, -1 ) != oVector )
    {
        return UnitTest::Fail( "Rotating about y-axis by 90 degrees failed" );
    }
    oVector /= oTransform;
    if( Point3D( 1, 2, 3 ) != oVector )
    {
        return UnitTest::Fail( "Failed to undo rotating about y-axis by 90 degrees" );
    }
    oTransform = PointDegreeRotation( 90, Point3D::Unit(2) );
    oVector *= oTransform;
    if( Point3D( -2, 1, 3 ) != oVector )
    {
        return UnitTest::Fail( "Rotating about z-axis by 90 degrees failed" );
    }
    oVector /= oTransform;
    if( Point3D( 1, 2, 3 ) != oVector )
    {
        return UnitTest::Fail( "Failed to undo rotating about z-axis by 90 degrees" );
    }
    
    return UnitTest::PASS;
}

UnitTest::Result Matrix4x4TestGroup::Multiply()
{
    // set up some matrices in advance
    double aad4Square[4][4] = { { 1, 2, 3, 4 },
                                { 5, 6, 7, 8 },
                                { 9, 10, 11, 12 },
                                { 13, 14, 15, 16 } };
    Matrix< double, 4 > o4Square( aad4Square );
    // Left-inverse: A^-1 = (A^T*A)^-1*A^T
    // {{0,2,1},{0,0,-1},{-2,1,0},{2,0,0}}^-1
    //  = ({{0,0,-2,2},{2,0,1,0},{1,-1,0,0}}{{0,2,1},{0,0,-1},{-2,1,0},{2,0,0}})^-1*A^T
    //  = {{8,-2,0},{-2,5,2},{0,2,2}}^-1*{{0,0,-2,2},{2,0,1,0},{1,-1,0,0}}
    //  = {{0.15,0.1,-0.1},{0.1,0.4,-0.4},{-0.1,-0.4,0.9}}{{0,0,-2,2},{2,0,1,0},{1,-1,0,0}}
    //  = {{0.1,0.1,-0.2,0.3},{0.4,0.4,0.2,0.2},{0.1,-0.9,-0.2,-0.2}}
    double aad4x3[4][3] = { { 0, 2, 1 },
                            { 0, 0, -1 },
                            { -2, 1, 0 },
                            { 2, 0, 0 } };
    Matrix< double, 4, 3 > o4x3( aad4x3 );
    double aad3Square[3][3] = { { 0, 1, 0 }, { 1, 0, 0 }, { 0, 0, -1 } };
    Matrix< double, 3 > o3Square( aad3Square );

    // multiply square matrices
    double aad4Start[4][4] = { { 0, 1, 0, 0 },
                               { 1, 0, 0, 0 },
                               { 0, 0, 0, -1 },
                               { 0, 0, -1, 0 } };   // inverse is the same
    Matrix< double, 4 > oMatrix1( aad4Start );
    if( Matrix< double, 4 >::Identity() != oMatrix1 / oMatrix1 )
    {
        return UnitTest::Fail( "3x3 times inverse not equal to identity" );
    }
    oMatrix1 *= o4Square;
    double aadExpected1[4][4] = { { 5, 6, 7, 8 },
                                  { 1, 2, 3, 4 },
                                  { -13, -14, -15, -16 },
                                  { -9, -10, -11, -12 } };
    if( Matrix< double, 4 >( aadExpected1 ) != oMatrix1 )
    {
        return UnitTest::Fail( "4x4 multiplication failed" );
    }
    oMatrix1 /= Matrix< double, 4 >( aad4Start );
    double aadExpected2[4][4] = { { 6, 5, -8, -7 },
                                  { 2, 1, -4, -3 },
                                  { -14, -13, 16, 15 },
                                  { -10, -9, 12, 11 } };
    if( Matrix< double, 4 >( aadExpected2 ) != oMatrix1 )
    {
        return UnitTest::Fail( "4x4 division failed" );
    }
    double aad3Start[3][3] = { { 2, 0, 0 }, { 0, 0, -4 }, { 0, -4, 0 } };
    Matrix< double, 3 > oMatrix2( aad3Start );
    if( Matrix< double, 3 >::Identity() != oMatrix2 / oMatrix2 )
    {
        return UnitTest::Fail( "2x2 times inverse not equal to identity" );
    }
    oMatrix2 *= o3Square;
    double aadExpected3[3][3] = { { 0, 2, 0 }, { 0, 0, 4 }, { -4, 0, 0 } };
    if( Matrix< double, 3 >( aadExpected3 ) != oMatrix2 )
    {
        return UnitTest::Fail( "3x3 multiplication failed" );
    }
    oMatrix2 /= Matrix< double, 3 >( aad3Start );
    // {{2,0,0},{0,0,-4},{0,-4,0}}^-1 = {{0.5,0,0},{0,0,-0.25},{0,-0.25,0}}
    double aadExpected4[3][3] = { { 0, 0, -0.5 }, { 0, -1, 0 }, { -2, 0, 0 } };
    if( Matrix< double, 3 >( aadExpected4 ) != oMatrix2 )
    {
        return UnitTest::Fail( "3x3 division failed" );
    }
    
    // multiply square with non-square matrix
    Matrix< double, 4, 3 > oMatrix3 = o4Square * o4x3;
    double aadExpected5[4][3] = { { 2, 5, -1 },
                                  { 2, 17, -1 },
                                  { 2, 29, -1 },
                                  { 2, 41, -1 } };
    if( Matrix< double, 4, 3 >( aadExpected5 ) != oMatrix3 )
    {
        return UnitTest::Fail( "4x4 times 4x3 multiplication failed" );
    }
    oMatrix3 /= o3Square;
    double aadExpected6[4][3] = { { 5, 2, 1 },
                                  { 17, 2, 1 },
                                  { 29, 2, 1 },
                                  { 41, 2, 1 } };
    if( Matrix< double, 4, 3 >( aadExpected6 ) != oMatrix3 )
    {
        return UnitTest::Fail( "4x3 over 3x3 division failed" );
    }
    Matrix< double, 3, 4 > oMatrix4 = 10 * o3Square / o4x3; // *10 to avoid truncation
    double aadExpected7[3][4] = { { 0.4, 0.4, 0.2, 0.2 },
                                  { 0.1, 0.1, -0.2, 0.3 },
                                  { -0.1, 0.9, 0.2, 0.2 } };
    if( Matrix< double, 3, 4 >( aadExpected7 ) != oMatrix4.Round() / 10 )
    {
        return UnitTest::Fail( "3x3 over 4x3 division failed" );
    }
    oMatrix4 *= o4Square;
    double aadExpected8[3][4] = { { 6.8, 8, 9.2, 10.4 },
                                  { 2.7, 3, 3.3, 3.6 },
                                  { 8.8, 10, 11.2, 12.4 } };
    if( Matrix< double, 3, 4 >( aadExpected8 ) != oMatrix4.Round() / 10 )
    {
        return UnitTest::Fail( "3x4 times 4x4 multiplication failed" );
    }

    // multiply non-square matrices//{{5,2,1},{17,2,1},{29,2,1},{41,2,1}}{{6.8,8,9.2,10.4},{2.7,3,3.3,3.6},{8.8,10,11.2,12.4}}
    double aadExpected9[4][4] = { { 48.2, 56, 63.8, 71.6 },
                                  { 129.8, 152, 174.2, 196.4 },
                                  { 211.4, 248, 284.6, 321.2 },
                                  { 293, 344, 395, 446 } };
    if( Matrix< double, 4 >( aadExpected9 ) != oMatrix3 * oMatrix4 / 10 )
    {
        return UnitTest::Fail( "4x3 times 3x4 multiplication failed" );
    }
    double aadExpected10[3][3] = { { 863.2, 68.8, 34.4 },
                                   { 307.8, 25.2, 12.6 },
                                   { 1047.2, 84.8, 42.4 } };
    if( Matrix< double, 3 >( aadExpected10 ) != oMatrix4 * oMatrix3 / 10 )
    {
        return UnitTest::Fail( "3x4 times 4x3 multiplication failed" );
    }

    // Verify pseudo-inverse properties
    if(  ( o4x3 / o4x3 * o4x3 ).Round() != o4x3 )
    {
        return UnitTest::Fail( "4x3 pseudo-inverse not mapping all column"
                               " vectors to themselves" );
    }
    if( ( 10 * o4x3.Inverse() * o4x3 / o4x3 ).Round() != ( o4x3.Inverse() * 10 ).Round() )
    {
        return UnitTest::Fail( "4x3 pseudo-inverse not a weak inverse for the"
                               " multiplicative semigroup" );
    }
    if( !( o4x3 / o4x3 ).IsHermitian() )
    {
        return UnitTest::Fail( "4x3 times pseudo-inverse not Hermitian" );
    }
    if( !( o4x3.Inverse() * o4x3 ).Round().IsHermitian() )
    {
        return UnitTest::Fail( "pseudo-inverse times 4x3 not Hermitian" );
    }
    
    return UnitTest::PASS;
}