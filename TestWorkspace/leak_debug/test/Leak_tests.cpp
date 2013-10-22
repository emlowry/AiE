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

TEST_F( LeakTest, OutputOperator )
{
    // Print what you expect the leak to print as and the leak to string streams
    std::stringstream oExpectedStream, oActualStream;
    oExpectedStream << m_oLeakOne.size << " bytes at " << m_oLeakOne.pointer
                    << " allocated by " << m_oLeakOne.file
                    << "(" << m_oLeakOne.line << ")";
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
    m_oLeakTwo.pointer = &m_oLeakTwo;
    EXPECT_FALSE( m_oLeakOne == m_oLeakTwo );
    EXPECT_FALSE( m_oLeakTwo == m_oLeakOne );
    m_oLeakTwo.pointer = m_oLeakOne.pointer;

    // Equality operator returns false if sizes differ.
    m_oLeakTwo.size = 1;
    EXPECT_FALSE( m_oLeakOne == m_oLeakTwo );
    EXPECT_FALSE( m_oLeakTwo == m_oLeakOne );
    m_oLeakTwo.size = m_oLeakOne.size;

    // Equality operator returns false if file names differ.
    m_oLeakTwo.file = "";
    EXPECT_FALSE( m_oLeakOne == m_oLeakTwo );
    EXPECT_FALSE( m_oLeakTwo == m_oLeakOne );
    m_oLeakTwo.file = sm_cpcFileNameCopyTwo;

    // Equality operator returns false if line numbers differ.
    m_oLeakTwo.line++;
    EXPECT_FALSE( m_oLeakOne == m_oLeakTwo );
    EXPECT_FALSE( m_oLeakTwo == m_oLeakOne );
    m_oLeakTwo.line = m_oLeakOne.line;
}

TEST_F( LeakTest, InequalityOperator )
{
    // Inequality operator returns false for a struct with itself.
    EXPECT_FALSE( m_oLeakOne != m_oLeakOne );

    // Inequality operator returns false for equal structs.
    EXPECT_FALSE( m_oLeakOne != m_oLeakTwo );
    EXPECT_FALSE( m_oLeakTwo != m_oLeakOne );

    // Inequality operator returns true if addresses differ.
    m_oLeakTwo.pointer = &m_oLeakTwo;
    EXPECT_TRUE( m_oLeakOne != m_oLeakTwo );
    EXPECT_TRUE( m_oLeakTwo != m_oLeakOne );
    m_oLeakTwo.pointer = m_oLeakOne.pointer;

    // Inequality operator returns true if sizes differ.
    m_oLeakTwo.size = 1;
    EXPECT_TRUE( m_oLeakOne != m_oLeakTwo );
    EXPECT_TRUE( m_oLeakTwo != m_oLeakOne );
    m_oLeakTwo.size = m_oLeakOne.size;

    // Inequality operator returns true if file names differ.
    m_oLeakTwo.file = "";
    EXPECT_TRUE( m_oLeakOne != m_oLeakTwo );
    EXPECT_TRUE( m_oLeakTwo != m_oLeakOne );
    m_oLeakTwo.file = sm_cpcFileNameCopyTwo;

    // Inequality operator returns true if line numbers differ.
    m_oLeakTwo.line++;
    EXPECT_TRUE( m_oLeakOne != m_oLeakTwo );
    EXPECT_TRUE( m_oLeakTwo != m_oLeakOne );
    m_oLeakTwo.line = m_oLeakOne.line;
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
    m_oLeakTwo.pointer = &m_oLeakTwo;
    EXPECT_FALSE( m_oLeakOne > m_oLeakTwo );

    // ... true if vice-versa...
    EXPECT_TRUE( m_oLeakTwo > m_oLeakOne );

    // ... with no change in result if first size differs from second...
    m_oLeakOne.size = 1;
    EXPECT_FALSE( m_oLeakOne > m_oLeakTwo );
    EXPECT_TRUE( m_oLeakTwo > m_oLeakOne );
    m_oLeakOne.size = m_oLeakTwo.size;
    m_oLeakTwo.size = 1;
    EXPECT_FALSE( m_oLeakOne > m_oLeakTwo );
    EXPECT_TRUE( m_oLeakTwo > m_oLeakOne );
    m_oLeakTwo.size = m_oLeakOne.size;

    // ... or if first file name differs from second...
    m_oLeakOne.file = "";
    EXPECT_FALSE( m_oLeakOne > m_oLeakTwo );
    EXPECT_TRUE( m_oLeakTwo > m_oLeakOne );
    m_oLeakOne.file = sm_cpcFileNameCopyOne;
    m_oLeakTwo.file = "";
    EXPECT_FALSE( m_oLeakOne > m_oLeakTwo );
    EXPECT_TRUE( m_oLeakTwo > m_oLeakOne );
    m_oLeakTwo.file = sm_cpcFileNameCopyTwo;

    // ... or if first line number differs from second.
    m_oLeakTwo.line++;
    EXPECT_FALSE( m_oLeakOne > m_oLeakTwo );
    EXPECT_TRUE( m_oLeakTwo > m_oLeakOne );
    m_oLeakTwo.line = m_oLeakOne.line;
    m_oLeakOne.line++;
    EXPECT_FALSE( m_oLeakOne > m_oLeakTwo );
    EXPECT_TRUE( m_oLeakTwo > m_oLeakOne );
}

