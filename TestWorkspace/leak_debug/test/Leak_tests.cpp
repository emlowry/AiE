/** ***************************************************************************
 * @file      Leak_tests.cpp
 * @author    Elizabeth Lowry
 * @date      October 15, 2013 - October 15, 2013
 * @brief     Memory leak operator tests.
 * @details   Tests for the operators for the Leak struct.
 * @par       Last Modification:
 *              Implemented all tests.
 **************************************************************************** */

#include "externs/Leak.h"
#include "fixtures/LeakTest.h"
#include "gtest/gtest.h"

using LeakDebug::Leak;

TEST_F( LeakTest, Constructors )
{
    // Default constructor
    Leak oLeakOne;
    EXPECT_EQ( oLeakOne.GetAddress(), nullptr );
    EXPECT_EQ( oLeakOne.GetSize(), 0 );
    EXPECT_STREQ( oLeakOne.GetFile(), nullptr );
    EXPECT_EQ( oLeakOne.GetLine(), 0 );

    // Copy constructor
    Leak oLeakTwo( m_oLeakTwo );
    EXPECT_EQ( oLeakTwo, m_oLeakTwo );
    EXPECT_NE( oLeakTwo.GetFile(), m_oLeakTwo.GetFile() ); // deep copy check

    // Parameterized constructor
    Leak oLeakThree( m_oLeakOne.GetAddress(), m_oLeakOne.GetSize(),
                     m_oLeakOne.GetFile(), m_oLeakOne.GetLine() );
    EXPECT_EQ( oLeakThree, m_oLeakOne );
    EXPECT_NE( oLeakThree.GetFile(), m_oLeakOne.GetFile() );    // deep copy

    // Assignment operator
    oLeakOne = m_oLeakTwo;
    EXPECT_EQ( oLeakOne, m_oLeakTwo );
    EXPECT_NE( oLeakOne.GetFile(), m_oLeakTwo.GetFile() ); // deep copy check
}

TEST_F( LeakTest, AccessorsAndMutators )
{
    // Create leaks from local values
    char acDataOne[] = "Memory leak";
    std::size_t uiSize = sizeof( char ) * ( strlen( acDataOne ) + 1 );
    char acFileOne[] = __FILE__;
    unsigned int uiLine = __LINE__ + 1;
    Leak oLeakOne( acDataOne, uiSize, acFileOne, uiLine );
    Leak oLeakTwo( nullptr, 0, "", 0 );

    // Accessors
    EXPECT_EQ( oLeakOne.GetAddress(), acDataOne );
    EXPECT_EQ( oLeakOne.GetSize(), uiSize );
    EXPECT_STREQ( oLeakOne.GetFile(), acFileOne );
    EXPECT_NE( oLeakOne.GetFile(), acFileOne );   // deep copy check
    EXPECT_EQ( oLeakOne.GetLine(), uiLine );
    EXPECT_EQ( oLeakTwo.GetAddress(), nullptr );
    EXPECT_EQ( oLeakTwo.GetSize(), 0 );
    EXPECT_STREQ( oLeakTwo.GetFile(), "" );
    EXPECT_NE( oLeakTwo.GetFile(), nullptr );   // empty file name not null
    EXPECT_EQ( oLeakTwo.GetLine(), 0 );

    // Mutators
    oLeakOne.SetAddress( oLeakTwo.GetAddress() );
    oLeakOne.SetSize( oLeakTwo.GetSize() );
    oLeakOne.SetFile( oLeakTwo.GetFile() );
    oLeakOne.SetLine( oLeakTwo.GetLine() );
    EXPECT_EQ( oLeakOne, oLeakTwo );
    EXPECT_NE( oLeakOne.GetFile(), oLeakTwo.GetFile() );    // deep copy check
    oLeakOne.SetFile( nullptr );
    EXPECT_STREQ( oLeakOne.GetFile(), nullptr );
    EXPECT_EQ( oLeakOne.GetFile(), nullptr );
    oLeakTwo.SetAddress( m_oLeakTwo.GetAddress() );
    oLeakTwo.SetSize( m_oLeakTwo.GetSize() );
    oLeakTwo.SetFile( m_oLeakTwo.GetFile() );
    oLeakTwo.SetLine( m_oLeakTwo.GetLine() );
    EXPECT_EQ( oLeakTwo, m_oLeakTwo );
    EXPECT_NE( oLeakTwo.GetFile(), m_oLeakTwo.GetFile() );  // deep copy check
}

