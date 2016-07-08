#pragma once

template <typename T> class SmartPointer
{

private:

   struct ReferenceCount
   {
      int increment()
      {
         return (++count);
      }

      int decrement()
      {
         return (--count);
      }

      int count;
   };

public:

   // Constructor.
   SmartPointer() :
      dataPointer(0),
      referenceCount(0)
   {
      printf("Constructor()\n");

      referenceCount = new ReferenceCount();
      increment();
   }

   // Constructor.
   SmartPointer(
      T* dataPtr) :
         dataPointer(dataPtr),
         referenceCount(0)
   {
      printf("Constructor(T* dataPtr)\n");

      referenceCount = new ReferenceCount();
      increment();
   }

   // Copy constructor.
   SmartPointer(
      const SmartPointer<T>& smartPtr) :
         dataPointer(smartPtr.dataPointer),
         referenceCount(smartPtr.referenceCount)
   {
      printf("Copy Constructor(SmartPtr<T? smartPtr)\n");

      increment();
   }

   // Destructor.
   virtual ~SmartPointer()
   {
      decrement();
   }

   // Dereference operator.
   T& operator*()
   {
      return (*dataPointer);
   }

   // Dereference operator.
   T* operator->()
   {
      return (dataPointer);
   }

   // Assignment operator
   virtual SmartPointer<T>& operator=(
      const SmartPointer<T>& smartPtr)
   {
      printf("Assignment operator this[%d], smartPtr[%d]\n", this, &smartPtr);

      if (this != &smartPtr)
      {
         // Decrement, because we're no longer pointing at our old value.
         decrement();

         // Copy the data and reference pointer.
         dataPointer = smartPtr.dataPointer;
         referenceCount = smartPtr.referenceCount;

         printf("Reference count is now %d\n", referenceCount);

         // Increment, because now we're pointing at a new value.
         increment();
      }

      return (*this);
   }

   // Equality operator
   bool operator==(
      const SmartPointer<T>& smartPtr)
   {
      return (*this == smartPtr);
   }

   // Inequality operator
   bool operator!=(
      const SmartPointer<T>& smartPtr)
   {
      return (!(*this == smartPtr));
   }

   // Equality operator
   bool operator==(
      const void* voidPtr)
   {
      return (dataPointer == voidPtr);
   }

   // Inequality operator
   bool operator!=(
      const void* voidPtr)
   {
      return (!(*this == voidPtr));
   }

protected:

   virtual void increment()
   {
      referenceCount->increment();
      printf("referenceCount++ %d\n", referenceCount->count);
   }

   virtual void decrement()
   {
      referenceCount->decrement();
      printf("referenceCount-- %d\n", referenceCount->count);

      if (referenceCount->count == 0)
      {
         destroy();
      }
   }

   virtual void destroy()
   {
      printf("Destroy\n");

      delete dataPointer;
      delete referenceCount;
   }

    T* dataPointer;

    ReferenceCount* referenceCount;
};
