/******************************************************************************
 * File:               Hashable.inl
 * Author:             Elizabeth Lowry
 * Date Created:       October 29, 2013
 * Description:        Inline function implementations for Hashable.h.
 * Last Modified:      October 29, 2013
 * Last Modification:  Moved code out of Globals.inl.
 ******************************************************************************/

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

// Functor implementations
inline std::size_t
    std::hash< Hashable >::operator()( const Hashable& ac_roHashable ) const
{
    return ac_roHashable.Hash();
}
inline std::size_t
    HashablePointerHash::operator()( const Hashable* const ac_cpoHashable) const
{
    return ( nullptr == ac_cpoHashable ) ? 0 : ac_cpoHashable->Hash();
}
inline bool
    HashablePointerLess::operator()( const Hashable* const ac_cpoFirst,
                                     const Hashable* const ac_cpoSecond ) const
{
    return ( nullptr == ac_cpoFirst) ? ( nullptr == ac_cpoSecond )
                                     : ( nullptr == ac_cpoSecond ) ? false
                                     : ( ac_cpoFirst->Hash() < ac_cpoSecond->Hash() );
}