TEST_F( LeakTest, OutputOperator )
{
    // Print what you expect the leak to print as and the leak to string streams
    std::stringstream oExpectedStream, oActualStream;
    oExpectedStream << m_oLeakOne.GetSize() << " bytes at "
                    << m_oLeakOne.GetAddress() << " allocated by "
                    << m_oLeakOne.GetFile() << "(" << m_oLeakOne.GetLine()
                    << ")";
    oActualStream << m_oLeakOne;

    // Make sure both are the same.
    std::string oExpected, oActual;
    oExpectedStream >> oExpected;
    oActualStream >> oActual;
    ASSERT_EQ( oExpected, oActual );
}

TEST_F( LeakTest, EqualityOperator )
{
    // Equality operator returns true for a struct with itself.
    EXPECT_TRUE( m_oLeakOne == m_oLeakOne );

    // Equality operator returns true for equal structs.
    EXPECT_TRUE( m_oLeakOne == m_oLeakTwo );
    EXPECT_TRUE( m_oLeakTwo == m_oLeakOne );

    // Equality operator returns false if addresses differ.
    m_oLeakTwo.SetAddress( &m_oLeakTwo );
    EXPECT_FALSE( m_oLeakOne == m_oLeakTwo );
    EXPECT_FALSE( m_oLeakTwo == m_oLeakOne );
    m_oLeakTwo.SetAddress( m_oLeakOne.GetAddress() );

    // Equality operator returns false if sizes differ.
    m_oLeakTwo.SetSize( 1 );
    EXPECT_FALSE( m_oLeakOne == m_oLeakTwo );
    EXPECT_FALSE( m_oLeakTwo == m_oLeakOne );
    m_oLeakTwo.SetSize( m_oLeakOne.GetSize() );

    // Equality operator returns false if file names differ.
    m_oLeakTwo.SetFile( nullptr );
    EXPECT_FALSE( m_oLeakOne == m_oLeakTwo );
    EXPECT_FALSE( m_oLeakTwo == m_oLeakOne );
    m_oLeakTwo.SetFile( m_oLeakOne.GetFile() );

    // Equality operator returns false if line numbers differ.
    m_oLeakTwo.SetLine( m_oLeakTwo.GetLine() + 1 );
    EXPECT_FALSE( m_oLeakOne == m_oLeakTwo );
    EXPECT_FALSE( m_oLeakTwo == m_oLeakOne );
    m_oLeakTwo.SetLine( m_oLeakOne.GetLine() );
}

TEST_F( LeakTest, InequalityOperator )
{
    // Inequality operator returns false for a struct with itself.
    EXPECT_FALSE( m_oLeakOne != m_oLeakOne );

    // Inequality operator returns false for equal structs.
    EXPECT_FALSE( m_oLeakOne != m_oLeakTwo );
    EXPECT_FALSE( m_oLeakTwo != m_oLeakOne );

    // Inequality operator returns true if addresses differ.
    m_oLeakTwo.SetAddress( &m_oLeakTwo );
    EXPECT_TRUE( m_oLeakOne != m_oLeakTwo );
    EXPECT_TRUE( m_oLeakTwo != m_oLeakOne );
    m_oLeakTwo.SetAddress( m_oLeakOne.GetAddress() );

    // Inequality operator returns true if sizes differ.
    m_oLeakTwo.SetSize( 1 );
    EXPECT_TRUE( m_oLeakOne != m_oLeakTwo );
    EXPECT_TRUE( m_oLeakTwo != m_oLeakOne );
    m_oLeakTwo.SetSize( m_oLeakOne.GetSize() );

    // Inequality operator returns true if file names differ.
    m_oLeakTwo.SetFile( nullptr );
    EXPECT_TRUE( m_oLeakOne != m_oLeakTwo );
    EXPECT_TRUE( m_oLeakTwo != m_oLeakOne );
    m_oLeakTwo.SetFile( m_oLeakOne.GetFile() );

    // Inequality operator returns true if line numbers differ.
    m_oLeakTwo.SetLine( m_oLeakTwo.GetLine() + 1 );
    EXPECT_TRUE( m_oLeakOne != m_oLeakTwo );
    EXPECT_TRUE( m_oLeakTwo != m_oLeakOne );
    m_oLeakTwo.SetLine( m_oLeakOne.GetLine() );
}