TEST_F( LeakTest, GreaterThanOperatorSize )
{
    // Greater-than operator returns false if first size is less than
    // second...
    m_oLeakOne.size = 1;
    EXPECT_FALSE( m_oLeakOne > m_oLeakTwo );

    // ... true if vice-versa...
    EXPECT_TRUE( m_oLeakTwo > m_oLeakOne );

    // ... with no change in result if first file name differs from second...
    m_oLeakOne.file = "";
    EXPECT_FALSE( m_oLeakOne > m_oLeakTwo );
    EXPECT_TRUE( m_oLeakTwo > m_oLeakOne );
    m_oLeakOne.file = sm_cpcFileNameCopyOne;
    m_oLeakTwo.file = "";
    EXPECT_FALSE( m_oLeakOne > m_oLeakTwo );
    EXPECT_TRUE( m_oLeakTwo > m_oLeakOne );
    m_oLeakTwo.file = sm_cpcFileNameCopyTwo;

    // ... or if first line number differs from second.
    m_oLeakTwo.line++;
    EXPECT_FALSE( m_oLeakOne > m_oLeakTwo );
    EXPECT_TRUE( m_oLeakTwo > m_oLeakOne );
    m_oLeakTwo.line = m_oLeakOne.line;
    m_oLeakOne.line++;
    EXPECT_FALSE( m_oLeakOne > m_oLeakTwo );
    EXPECT_TRUE( m_oLeakTwo > m_oLeakOne );
}

TEST_F( LeakTest, GreaterThanOperatorFile )
{
    // Greater-than operator returns false if first file name is less than
    // second...
    m_oLeakOne.file = "";
    EXPECT_FALSE( m_oLeakOne > m_oLeakTwo );

    // ... true if vice-versa...
    EXPECT_TRUE( m_oLeakTwo > m_oLeakOne );

    // ... with no change in result if first line number differs from second.
    m_oLeakTwo.line++;
    EXPECT_FALSE( m_oLeakOne > m_oLeakTwo );
    EXPECT_TRUE( m_oLeakTwo > m_oLeakOne );
    m_oLeakTwo.line = m_oLeakOne.line;
    m_oLeakOne.line++;
    EXPECT_FALSE( m_oLeakOne > m_oLeakTwo );
    EXPECT_TRUE( m_oLeakTwo > m_oLeakOne );
}

