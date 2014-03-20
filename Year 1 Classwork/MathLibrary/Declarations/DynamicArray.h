/******************************************************************************
 * File:               DynamicArray.h
 * Author:             Elizabeth Lowry
 * Date Created:       March 11, 2014
 * Description:        Class representing an array that can be resized.
 * Last Modified:      March 17, 2014
 * Last Modification:  Debugging.
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
    DynamicArray( unsigned int a_uiSize = 0 )
        : m_uiSize( a_uiSize ),
          m_paData( 0 == a_uiSize ? nullptr : new T[ a_uiSize ] ) {}
    DynamicArray( unsigned int a_uiSize, const T& ac_rFill )
        : m_uiSize( a_uiSize ),
          m_paData( 0 == a_uiSize ? nullptr : new T[ a_uiSize ] )
    {
        Fill( ac_rFill );
    }

    // construct from data
    DynamicArray( const T& ac_rData )
        : m_uiSize( 1 ), m_paData( new Frame[1] )
    {
        CopyData( &ac_rData, 1 );
    }
    DynamicArray( const T* a_pacData, unsigned int a_uiSize )
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
    DynamicArray( const DynamicArray& ac_roArray )
        : m_uiSize( nullptr == ac_roArray.m_paData ? 0 : ac_roArray.m_uiSize ),
          m_paData( 0 == a_uiSize || nullptr == a_pacData ? nullptr
                                                          : new T[ a_uiSize ] )
    {
        if( 0 < m_uiSize )
        {
            CopyData( ac_roArray.m_paData, ac_roArray.m_uiSize );
        }
    }

    // destroy
    virtual ~DynamicArray()
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
    DynamicArray& operator=( const DynamicArray& ac_roArray )
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
    DynamicArray& operator=( const T& ac_rData )
    {
        SetSize( 1 );
        CopyData( &ac_rData, 1 );
    }

    // access array elements
    T& operator[]( unsigned int a_uiIndex )
    {
        if( nullptr == m_paData || a_uiIndex >= m_uiSize )
        {
            throw std::out_of_range( "Index outside array bounds" );
        }
        return m_paData[ a_uiIndex ];
    }
    const T& operator[]( unsigned int a_uiIndex ) const
    {
        if( nullptr == m_paData || a_uiIndex >= m_uiSize )
        {
            throw std::out_of_range( "Index outside array bounds" );
        }
        return m_paData[ a_uiIndex ];
    }

    // manage array size
    unsigned int Size() const { return m_uiSize; }
    DynamicArray& SetSize( unsigned int a_uiSize )
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
    DynamicArray& SetSize( unsigned int a_uiSize, const T& ac_rFill )
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
    DynamicArray& Fill( const T& ac_rFill )
    {
        for( unsigned int ui = 0; ui < m_uiSize; ++ui )
        {
            m_paData[ui] = ac_rFill;
        }
    }

    // copy data
    DynamicArray& CopyData( const T* a_pacData, unsigned int a_uiSize,
                            unsigned int a_uiStart = 0 )
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

    static const DynamicArray EMPTY;

protected:

    T* m_paData;
    unsigned int m_uiSize;

};  // class DynamicArray

template< typename T >
const DynamicArray< T > DynamicArray< T >::EMPTY = DynamicArray< T >( 0 );

}   // namespace Utility

#endif  // DYNAMIC_ARRAY__H