TEST_F( LeakTest, GreaterThanOperatorBase )
{
    // Greater-than operator returns false for a struct with itself.
    EXPECT_FALSE( m_oLeakOne > m_oLeakOne );

    // Greater-than operator returns false for equal structs.
    EXPECT_FALSE( m_oLeakOne > m_oLeakTwo );
    EXPECT_FALSE( m_oLeakTwo > m_oLeakOne );
}

TEST_F( LeakTest, GreaterThanOperatorAddress )
{
    // Greater-than operator returns false if first address is less than
    // second...
    m_oLeakTwo.SetAddress( &m_oLeakTwo );
    EXPECT_FALSE( m_oLeakOne > m_oLeakTwo );

    // ... true if vice-versa...
    EXPECT_TRUE( m_oLeakTwo > m_oLeakOne );

    // ... with no change in result if first size differs from second...
    m_oLeakOne.SetSize( 1 );
    EXPECT_FALSE( m_oLeakOne > m_oLeakTwo );
    EXPECT_TRUE( m_oLeakTwo > m_oLeakOne );
    m_oLeakOne.SetSize( m_oLeakTwo.GetSize() );
    m_oLeakTwo.SetSize( 1 );
    EXPECT_FALSE( m_oLeakOne > m_oLeakTwo );
    EXPECT_TRUE( m_oLeakTwo > m_oLeakOne );
    m_oLeakTwo.SetSize( m_oLeakOne.GetSize() );

    // ... or if first file name differs from second...
    m_oLeakOne.SetFile( nullptr );
    EXPECT_FALSE( m_oLeakOne > m_oLeakTwo );
    EXPECT_TRUE( m_oLeakTwo > m_oLeakOne );
    m_oLeakOne.SetFile( m_oLeakTwo.GetFile() );
    m_oLeakTwo.SetFile( nullptr );
    EXPECT_FALSE( m_oLeakOne > m_oLeakTwo );
    EXPECT_TRUE( m_oLeakTwo > m_oLeakOne );
    m_oLeakTwo.SetFile( m_oLeakOne.GetFile() );

    // ... or if first line number differs from second.
    m_oLeakTwo.SetLine( m_oLeakTwo.GetLine() + 1 );
    EXPECT_FALSE( m_oLeakOne > m_oLeakTwo );
    EXPECT_TRUE( m_oLeakTwo > m_oLeakOne );
    m_oLeakTwo.SetLine( m_oLeakOne.GetLine() );
    m_oLeakOne.SetLine( m_oLeakOne.GetLine() + 1 );
    EXPECT_FALSE( m_oLeakOne > m_oLeakTwo );
    EXPECT_TRUE( m_oLeakTwo > m_oLeakOne );
}

