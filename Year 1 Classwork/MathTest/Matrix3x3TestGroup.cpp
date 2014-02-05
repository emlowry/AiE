/******************************************************************************
 * File:               Matrix3x3TestGroup.cpp
 * Author:             Elizabeth Lowry
 * Date Created:       January 5, 2014
 * Description:        3x3 Matrix tests.
 * Last Modified:      February 5, 2014
 * Last Modification:  Refactoring.
 ******************************************************************************/

#include "Matrix3x3TestGroup.h"
#include "MathLibrary.h"

using namespace Plane;
using Math::Matrix;

Matrix3x3TestGroup::Matrix3x3TestGroup()
    : UnitTestGroup("3x3 Matrix tests")
{
    AddTest( "HVector scale transformation", Scale );
    AddTest( "HVector rotation ", Rotate );
    AddTest( "HVector translation ", Translate );
    AddTest( "Point scale transformation", PointScale );
    AddTest( "Point rotation", PointRotate );
    AddTest( "Matrix multiplication", Multiply );
}

UnitTest::Result Matrix3x3TestGroup::Scale()
{
    // Scale a non-homogeneous 2D vector by a uniform factor
    HVector2D oVector( 1, 2 );
    Transform2D oTransform = Scaling( 0.5 );
    oVector *= oTransform;
    if( HVector2D( 0.5, 1 ) != oVector )
    {
        return UnitTest::Fail( "Scaling by a factor of 0.5 failed" );
    }
    oVector /= oTransform;
    if( HVector2D( 1, 2 ) != oVector )
    {
        return UnitTest::Fail( "Failed to undo scaling by a factor of 0.5" );
    }

    // Scale by different factors for each direction
    oTransform = Scaling( 2, 0.5 );
    oVector *= oTransform;
    if( HVector2D( 2, 1 ) != oVector )
    {
        return UnitTest::Fail( "Scaling by factors of 0.5 in the x direction"
                               " and 2 in the y direction failed" );
    }
    oVector /= oTransform;
    if( HVector2D( 1, 2 ) != oVector )
    {
        return UnitTest::Fail( "Failed to undo scaling by a factor of 0.5 in"
                               " the x direction and 2 in the y direction" );
    }

    // Scale by factors in each direction given by a vector
    oTransform = Scaling( oVector );
    oVector *= oTransform;
    if( HVector2D( 1, 4 ) != oVector )
    {
        return UnitTest::Fail( "Scaling by a vector factor failed" );
    }
    oVector /= oTransform;
    if( HVector2D( 1, 2 ) != oVector )
    {
        return UnitTest::Fail( "Failed to undo scaling by a vector factor" );
    }
    
    // Scale a non-homogeneous 2D vector about a point by a uniform factor
    oTransform = Scaling( 0.5, Point2D( 2, 1 ) );
    oVector *= oTransform;
    if( HVector2D( 1.5, 1.5 ) != oVector )
    {
        return UnitTest::Fail( "Scaling by a factor of 0.5 failed" );
    }
    oVector /= oTransform;
    if( HVector2D( 1, 2 ) != oVector )
    {
        return UnitTest::Fail( "Failed to undo scaling by a factor of 0.5" );
    }

    // Scale about a point by different factors for each direction
    oTransform = Scaling( 2, 0.5, Point2D( 2, 1 ) );
    oVector *= oTransform;
    if( HVector2D( 0, 1.5 ) != oVector )
    {
        return UnitTest::Fail( "Scaling by factors of 0.5 in the x direction"
                               " and 2 in the y direction failed" );
    }
    oVector /= oTransform;
    if( HVector2D( 1, 2 ) != oVector )
    {
        return UnitTest::Fail( "Failed to undo scaling by a factor of 0.5 in"
                               " the x direction and 2 in the y direction" );
    }

    // Scale about a point by factors in each direction given by a vector
    oTransform = Scaling( oVector, Point2D( 2, 1 ) );
    oVector *= oTransform;
    if( HVector2D( 1, 3 ) != oVector )
    {
        return UnitTest::Fail( "Scaling by a vector factor failed" );
    }
    oVector /= oTransform;
    if( HVector2D( 1, 2 ) != oVector )
    {
        return UnitTest::Fail( "Failed to undo scaling by a vector factor" );
    }
    
    return UnitTest::PASS;
}