TEST_F( LeakTest, GreaterThanOperatorLine )
{
    // Greater-than operator returns false if first line number is less than
    // second...
    m_oLeakTwo.line++;
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
    m_oLeakTwo.pointer = &m_oLeakTwo;
    EXPECT_FALSE( m_oLeakOne >= m_oLeakTwo );

    // ... true if vice-versa...
    EXPECT_TRUE( m_oLeakTwo >= m_oLeakOne );

    // ... with no change in result if first size differs from second...
    m_oLeakOne.size = 1;
    EXPECT_FALSE( m_oLeakOne >= m_oLeakTwo );
    EXPECT_TRUE( m_oLeakTwo >= m_oLeakOne );
    m_oLeakOne.size = m_oLeakTwo.size;
    m_oLeakTwo.size = 1;
    EXPECT_FALSE( m_oLeakOne >= m_oLeakTwo );
    EXPECT_TRUE( m_oLeakTwo >= m_oLeakOne );
    m_oLeakTwo.size = m_oLeakOne.size;

    // ... or if first file name differs from second...
    m_oLeakOne.file = "";
    EXPECT_FALSE( m_oLeakOne >= m_oLeakTwo );
    EXPECT_TRUE( m_oLeakTwo >= m_oLeakOne );
    m_oLeakOne.file = sm_cpcFileNameCopyOne;
    m_oLeakTwo.file = "";
    EXPECT_FALSE( m_oLeakOne >= m_oLeakTwo );
    EXPECT_TRUE( m_oLeakTwo >= m_oLeakOne );
    m_oLeakTwo.file = sm_cpcFileNameCopyTwo;

    // ... or if first line number differs from second.
    m_oLeakTwo.line++;
    EXPECT_FALSE( m_oLeakOne >= m_oLeakTwo );
    EXPECT_TRUE( m_oLeakTwo >= m_oLeakOne );
    m_oLeakTwo.line = m_oLeakOne.line;
    m_oLeakOne.line++;
    EXPECT_FALSE( m_oLeakOne >= m_oLeakTwo );
    EXPECT_TRUE( m_oLeakTwo >= m_oLeakOne );
}

TEST_F( LeakTest, GreaterThanOrEqualToOperatorSize )
{
    // Greater-than-or-equal-to operator returns false if first size is less
    // than second...
    m_oLeakOne.size = 1;
    EXPECT_FALSE( m_oLeakOne >= m_oLeakTwo );

    // ... true if vice-versa...
    EXPECT_TRUE( m_oLeakTwo >= m_oLeakOne );

    // ... with no change in result if first file name differs from second...
    m_oLeakOne.file = "";
    EXPECT_FALSE( m_oLeakOne >= m_oLeakTwo );
    EXPECT_TRUE( m_oLeakTwo >= m_oLeakOne );
    m_oLeakOne.file = sm_cpcFileNameCopyOne;
    m_oLeakTwo.file = "";
    EXPECT_FALSE( m_oLeakOne >= m_oLeakTwo );
    EXPECT_TRUE( m_oLeakTwo >= m_oLeakOne );
    m_oLeakTwo.file = sm_cpcFileNameCopyTwo;

    // ... or if first line number differs from second.
    m_oLeakTwo.line++;
    EXPECT_FALSE( m_oLeakOne >= m_oLeakTwo );
    EXPECT_TRUE( m_oLeakTwo >= m_oLeakOne );
    m_oLeakTwo.line = m_oLeakOne.line;
    m_oLeakOne.line++;
    EXPECT_FALSE( m_oLeakOne >= m_oLeakTwo );
    EXPECT_TRUE( m_oLeakTwo >= m_oLeakOne );
}

TEST_F( LeakTest, GreaterThanOrEqualToOperatorFile )
{
    // Greater-than-or-equal-to operator returns false if first file name is
    // less than second...
    m_oLeakOne.file = "";
    EXPECT_FALSE( m_oLeakOne >= m_oLeakTwo );

    // ... true if vice-versa...
    EXPECT_TRUE( m_oLeakTwo >= m_oLeakOne );

    // ... with no change in result if first line number differs from second.
    m_oLeakTwo.line++;
    EXPECT_FALSE( m_oLeakOne >= m_oLeakTwo );
    EXPECT_TRUE( m_oLeakTwo >= m_oLeakOne );
    m_oLeakTwo.line = m_oLeakOne.line;
    m_oLeakOne.line++;
    EXPECT_FALSE( m_oLeakOne >= m_oLeakTwo );
    EXPECT_TRUE( m_oLeakTwo >= m_oLeakOne );
}