TEST_F( LeakTest, GreaterThanOperatorSize )
{
    // Greater-than operator returns false if first size is less than
    // second...
    m_oLeakOne.SetSize( 1 );
    EXPECT_FALSE( m_oLeakOne > m_oLeakTwo );

    // ... true if vice-versa...
    EXPECT_TRUE( m_oLeakTwo > m_oLeakOne );

    // ... with no change in result if first file name differs from second...
    m_oLeakOne.SetFile( nullptr );
    EXPECT_FALSE( m_oLeakOne > m_oLeakTwo );
    EXPECT_TRUE( m_oLeakTwo > m_oLeakOne );
    m_oLeakOne.SetFile( m_oLeakTwo.GetFile() );
    m_oLeakTwo.SetFile( nullptr );
    EXPECT_FALSE( m_oLeakOne > m_oLeakTwo );
    EXPECT_TRUE( m_oLeakTwo > m_oLeakOne );
    m_oLeakTwo.SetFile( m_oLeakOne.GetFile() );

    // ... or if first line number differs from second.
    m_oLeakTwo.SetLine( m_oLeakTwo.GetLine() + 1 );
    EXPECT_FALSE( m_oLeakOne > m_oLeakTwo );
    EXPECT_TRUE( m_oLeakTwo > m_oLeakOne );
    m_oLeakTwo.SetLine( m_oLeakOne.GetLine() );
    m_oLeakOne.SetLine( m_oLeakOne.GetLine() + 1 );
    EXPECT_FALSE( m_oLeakOne > m_oLeakTwo );
    EXPECT_TRUE( m_oLeakTwo > m_oLeakOne );
}

TEST_F( LeakTest, GreaterThanOperatorFile )
{
    // Greater-than operator returns false if first file name is less than
    // second...
    m_oLeakOne.SetFile( nullptr );
    EXPECT_FALSE( m_oLeakOne > m_oLeakTwo );

    // ... true if vice-versa...
    EXPECT_TRUE( m_oLeakTwo > m_oLeakOne );

    // ... with no change in result if first line number differs from second.
    m_oLeakTwo.SetLine( m_oLeakTwo.GetLine() + 1 );
    EXPECT_FALSE( m_oLeakOne > m_oLeakTwo );
    EXPECT_TRUE( m_oLeakTwo > m_oLeakOne );
    m_oLeakTwo.SetLine( m_oLeakOne.GetLine() );
    m_oLeakOne.SetLine( m_oLeakOne.GetLine() + 1 );
    EXPECT_FALSE( m_oLeakOne > m_oLeakTwo );
    EXPECT_TRUE( m_oLeakTwo > m_oLeakOne );
}

TEST_F( LeakTest, GreaterThanOperatorLine )
{
    // Greater-than operator returns false if first line number is less than
    // second...
    m_oLeakTwo.SetLine( m_oLeakTwo.GetLine() + 1 );
    EXPECT_FALSE( m_oLeakOne > m_oLeakTwo );

    // ... true if vice-versa.
    EXPECT_TRUE( m_oLeakTwo > m_oLeakOne );
}

TEST_F( LeakTest, GreaterThanOrEqualToOperatorBase )
{
    // Greater-than-or-equal-to operator returns true for a struct with itself.
    EXPECT_TRUE( m_oLeakOne >= m_oLeakOne );

    // Greater-than-or-equal-to operator returns true for equal structs.
    EXPECT_TRUE( m_oLeakOne >= m_oLeakTwo );
    EXPECT_TRUE( m_oLeakTwo >= m_oLeakOne );
}

