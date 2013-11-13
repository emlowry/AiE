/******************************************************************************
 * File:               Hashable.inl
 * Author:             Elizabeth Lowry
 * Date Created:       October 29, 2013
 * Description:        Inline function implementations for Hashable.h.
 * Last Modified:      October 29, 2013
 * Last Modification:  Moved code out of Globals.inl.
 ******************************************************************************/

#ifndef _HASHABLE_INL_
#define _HASHABLE_INL_

// Comparison operators
inline std::size_t Hashable::operator<( const Hashable& ac_roHashable ) const
{
    return Hash() < ac_roHashable.Hash();
}
inline std::size_t Hashable::operator>( const Hashable& ac_roHashable ) const
{
    return Hash() > ac_roHashable.Hash();
}
inline std::size_t Hashable::operator<=( const Hashable& ac_roHashable ) const
{
    return Hash() <= ac_roHashable.Hash();
}
inline std::size_t Hashable::operator>=( const Hashable& ac_roHashable ) const
{
    return Hash() >= ac_roHashable.Hash();
}
inline std::size_t Hashable::operator==( const Hashable& ac_roHashable ) const
{
    return Hash() == ac_roHashable.Hash();
}
inline std::size_t Hashable::operator!=( const Hashable& ac_roHashable ) const
{
    return Hash() != ac_roHashable.Hash();
}

#endif  // _HASHABLE_INL_
