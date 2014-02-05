/******************************************************************************
 * File:               Vector3TestGroup.cpp
 * Author:             Elizabeth Lowry
 * Date Created:       January 5, 2014
 * Description:        Vector3 tests.
 * Last Modified:      February 5, 2014
 * Last Modification:  Refactoring.
 ******************************************************************************/

#include "Vector3TestGroup.h"
#include "MathLibrary.h"
#include <string>
#include <sstream>

Vector3TestGroup::Vector3TestGroup()
    : UnitTestGroup("Vector3 tests")
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

UnitTest::Result Vector3TestGroup::DotProduct()
{
    // perpendicular vectors have dot product of 0
    double dDot = Point3D::Unit(0).Dot( Point3D::Unit(1) );
    if( dDot != 0 )
    {
        return UnitTest::Fail( "Perpendicular vectors with non-zero dot product" );
    }

    // identical vectors have dot product of magnitude squared
    Point3D oVector( 1, 2, 2 );
    dDot = oVector.Dot( oVector );
    if( dDot != oVector.MagnitudeSquared() )
    {
        return UnitTest::Fail( "Identical vectors with dot product not equal to"
                               " magnitude squared" );
    }

    // dot product of two vectors gives projection of one vector onto the other
    // times said other's magnitude
    Point3D oXAxis( 2, 0, 0 );
    dDot = oVector.Dot( oXAxis );
    if( dDot != oVector.x * oXAxis.Magnitude() )
    {
        return UnitTest::Fail( "Dot product of two vectors not equal to"
                               " projection of first onto second times"
                               " magnitude of second" );
    }
    
    return UnitTest::PASS;
}