TEST_F( LeakTest, GreaterThanOrEqualToOperatorAddress )
{
    // Greater-than-or-equal-to operator returns false if first address is less
    // than second...
    m_oLeakTwo.SetAddress( &m_oLeakTwo );
    EXPECT_FALSE( m_oLeakOne >= m_oLeakTwo );

    // ... true if vice-versa...
    EXPECT_TRUE( m_oLeakTwo >= m_oLeakOne );

    // ... with no change in result if first size differs from second...
    m_oLeakOne.SetSize( 1 );
    EXPECT_FALSE( m_oLeakOne >= m_oLeakTwo );
    EXPECT_TRUE( m_oLeakTwo >= m_oLeakOne );
    m_oLeakOne.SetSize( m_oLeakTwo.GetSize() );
    m_oLeakTwo.SetSize( 1 );
    EXPECT_FALSE( m_oLeakOne >= m_oLeakTwo );
    EXPECT_TRUE( m_oLeakTwo >= m_oLeakOne );
    m_oLeakTwo.SetSize( m_oLeakOne.GetSize() );

    // ... or if first file name differs from second...
    m_oLeakOne.SetFile( nullptr );
    EXPECT_FALSE( m_oLeakOne >= m_oLeakTwo );
    EXPECT_TRUE( m_oLeakTwo >= m_oLeakOne );
    m_oLeakOne.SetFile( m_oLeakTwo.GetFile() );
    m_oLeakTwo.SetFile( nullptr );
    EXPECT_FALSE( m_oLeakOne >= m_oLeakTwo );
    EXPECT_TRUE( m_oLeakTwo >= m_oLeakOne );
    m_oLeakTwo.SetFile( m_oLeakOne.GetFile() );

    // ... or if first line number differs from second.
    m_oLeakTwo.SetLine( m_oLeakTwo.GetLine() + 1 );
    EXPECT_FALSE( m_oLeakOne >= m_oLeakTwo );
    EXPECT_TRUE( m_oLeakTwo >= m_oLeakOne );
    m_oLeakTwo.SetLine( m_oLeakOne.GetLine() );
    m_oLeakOne.SetLine( m_oLeakOne.GetLine() + 1 );
    EXPECT_FALSE( m_oLeakOne >= m_oLeakTwo );
    EXPECT_TRUE( m_oLeakTwo >= m_oLeakOne );
}

TEST_F( LeakTest, GreaterThanOrEqualToOperatorSize )
{
    // Greater-than-or-equal-to operator returns false if first size is less
    // than second...
    m_oLeakOne.SetSize( 1 );
    EXPECT_FALSE( m_oLeakOne >= m_oLeakTwo );

    // ... true if vice-versa...
    EXPECT_TRUE( m_oLeakTwo >= m_oLeakOne );

    // ... with no change in result if first file name differs from second...
    m_oLeakOne.SetFile( nullptr );
    EXPECT_FALSE( m_oLeakOne >= m_oLeakTwo );
    EXPECT_TRUE( m_oLeakTwo >= m_oLeakOne );
    m_oLeakOne.SetFile( m_oLeakTwo.GetFile() );
    m_oLeakTwo.SetFile( nullptr );
    EXPECT_FALSE( m_oLeakOne >= m_oLeakTwo );
    EXPECT_TRUE( m_oLeakTwo >= m_oLeakOne );
    m_oLeakTwo.SetFile( m_oLeakOne.GetFile() );

    // ... or if first line number differs from second.
    m_oLeakTwo.SetLine( m_oLeakTwo.GetLine() + 1 );
    EXPECT_FALSE( m_oLeakOne >= m_oLeakTwo );
    EXPECT_TRUE( m_oLeakTwo >= m_oLeakOne );
    m_oLeakTwo.SetLine( m_oLeakOne.GetLine() );
    m_oLeakOne.SetLine( m_oLeakOne.GetLine() + 1 );
    EXPECT_FALSE( m_oLeakOne >= m_oLeakTwo );
    EXPECT_TRUE( m_oLeakTwo >= m_oLeakOne );
}

TEST_F( LeakTest, GreaterThanOrEqualToOperatorFile )
{
    // Greater-than-or-equal-to operator returns false if first file name is
    // less than second...
    m_oLeakOne.SetFile( nullptr );
    EXPECT_FALSE( m_oLeakOne >= m_oLeakTwo );

    // ... true if vice-versa...
    EXPECT_TRUE( m_oLeakTwo >= m_oLeakOne );

    // ... with no change in result if first line number differs from second.
    m_oLeakTwo.SetLine( m_oLeakTwo.GetLine() + 1 );
    EXPECT_FALSE( m_oLeakOne >= m_oLeakTwo );
    EXPECT_TRUE( m_oLeakTwo >= m_oLeakOne );
    m_oLeakTwo.SetLine( m_oLeakOne.GetLine() );
    m_oLeakOne.SetLine( m_oLeakOne.GetLine() + 1 );
    EXPECT_FALSE( m_oLeakOne >= m_oLeakTwo );
    EXPECT_TRUE( m_oLeakTwo >= m_oLeakOne );
}

