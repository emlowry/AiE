/******************************************************************************
 * File:               HTMLCharacters.cpp
 * Author:             Elizabeth Lowry
 * Date Created:       March 21, 2014
 * Description:        Initialization of HTML::Map.
 * Last Modified:      March 21, 2014
 * Last Modification:  Creation.
 ******************************************************************************/

#include "../Declarations/HTMLCharacters.h"
#include "../Declarations/CharacterMap.h"
#include "MathLibrary.h"
#include <sstream>

namespace
{
// create a character map for all the displayable ascii characters, mapping each
// character to itself, its hex code, its number code, and (if available) its
// html code
static MyFirstEngine::CharacterMap HTMLMap()
{
    MyFirstEngine::CharacterMap oHTML;
    std::stringstream oStream;

    // map all characters to their number codes( #___, x__ ) and to themselves
    for( unsigned int ui = 0; ui < 256; ++ui )
    {
        oStream.clear();
        oStream << std::ios::dec;
        oStream << ui;
        Utility::DumbString oNum( '#' );
        oNum += oStream.str().c_str();
        oStream.clear();
        oStream << std::ios::hex;
        oStream << ui;
        oNum = oStream.str().c_str() + 1;
        oHTML[ oNum ] =
            oHTML[ Utility::DumbString( (char)ui ) ] = (char)ui;
    }

    // map HTML codes
    oHTML[ "quot" ] = HTML::quot;
    oHTML[ "amp" ] = HTML::amp;
    oHTML[ "apos" ] = HTML::apos;
    oHTML[ "lt" ] = HTML::lt;
    oHTML[ "gt" ] = HTML::gt;
    oHTML[ "euro" ] = HTML::euro;
    oHTML[ "sbquo" ] = HTML::sbquo;
    oHTML[ "fnof" ] = HTML::fnof;
    oHTML[ "bdquo" ] = HTML::bdquo;
    oHTML[ "hellip" ] = HTML::hellip;
    oHTML[ "circ" ] = HTML::circ;
    oHTML[ "dagger" ] = HTML::dagger;
    oHTML[ "Dagger" ] = HTML::Dagger;
    oHTML[ "permil" ] = HTML::permil;
    oHTML[ "Scaron" ] = HTML::Scaron;
    oHTML[ "lsaquo" ] = HTML::lsaquo;
    oHTML[ "OElig" ] = HTML::OElig;
    oHTML[ "Zscaron" ] = HTML::Zcaron;
    oHTML[ "lsquo" ] = HTML::lsquo;
    oHTML[ "rsquo" ] = HTML::rsquo;
    oHTML[ "ldquo" ] = HTML::ldquo;
    oHTML[ "rdquo" ] = HTML::rdquo;
    oHTML[ "bull" ] = HTML::bull;
    oHTML[ "ndash" ] = HTML::ndash;
    oHTML[ "mdash" ] = HTML::mdash;
    oHTML[ "tilde" ] = HTML::tilde;
    oHTML[ "trade" ] = HTML::trade;
    oHTML[ "scaron" ] = HTML::scaron;
    oHTML[ "rsaquo" ] = HTML::rsaquo;
    oHTML[ "oelig" ] = HTML::oelig;
    oHTML[ "zcaron" ] = HTML::zcaron;
    oHTML[ "Yuml" ] = HTML::Yuml;
    oHTML[ "nbsp" ] = HTML::nbsp;
    oHTML[ "iexcl" ] = HTML::iexcl;
    oHTML[ "cent" ] = HTML::cent;
    oHTML[ "pound" ] = HTML::pound;
    oHTML[ "curren" ] = HTML::curren;
    oHTML[ "yen" ] = HTML::yen;
    oHTML[ "brvbar" ] = HTML::brvbar;
    oHTML[ "sect" ] = HTML::sect;
    oHTML[ "uml" ] = HTML::uml;
    oHTML[ "copy" ] = HTML::copy;
    oHTML[ "ordf" ] = HTML::ordf;
    oHTML[ "laquo" ] = HTML::laquo;
    oHTML[ "not" ] = HTML::not;
    oHTML[ "shy" ] = HTML::shy;
    oHTML[ "reg" ] = HTML::reg;
    oHTML[ "macr" ] = HTML::macr;
    oHTML[ "deg" ] = HTML::deg;
    oHTML[ "plusmn" ] = HTML::plusmn;
    oHTML[ "sup2" ] = HTML::sup2;
    oHTML[ "sup3" ] = HTML::sup3;
    oHTML[ "acute" ] = HTML::acute;
    oHTML[ "micro" ] = HTML::micro;
    oHTML[ "para" ] = HTML::para;
    oHTML[ "middot" ] = HTML::middot;
    oHTML[ "cedil" ] = HTML::cedil;
    oHTML[ "sup1" ] = HTML::sup1;
    oHTML[ "ordm" ] = HTML::ordm;
    oHTML[ "raquo" ] = HTML::raquo;
    oHTML[ "frac14" ] = HTML::frac14;
    oHTML[ "frac12" ] = HTML::frac12;
    oHTML[ "frac34" ] = HTML::frac34;
    oHTML[ "iquest" ] = HTML::iquest;
    oHTML[ "Agrave" ] = HTML::Agrave;
    oHTML[ "Aacute" ] = HTML::Aacute;
    oHTML[ "Acirc" ] = HTML::Acirc;
    oHTML[ "Atilde" ] = HTML::Atilde;
    oHTML[ "Auml" ] = HTML::Auml;
    oHTML[ "Aring" ] = HTML::Aring;
    oHTML[ "AElig" ] = HTML::AElig;
    oHTML[ "Ccedil" ] = HTML::Ccedil;
    oHTML[ "Egrave" ] = HTML::Egrave;
    oHTML[ "Eacute" ] = HTML::Eacute;
    oHTML[ "Ecirc" ] = HTML::Ecirc;
    oHTML[ "Euml" ] = HTML::Euml;
    oHTML[ "Igrave" ] = HTML::Igrave;
    oHTML[ "Iacute" ] = HTML::Iacute;
    oHTML[ "Icirc" ] = HTML::Icirc;
    oHTML[ "Iuml" ] = HTML::Iuml;
    oHTML[ "ETH" ] = HTML::ETH;
    oHTML[ "Ntilde" ] = HTML::Ntilde;
    oHTML[ "Ograve" ] = HTML::Ograve;
    oHTML[ "Oacute" ] = HTML::Oacute;
    oHTML[ "Ocirc" ] = HTML::Ocirc;
    oHTML[ "Otilde" ] = HTML::Otilde;
    oHTML[ "Ouml" ] = HTML::Ouml;
    oHTML[ "times" ] = HTML::times;
    oHTML[ "Oslash" ] = HTML::Oslash;
    oHTML[ "Ugrave" ] = HTML::Ugrave;
    oHTML[ "Uacute" ] = HTML::Uacute;
    oHTML[ "Ucirc" ] = HTML::Ucirc;
    oHTML[ "Uuml" ] = HTML::Uuml;
    oHTML[ "Yacute" ] = HTML::Yacute;
    oHTML[ "THORN" ] = HTML::THORN;
    oHTML[ "szlig" ] = HTML::szlig;
    oHTML[ "agrave" ] = HTML::agrave;
    oHTML[ "aacute" ] = HTML::aacute;
    oHTML[ "acirc" ] = HTML::acirc;
    oHTML[ "atilde" ] = HTML::atilde;
    oHTML[ "auml" ] = HTML::auml;
    oHTML[ "aring" ] = HTML::aring;
    oHTML[ "aelig" ] = HTML::aelig;
    oHTML[ "ccedil" ] = HTML::ccedil;
    oHTML[ "egrave" ] = HTML::egrave;
    oHTML[ "eacute" ] = HTML::eacute;
    oHTML[ "ecirc" ] = HTML::ecirc;
    oHTML[ "euml" ] = HTML::euml;
    oHTML[ "igrave" ] = HTML::igrave;
    oHTML[ "iacute" ] = HTML::iacute;
    oHTML[ "icirc" ] = HTML::icirc;
    oHTML[ "iuml" ] = HTML::iuml;
    oHTML[ "eth" ] = HTML::eth;
    oHTML[ "ntilde" ] = HTML::ntilde;
    oHTML[ "ograve" ] = HTML::ograve;
    oHTML[ "oacute" ] = HTML::oacute;
    oHTML[ "ocirc" ] = HTML::ocirc;
    oHTML[ "otilde" ] = HTML::otilde;
    oHTML[ "ouml" ] = HTML::ouml;
    oHTML[ "divide" ] = HTML::divide;
    oHTML[ "oslash" ] = HTML::oslash;
    oHTML[ "ugrave" ] = HTML::ugrave;
    oHTML[ "uacute" ] = HTML::uacute;
    oHTML[ "ucirc" ] = HTML::ucirc;
    oHTML[ "uuml" ] = HTML::uuml;
    oHTML[ "yacute" ] = HTML::yacute;
    oHTML[ "thorn" ] = HTML::thorn;
    oHTML[ "yuml" ] = HTML::yuml;

    // return the resulting character map
    return oHTML;
}   // HTMLMap()
}   // namespace

namespace HTML
{
const MyFirstEngine::CharacterMap& Map()
{
    static MyFirstEngine::CharacterMap soMap = HTMLMap();
    return soMap;
}
}