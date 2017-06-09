#include "Address.hpp"
#include "StringUtils.hpp"

Address::Address() :
   numTokens(0)
{
}

Address::Address(
   const String& addressString) :
      numTokens(0)
{
   parse(addressString);
}

Address::~Address()
{

}

int Address::length() const
{
   return (numTokens);
}

void Address::parse(
   const String& addressString)
{
   numTokens = 0;

   String nonConstString = addressString;

   String tempTokens[MAX_TOKENS];
   int i = 0;

   // Tokenize.
   String token = StringUtils::tokenize(nonConstString, MESSAGE_HANDLER_ID_SEPARATOR);
   while ((token != "") &&
          (i < MAX_TOKENS))
   {
      tempTokens[i] = token;

      i++;
      token = StringUtils::tokenize(nonConstString, MESSAGE_HANDLER_ID_SEPARATOR);
   }

   // Push on in reverse order.
   for (int j = i; j > 0; j--)
   {
      push(tempTokens[j - 1]);
   }
}

HandlerId Address::getTop() const
{
   String token = "";

   if (numTokens > 0)
   {
      token = tokens[numTokens - 1];
   }

   return (token);
}

void Address::push(
   const HandlerId& handlerId)
{
   if (numTokens < MAX_TOKENS)
   {
      tokens[numTokens] = handlerId;
      numTokens++;
   }
}

HandlerId Address::pop()
{
   HandlerId handlerId = "";

   if (numTokens > 0)
   {
      handlerId = tokens[numTokens - 1];
      tokens[numTokens - 1] = "";
      numTokens--;
   }

   return (handlerId);
}

String Address::toString() const
{
   String addressString = "";

   for (int i = numTokens; i > 0; i--)
   {
      if (i < numTokens)
      {
         addressString += MESSAGE_HANDLER_ID_SEPARATOR;
      }

      addressString += tokens[i - 1];
   }

   return (addressString);
}