TEST_F( LeakTest, GreaterThanOrEqualToOperatorLine )
{
    // Greater-than-or-equal-to operator returns false if first line number is
    // less than second...
    m_oLeakTwo.SetLine( m_oLeakTwo.GetLine() + 1 );
    EXPECT_FALSE( m_oLeakOne >= m_oLeakTwo );

    // ... true if vice-versa.
    EXPECT_TRUE( m_oLeakTwo >= m_oLeakOne );
}

TEST_F( LeakTest, LessThanOperatorBase )
{
    // Less-than operator returns false for a struct with itself.
    EXPECT_FALSE( m_oLeakOne < m_oLeakOne );

    // Less-than operator returns false for equal structs.
    EXPECT_FALSE( m_oLeakOne < m_oLeakTwo );
    EXPECT_FALSE( m_oLeakTwo < m_oLeakOne );
}

TEST_F( LeakTest, LessThanOperatorAddress )
{
    // Less-than operator returns true if first address is less than second...
    m_oLeakTwo.SetAddress( &m_oLeakTwo );
    EXPECT_TRUE( m_oLeakOne < m_oLeakTwo );

    // ... false if vice-versa...
    EXPECT_FALSE( m_oLeakTwo < m_oLeakOne );

    // ... with no change in result if first size differs from second...
    m_oLeakOne.SetSize( 1 );
    EXPECT_TRUE( m_oLeakOne < m_oLeakTwo );
    EXPECT_FALSE( m_oLeakTwo < m_oLeakOne );
    m_oLeakOne.SetSize( m_oLeakTwo.GetSize() );
    m_oLeakTwo.SetSize( 1 );
    EXPECT_TRUE( m_oLeakOne < m_oLeakTwo );
    EXPECT_FALSE( m_oLeakTwo < m_oLeakOne );
    m_oLeakTwo.SetSize( m_oLeakOne.GetSize() );

    // ... or if first file name differs from second...
    m_oLeakOne.SetFile( nullptr );
    EXPECT_TRUE( m_oLeakOne < m_oLeakTwo );
    EXPECT_FALSE( m_oLeakTwo < m_oLeakOne );
    m_oLeakOne.SetFile( m_oLeakTwo.GetFile() );
    m_oLeakTwo.SetFile( nullptr );
    EXPECT_TRUE( m_oLeakOne < m_oLeakTwo );
    EXPECT_FALSE( m_oLeakTwo < m_oLeakOne );
    m_oLeakTwo.SetFile( m_oLeakOne.GetFile() );

    // ... or if first line number differs from second.
    m_oLeakTwo.SetLine( m_oLeakTwo.GetLine() + 1 );
    EXPECT_TRUE( m_oLeakOne < m_oLeakTwo );
    EXPECT_FALSE( m_oLeakTwo < m_oLeakOne );
    m_oLeakTwo.SetLine( m_oLeakOne.GetLine() );
    m_oLeakOne.SetLine( m_oLeakOne.GetLine() + 1 );
    EXPECT_TRUE( m_oLeakOne < m_oLeakTwo );
    EXPECT_FALSE( m_oLeakTwo < m_oLeakOne );
}

TEST_F( LeakTest, LessThanOperatorSize )
{
    // Less-than operator returns true if first size is less than second...
    m_oLeakOne.SetSize( 1 );
    EXPECT_TRUE( m_oLeakOne < m_oLeakTwo );

    // ... false if vice-versa...
    EXPECT_FALSE( m_oLeakTwo < m_oLeakOne );

    // ... with no change in result if first file name differs from second...
    m_oLeakOne.SetFile( nullptr );
    EXPECT_TRUE( m_oLeakOne < m_oLeakTwo );
    EXPECT_FALSE( m_oLeakTwo < m_oLeakOne );
    m_oLeakOne.SetFile( m_oLeakTwo.GetFile() );
    m_oLeakTwo.SetFile( nullptr );
    EXPECT_TRUE( m_oLeakOne < m_oLeakTwo );
    EXPECT_FALSE( m_oLeakTwo < m_oLeakOne );
    m_oLeakTwo.SetFile( m_oLeakOne.GetFile() );

    // ... or if first line number differs from second.
    m_oLeakTwo.SetLine( m_oLeakTwo.GetLine() + 1 );
    EXPECT_TRUE( m_oLeakOne < m_oLeakTwo );
    EXPECT_FALSE( m_oLeakTwo < m_oLeakOne );
    m_oLeakTwo.SetLine( m_oLeakOne.GetLine() );
    m_oLeakOne.SetLine( m_oLeakOne.GetLine() + 1 );
    EXPECT_TRUE( m_oLeakOne < m_oLeakTwo );
    EXPECT_FALSE( m_oLeakTwo < m_oLeakOne );
}

