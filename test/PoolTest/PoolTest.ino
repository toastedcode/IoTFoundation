#include <Arduino.h>
#include "Pool.hpp"

struct BigDataStructure
{
   char buffer[100];
};

void setup()
{
   Serial.begin(9600);

   Serial.printf("Heap before: %d\n", ESP.getFreeHeap());

   Serial.printf("Creating pool of 500 big BigDataStructure\n");
   Pool<BigDataStructure> myPool(50);
   BigDataStructure* myStructs[50];

   Serial.printf("Heap during: %d\n", ESP.getFreeHeap());

   Serial.printf("Pool size: %d\n", myPool.size());
   Serial.printf("Free size: %d\n", myPool.freeSize());

   Serial.printf("Testing getFree() (50 iterations)\n");
   for (int i = 0; i < 50; i++)
   {
      myStructs[i] = myPool.getFree();
      ESP.wdtFeed();
   }

   Serial.printf("Free size: %d\n", myPool.freeSize());

   BigDataStructure* myStruct = myPool.getFree();
   Serial.printf("Testing empty pool: myStruct %s null\n", (myStruct == 0) ? "is" : "is not");

   Serial.printf("Testing getFree() (50 iterations)\n");
   for (int i = 0; i < 50; i++)
   {
      myPool.setFree(myStructs[i]);

      ESP.wdtFeed();
   }
   
   Serial.printf("Free size: %d\n", myPool.freeSize());

   Serial.printf("Heap after: %d\n", ESP.getFreeHeap());
}

void loop()
{
}