UnitTest::Result Vector3TestGroup::Normalization()
{
    Point3D oVector( 9, 12, 20 );
    oVector.Normalize();

    // check values
    if( oVector != Point3D( 0.36, 0.48, 0.8 ) )
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

UnitTest::Result Vector3TestGroup::CrossProduct()
{
    // vectors to cross
    Point3D aoVectors[8][2] = {
        { Point3D::Unit(0), Point3D::Unit(0) },
        { Point3D::Unit(0), Point3D::Unit(1) },
        { Point3D::Unit(0), Point3D::Unit(2) },
        { Point3D::Unit(0), -Point3D::Unit(0) },
        { Point3D( 9, 12, 0 ), Point3D( 0, 0, 20 ) },
        { Point3D( -6, 0, 4.5 ), Point3D( 0, 10, 0 ) },
        { Point3D( 0, -2.25, -3 ), Point3D( 5, 0, 0 ) },
        { Point3D( 1.125, -1.5, 0 ), Point3D( 0, 0, -2.5 ) }
    };

    // expected cross products
    Point3D aoExpected[8] = {
        Point3D::Zero(),
        Point3D::Unit(2),
        -Point3D::Unit(1),
        Point3D::Zero(),
        Point3D( 240, -180, 0 ),
        Point3D( -45, 0, -60 ),
        Point3D( 0, -15, 11.25 ),
        Point3D( 3.75, 2.8125, 0 )
    };

    for( unsigned int ui = 0; ui < 8; ++ui )
    {
        Point3D oCross = aoVectors[ui][0].Cross( aoVectors[ui][1] );

        // Confirm that cross product is as expected for different pairs of vectors
        if( oCross != aoExpected[ui] )
        {
            std::ostringstream oSStream;
            oSStream << "Cross product of " << aoVectors[ui][0] << " and "
                     << aoVectors[ui][1] << " other than " << aoExpected[ui];
            return UnitTest::Fail( oSStream.str() );
        }

        // Confirm that cross product is perpendicular to both vectors
        if( oCross.Dot( aoVectors[ui][0] ) != 0 ||
            oCross.Dot( aoVectors[ui][1] ) != 0 )
        {
            std::ostringstream oSStream;
            oSStream << "Cross product of " << aoVectors[ui][0] << " and "
                     << aoVectors[ui][1] << " not perpendicular to both";
            return UnitTest::Fail( oSStream.str() );
        }
    }

    return UnitTest::PASS;
}

UnitTest::Result Vector3TestGroup::Magnitude()
{
    // Unit vectors have magnitude of 1
    if( Point3D::Unit(0).Magnitude() != 1.0 )
    {
        return UnitTest::Fail( "X-axis unit vector has magnitude other than 1" );
    }
    if( Point3D::Unit(1).Magnitude() != 1.0 )
    {
        return UnitTest::Fail( "Y-axis unit vector has magnitude other than 1" );
    }
    if( Point3D::Unit(2).Magnitude() != 1.0 )
    {
        return UnitTest::Fail( "Z-axis unit vector has magnitude other than 1" );
    }
    if( Point3D::Unit(0).MagnitudeSquared() != 1.0 )
    {
        return UnitTest::Fail( "X-axis unit vector has squared magnitude other than 1" );
    }
    if( Point3D::Unit(1).MagnitudeSquared() != 1.0 )
    {
        return UnitTest::Fail( "Y-axis unit vector has squared magnitude other than 1" );
    }
    if( Point3D::Unit(2).MagnitudeSquared() != 1.0 )
    {
        return UnitTest::Fail( "Z-axis unit vector has squared magnitude other than 1" );
    }

    // Negative Unit vectors have magnitude of 1
    if( ( -Point3D::Unit(0) ).Magnitude() != 1.0 )
    {
        return UnitTest::Fail( "Negative X-axis unit vector has magnitude other than 1" );
    }
    if( ( -Point3D::Unit(1) ).Magnitude() != 1.0 )
    {
        return UnitTest::Fail( "Negative Y-axis unit vector has magnitude other than 1" );
    }
    if( ( -Point3D::Unit(2) ).Magnitude() != 1.0 )
    {
        return UnitTest::Fail( "Negative Z-axis unit vector has magnitude other than 1" );
    }
    if( ( -Point3D::Unit(0) ).MagnitudeSquared() != 1.0 )
    {
        return UnitTest::Fail( "Negative X-axis unit vector has squared magnitude other than 1" );
    }
    if( ( -Point3D::Unit(1) ).MagnitudeSquared() != 1.0 )
    {
        return UnitTest::Fail( "Negative Y-axis unit vector has squared magnitude other than 1" );
    }
    if( ( -Point3D::Unit(2) ).MagnitudeSquared() != 1.0 )
    {
        return UnitTest::Fail( "Negative Z-axis unit vector has squared magnitude other than 1" );
    }

    // Zero vector has magnitude of 0
    if( Point3D::Zero().Magnitude() != 0.0 )
    {
        return UnitTest::Fail( "Zero vector has magnitude other than 0" );
    }
    if( Point3D::Zero().MagnitudeSquared() != 0.0 )
    {
        return UnitTest::Fail( "Zero vector has squared magnitude other than 0" );
    }

    // Pythagorean theorem holds
    if( Point3D( 2, 3, 6 ).Magnitude() != 7.0 )
    {
        return UnitTest::Fail( "Magnitude inconsistant with Pythagorean Theorem" );
    }
    if( Point3D( 2, 3, 6 ).MagnitudeSquared() != 49.0 )
    {
        return UnitTest::Fail( "Squared magnitude inconsistant with Pythagorean Theorem" );
    }

    return UnitTest::PASS;
}

UnitTest::Result Vector3TestGroup::Operators()
{
    // Element access
    Point3D oVector( 1, 1, 3 );
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
        oVector[3] = 4;
        return UnitTest::Fail( "Out of range element access didn't throw error" );
    }
    catch( ... ) {}

    // (In)Equality
    if( !( oVector == Point3D( 1, 2, 3 ) ) )
    {
        return UnitTest::Fail( "Equality operator failed to return true" );
    }
    if( oVector == Point3D( -1, -2, -3 ) )
    {
        return UnitTest::Fail( "Equality operator failed to return false" );
    }
    if( !( oVector != Point3D( -1, -2, -3 ) ) )
    {
        return UnitTest::Fail( "Inequality operator failed to return true" );
    }
    if( oVector != Point3D( 1, 2, 3 ) )
    {
        return UnitTest::Fail( "Inequality operator failed to return false" );
    }

    // Stream output
    std::ostringstream oOut;
    oOut << Math::Vector< int, 3 >( oVector );  // no floating-point formatting
    if( oOut.str() != "{ { 1, 2, 3 } }" )
    {
        return UnitTest::Fail( "Stream output operator did not perform as expected" );
    }
    
    return UnitTest::PASS;
}

