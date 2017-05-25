#include "CommonDefs.hpp"
#include "MessagingDefs.hpp"

class Address
{

public:

   Address();

   Address(
      const String& addressString);

   virtual ~Address();

   int length() const;

   void parse(
      const String& addressString);

   HandlerId getTop() const;

   void push(
      const HandlerId& handlerId);

   HandlerId pop();

   String toString() const;

private:

   static const int MAX_TOKENS = 3;

   HandlerId tokens[MAX_TOKENS];

   int numTokens;
};
