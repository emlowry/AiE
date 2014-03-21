/******************************************************************************
 * File:               DynamicArray.inl
 * Author:             Elizabeth Lowry
 * Date Created:       March 20, 2014
 * Description:        Function implementations for DynamicArray.
 * Last Modified:      March 20, 2014
 * Last Modification:  Debugging.
 ******************************************************************************/

#ifndef DYNAMIC_ARRAY__INL
#define DYNAMIC_ARRAY__INL

#include "../Declarations/DynamicArray.h"

namespace Utility
{

// empty array
template< typename T >
const DynamicArray< T > DynamicArray< T >::EMPTY = DynamicArray< T >( 0 );

// default constructor
template< typename T >
DynamicArray< T >::DynamicArray( unsigned int a_uiSize )
    : m_uiSize( a_uiSize ),
      m_paData( 0 == a_uiSize ? nullptr : new T[ a_uiSize ] ) {}
template< typename T >
DynamicArray< T >::DynamicArray( unsigned int a_uiSize, const T& ac_rFill )
    : m_uiSize( a_uiSize ),
      m_paData( 0 == a_uiSize ? nullptr : new T[ a_uiSize ] )
{
    Fill( ac_rFill );
}

// construct from data
template< typename T >
DynamicArray< T >::DynamicArray( const T& ac_rData )
    : m_uiSize( 1 ), m_paData( new T[1] )
{
    CopyData( &ac_rData, 1 );
}
template< typename T >
DynamicArray< T >::DynamicArray( const T* a_pacData, unsigned int a_uiSize )
    : m_uiSize( nullptr == a_pacData ? 0 : a_uiSize ),
      m_paData( 0 == a_uiSize || nullptr == a_pacData ? nullptr
                                                      : new T[ a_uiSize ] )
{
    if( 0 < m_uiSize )
    {
        CopyData( a_pacData, a_uiSize );
    }
}

// copy construct
template< typename T >
DynamicArray< T >::DynamicArray( const DynamicArray& ac_roArray )
    : m_uiSize( nullptr == ac_roArray.m_paData ? 0 : ac_roArray.m_uiSize ),
      m_paData( 0 == ac_roArray.m_uiSize || nullptr == ac_roArray.m_paData
                ? nullptr : new T[ ac_roArray.m_uiSize ] )
{
    if( 0 < m_uiSize )
    {
        CopyData( ac_roArray.m_paData, ac_roArray.m_uiSize );
    }
}

// destroy
template< typename T >
DynamicArray< T >::~DynamicArray()
{
    if( nullptr != m_paData )
    {
        m_uiSize = 0;
        T* paData = m_paData;
        m_paData = nullptr;
        delete[] paData;
    }
}

// copy assign
template< typename T >
DynamicArray< T >&
    DynamicArray< T >::operator=( const DynamicArray& ac_roArray )
{
    if( &ac_roArray.m_uiSize != &m_uiSize )
    {
        SetSize( nullptr == ac_roArray.m_paData ? 0 : ac_roArray.m_uiSize );
        if( 0 < m_uiSize )
        {
            CopyData( ac_roArray.m_paData, ac_roArray.m_uiSize );
        }
    }
    return *this;
}

// assign size of 1
template< typename T >
DynamicArray< T >& DynamicArray< T >::operator=( const T& ac_rData )
{
    SetSize( 1 );
    CopyData( &ac_rData, 1 );
    return *this;
}

// access array elements
template< typename T >
T& DynamicArray< T >::operator[]( unsigned int a_uiIndex )
{
    if( nullptr == m_paData || a_uiIndex >= m_uiSize )
    {
        throw std::out_of_range( "Index outside array bounds" );
    }
    return m_paData[ a_uiIndex ];
}
template< typename T >
const T& DynamicArray< T >::operator[]( unsigned int a_uiIndex ) const
{
    if( nullptr == m_paData || a_uiIndex >= m_uiSize )
    {
        throw std::out_of_range( "Index outside array bounds" );
    }
    return m_paData[ a_uiIndex ];
}

// manage array size
template< typename T >
DynamicArray< T >& DynamicArray< T >::SetSize( unsigned int a_uiSize )
{
    if( a_uiSize != m_uiSize )
    {
        T* paData = m_paData;
        m_paData = ( 0 == a_uiSize ? nullptr : new T[ a_uiSize ] );
        CopyData( paData, a_uiSize );
        m_uiSize = a_uiSize;
        if( nullptr != paData )
        {
            delete[] paData;
        }
    }
    return *this;
}
template< typename T >
DynamicArray< T >& DynamicArray< T >::SetSize( unsigned int a_uiSize,
                                               const T& ac_rFill )
{
    unsigned int uiSize = m_uiSize;
    SetSize( a_uiSize );
    for( unsigned int ui = uiSize; ui < m_uiSize; ++ui )
    {
        m_paData[ ui ] = ac_rFill;
    }
    return *this;
}

// set all elements to the given value
template< typename T >
DynamicArray< T >& DynamicArray< T >::Fill( const T& ac_rFill )
{
    for( unsigned int ui = 0; ui < m_uiSize; ++ui )
    {
        m_paData[ui] = ac_rFill;
    }
    return *this;
}

// copy data
template< typename T >
DynamicArray< T >& DynamicArray< T >::CopyData( const T* a_pacData,
                                                unsigned int a_uiSize,
                                                unsigned int a_uiStart )
{
    if( nullptr != m_paData && nullptr != a_pacData &&
        0 < a_uiSize && a_uiStart < m_uiSize )
    {
        unsigned int uiSize = ( m_uiSize - a_uiStart < a_uiSize
                                ? m_uiSize - a_uiStart : a_uiSize );
        T* paData = m_paData + a_uiStart;
        for( unsigned int ui = 0; ui < uiSize; ++ui )
        {
            paData[ ui ] = a_pacData[ ui ];
        }
    }
    return *this;
}

}   // namespace Utility

#endif  // DYNAMIC_ARRAY__INL
