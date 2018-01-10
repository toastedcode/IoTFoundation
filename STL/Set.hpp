#pragma once

#include "List.hpp"

template <typename T>
class Set
{

public:

   typedef typename List<T>::Iterator Iterator;

   Set();

   virtual ~Set();

   virtual Iterator begin() const;

   virtual void clear();

   virtual Iterator end() const;

   virtual Iterator erase(
      const T& value);

   virtual void erase(
      const Iterator& iterator);

   virtual const Iterator find(
      const T& value) const;

   virtual Iterator insert(
      const T& value);

   virtual unsigned int size() const;

   virtual bool operator==(
      const Set<T>& rhs) const;

   virtual Set<T>& operator=(
      const Set<T>& rhs);

private:

   List<T> list;
};

template<typename T>
Set<T>::Set()
{  
}

template<typename T>
Set<T>::~Set()
{
   list.clear();
}

template<typename T>
typename List<T>::Iterator Set<T>::begin() const
{
   return (list.begin());
}

template<typename T>
void Set<T>::clear()
{
  list.clear();
}

template<typename T>
typename Set<T>::Iterator Set<T>::end() const
{
   return (list.end());
}

template<typename T>
typename Set<T>::Iterator Set<T>::erase(
   const T& value)
{
   list.remove(value);
}

template<typename T>
void Set<T>::erase(
   const typename Set<T>::Iterator& iterator)
{
   list.erase(iterator);
}

template<typename T>
const typename Set<T>::Iterator Set<T>::find(
   const T& value) const
{
   return list.find(value);
}

template<typename T>
typename Set<T>::Iterator Set<T>::insert(
   const T& value)
{
   typename Set<T>::Iterator foundIt = find(value);

   if (foundIt == end())
   {
      list.push_back(value);
   }

   return (begin());  //  TODO: Return actual iterator.
}

template<typename T>
unsigned int Set<T>::size() const
{
   return (list.size());
}

// Assignment operator.
template<class T>
Set<T>& Set<T>::operator=(
   const Set<T>& copyObject)
{
   if (this != &copyObject)
   {
      list = copyObject.list;
   }

   return (*this);
}

// Comparison operator.
template<class T>
bool Set<T>::operator==(
   const Set<T>& rhs) const
{
   return (list == rhs.list);
}
