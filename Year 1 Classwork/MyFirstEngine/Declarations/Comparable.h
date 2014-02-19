/******************************************************************************
 * File:               Comparable.h
 * Author:             Elizabeth Lowry
 * Date Created:       February 18, 2014
 * Description:        Abstract parent class for objects that can be compared.
 * Last Modified:      February 18, 2014
 * Last Modification:  Creation.
 ******************************************************************************/

#ifndef COMPARABLE__H
#define COMPARABLE__H

#include <type_traits>  // for conditional and is_fundamental

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
};

#endif  // COMPARABLE__H
