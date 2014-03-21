/******************************************************************************
 * File:               DynamicArray.h
 * Author:             Elizabeth Lowry
 * Date Created:       March 11, 2014
 * Description:        Class representing an array that can be resized.
 * Last Modified:      March 20, 2014
 * Last Modification:  Moving implementations to separate inl file.
 ******************************************************************************/

#ifndef DYNAMIC_ARRAY__H
#define DYNAMIC_ARRAY__H

#include <stdexcept>

namespace Utility
{

template< typename T >
class DynamicArray
{
public:

    // default constructor
    DynamicArray( unsigned int a_uiSize = 0 );
    DynamicArray( unsigned int a_uiSize, const T& ac_rFill );

    // construct from data
    DynamicArray( const T& ac_rData );
    DynamicArray( const T* a_pacData, unsigned int a_uiSize );

    // copy construct
    DynamicArray( const DynamicArray& ac_roArray );

    // destroy
    virtual ~DynamicArray();

    // copy assign
    DynamicArray& operator=( const DynamicArray& ac_roArray );

    // assign size of 1
    DynamicArray& operator=( const T& ac_rData );

    // access array elements
    T& operator[]( unsigned int a_uiIndex );
    const T& operator[]( unsigned int a_uiIndex ) const;

    // manage array size
    unsigned int Size() const { return m_uiSize; }
    DynamicArray& SetSize( unsigned int a_uiSize );
    DynamicArray& SetSize( unsigned int a_uiSize, const T& ac_rFill );

    // set all elements to the given value
    DynamicArray& Fill( const T& ac_rFill );

    // copy data
    DynamicArray& CopyData( const T* a_pacData, unsigned int a_uiSize,
                            unsigned int a_uiStart = 0 );

    static const DynamicArray EMPTY;

protected:

    T* m_paData;
    unsigned int m_uiSize;

};  // class DynamicArray

}   // namespace Utility

#include "../Implementations/DynamicArray.inl"

#endif  // DYNAMIC_ARRAY__H
