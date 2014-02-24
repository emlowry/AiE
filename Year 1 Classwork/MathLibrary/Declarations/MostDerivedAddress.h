/******************************************************************************
 * File:               MostDerivedAddress.h
 * Author:             Elizabeth Lowry
 * Date Created:       December 17, 2013
 * Description:        Base class that provides a function for returning a const
 *                      void pointer to the most derived object pointed to by
 *                      the object's this pointer.
 * Last Modified:      December 17, 2013
 * Last Modification:  Creation.
 ******************************************************************************/

#ifndef MOST_DERIVED_ADDRESS__H
#define MOST_DERIVED_ADDRESS__H

#include "ImExportMacro.h"

namespace Utility
{

class IMEXPORT_CLASS MostDerivedAddress
{
public:
    virtual ~MostDerivedAddress() {}
    const void* Address() const { return dynamic_cast< const void* >( this ); }
};

}   // namespace Utility

#endif  // MOST_DERIVED_ADDRESS__H