UnitTest::Result Matrix3x3TestGroup::Rotate()
{
    // Rotate by radians
    HVector2D oVector( 1, 2 );
    Transform2D oTransform = Rotation( Math::PI / 2 );
    oVector *= oTransform;
    if( HVector2D( -2, 1 ) != oVector )
    {
        return UnitTest::Fail( "Rotating by pi/2 radians failed" );
    }
    oVector /= oTransform;
    if( HVector2D( 1, 2 ) != oVector )
    {
        return UnitTest::Fail( "Failed to undo rotating by pi/2 radians" );
    }

    // Rotate by degrees
    oTransform = DegreeRotation( 90 );
    oVector *= oTransform;
    if( HVector2D( -2, 1 ) != oVector )
    {
        return UnitTest::Fail( "Rotating by 90 degrees failed" );
    }
    oVector /= oTransform;
    if( HVector2D( 1, 2 ) != oVector )
    {
        return UnitTest::Fail( "Failed to undo rotating by 90 degrees" );
    }
    
    // Rotate by radians about a point
    oTransform = Rotation( Math::PI / 2, Point2D( 2, 1 ) );
    oVector *= oTransform;
    if( HVector2D( 1, 0 ) != oVector )
    {
        return UnitTest::Fail( "Rotating about (2,1) by pi/2 radians failed" );
    }
    oVector /= oTransform;
    if( HVector2D( 1, 2 ) != oVector )
    {
        return UnitTest::Fail( "Failed to undo rotating about (2,1) by pi/2 radians" );
    }

    // Rotate by degrees about a point
    oTransform = DegreeRotation( 90, Point2D( 2, 1 ) );
    oVector *= oTransform;
    if( HVector2D( 1, 0 ) != oVector )
    {
        return UnitTest::Fail( "Rotating about (2,1) by 90 degrees failed" );
    }
    oVector /= oTransform;
    if( HVector2D( 1, 2 ) != oVector )
    {
        return UnitTest::Fail( "Failed to undo rotating about (2,1) by 90 degrees" );
    }

    return UnitTest::PASS;
}

UnitTest::Result Matrix3x3TestGroup::Translate()
{
    // translate by a given amount in each direction
    HVector2D oVector( 1, 2 );
    Transform2D oTransform = Translation( -2, 2 );
    oVector *= oTransform;
    if( HVector2D( -1, 4 ) != oVector )
    {
        return UnitTest::Fail( "Translating 2 left and 2 up failed" );
    }
    oVector /= oTransform;
    if( HVector2D( 1, 2 ) != oVector )
    {
        return UnitTest::Fail( "Failed to undo translating 2 left and 2 up" );
    }
    
    // translate by a vector
    oTransform = Translation( Point2D( 1, -3 ) );
    oVector *= oTransform;
    if( HVector2D( 2, -1 ) != oVector )
    {
        return UnitTest::Fail( "Translating by (1,-3) failed" );
    }
    oVector /= oTransform;
    if( HVector2D( 1, 2 ) != oVector )
    {
        return UnitTest::Fail( "Failed to undo translating by (1,-3)" );
    }
    
    // translate at a given velocity for a given amount of time
    oTransform = Translation( 0.5, Point2D( 1, 1 ) );
    oVector *= oTransform;
    if( HVector2D( 1.5, 2.5 ) != oVector )
    {
        return UnitTest::Fail( "Translating with velocity (1,1) for 0.5 units"
                               " of time failed" );
    }
    oVector /= oTransform;
    if( HVector2D( 1, 2 ) != oVector )
    {
        return UnitTest::Fail( "Failed to undo translating with velocity (1,1)"
                               " for 0.5 units of time" );
    }

    return UnitTest::PASS;
}

