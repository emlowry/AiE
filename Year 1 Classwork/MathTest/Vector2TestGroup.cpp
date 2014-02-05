/******************************************************************************
 * File:               Vector2TestGroup.cpp
 * Author:             Elizabeth Lowry
 * Date Created:       January 5, 2014
 * Description:        Vector2 tests.
 * Last Modified:      February 5, 2014
 * Last Modification:  Refactoring.
 ******************************************************************************/

#include "Vector2TestGroup.h"
#include "MathLibrary.h"
#include <string>
#include <sstream>

Vector2TestGroup::Vector2TestGroup()
    : UnitTestGroup("Vector2 tests")
{
    AddTest( "Dot Product", DotProduct );
    AddTest( "Normalization", Normalization );
    AddTest( "Cross product", CrossProduct );
    AddTest( "Magnitude", Magnitude );
    AddTest( "Operator overrides", Operators );
    AddTest( "Addition, subtraction, negation, and modulo operator overrides",
             Arithmatic );
    AddTest( "Multiplication operator overrides", Multiplication );
    AddTest( "Division operator overrides", Division );
    AddTest( "Division by zero", DivisionByZero );
    AddTest( "Interpolation", Interpolation );
}

UnitTest::Result Vector2TestGroup::DotProduct()
{
    // perpendicular vectors have dot product of 0
    double dDot = Point2D::Unit(0).Dot( Point2D::Unit(1) );
    if( dDot != 0 )
    {
        return UnitTest::Fail( "Perpendicular vectors with non-zero dot product" );
    }

    // identical vectors have dot product of magnitude squared
    Point2D oVector( 3, 4 );
    dDot = oVector.Dot( oVector );
    if( dDot != oVector.MagnitudeSquared() )
    {
        return UnitTest::Fail( "Identical vectors with dot product not equal to"
                               " magnitude squared" );
    }

    // dot product of two vectors gives projection of one vector onto the other
    // times said other's magnitude
    Point2D oXAxis( 2, 0 );
    dDot = oVector.Dot( oXAxis );
    if( dDot != oVector.x * oXAxis.Magnitude() )
    {
        return UnitTest::Fail( "Dot product of two vectors not equal to"
                               " projection of first onto second times"
                               " magnitude of second" );
    }
    
    return UnitTest::PASS;
}

UnitTest::Result Vector2TestGroup::Normalization()
{
    Point2D oVector( 3, 4 );
    oVector.Normalize();

    // check values
    if( oVector != Point2D( 0.6, 0.8 ) )
    {
        return UnitTest::Fail( "Normalized vector has wrong values" );
    }

    // Normalized vector has magnitude of 1
    if( oVector.Magnitude() != 1.0 )
    {
        return UnitTest::Fail( "Normalized vector has magnitude other than 1" );
    }
    
    return UnitTest::PASS;
}

UnitTest::Result Vector2TestGroup::CrossProduct()
{
    // The cross product for vectors of size N requires N-2 additional vectors
    // as parameters.  Since Visual Studio 2010 doesn't implement variadic
    // templates, this means one parameter is given for this function - which is
    // ignored for N = 2.  In 2D space, "cross product" just means "this vector,
    // rotated 90 degrees".  You'd get the same thing by crossing a 3D version
    // of this vector with the z-axis.

    // Confirm that "cross product" is perpendicular for different vectors
    Point2D aoVectors[8] = {
        Point2D::Unit(0),
        Point2D::Unit(1),
        -Point2D::Unit(0),
        -Point2D::Unit(1),
        Point2D( 1, 2 ),
        Point2D( -3, 4 ),
        Point2D( -5.6, -7.8 ),
        Point2D( 9.0, -1.2 )
    };
    Point2D aoExpected[8] = {
        -Point2D::Unit(1),
        Point2D::Unit(0),
        Point2D::Unit(1),
        -Point2D::Unit(0),
        Point2D( 2, -1 ),
        Point2D( 4, 3 ),
        Point2D( -7.8, 5.6 ),
        Point2D( -1.2, -9.0 )
    };
    for( unsigned int ui = 0; ui < 8; ++ui )
    {
        if( aoVectors[ui].Cross() != aoExpected[ui] )
        {
            std::ostringstream oSStream;
            oSStream << "2D \"cross product\" for " << aoVectors[ui]
                     << " other than " << aoExpected[ui];
            return UnitTest::Fail( oSStream.str() );
        }
    }

    // Confirm that result is the same no matter what the parameter value is
    for( unsigned int ui = 0; ui < 8; ++ui )
    {
        if( Point2D::Unit(0).Cross( aoVectors[ui] ) != -Point2D::Unit(1) )
        {
            std::ostringstream oSStream;
            oSStream << "2D \"cross product\" for X-axis other than negative"
                     << " Y-axis when " << aoVectors[ui]
                     << " is given as the parameter";
            return UnitTest::Fail( oSStream.str() );
        }
    }

    return UnitTest::PASS;
}

