/******************************************************************************
 * File:               Hashable.h
 * Author:             Elizabeth Lowry
 * Date Created:       February 18, 2014
 * Description:        Abstract parent class for objects that can be hashed.
 * Last Modified:      February 18, 2014
 * Last Modification:  Creation.
 ******************************************************************************/

#ifndef HASHABLE__H
#define HASHABLE__H

#include <functional>
#include "MyFirstEngineMacros.h"

class IMEXPORT_CLASS Hashable
{
public:
    virtual ~Hashable() {}
    virtual std::size_t Hash() const = 0;
};
template<>
struct std::hash< Hashable >
{
    typedef std::size_t result_type;
    typedef const Hashable& argument_type;
    std::size_t operator()( const Hashable& ac_roHashable ) const
    { return ac_roHashable.Hash(); }
};

#endif  // HASHABLE__H