TEST_F( LeakTest, LessThanOperatorFile )
{
    // Less-than operator returns true if first file name is less than second...
    m_oLeakOne.SetFile( nullptr );
    EXPECT_TRUE( m_oLeakOne < m_oLeakTwo );

    // ... false if vice-versa...
    EXPECT_FALSE( m_oLeakTwo < m_oLeakOne );

    // ... with no change in result if first line number differs from second.
    m_oLeakTwo.SetLine( m_oLeakTwo.GetLine() + 1 );
    EXPECT_TRUE( m_oLeakOne < m_oLeakTwo );
    EXPECT_FALSE( m_oLeakTwo < m_oLeakOne );
    m_oLeakTwo.SetLine( m_oLeakOne.GetLine() );
    m_oLeakOne.SetLine( m_oLeakOne.GetLine() + 1 );
    EXPECT_TRUE( m_oLeakOne < m_oLeakTwo );
    EXPECT_FALSE( m_oLeakTwo < m_oLeakOne );
}

TEST_F( LeakTest, LessThanOperatorLine )
{
    // Less-than operator returns true if first line number is less than
    // second...
    m_oLeakTwo.SetLine( m_oLeakTwo.GetLine() + 1 );
    EXPECT_TRUE( m_oLeakOne < m_oLeakTwo );

    // ... false if vice-versa.
    EXPECT_FALSE( m_oLeakTwo < m_oLeakOne );
}

TEST_F( LeakTest, LessThanOrEqualToOperatorBase )
{
    // Less-than-or-equal-to operator returns true for a struct with itself.
    EXPECT_TRUE( m_oLeakOne <= m_oLeakOne );

    // Less-than-or-equal-to operator returns true for equal structs.
    EXPECT_TRUE( m_oLeakOne <= m_oLeakTwo );
    EXPECT_TRUE( m_oLeakTwo <= m_oLeakOne );
}

TEST_F( LeakTest, LessThanOrEqualToOperatorAddress )
{
    // Less-than-or-equal-to operator returns true if first address is less than
    // second...
    m_oLeakTwo.SetAddress( &m_oLeakTwo );
    EXPECT_TRUE( m_oLeakOne <= m_oLeakTwo );

    // ... false if vice-versa...
    EXPECT_FALSE( m_oLeakTwo <= m_oLeakOne );

    // ... with no change in result if first size differs from second...
    m_oLeakOne.SetSize( 1 );
    EXPECT_TRUE( m_oLeakOne <= m_oLeakTwo );
    EXPECT_FALSE( m_oLeakTwo <= m_oLeakOne );
    m_oLeakOne.SetSize( m_oLeakTwo.GetSize() );
    m_oLeakTwo.SetSize( 1 );
    EXPECT_TRUE( m_oLeakOne <= m_oLeakTwo );
    EXPECT_FALSE( m_oLeakTwo <= m_oLeakOne );
    m_oLeakTwo.SetSize( m_oLeakOne.GetSize() );

    // ... or if first file name differs from second...
    m_oLeakOne.SetFile( nullptr );
    EXPECT_TRUE( m_oLeakOne <= m_oLeakTwo );
    EXPECT_FALSE( m_oLeakTwo <= m_oLeakOne );
    m_oLeakOne.SetFile( m_oLeakTwo.GetFile() );
    m_oLeakTwo.SetFile( nullptr );
    EXPECT_TRUE( m_oLeakOne <= m_oLeakTwo );
    EXPECT_FALSE( m_oLeakTwo <= m_oLeakOne );
    m_oLeakTwo.SetFile( m_oLeakOne.GetFile() );

    // ... or if first line number differs from second.
    m_oLeakTwo.SetLine( m_oLeakTwo.GetLine() + 1 );
    EXPECT_TRUE( m_oLeakOne <= m_oLeakTwo );
    EXPECT_FALSE( m_oLeakTwo <= m_oLeakOne );
    m_oLeakTwo.SetLine( m_oLeakOne.GetLine() );
    m_oLeakOne.SetLine( m_oLeakOne.GetLine() + 1 );
    EXPECT_TRUE( m_oLeakOne <= m_oLeakTwo );
    EXPECT_FALSE( m_oLeakTwo <= m_oLeakOne );
}