UnitTest::Result Vector2TestGroup::Magnitude()
{
    // Unit vectors have magnitude of 1
    if( Point2D::Unit(0).Magnitude() != 1.0 )
    {
        return UnitTest::Fail( "X-axis unit vector has magnitude other than 1" );
    }
    if( Point2D::Unit(1).Magnitude() != 1.0 )
    {
        return UnitTest::Fail( "Y-axis unit vector has magnitude other than 1" );
    }
    if( Point2D::Unit(0).MagnitudeSquared() != 1.0 )
    {
        return UnitTest::Fail( "X-axis unit vector has squared magnitude other than 1" );
    }
    if( Point2D::Unit(1).MagnitudeSquared() != 1.0 )
    {
        return UnitTest::Fail( "Y-axis unit vector has squared magnitude other than 1" );
    }

    // Negative Unit vectors have magnitude of 1
    if( ( -Point2D::Unit(0) ).Magnitude() != 1.0 )
    {
        return UnitTest::Fail( "Negative X-axis unit vector has magnitude other than 1" );
    }
    if( ( -Point2D::Unit(1) ).Magnitude() != 1.0 )
    {
        return UnitTest::Fail( "Negative Y-axis unit vector has magnitude other than 1" );
    }
    if( ( -Point2D::Unit(0) ).MagnitudeSquared() != 1.0 )
    {
        return UnitTest::Fail( "Negative X-axis unit vector has squared magnitude other than 1" );
    }
    if( ( -Point2D::Unit(1) ).MagnitudeSquared() != 1.0 )
    {
        return UnitTest::Fail( "Negative Y-axis unit vector has squared magnitude other than 1" );
    }

    // Zero vector has magnitude of 0
    if( Point2D::Zero().Magnitude() != 0.0 )
    {
        return UnitTest::Fail( "Zero vector has magnitude other than 0" );
    }
    if( Point2D::Zero().MagnitudeSquared() != 0.0 )
    {
        return UnitTest::Fail( "Zero vector has squared magnitude other than 0" );
    }

    // Pythagorean theorem holds
    if( Point2D( 3, 4 ).Magnitude() != 5.0 )
    {
        return UnitTest::Fail( "Magnitude inconsistant with Pythagorean Theorem" );
    }
    if( Point2D( 3, 4 ).MagnitudeSquared() != 25.0 )
    {
        return UnitTest::Fail( "Squared magnitude inconsistant with Pythagorean Theorem" );
    }

    return UnitTest::PASS;
}

UnitTest::Result Vector2TestGroup::Operators()
{
    // Element access
    Point2D oVector( 1, 1 );
    if( oVector[0] != 1.0 )
    {
        return UnitTest::Fail( "Element access operator failed" );
    }
    oVector[1] = 2;
    if( oVector[1] != 2.0 )
    {
        return UnitTest::Fail( "Assignment through element access operator failed" );
    }
    try
    {
        oVector[2] = 3;
        return UnitTest::Fail( "Out of range element access didn't throw error" );
    }
    catch( ... ) {}

    // (In)Equality
    if( !( oVector == Point2D( 1, 2 ) ) )
    {
        return UnitTest::Fail( "Equality operator failed to return true" );
    }
    if( oVector == Point2D( -1, -2 ) )
    {
        return UnitTest::Fail( "Equality operator failed to return false" );
    }
    if( !( oVector != Point2D( -1, -2 ) ) )
    {
        return UnitTest::Fail( "Inequality operator failed to return true" );
    }
    if( oVector != Point2D( 1, 2 ) )
    {
        return UnitTest::Fail( "Inequality operator failed to return false" );
    }

    // Stream output
    std::ostringstream oOut;
    oOut << Math::Vector< int, 2 >( oVector );  // no floating-point formatting
    if( oOut.str() != "{ { 1, 2 } }" )
    {
        return UnitTest::Fail( "Stream output operator did not perform as expected" );
    }
    
    return UnitTest::PASS;
}

