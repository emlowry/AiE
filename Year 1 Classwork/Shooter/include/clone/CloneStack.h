/******************************************************************************
 * File:               CloneStack.h
 * Author:             Elizabeth Lowry
 * Date Created:       November 12, 2013
 * Description:        Stack implementation that stores pointers to clones
 *                      instead of storing copies.  Assumes the template
 *                      parameter type has Cloneable as a base class.
 * Last Modified:      November 12, 2013
 * Last Modification:  Creation.
 ******************************************************************************/

#ifndef _CLONE__CLONE_STACK_H_
#define _CLONE__CLONE_STACK_H_

#include <stack>

template< typename T >
class CloneStack : private std::stack< T* >
{
public:

    bool IsEmpty() const;
    void Push( const T& ac_roValue );
    void Pop();
    std::size_t Size() const;
    T& Top();

protected:

    typedef std::stack< T* > stack_type;

};

#include "inline/clone/CloneStack.inl"

#endif  // _CLONE__CLONE_STACK_H_