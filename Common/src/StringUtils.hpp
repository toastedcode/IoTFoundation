// *****************************************************************************
// *****************************************************************************
// StringUtils.h
//
// Author: Jason Tost
// Date:   7.26.2016
//
// *****************************************************************************
// *****************************************************************************

#pragma once

#include "CommonDefs.hpp"

class StringUtils
{

public:

   // This operation searches a string for the first character that matches any of the specified characters.
   static int findFirstOf(
      // The string to search.
      const String& string,
      // A string containing the characters to search for.
      const String& characters,
      // The position in the string to start the search.
      const int& position = 0);

   // This operation searches a string for the first character that matches any of the specified characters.
   static int findFirstNotOf(
      // The string to search.
      const String& string,
      // A string containing the characters to search for.
      const String& characters,
      // The position in the string to start the search.
      const int& position = 0);

   // This operation returns the next token from the specified string, broken up by any of the specified delimiters.
   static String tokenize(
      // The string to tokenize.
      String& string,
      // A string containing the characters to search for.
      const String& delimiters);

   static String removeAll(
      const String& string,
      const String& characters);

   static bool toBool(
      const String& string);
};
