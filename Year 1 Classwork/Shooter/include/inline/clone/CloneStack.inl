/******************************************************************************
 * File:               CloneStack.inl
 * Author:             Elizabeth Lowry
 * Date Created:       November 12, 2013
 * Description:        Inline function implementations for CloneStack.h.
 * Last Modified:      November 12, 2013
 * Last Modification:  Creation.
 ******************************************************************************/

#ifndef _CLONE__CLONE_STACK_INL_
#define _CLONE__CLONE_STACK_INL_

// Is the stack empty?
template< typename T >
bool CloneStack< T >::IsEmpty() const
{
    return stack_type::empty();
}

// Add a clone of the given object to the stack
template< typename T >
void CloneStack< T >::Push( const T& ac_roValue )
{
    stack_type::push( ac_roValue.Clone() );
}

// Remove and deallocate the topmost element of the stack
template< typename T >
void CloneStack< T >::Pop()
{
    if( !IsEmpty() )
    {
        T* poValue = stack_type::top();
        stack_type::pop();
        if( nullptr != poValue )
        {
            delete poValue;
        }
    }
}

// How many elements are in the stack?
template< typename T >
std::size_t CloneStack< T >::Size() const
{
    return stack_type::size();
}

// Return a reference to the topmost element of the stack
template< typename T >
T& CloneStack< T >::Top()
{
    return *( stack_type::top() );
}

#endif  // _CLONE__CLONE_STACK_INL_