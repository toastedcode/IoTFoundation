// *****************************************************************************
// *****************************************************************************
// StringUtils.cpp
//
// Author: Jason Tost
// Date:   7.26.2016
//
// *****************************************************************************

#include "StringUtils.hpp"

int StringUtils::findFirstOf(
   const String& string,
   const String& characters,
   const int& position)
{
   int firstPos = -1;

   for (int pos = 0; pos < characters.length(); pos++)
   {
      int foundPos = string.indexOf(characters.charAt(pos), position);

      if (foundPos != -1)
      {
#ifdef ARDUINO
         firstPos = (firstPos == -1) ? foundPos : min(firstPos, foundPos);
#else
         firstPos = (firstPos == -1) ? foundPos : std::min(firstPos, foundPos);
#endif
      }
   }

   return (firstPos);
}

int StringUtils::findFirstNotOf(
   const String& string,
   const String& characters,
   const int& position)
{
   int firstPos = -1;

   for (int pos = position; pos < string.length(); pos++)
   {
      int foundPos = characters.indexOf(string.charAt(pos), 0);

      if (foundPos == -1)
      {
         firstPos = pos;
         break;
      }
   }

   return (firstPos);
}

String StringUtils::tokenize(
   String& string,
   const String& delimiters)
{
   String token = "";

   // Strip off leading delimiters.
   while (findFirstOf(string, delimiters, 0) == 0)
   {
      string = string.substring(1);
   }

   // Now search for first occurance of a delimiter.
   int firstPos = findFirstOf(string, delimiters, 0);

   if (firstPos == -1)
   {
      token = string;
      string = "";
   }
   else
   {
      token = string.substring(0, firstPos);
      string = string.substring(firstPos + 1);
   }

   return (token);
}

String StringUtils::removeAll(
   const String& string,
   const String& characters)
{
   String newString;

   int startPos = 0;
   int foundPos = findFirstOf(string, characters, startPos);

   while (foundPos != -1)
   {
      if (foundPos != 0)
      {
         newString += string.substring(startPos, foundPos);
      }

      startPos = foundPos + 1;
      foundPos = findFirstOf(string, characters, startPos);
   }

   newString += string.substring(startPos, foundPos);

   return (newString);
}

bool StringUtils::toBool(
   const String& string)
{
   bool b = false;

   if (findFirstNotOf(string, "123456789.-") == -1)  // is numeric
   {
      b = (string.toInt() != 0);
   }
   else
   {
      // TODO: Another way that doesn't involve creating a String?
      String lowerCaseString = string;
      lowerCaseString.toLowerCase();

      b = (lowerCaseString == "true");
   }

   return (b);
}
