/******************************************************************************
 * File:               CharacterMap.cpp
 * Author:             Elizabeth Lowry
 * Date Created:       March 21, 2014
 * Description:        Class mapping character symbols or codes to char values.
 * Last Modified:      March 21, 2014
 * Last Modification:  Creation.
 ******************************************************************************/

#include "../Declarations/CharacterMap.h"
#include "MathLibrary.h"
#include <unordered_map>

namespace MyFirstEngine
{

// PIMPLE idiom - this class is only defined in the cpp, so inheritance from
// an stl container won't result in warnings.
class CharacterMap::CharacterLookup
    : public std::unordered_map< Utility::DumbString, char >
{
public:
    typedef std::unordered_map< Utility::DumbString, char > BaseType;
    typedef BaseType::value_type ValueType;
    CharacterLookup() {}
    CharacterLookup( const CharacterLookup& ac_roLookup )
        : BaseType( ac_roLookup ) {}
    virtual ~CharacterLookup() {}
};

// Constructors
CharacterMap::CharacterMap() : m_poLookup( new CharacterLookup ) {}
CharacterMap::CharacterMap( const CharacterMap& ac_roMap )
    : m_poLookup( new CharacterLookup( *( ac_roMap.m_poLookup ) ) ) {}

// Destructor
CharacterMap::~CharacterMap()
{
    CharacterLookup* poLookup = m_poLookup;
    m_poLookup = nullptr;
    if( nullptr != poLookup )
    {
        delete poLookup;
    }
}

// Assignment operator
CharacterMap& CharacterMap::operator=( const CharacterMap& ac_roMap )
{
    if( this != &ac_roMap )
    {
        m_poLookup->clear();
        for each( CharacterLookup::ValueType oPair in *(ac_roMap.m_poLookup) )
        {
            (*m_poLookup)[ oPair.first ] = oPair.second;
        }
    }
    return *this;
}

// Does this character map associate the given symbol name with a character?
bool CharacterMap::Has( const char* ac_pcName ) const
{
    return ( 0 < m_poLookup->count( ac_pcName ) );
}

// Remove this map's association of the given symbol name with a character
CharacterMap& CharacterMap::Remove( const char* ac_pcName )
{
    m_poLookup->erase( ac_pcName );
    return *this;
}

// Get/Set character mappings directly
char& CharacterMap::operator[]( const char* ac_pcName )
{
    if( !Has( ac_pcName ) )
    {
        m_poLookup->emplace( CharacterLookup::ValueType( ac_pcName ,
                                                         ABSENT_CHARACTER ) );
    }
    return m_poLookup->at( ac_pcName );
}
const char& CharacterMap::operator[]( const char* ac_pcName ) const
{
    const CharacterLookup& croLookup = *m_poLookup;
    return ( Has( ac_pcName ) ? croLookup.at( ac_pcName ) : ABSENT_CHARACTER );
}

}   // namespace MyFirstEngine
