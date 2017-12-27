#pragma once

#include "LinkedList.hpp"
#include "Set.hpp"

template <typename T>
class ListSet : public Set<T>
{

public:

   typedef typename LinkedList<T>::Iterator Iterator;

   ListSet();

   virtual ~ListSet();

   virtual typename List<T>::Iterator begin() const;

   virtual void clear();

   virtual typename List<T>::Iterator end() const;

   virtual typename List<T>::Iterator erase(
      const T& value);

   virtual void erase(
      const typename List<T>::Iterator& iterator);

   virtual const typename List<T>::Iterator find(
      const T& value) const;

   virtual typename List<T>::Iterator insert(
         const T& value);

   virtual unsigned int size() const;

private:

   LinkedList<T> list;
};

template<typename T>
ListSet<T>::ListSet()
{  
}

template<typename T>
ListSet<T>::~ListSet()
{
   list.clear();
}

template<typename T>
typename List<T>::Iterator ListSet<T>::begin() const
{
   return (list.begin());
}

template<typename T>
void ListSet<T>::clear()
{
  list.clear();
}

template<typename T>
typename List<T>::Iterator ListSet<T>::end() const
{
   return (list.end());
}

template<typename T>
typename List<T>::Iterator erase(
   const T& value)
{
   // TODO
}

template<typename T>
typename List<T>::Iterator ListSet<T>::erase(
   const T& value)
{
   typename List<T>::Iterator findIt = find(value);
   if (findIt != end())
   {
      list.erase(findIt);
   }
}

template<typename T>
void ListSet<T>::erase(
   const typename List<T>::Iterator& iterator)
{
   list.erase(iterator);
}

template<typename T>
const typename List<T>::Iterator ListSet<T>::find(
   const T& value) const
{
   typename List<T>::Iterator foundIt = this->end();
   
   for (typename Set<T>::Iterator it = this->begin(); it != this->end(); it++)
   {
      if ((*it) == value)
      {
         foundIt = it;
         break;
      }
   }

   return (foundIt);
}

template<typename T>
typename List<T>::Iterator ListSet<T>::insert(
   const T& value)
{
   typename List<T>::Iterator foundIt = find(value);

   if (foundIt == end())
   {
      list.add(value);
   }

   return (begin());  //  TODO: Return actual iterator.
}

template<typename T>
unsigned int ListSet<T>::size() const
{
   return (list.length());
}
