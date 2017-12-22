#pragma once

#include "LinkedList.hpp"
#include "Map.hpp"

template <typename KEY, typename VALUE>
class ListMap : public Map<KEY, VALUE>
{

public:

   typedef typename LinkedList<typename Map<KEY, VALUE>::Element>::Iterator Iterator;

   ListMap();

   virtual ~ListMap();

   virtual bool isSet(const KEY& key) const;

   virtual unsigned int length() const;

   virtual const typename Map<KEY, VALUE>::Iterator find(
      const KEY& key) const;

   virtual const typename Map<KEY, VALUE>::Element* item(
      const int& index) const;

   virtual const typename Map<KEY, VALUE>::Iterator put(
      const KEY& key,
      const VALUE& value);

   virtual int erase(
      const KEY& key);

   virtual typename Map<KEY, VALUE>::Iterator erase(
      const typename Map<KEY, VALUE>::Iterator& iterator);
      
   virtual VALUE& operator[](
      const KEY& key);

   virtual void clear();

   virtual typename Map<KEY, VALUE>::Iterator begin() const;

   virtual typename Map<KEY, VALUE>::Iterator end() const;

private:

   LinkedList<typename Map<KEY, VALUE>::Element> list;
};

template<typename KEY, typename VALUE>
ListMap<KEY, VALUE>::ListMap()
{  
}

template<typename KEY, typename VALUE>
ListMap<KEY, VALUE>::~ListMap()
{
   list.clear();
}

template<typename KEY, typename VALUE>
bool ListMap<KEY, VALUE>::isSet(const KEY& key) const
{
   return (find(key) != end());
}

template<typename KEY, typename VALUE>
unsigned int ListMap<KEY, VALUE>::length() const
{
  return (list.length());
}

template<typename KEY, typename VALUE>
const typename Map<KEY, VALUE>::Iterator ListMap<KEY, VALUE>::find(
   const KEY& key) const
{
   typename Map<KEY, VALUE>::Iterator foundIt = this->end();
   
   for (typename Map<KEY, VALUE>::Iterator it = this->begin(); it != this->end(); it++)
   {
      if ((*it).key == key)
      {
         foundIt = it;
         break;
      }
   }

   return (foundIt);
}

template<typename KEY, typename VALUE>
const typename  Map<KEY, VALUE>::Element* ListMap<KEY, VALUE>::item(
  const int& index) const
{
   return (list.item(index));
}

template<typename KEY, typename VALUE>
const typename Map<KEY, VALUE>::Iterator ListMap<KEY, VALUE>::put(
  const KEY& key,
  const VALUE& value)
{
  typename Map<KEY, VALUE>::Iterator foundIt = find(key);
  if (foundIt == end())
  {
     list.add(typename Map<KEY, VALUE>::Element(key, value));
     foundIt = find(key);  // TODO: A better way.
  }
  else
  {
     (*foundIt).value = value;
  }

  return (foundIt);
}

template<typename KEY, typename VALUE>
int ListMap<KEY, VALUE>::erase(
   const KEY& key)
{
   int erased = 0;
   
   typename Map<KEY, VALUE>::Iterator findIt = find(key);
   if (findIt != end())
   {
      list.erase(findIt);
      erased  = 1;
   }

   return (erased);   
}

template<typename KEY, typename VALUE>
typename Map<KEY, VALUE>::Iterator ListMap<KEY, VALUE>::erase(
   const typename Map<KEY, VALUE>::Iterator& iterator)
{
   return (list.erase(iterator));
}

template<typename KEY, typename VALUE>
VALUE& ListMap<KEY, VALUE>::operator[](
  const KEY& key)
{
  typename Map<KEY, VALUE>::Iterator foundIt = find(key);
  if (foundIt == end())
  {
     list.add(typename Map<KEY, VALUE>::Element(key, VALUE()));
     foundIt = find(key);  // TODO: A better way.
  }

  return ((*foundIt).value);
}

template<typename KEY, typename VALUE>
void ListMap<KEY, VALUE>::clear()
{
  list.clear();
}

template<typename KEY, typename VALUE>
typename Map<KEY, VALUE>::Iterator ListMap<KEY, VALUE>::begin() const
{
   return (list.begin());
}

template<typename KEY, typename VALUE>
typename Map<KEY, VALUE>::Iterator ListMap<KEY, VALUE>::end() const
{
   return (list.end());
}

