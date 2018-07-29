#pragma once

#include "Set.hpp"

template <typename T>
class Pool
{

public:

   Pool();

   Pool(
      const int& size);

   ~Pool();

   void allocate(
      const int& size);

   unsigned int size() const;

   unsigned int freeSize() const;

   T* getFree();

   void setFree(
      T* value);

   const Set<T*>& inUseSet();

private:

   Set<T*> inUse;

   Set<T*> free;
};

template<class T>
Pool<T>::Pool()
{
}

template<class T>
Pool<T>::Pool(
   const int& size)
{
   allocate(size);
}

template<class T>
Pool<T>::~Pool()
{
   for (typename Set<T*>::Iterator it = free.begin(); it != free.end(); it++)
   {
      delete(*it);
   }
   free.clear();

   for (typename Set<T*>::Iterator it = inUse.begin(); it != inUse.end(); it++)
   {
      delete(*it);
   }
   inUse.clear();
}

template<class T>
void Pool<T>::allocate(
   const int& size)
{
   for (typename Set<T*>::Iterator it = free.begin(); it != free.end(); it++)
   {
      delete(*it);
   }
   free.clear();

   for (typename Set<T*>::Iterator it = inUse.begin(); it != inUse.end(); it++)
   {
      delete(*it);
   }
   inUse.clear();

   for (int i = 0; i < size; i++)
   {
      free.insert(new T());
   }
}

template<class T>
unsigned int Pool<T>::size() const
{
  return (free.size() + inUse.size());
}

template<class T>
unsigned int Pool<T>::freeSize() const
{
  return (free.size());
}

template<class T>
T* Pool<T>::getFree()
{
   T* value = 0;

   if (free.size() > 0)
   {
      value = *(free.begin());
      free.erase(value);
      inUse.insert(value);
   }

   return (value);
}

template<class T>
void Pool<T>::setFree(
   T* value)
{
   inUse.erase(value);
   free.insert(value);
}

template<class T>
const Set<T*>& Pool<T>::inUseSet()
{
   return (inUse);
}
