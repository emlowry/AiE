/******************************************************************************
 * File:               CharacterMap.h
 * Author:             Elizabeth Lowry
 * Date Created:       March 21, 2014
 * Description:        Class mapping character symbols or codes to char values.
 * Last Modified:      March 21, 2014
 * Last Modification:  Creation.
 ******************************************************************************/

#ifndef CHARACTER_MAP__H
#define CHARACTER_MAP__H

#include "MyFirstEngineMacros.h"

namespace MyFirstEngine
{

class IMEXPORT_CLASS CharacterMap
{
public:

    CharacterMap();
    CharacterMap( const CharacterMap& ac_roMap );
    virtual ~CharacterMap();
    CharacterMap& operator=( const CharacterMap& ac_roMap );

    bool Has( const char* ac_pcName ) const;
    CharacterMap& Remove( const char* ac_pcName );
    char& operator[]( const char* ac_pcName );
    const char& operator[]( const char* ac_pcName ) const;

    // returned by const operator[] for symbols not in the map
    static const char ABSENT_CHARACTER = 0;

private:

    // PIMPLE idiom - this class is only defined in the cpp, so inheritance from
    // an stl container won't result in warnings.
    class CharacterLookup;
    CharacterLookup* m_poLookup;

};  // class CharacterMap

}   // namespace MyFirstEngine

#endif  // CHARACTER_MAP__H
