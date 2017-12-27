#pragma once

#include "List.hpp"

template <typename T>
class Set
{

public:

   typedef typename List<T>::Iterator Iterator;

   virtual Iterator begin() const = 0;

   virtual void clear() = 0;

   virtual Iterator end() const = 0;

   virtual Iterator erase(
      const T& value) = 0;

   virtual void erase(
      const Iterator& iterator) = 0;

   virtual const Iterator find(
      const T& value) const = 0;

   virtual Iterator insert(
         const T& value);

   virtual unsigned int size() const = 0;

   void operator=(
      const Set<T>& copyObject);

   bool operator==(
      const Set<T>& rhs);
};

// Assignment operator.
template<class T>
void Set<T>::operator=(
   const Set<T>& copyObject)
{
   if (this != &copyObject)
   {
      clear();

      for (typename Set<T>::Iterator it = copyObject.begin(); it != copyObject.end(); it++)
      {
         insert(*it);
      }
   }
}

// Comparison operator.
template<class T>
bool Set<T>::operator==(
   const Set<T>& rhs)
{
   bool equal = false;

   if (this->size() == rhs.size())
   {
      equal = true;

      typename List<T>::Iterator it = this->begin();
      typename List<T>::Iterator ot = rhs.begin();

      for (; it != this->end(); it++, ot++)
      {
         if (!(equal &= ((*it) == (*ot))))
         {
            break;
         }
      }
   }

   return (equal);
}
