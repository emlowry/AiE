/******************************************************************************
 * File:               Hashable.h
 * Author:             Elizabeth Lowry
 * Date Created:       February 18, 2014
 * Description:        Abstract parent class for objects that can be hashed.
 * Last Modified:      February 24, 2014
 * Last Modification:  Moved into Utility namespace from MyFirstEngine project.
 ******************************************************************************/

#ifndef HASHABLE__H
#define HASHABLE__H

#include <functional>
#include "ImExportMacro.h"

namespace Utility
{

class IMEXPORT_CLASS Hashable
{
public:
    virtual ~Hashable() {}
    virtual std::size_t Hash() const = 0;
};

}   // namespace Utility

namespace std
{

template<>
struct hash< Utility::Hashable >
{
    typedef size_t result_type;
    typedef const Utility::Hashable& argument_type;
    size_t operator()( const Utility::Hashable& ac_roHashable ) const
    { return ac_roHashable.Hash(); }
};

}   // namespace std

#endif  // HASHABLE__H