TEST_F( LeakTest, GreaterThanOrEqualToOperatorLine )
{
    // Greater-than-or-equal-to operator returns false if first line number is
    // less than second...
    m_oLeakTwo.line++;
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
    m_oLeakTwo.pointer = &m_oLeakTwo;
    EXPECT_TRUE( m_oLeakOne < m_oLeakTwo );

    // ... false if vice-versa...
    EXPECT_FALSE( m_oLeakTwo < m_oLeakOne );

    // ... with no change in result if first size differs from second...
    m_oLeakOne.size = 1;
    EXPECT_TRUE( m_oLeakOne < m_oLeakTwo );
    EXPECT_FALSE( m_oLeakTwo < m_oLeakOne );
    m_oLeakOne.size = m_oLeakTwo.size;
    m_oLeakTwo.size = 1;
    EXPECT_TRUE( m_oLeakOne < m_oLeakTwo );
    EXPECT_FALSE( m_oLeakTwo < m_oLeakOne );
    m_oLeakTwo.size = m_oLeakOne.size;

    // ... or if first file name differs from second...
    m_oLeakOne.file = "";
    EXPECT_TRUE( m_oLeakOne < m_oLeakTwo );
    EXPECT_FALSE( m_oLeakTwo < m_oLeakOne );
    m_oLeakOne.file = sm_cpcFileNameCopyOne;
    m_oLeakTwo.file = "";
    EXPECT_TRUE( m_oLeakOne < m_oLeakTwo );
    EXPECT_FALSE( m_oLeakTwo < m_oLeakOne );
    m_oLeakTwo.file = sm_cpcFileNameCopyTwo;

    // ... or if first line number differs from second.
    m_oLeakTwo.line++;
    EXPECT_TRUE( m_oLeakOne < m_oLeakTwo );
    EXPECT_FALSE( m_oLeakTwo < m_oLeakOne );
    m_oLeakTwo.line = m_oLeakOne.line;
    m_oLeakOne.line++;
    EXPECT_TRUE( m_oLeakOne < m_oLeakTwo );
    EXPECT_FALSE( m_oLeakTwo < m_oLeakOne );
}

TEST_F( LeakTest, LessThanOperatorSize )
{
    // Less-than operator returns true if first size is less than second...
    m_oLeakOne.size = 1;
    EXPECT_TRUE( m_oLeakOne < m_oLeakTwo );

    // ... false if vice-versa...
    EXPECT_FALSE( m_oLeakTwo < m_oLeakOne );

    // ... with no change in result if first file name differs from second...
    m_oLeakOne.file = "";
    EXPECT_TRUE( m_oLeakOne < m_oLeakTwo );
    EXPECT_FALSE( m_oLeakTwo < m_oLeakOne );
    m_oLeakOne.file = sm_cpcFileNameCopyOne;
    m_oLeakTwo.file = "";
    EXPECT_TRUE( m_oLeakOne < m_oLeakTwo );
    EXPECT_FALSE( m_oLeakTwo < m_oLeakOne );
    m_oLeakTwo.file = sm_cpcFileNameCopyTwo;

    // ... or if first line number differs from second.
    m_oLeakTwo.line++;
    EXPECT_TRUE( m_oLeakOne < m_oLeakTwo );
    EXPECT_FALSE( m_oLeakTwo < m_oLeakOne );
    m_oLeakTwo.line = m_oLeakOne.line;
    m_oLeakOne.line++;
    EXPECT_TRUE( m_oLeakOne < m_oLeakTwo );
    EXPECT_FALSE( m_oLeakTwo < m_oLeakOne );
}

TEST_F( LeakTest, LessThanOperatorFile )
{
    // Less-than operator returns true if first file name is less than second...
    m_oLeakOne.file = "";
    EXPECT_TRUE( m_oLeakOne < m_oLeakTwo );

    // ... false if vice-versa...
    EXPECT_FALSE( m_oLeakTwo < m_oLeakOne );

    // ... with no change in result if first line number differs from second.
    m_oLeakTwo.line++;
    EXPECT_TRUE( m_oLeakOne < m_oLeakTwo );
    EXPECT_FALSE( m_oLeakTwo < m_oLeakOne );
    m_oLeakTwo.line = m_oLeakOne.line;
    m_oLeakOne.line++;
    EXPECT_TRUE( m_oLeakOne < m_oLeakTwo );
    EXPECT_FALSE( m_oLeakTwo < m_oLeakOne );
}