UnitTest::Result Vector2TestGroup::Arithmatic()
{
    // Addition
    if( Point2D( 1, 2 ) + Point2D( 3, 4 ) != Point2D( 4, 6 ) )
    {
        return UnitTest::Fail( "Addition operator failed" );
    }
    Point2D oVector( 1, 2 );
    oVector += Point2D( 3, 4 );
    if( Point2D( 4, 6 ) != oVector )
    {
        return UnitTest::Fail( "Add-assign operator failed" );
    }
    
    // Subtraction
    if( Point2D( 1, 2 ) - Point2D( 3, 4 ) != Point2D( -2, -2 ) )
    {
        return UnitTest::Fail( "Subtraction operator failed" );
    }
    oVector -= Point2D( 3, 4 );
    if( Point2D( 1, 2 ) != oVector )
    {
        return UnitTest::Fail( "Subtract-assign operator failed" );
    }

    // Unary negation operator
    if( -Point2D( 1, 2 ) != Point2D( -1, -2 ) )
    {
        return UnitTest::Fail( "Unary negation operator failed" );
    }

    // Modulo
    if( Point2D( 1, 2 ) % 2 != Point2D( 1, 0 ) )
    {
        return UnitTest::Fail( "Modulo operator failed" );
    }
    oVector %= 2;
    if( Point2D( 1, 0 ) != oVector )
    {
        return UnitTest::Fail( "Modulo-assign operator failed" );
    }

    return UnitTest::PASS;
}

UnitTest::Result Vector2TestGroup::Multiplication()
{
    // Scalar multiplication
    if( Point2D( 1, 2 ) * 3 != Point2D( 3, 6 ) )
    {
        return UnitTest::Fail( "Scalar multiplication operator failed" );
    }
    if( 4 * Point2D( 5, 6 ) != Point2D( 20, 24 ) )
    {
        return UnitTest::Fail( "Scalar multiplication operator (other way) failed" );
    }
    Point2D oVector( 1, 2 );
    oVector *= 7;
    if( Point2D( 7, 14 ) != oVector )
    {
        return UnitTest::Fail( "Scalar multiply-assign operator failed" );
    }

    // Matrix multiplication
    double aadSquare[2][2] = { { 0, 1 }, { 1, 0 } };
    Math::Matrix< double, 2 > oSquare( aadSquare );
    if( Point2D( 1, 2 ) * oSquare != Point2D( 2, 1 ) )
    {
        return UnitTest::Fail( "Square matrix multiplication operator failed" );
    }
    oVector *= oSquare;
    if( Point2D( 14, 7 ) != oVector )
    {
        return UnitTest::Fail( "Square matrix multiply-assign operator failed" );
    }
    double aadNotSquare[2][3] = { { 0, 1, -1 }, { 1, 0, -1 } };
    Math::Matrix< double, 2, 3 > oNotSquare( aadNotSquare );
    if( Point2D( 1, 2 ) * oNotSquare != Point3D( 2, 1, -3 ) )
    {
        return UnitTest::Fail( "Non-square matrix multiplication operator failed" );
    }
    
    return UnitTest::PASS;
}