UnitTest::Result Matrix3x3TestGroup::PointScale()
{
    // Scale a non-homogeneous 2D vector by a uniform factor
    Point2D oVector( 1, 2 );
    PointTransform2D oTransform = PointScaling( 0.5 );
    oVector *= oTransform;
    if( Point2D( 0.5, 1 ) != oVector )
    {
        return UnitTest::Fail( "Scaling by a factor of 0.5 failed" );
    }
    oVector /= oTransform;
    if( Point2D( 1, 2 ) != oVector )
    {
        return UnitTest::Fail( "Failed to undo scaling by a factor of 0.5" );
    }

    // Scale by different factors for each direction
    oTransform = PointScaling( 2, 0.5 );
    oVector *= oTransform;
    if( Point2D( 2, 1 ) != oVector )
    {
        return UnitTest::Fail( "Scaling by factors of 0.5 in the x direction"
                               " and 2 in the y direction failed" );
    }
    oVector /= oTransform;
    if( Point2D( 1, 2 ) != oVector )
    {
        return UnitTest::Fail( "Failed to undo scaling by a factor of 0.5 in"
                               " the x direction and 2 in the y direction" );
    }

    // Scale by factors in each direction given by a vector
    oTransform = PointScaling( oVector );
    oVector *= oTransform;
    if( Point2D( 1, 4 ) != oVector )
    {
        return UnitTest::Fail( "Scaling by a vector factor failed" );
    }
    oVector /= oTransform;
    if( Point2D( 1, 2 ) != oVector )
    {
        return UnitTest::Fail( "Failed to undo scaling by a vector factor" );
    }
    
    return UnitTest::PASS;
}

UnitTest::Result Matrix3x3TestGroup::PointRotate()
{
    // Rotate by radians
    Point2D oVector( 1, 2 );
    PointTransform2D oTransform = PointRotation( Math::PI / 2 );
    oVector *= oTransform;
    if( Point2D( -2, 1 ) != oVector )
    {
        return UnitTest::Fail( "Rotating by pi/2 radians failed" );
    }
    oVector /= oTransform;
    if( Point2D( 1, 2 ) != oVector )
    {
        return UnitTest::Fail( "Failed to undo rotating by pi/2 radians" );
    }

    // Rotate by degrees
    oTransform = PointDegreeRotation( 90 );
    oVector *= oTransform;
    if( Point2D( -2, 1 ) != oVector )
    {
        return UnitTest::Fail( "Rotating by 90 degrees failed" );
    }
    oVector /= oTransform;
    if( Point2D( 1, 2 ) != oVector )
    {
        return UnitTest::Fail( "Failed to undo rotating by 90 degrees" );
    }

    return UnitTest::PASS;
}

