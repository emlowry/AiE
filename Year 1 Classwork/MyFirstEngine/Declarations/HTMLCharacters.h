/******************************************************************************
 * File:               HTMLCharacters.h
 * Author:             Elizabeth Lowry
 * Date Created:       March 21, 2014
 * Description:        Constants and character map for html extended ASCII.
 * Last Modified:      March 21, 2014
 * Last Modification:  Creation.
 ******************************************************************************/

#ifndef HTML_CHARACTERS__H
#define HTML_CHARACTERS__H

#include "CharacterMap.h"
#include "MyFirstEngineMacros.h"

// constants named after HTML symbols (such as &amp; or &quot;) with values
// of the associated html number (such as &#38; or &#34;, respectively)
namespace HTML
{

// Map for ASCII and ANSI extended ASCII characters mapped to their actual char
// values ("&" for '&'), numbers ("#38" or "x26" for '&'), and, if present, HTML
// names ("amp" for '&')
IMEXPORT const MyFirstEngine::CharacterMap& Map();

const char quot = '"';
const char amp = '&';
const char apos = '\'';
const char lt = '<';
const char gt = '>';

// taken from http://www.ascii-code.com/
const char euro = '\x80';
const char sbquo = '\x82';
const char fnof = '\x83';
const char bdquo = '\x84';
const char hellip = '\x85';
const char circ = '\x86';
const char dagger = '\x87';
const char Dagger = '\x88';
const char permil = '\x89';
const char Scaron = '\x8A';
const char lsaquo = '\x8B';
const char OElig = '\x8C';
const char Zcaron = '\x8E';
const char lsquo = '\x91';
const char rsquo = '\x92';
const char ldquo = '\x93';
const char rdquo = '\x94';
const char bull = '\x95';
const char ndash = '\x96';
const char mdash = '\x97';
const char tilde = '\x98';
const char trade = '\x99';
const char scaron = '\x9A';
const char rsaquo = '\x9B';
const char oelig = '\x9C';
const char zcaron = '\x9E';
const char Yuml = '\x9F';
const char nbsp = '\xA0';
const char iexcl = '\xA1';
const char cent = '\xA2';
const char pound = '\xA3';
const char curren = '\xA4';
const char yen = '\xA5';
const char brvbar = '\xA6';
const char sect = '\xA7';
const char uml = '\xA8';
const char copy = '\xA9';
const char ordf = '\xAA';
const char laquo = '\xAB';
const char not = '\xAC';
const char shy = '\xAD';
const char reg = '\xAE';
const char macr = '\xAF';
const char deg = '\xB0';
const char plusmn = '\xB1';
const char sup2 = '\xB2';
const char sup3 = '\xB3';
const char acute = '\xB4';
const char micro = '\xB5';
const char para = '\xB6';
const char middot = '\xB7';
const char cedil = '\xB8';
const char sup1 = '\xB9';
const char ordm = '\xBA';
const char raquo = '\xBB';
const char frac14 = '\xBC';
const char frac12 = '\xBD';
const char frac34 = '\xBE';
const char iquest = '\xBF';
const char Agrave = '\xC0';
const char Aacute = '\xC1';
const char Acirc = '\xC2';
const char Atilde = '\xC3';
const char Auml = '\xC4';
const char Aring = '\xC5';
const char AElig = '\xC6';
const char Ccedil = '\xC7';
const char Egrave = '\xC8';
const char Eacute = '\xC9';
const char Ecirc = '\xCA';
const char Euml = '\xCB';
const char Igrave = '\xCC';
const char Iacute = '\xCD';
const char Icirc = '\xCE';
const char Iuml = '\xCF';
const char ETH = '\xD0';
const char Ntilde = '\xD1';
const char Ograve = '\xD2';
const char Oacute = '\xD3';
const char Ocirc = '\xD4';
const char Otilde = '\xD5';
const char Ouml = '\xD6';
const char times = '\xD7';
const char Oslash = '\xD8';
const char Ugrave = '\xD9';
const char Uacute = '\xDA';
const char Ucirc = '\xDB';
const char Uuml = '\xDC';
const char Yacute = '\xDD';
const char THORN = '\xDE';
const char szlig = '\xDF';
const char agrave = '\xE0';
const char aacute = '\xE1';
const char acirc = '\xE2';
const char atilde = '\xE3';
const char auml = '\xE4';
const char aring = '\xE5';
const char aelig = '\xE6';
const char ccedil = '\xE7';
const char egrave = '\xE8';
const char eacute = '\xE9';
const char ecirc = '\xEA';
const char euml = '\xEB';
const char igrave = '\xEC';
const char iacute = '\xED';
const char icirc = '\xEE';
const char iuml = '\xEF';
const char eth = '\xF0';
const char ntilde = '\xF1';
const char ograve = '\xF2';
const char oacute = '\xF3';
const char ocirc = '\xF4';
const char otilde = '\xF5';
const char ouml = '\xF6';
const char divide = '\xF7';
const char oslash = '\xF8';
const char ugrave = '\xF9';
const char uacute = '\xFA';
const char ucirc = '\xFB';
const char uuml = '\xFC';
const char yacute = '\xFD';
const char thorn = '\xFE';
const char yuml = '\xFF';

}   // namespace HTML

#endif  // HTML_CHARACTERS__H