UnitTest::Result Vector2TestGroup::Division()
{
    // Scalar division
    if( Point2D( 1, 2 ) / 4 != Point2D( 0.25, 0.5 ) )
    {
        return UnitTest::Fail( "Scalar division operator failed" );
    }
    // Left-inverse: A^-1 = A^T*(A*A^T)^-1
    // {{1,2}}^-1 = {{1},{2}}({{1,2}}{{1},{2}})^-1 = {{1},{2}}{{5}}^-1
    //            = {{1},{2}}{{0.2}} = {{0.2},{0.4}}
    if( ( 10 / Point2D( 1, 2 ) ).Transpose() != Point2D( 2, 4 ) )
    {
        return UnitTest::Fail( "Scalar/right-invertable vector division failed" );
    }
    Point2D oVector( 1, 2 );
    oVector /= 4;
    if( Point2D( 0.25, 0.5 ) != oVector )
    {
        return UnitTest::Fail( "Scalar divide-assign operator failed" );
    }
    
    // Matrix division
    double aadSquare[2][2] = { { 1, 2 }, { 3, 4 } };
    Math::Matrix< double, 2 > oSquare( aadSquare );
    // {{1,2},{3,4}}^-1 = {{4,-2},{-3,1}}/det({{1,2},{3,4}})
    //                  = {{4,-2},{-3,1}}/(1*4-2*3) = {{4,-2},{-3,1}}/-2
    //                  = {{-2,1},{1.5,-0.5}}
    if( Point2D( 1, 2 ) / oSquare != Point2D( 1, 0 ) )
    {
        return UnitTest::Fail( "Square matrix division operator failed" );
    }
    oVector /= oSquare;
    if( Point2D( 0.25, 0 ) != oVector )
    {
        return UnitTest::Fail( "Square matrix divide-assign operator failed" );
    }
    double aadNotSquare[3][2] = { { 0, 0 }, { 2, 0 }, { -1, -2 } };
    Math::Matrix< double, 3, 2 > oNotSquare( aadNotSquare );
    // Left-inverse: A^-1 = (A^T*A)^-1*A^T
    // {{0,0},{2,0},{-1,-2}}^-1
    //              = ({{0,0,-1},{2,0,-2}}{{0,0},{2,0},{-1,-2}})^-1*{{0,0,-1},{2,0,-2}}
    //              = {{1,2},{2,8}}^-1*{{0,0,-1},{2,0,-2}}
    //              = {{8,-2},{-2,1}}/(8*1-2*2)*{{0,0,-1},{2,0,-2}}
    //              = {{8,-2},{-2,1}}{{0,0,-1},{2,0,-2}}/4
    //              = {{-4,0,-4},{2,0,0}}/4 = {{-1,0,-1},{0.5,0,0}}
    if( Point2D( 1, 2 ) / oNotSquare != Point3D( 0, 0, -1 ) )
    {
        return UnitTest::Fail( "Non-square matrix division operator failed" );
    }
    
    return UnitTest::PASS;
}

UnitTest::Result Vector2TestGroup::DivisionByZero()
{
    // Scalar division that should fail
    Point2D oVector( 1, 2 );
    try
    {
        oVector = Point2D( 1, 2 ) / 0;
        return UnitTest::Fail( "Divide by zero didn't throw error" );
    }
    catch( ... ) {}
    try
    {
        oVector /= 0;
        return UnitTest::Fail( "Divide-assign by zero didn't throw error" );
    }
    catch( ... ) {}
    try
    {
        oVector = ( 1 / Point2D::Zero() ).Transpose();
        return UnitTest::Fail( "Divide scalar by non-right-invertable vector"
                               " didn't throw error" );
    }
    catch( ... ) {}
    
    // Matrix division (multiplication by inverse) that should fail
    try
    {
        oVector = Point2D( 1, 2 ) / Math::Matrix< double, 2 >::Zero();
        return UnitTest::Fail( "Divide by non-invertable square matrix didn't"
                               " throw error" );
    }
    catch( ... ) {}
    try
    {
        oVector /= Math::Matrix< double, 2 >::Zero();
        return UnitTest::Fail( "Divide-assign by non-invertable square matrix"
                               " didn't throw error" );
    }
    catch( ... ) {}
    try
    {
        Point3D oVector3 = Point2D( 1, 2 ) / Math::Matrix< double, 3, 2 >::Zero();
        return UnitTest::Fail( "Divide by non-invertable non-square matrix"
                               " didn't throw error" );
    }
    catch( ... ) {}

    return UnitTest::PASS;
}

UnitTest::Result Vector2TestGroup::Interpolation()
{
    // Default interpolation
    if( Math::Interpolate( Point2D( 0, 0 ), Point2D( 1, 0 ) ) != Point2D( 0.5, 0 ) )
    {
        return UnitTest::Fail( "Incorrect default interpolation of (0,0) and (1,0)" );
    }
    if( Math::Interpolate( -Point2D::Unit(0), -Point2D::Unit(1) ) != Point2D( -0.5 ) )
    {
        return UnitTest::Fail( "Incorrect default interpolation of (-1,0) and (0,-1)" );
    }

    // Custom interpolation
    if( Math::Interpolate( Point2D( 0, 0 ), Point2D( 2, 4 ), 0.75 ) != Point2D( 1.5, 3 ) )
    {
        return UnitTest::Fail( "Incorrect 3/4 interpolation of (0,0) and (2,4)" );
    }
    if( Math::Interpolate( Point2D( 4, 3 ), Point2D( -2, 1 ), 0.75 ) != Point2D( -0.5, 1.5 ) )
    {
        return UnitTest::Fail( "Incorrect 3/4 interpolation of (4,3) and (-2,1)" );
    }

    return UnitTest::PASS;
}
