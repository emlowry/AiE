/******************************************************************************
 * File:               Comparable.h
 * Author:             Elizabeth Lowry
 * Date Created:       February 18, 2014
 * Description:        Abstract parent class for objects that can be compared.
 * Last Modified:      February 24, 2014
 * Last Modification:  Moved into Utility namespace from MyFirstEngine project.
 ******************************************************************************/

#ifndef COMPARABLE__H
#define COMPARABLE__H

#include <type_traits>  // for conditional and is_fundamental

namespace Utility
{

// Has a member function, Compare, which must be defined to return 0 if the
// object is equal to the parameter, -1 if the object is less than the
// parameter, or 1 if the object is less than the parameter.
template< typename T >
class Comparable
{
public:

    // simplify typing
    typedef
        typename std::conditional< std::is_fundamental< T >::value, T,
            typename std::conditional< std::is_pointer< T >::value,
                                       typename std::add_pointer<
                                        typename std::add_const<
                                         typename std::remove_pointer< T >::type
                                        >::type
                                       >::type,
                                       typename std::add_lvalue_reference<
                                        typename std::add_const< T >::type
                                       >::type
            >::type
        >::type CompareType;

    // destructor is virtual because there is inheritance
    virtual ~Comparable() {}

    // compare this object to the parameter
    virtual int Compare( CompareType a_Value ) const = 0;

    // Use the Compare function to implement the comparison operators
    bool operator==( CompareType a_Val ) const { return Compare( a_Val ) == 0; }
    bool operator!=( CompareType a_Val ) const { return Compare( a_Val ) != 0; }
    bool operator>=( CompareType a_Val ) const { return Compare( a_Val ) >= 0; }
    bool operator<=( CompareType a_Val ) const { return Compare( a_Val ) <= 0; }
    bool operator>( CompareType a_Val ) const { return Compare( a_Val ) > 0; }
    bool operator<( CompareType a_Val ) const { return Compare( a_Val ) < 0; }

};  // class Comparable

// default comparison function
template< typename T >
inline int SimpleCompare( const T& ac_roFirst, const T& ac_roSecond )
{
    return ( ac_roFirst == ac_roSecond
             ? 0
             : ( ac_roFirst > ac_roSecond ? 1 : -1 ) );
}

}   // namespace Utility

#endif  // COMPARABLE__H
