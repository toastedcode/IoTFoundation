#pragma once

template <typename TYPE, unsigned int SIZE>
class Pool
{

public:

   Pool() :
      freeCount(SIZE)
   {
   }

   int size()
   {
      return (SIZE);
   }

   int getFreeCount()
   {
      return (freeCount);
   }

   int getUsedCount()
   {
      return (SIZE - freeCount);
   }

   TYPE* getFromPool()
   {
      TYPE* value = 0;

      for (int i = 0; i < SIZE; i++)
      {
         if (entries[i].isFree == true)
         {
            // Call the default constructor on the memory allocation to initialize the value.
            new (&(entries[i].value)) TYPE();

            // Mark as in use.
            entries[i].isFree = false;

            // Decrement our free count and return this value from the pool.
            value = &(entries[i].value);
            freeCount--;
            break;
         }
      }

      return (value);
   }

   void returnToPool(
      TYPE* valuePtr)
   {
      for (int i = 0; i < SIZE; i++)
      {
         if ((&(entries[i].value) == valuePtr) &&
             (entries[i].isFree == false))
         {
            entries[i].isFree = true;
            freeCount++;
            break;
         }
      }
   }

private:

   struct Entry
   {
      TYPE value;

      bool isFree;

      Entry() :
         isFree(true)
      {
      }
   };

   Entry entries[SIZE];

   int freeCount;
};