TEST_F( LeakTest, LessThanOperatorLine )
{
    // Less-than operator returns true if first line number is less than
    // second...
    m_oLeakTwo.line++;
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
    m_oLeakTwo.pointer = &m_oLeakTwo;
    EXPECT_TRUE( m_oLeakOne <= m_oLeakTwo );

    // ... false if vice-versa...
    EXPECT_FALSE( m_oLeakTwo <= m_oLeakOne );

    // ... with no change in result if first size differs from second...
    m_oLeakOne.size = 1;
    EXPECT_TRUE( m_oLeakOne <= m_oLeakTwo );
    EXPECT_FALSE( m_oLeakTwo <= m_oLeakOne );
    m_oLeakOne.size = m_oLeakTwo.size;
    m_oLeakTwo.size = 1;
    EXPECT_TRUE( m_oLeakOne <= m_oLeakTwo );
    EXPECT_FALSE( m_oLeakTwo <= m_oLeakOne );
    m_oLeakTwo.size = m_oLeakOne.size;

    // ... or if first file name differs from second...
    m_oLeakOne.file = "";
    EXPECT_TRUE( m_oLeakOne <= m_oLeakTwo );
    EXPECT_FALSE( m_oLeakTwo <= m_oLeakOne );
    m_oLeakOne.file = sm_cpcFileNameCopyOne;
    m_oLeakTwo.file = "";
    EXPECT_TRUE( m_oLeakOne <= m_oLeakTwo );
    EXPECT_FALSE( m_oLeakTwo <= m_oLeakOne );
    m_oLeakTwo.file = sm_cpcFileNameCopyTwo;

    // ... or if first line number differs from second.
    m_oLeakTwo.line++;
    EXPECT_TRUE( m_oLeakOne <= m_oLeakTwo );
    EXPECT_FALSE( m_oLeakTwo <= m_oLeakOne );
    m_oLeakTwo.line = m_oLeakOne.line;
    m_oLeakOne.line++;
    EXPECT_TRUE( m_oLeakOne <= m_oLeakTwo );
    EXPECT_FALSE( m_oLeakTwo <= m_oLeakOne );
}

TEST_F( LeakTest, LessThanOrEqualToOperatorSize )
{
    // Less-than-or-equal-to operator returns true if first size is less than
    // second...
    m_oLeakOne.size = 1;
    EXPECT_TRUE( m_oLeakOne <= m_oLeakTwo );

    // ... false if vice-versa...
    EXPECT_FALSE( m_oLeakTwo <= m_oLeakOne );

    // ... with no change in result if first file name differs from second...
    m_oLeakOne.file = "";
    EXPECT_TRUE( m_oLeakOne <= m_oLeakTwo );
    EXPECT_FALSE( m_oLeakTwo <= m_oLeakOne );
    m_oLeakOne.file = sm_cpcFileNameCopyOne;
    m_oLeakTwo.file = "";
    EXPECT_TRUE( m_oLeakOne <= m_oLeakTwo );
    EXPECT_FALSE( m_oLeakTwo <= m_oLeakOne );
    m_oLeakTwo.file = sm_cpcFileNameCopyTwo;

    // ... or if first line number differs from second.
    m_oLeakTwo.line++;
    EXPECT_TRUE( m_oLeakOne <= m_oLeakTwo );
    EXPECT_FALSE( m_oLeakTwo <= m_oLeakOne );
    m_oLeakTwo.line = m_oLeakOne.line;
    m_oLeakOne.line++;
    EXPECT_TRUE( m_oLeakOne <= m_oLeakTwo );
    EXPECT_FALSE( m_oLeakTwo <= m_oLeakOne );
}

TEST_F( LeakTest, LessThanOrEqualToOperatorFile )
{
    // Less-than-or-equal-to operator returns true if first file name is less
    // than second...
    m_oLeakOne.file = "";
    EXPECT_TRUE( m_oLeakOne <= m_oLeakTwo );

    // ... false if vice-versa...
    EXPECT_FALSE( m_oLeakTwo <= m_oLeakOne );

    // ... with no change in result if first line number differs from second.
    m_oLeakTwo.line++;
    EXPECT_TRUE( m_oLeakOne <= m_oLeakTwo );
    EXPECT_FALSE( m_oLeakTwo <= m_oLeakOne );
    m_oLeakTwo.line = m_oLeakOne.line;
    m_oLeakOne.line++;
    EXPECT_TRUE( m_oLeakOne <= m_oLeakTwo );
    EXPECT_FALSE( m_oLeakTwo <= m_oLeakOne );
}

TEST_F( LeakTest, LessThanOrEqualToOperatorLine )
{
    // Less-than-or-equal-to operator returns true if first line number is less
    // than second...
    m_oLeakTwo.line++;
    EXPECT_TRUE( m_oLeakOne <= m_oLeakTwo );

    // ... false if vice-versa.
    EXPECT_FALSE( m_oLeakTwo <= m_oLeakOne );
}