UnitTest::Result Vector3TestGroup::Arithmatic()
{
    // Addition
    if( Point3D( 1, 2, 3 ) + Point3D( 4, 5, 6 ) != Point3D( 5, 7, 9 ) )
    {
        return UnitTest::Fail( "Addition operator failed" );
    }
    Point3D oVector( 1, 2, 3 );
    oVector += Point3D( 4, 5, 6 );
    if( Point3D( 5, 7, 9 ) != oVector )
    {
        return UnitTest::Fail( "Add-assign operator failed" );
    }
    
    // Subtraction
    if( Point3D( 1, 2, 3 ) - Point3D( 4, 5, 6 ) != Point3D( -3, -3, -3 ) )
    {
        return UnitTest::Fail( "Subtraction operator failed" );
    }
    oVector -= Point3D( 4, 5, 6 );
    if( Point3D( 1, 2, 3 ) != oVector )
    {
        return UnitTest::Fail( "Subtract-assign operator failed" );
    }

    // Unary negation operator
    if( -Point3D( 1, 2, 3 ) != Point3D( -1, -2, -3 ) )
    {
        return UnitTest::Fail( "Unary negation operator failed" );
    }

    // Modulo
    if( Point3D( 1, 2, 3 ) % 2 != Point3D( 1, 0, 1 ) )
    {
        return UnitTest::Fail( "Modulo operator failed" );
    }
    oVector %= 2;
    if( Point3D( 1, 0, 1 ) != oVector )
    {
        return UnitTest::Fail( "Modulo-assign operator failed" );
    }

    return UnitTest::PASS;
}

UnitTest::Result Vector3TestGroup::Multiplication()
{
    // Scalar multiplication
    if( Point3D( 1, 2, 3 ) * 4 != Point3D( 4, 8, 12 ) )
    {
        return UnitTest::Fail( "Scalar multiplication operator failed" );
    }
    if( 5 * Point3D( 6, 7, 8 ) != Point3D( 30, 35, 40 ) )
    {
        return UnitTest::Fail( "Scalar multiplication operator (other way) failed" );
    }
    Point3D oVector( 1, 2, 3 );
    oVector *= 9;
    if( Point3D( 9, 18, 27 ) != oVector )
    {
        return UnitTest::Fail( "Scalar multiply-assign operator failed" );
    }

    // Matrix multiplication
    double aadSquare[3][3] = { { 0, 1, 0 }, { 1, 0, 0 }, { 0, 0, -1 } };
    Math::Matrix< double, 3 > oSquare( aadSquare );
    if( Point3D( 1, 2, 3 ) * oSquare != Point3D( 2, 1, -3 ) )
    {
        return UnitTest::Fail( "Square matrix multiplication operator failed" );
    }
    oVector *= oSquare;
    if( Point3D( 18, 9, -27 ) != oVector )
    {
        return UnitTest::Fail( "Square matrix multiply-assign operator failed" );
    }
    double aadNotSquare[3][2] = { { 0, 1 }, { 1, 0 }, { -1, -1 } };
    Math::Matrix< double, 3, 2 > oNotSquare( aadNotSquare );
    if( Point3D( 1, 2, 3 ) * oNotSquare != Point2D( -1, -2 ) )
    {
        return UnitTest::Fail( "Non-square matrix multiplication operator failed" );
    }
    
    return UnitTest::PASS;
}