UnitTest::Result Matrix3x3TestGroup::Multiply()
{
    // set up some matrices in advance
    double aad3Square[3][3] = { { 1, 2, 3 }, { 4, 5, 6 }, { 7, 8, 9 } };
    Matrix< double, 3 > o3Square( aad3Square );
    double aad3x2[3][2] = { { 0, 2 }, { 0, 0 }, { -1, -2 } };
    Matrix< double, 3, 2 > o3x2( aad3x2 );
    double aad2Square[2][2] = { { 1, 2 }, { 3, 4 } };
    Matrix< double, 2 > o2Square( aad2Square );

    // multiply square matrices
    double aad3Start[3][3] = { { 0, 1, 0 }, { 1, 0, 0 }, { 0, 0, -1 } };
    Matrix< double, 3 > oMatrix1( aad3Start );
    if( Matrix< double, 3 >::Identity() != oMatrix1 / oMatrix1 )
    {
        return UnitTest::Fail( "3x3 times inverse not equal to identity" );
    }
    oMatrix1 *= o3Square;
    double aadExpected1[3][3] = { { 4, 5, 6 }, { 1, 2, 3 }, { -7, -8, -9 } };
    if( Matrix< double, 3 >( aadExpected1 ) != oMatrix1 )
    {
        return UnitTest::Fail( "3x3 multiplication failed" );
    }
    oMatrix1 /= Matrix< double, 3 >( aad3Start );
    // {{0,1,0},{1,0,0},{0,0,-1}}^1 = {{0,1,0},{1,0,0},{0,0,-1}}
    double aadExpected2[3][3] = { { 5, 4, -6 }, { 2, 1, -3 }, { -8, -7, 9 } };
    if( Matrix< double, 3 >( aadExpected2 ) != oMatrix1 )
    {
        return UnitTest::Fail( "3x3 division failed" );
    }
    double aad2Start[2][2] = { { 5, 6 }, { 7, 8 } };
    Matrix< double, 2 > oMatrix2( aad2Start );
    if( Matrix< double, 2 >::Identity() != oMatrix2 / oMatrix2 )
    {
        return UnitTest::Fail( "2x2 times inverse not equal to identity" );
    }
    oMatrix2 *= o2Square;
    double aadExpected3[2][2] = { { 23, 34 }, { 31, 46 } };
    if( Matrix< double, 2 >( aadExpected3 ) != oMatrix2 )
    {
        return UnitTest::Fail( "2x2 multiplication failed" );
    }
    oMatrix2 /= Matrix< double, 2 >( aad2Start );
    // {{5,6},{7,8}}^-1 = {{-4,3},{3.5,-2.5}}
    double aadExpected4[2][2] = { { 27, -16 }, { 37, -22 } };
    if( Matrix< double, 2 >( aadExpected4 ) != oMatrix2 )
    {
        return UnitTest::Fail( "2x2 division failed" );
    }

    // multiply square with non-square matrix
    Matrix< double, 3, 2 > oMatrix3 = o3Square * o3x2;
    double aadExpected5[3][2] = { { -3, -4 }, { -6, -4 }, { -9, -4 } };
    if( Matrix< double, 3, 2 >( aadExpected5 ) != oMatrix3 )
    {
        return UnitTest::Fail( "3x3 times 3x2 multiplication failed" );
    }
    oMatrix3 /= o2Square;
    // {{1,2},{3,4}}^-1 = {{-2,1},{1.5,-0.5}}
    double aadExpected6[3][2] = { { 0, -1 }, { 6, -4 }, { 12, -7 } };
    if( Matrix< double, 3, 2 >( aadExpected6 ) != oMatrix3 )
    {
        return UnitTest::Fail( "3x2 over 2x2 division failed" );
    }
    Matrix< double, 2, 3 > oMatrix4 = o2Square / o3x2;
    // {{0,2},{0,0},{-1,-2}}^-1 = {{-1,0,-1},{0.5,0,0}}
    double aadExpected7[2][3] = { { 0, 0, -1 }, { -1, 0, -3 } };
    if( Matrix< double, 2, 3 >( aadExpected7 ) != oMatrix4 )
    {
        return UnitTest::Fail( "2x2 over 3x2 division failed" );
    }
    oMatrix4 *= o3Square;
    double aadExpected8[2][3] = { { -7, -8, -9 }, { -22, -26, -30 } };
    if( Matrix< double, 2, 3 >( aadExpected8 ) != oMatrix4 )
    {
        return UnitTest::Fail( "2x3 times 3x3 multiplication failed" );
    }

    // multiply non-square matrices
    double aadExpected9[3][3] = { { 22, 26, 30 }, { 46, 56, 66 }, { 70, 86, 102 } };
    if( Matrix< double, 3 >( aadExpected9 ) != oMatrix3 * oMatrix4 )
    {
        return UnitTest::Fail( "3x2 times 2x3 multiplication failed" );
    }
    double aadExpected10[2][2] = { { -156, 102 }, { -516, 336 } };
    if( Matrix< double, 2 >( aadExpected10 ) != oMatrix4 * oMatrix3 )
    {
        return UnitTest::Fail( "2x3 times 3x2 multiplication failed" );
    }

    // Verify pseudo-inverse properties
    if(  o3x2 / o3x2 * o3x2 != o3x2 )
    {
        return UnitTest::Fail( "3x2 pseudo-inverse not mapping all column"
                               " vectors to themselves" );
    }
    if( o3x2.Inverse() * o3x2 / o3x2 != o3x2.Inverse() )
    {
        return UnitTest::Fail( "3x2 pseudo-inverse not a weak inverse for the"
                               " multiplicative semigroup" );
    }
    if( !( o3x2 / o3x2 ).IsHermitian() )
    {
        return UnitTest::Fail( "3x2 times pseudo-inverse not Hermitian" );
    }
    if( !( o3x2.Inverse() * o3x2 ).IsHermitian() )
    {
        return UnitTest::Fail( "pseudo-inverse times 3x2 not Hermitian" );
    }

    return UnitTest::PASS;
}