TEST_F( LeakTest, LessThanOrEqualToOperatorSize )
{
    // Less-than-or-equal-to operator returns true if first size is less than
    // second...
    m_oLeakOne.SetSize( 1 );
    EXPECT_TRUE( m_oLeakOne <= m_oLeakTwo );

    // ... false if vice-versa...
    EXPECT_FALSE( m_oLeakTwo <= m_oLeakOne );

    // ... with no change in result if first file name differs from second...
    m_oLeakOne.SetFile( nullptr );
    EXPECT_TRUE( m_oLeakOne <= m_oLeakTwo );
    EXPECT_FALSE( m_oLeakTwo <= m_oLeakOne );
    m_oLeakOne.SetFile( m_oLeakTwo.GetFile() );
    m_oLeakTwo.SetFile( nullptr );
    EXPECT_TRUE( m_oLeakOne <= m_oLeakTwo );
    EXPECT_FALSE( m_oLeakTwo <= m_oLeakOne );
    m_oLeakTwo.SetFile( m_oLeakOne.GetFile() );

    // ... or if first line number differs from second.
    m_oLeakTwo.SetLine( m_oLeakTwo.GetLine() + 1 );
    EXPECT_TRUE( m_oLeakOne <= m_oLeakTwo );
    EXPECT_FALSE( m_oLeakTwo <= m_oLeakOne );
    m_oLeakTwo.SetLine( m_oLeakOne.GetLine() );
    m_oLeakOne.SetLine( m_oLeakOne.GetLine() + 1 );
    EXPECT_TRUE( m_oLeakOne <= m_oLeakTwo );
    EXPECT_FALSE( m_oLeakTwo <= m_oLeakOne );
}

TEST_F( LeakTest, LessThanOrEqualToOperatorFile )
{
    // Less-than-or-equal-to operator returns true if first file name is less
    // than second...
    m_oLeakOne.SetFile( nullptr );
    EXPECT_TRUE( m_oLeakOne <= m_oLeakTwo );

    // ... false if vice-versa...
    EXPECT_FALSE( m_oLeakTwo <= m_oLeakOne );

    // ... with no change in result if first line number differs from second.
    m_oLeakTwo.SetLine( m_oLeakTwo.GetLine() + 1 );
    EXPECT_TRUE( m_oLeakOne <= m_oLeakTwo );
    EXPECT_FALSE( m_oLeakTwo <= m_oLeakOne );
    m_oLeakTwo.SetLine( m_oLeakOne.GetLine() );
    m_oLeakOne.SetLine( m_oLeakOne.GetLine() + 1 );
    EXPECT_TRUE( m_oLeakOne <= m_oLeakTwo );
    EXPECT_FALSE( m_oLeakTwo <= m_oLeakOne );
}

TEST_F( LeakTest, LessThanOrEqualToOperatorLine )
{
    // Less-than-or-equal-to operator returns true if first line number is less
    // than second...
    m_oLeakTwo.SetLine( m_oLeakTwo.GetLine() + 1 );
    EXPECT_TRUE( m_oLeakOne <= m_oLeakTwo );

    // ... false if vice-versa.
    EXPECT_FALSE( m_oLeakTwo <= m_oLeakOne );
}