UnitTest::Result Vector3TestGroup::Division()
{
    // Scalar division
    if( Point3D( 1, 2, 3 ) / 4 != Point3D( 0.25, 0.5, 0.75 ) )
    {
        return UnitTest::Fail( "Scalar division operator failed" );
    }
    // Right-inverse: A^-1 = A^T*(A*A^T)^-1
    // {{3,4,5}}^-1 = {{3},{4},{5}}({{3,4,5}}{{3},{4},{5}})^-1
    //            = {{3},{4},{5}}{{50}}^-1 = {{3},{4},{5}}{{0.02}}
    //            = {{0.06},{0.08},{0.1}}
    if( ( 10 / Point3D( 3, 4, 5 ) ).Transpose() != Point3D( 0.6, 0.8, 1 ) )
    {
        return UnitTest::Fail( "Scalar/right-invertable vector division failed" );
    }
    Point3D oVector( 1, 2, 3 );
    oVector /= 4;
    if( Point3D( 0.25, 0.5, 0.75 ) != oVector )
    {
        return UnitTest::Fail( "Scalar divide-assign operator failed" );
    }
    
    // Matrix division
    double aadSquare[3][3] = { { 1, 2, 3 }, { 0, 1, 4 }, { 5, 6, 0 } };
    Math::Matrix< double, 3 > oSquare( aadSquare );
    // According to http://www.purplemath.com/modules/mtrxinvr2.htm:
    // {{1,2,3},{0,1,4},{5,6,0}}^-1 = {{-24,18,5},{20,-15,-4},{-5,4,1}}
    if( Point3D( 1, 2, 3 ) / oSquare != Point3D( 1, 0, 0 ) )
    {
        return UnitTest::Fail( "Square matrix division operator failed" );
    }
    oVector /= oSquare;
    if( Point3D( 0.25, 0, 0 ) != oVector )
    {
        return UnitTest::Fail( "Square matrix divide-assign operator failed" );
    }
    double aadNotSquare[2][3] = { { 0, 0, -1 }, { 2, 0, -2 } };
    Math::Matrix< double, 2, 3 > oNotSquare( aadNotSquare );
    // Right-inverse: A^-1 = A^T*(A*A^T)^-1
    // {{0,0,-1},{2,0,-2}}^-1
    //              = {{0,2},{0,0},{-1,-2}}({{0,0,-1},{2,0,-2}}{{0,2},{0,0},{-1,-2}})^-1
    //              = {{0,2},{0,0},{-1,-2}}{{1,2},{2,8}}^-1
    //              = {{0,2},{0,0},{-1,-2}}{{8,-2},{-2,1}}/(8*1-2*2)
    //              = {{-4,2},{0,0},{-4,0}}/4 = {{-1,0.5},{0,0},{-1,0}}
    if( Point3D( 1, 2, 3 ) / oNotSquare != Point2D( -4, 0.5 ) )
    {
        return UnitTest::Fail( "Non-square matrix division operator failed" );
    }
    
    return UnitTest::PASS;
}

UnitTest::Result Vector3TestGroup::DivisionByZero()
{
    // Scalar division that should fail
    Point3D oVector( 1, 2, 3 );
    try
    {
        oVector = Point3D( 1, 2, 3 ) / 0;
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
        oVector = ( 1 / Point3D::Zero() ).Transpose();
        return UnitTest::Fail( "Divide scalar by non-right-invertable vector"
                               " didn't throw error" );
    }
    catch( ... ) {}
    
    // Matrix division (multiplication by inverse) that should fail
    try
    {
        oVector = Point3D( 1, 2, 3 ) / Math::Matrix< double, 3 >::Zero();
        return UnitTest::Fail( "Divide by non-invertable square matrix didn't"
                               " throw error" );
    }
    catch( ... ) {}
    try
    {
        oVector /= Math::Matrix< double, 3 >::Zero();
        return UnitTest::Fail( "Divide-assign by non-invertable square matrix"
                               " didn't throw error" );
    }
    catch( ... ) {}
    try
    {
        Point2D oVector2 = Point3D( 1, 2, 3 ) / Math::Matrix< double, 2, 3 >::Zero();
        return UnitTest::Fail( "Divide by non-invertable non-square matrix"
                               " didn't throw error" );
    }
    catch( ... ) {}

    return UnitTest::PASS;
}

UnitTest::Result Vector3TestGroup::Interpolation()
{
    // Default interpolation
    if( Math::Interpolate( Point3D( 0, 0, -2 ), Point3D( 1, 0, 0 ) )
        != Point3D( 0.5, 0, -1 ) )
    {
        return UnitTest::Fail( "Incorrect default interpolation of (0,0,-2) and"
                               " (1,0,0)" );
    }
    if( Math::Interpolate( -Point3D::Unit(0), -Point3D::Unit(1) )
        != Point3D( -0.5, -0.5, 0 ) )
    {
        return UnitTest::Fail( "Incorrect default interpolation of (-1,00) and"
                               " (0,-1,0)" );
    }

    // Custom interpolation
    if( Math::Interpolate( Point3D( 0, 0, 0 ), Point3D( 2, 4, 6 ), 0.75 )
        != Point3D( 1.5, 3, 4.5 ) )
    {
        return UnitTest::Fail( "Incorrect 3/4 interpolation of (0,0,0) and"
                               " (2,4,6)" );
    }
    if( Math::Interpolate( Point3D( 4, 3, -1 ), Point3D( -2, 1, -2 ), 0.75 )
        != Point3D( -0.5, 1.5, -1.75 ) )
    {
        return UnitTest::Fail( "Incorrect 3/4 interpolation of (4,3,-1) and"
                               " (-2,1,-2)" );
    }

    return UnitTest::PASS;
}
