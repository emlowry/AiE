/******************************************************************************
 * File:               DynamicArray.h
 * Author:             Elizabeth Lowry
 * Date Created:       March 11, 2014
 * Description:        Class representing an array that can be resized.
 * Last Modified:      March 11, 2014
 * Last Modification:  Creation.
 ******************************************************************************/

#ifndef DYNAMIC_ARRAY__H
#define DYNAMIC_ARRAY__H

#include <stdexcept>
#include <type_traits>

namespace Utility
{

template< typename T >
class DynamicArray
{
public:

    // default constructor
    DynamicArray( unsigned int a_uiSize = 1 )
        : m_uiSize( a_uiSize ),
          m_paData( 0 == m_uiSize ? nullptr : new T[ m_uiSize ] ) {}

    // construct from data
    DynamicArray( const T& ac_rData )
        : m_uiSize( 1 ), m_paData( new Frame[1] )
    {
        CopyData( &ac_rData, 1 );
    }
    DynamicArray( const T* a_pacData, unsigned int a_uiSize )
        : m_uiSize( nullptr == a_pacData ? 0 : a_uiSize ),
          m_paData( 0 == m_uiSize ? nullptr : new T[ m_uiSize ] )
    {
        CopyData( a_pacData, a_uiSize );
    }

    // copy construct
    DynamicArray( const DynamicArray& ac_roArray )
        : m_uiSize( nullptr == ac_roArray.m_paData ? 0 : ac_roArray.m_uiSize ),
          m_paData( 0 == m_uiSize ? nullptr : new T[ m_uiSize ] )
    {
        CopyData( ac_roArray.m_paData, ac_roArray.m_uiSize );
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
            SetSize( ac_roArray.m_uiSize );
            CopyData( ac_roArray.m_paData, ac_roArray.m_uiSize );
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
                delete[] paoFrames;
            }
        }
        return *this;
    }

    // copy data
    DynamicArray& CopyData( const T* a_pacoData, unsigned int a_uiSize,
                            unsigned int a_uiStart = 0 )
    {
        if( nullptr != m_paoData && nullptr != a_pacoData &&
            0 < a_uiSize && a_uiStart < m_uiSize )
        {
            unsigned int uiSize = ( m_uiSize - a_uiStart < a_uiSize
                                    ? m_uiSize - a_uiStart : a_uiSize );
            if( std::is_trivially_assignable< T >() )
            {
                memcpy( m_paoData + a_uiStart, a_pacoData,
                        uiSize * sizeof( Frame ) );
            }
            else
            {
                Frame* paoData = m_paoData + a_uiStart;
                for( unsigned int ui = 0; ui < uiSize; ++ui )
                {
                    paoData[ ui ] = a_pacoData[ ui ];
                }
            }
        }
        return *this;
    }

protected:

    T* m_paData;
    unsigned int m_uiSize;

};  // class DynamicArray

}   // namespace Utility

#endif  // DYNAMIC_ARRAY__H
