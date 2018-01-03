#pragma once

#include "List.hpp"
#include "Pair.hpp"

template <typename KEY, typename VALUE>
class Map
{

public:

   typedef Pair<KEY, VALUE> Element;

   typedef typename List<Element>::Iterator Iterator;

   Map();

   virtual ~Map();

   virtual bool isSet(const KEY& key) const;

   virtual unsigned int size() const;

   virtual const Iterator find(
      const KEY& key) const;

   virtual const typename Map<KEY, VALUE>::Iterator put(
      const KEY& key,
      const VALUE& value);

   virtual typename Map<KEY, VALUE>::Iterator erase(
      const KEY& key);

   virtual void erase(
      const typename Map<KEY, VALUE>::Iterator& iterator);
      
   virtual VALUE& operator[](
      const KEY& key);

   virtual void clear();

   virtual typename Map<KEY, VALUE>::Iterator begin() const;

   virtual typename Map<KEY, VALUE>::Iterator end() const;

   virtual bool operator==(
      const Map<KEY, VALUE>& rhs) const;

   virtual Map<KEY, VALUE>& operator=(
      const Map<KEY, VALUE>& rhs);

private:

   List<Element> list;
};

template<typename KEY, typename VALUE>
Map<KEY, VALUE>::Map()
{  
}

template<typename KEY, typename VALUE>
Map<KEY, VALUE>::~Map()
{
   list.clear();
}

template<typename KEY, typename VALUE>
bool Map<KEY, VALUE>::isSet(const KEY& key) const
{
   return (find(key) != end());
}

template<typename KEY, typename VALUE>
unsigned int Map<KEY, VALUE>::size() const
{
  return (list.size());
}

template<typename KEY, typename VALUE>
const typename Map<KEY, VALUE>::Iterator Map<KEY, VALUE>::find(
   const KEY& key) const
{
   typename Map<KEY, VALUE>::Iterator foundIt = this->end();
   
   for (typename Map<KEY, VALUE>::Iterator it = this->begin(); it != this->end(); it++)
   {
      if (it->first == key)
      {
         foundIt = it;
         break;
      }
   }

   return (foundIt);
}

template<typename KEY, typename VALUE>
const typename Map<KEY, VALUE>::Iterator Map<KEY, VALUE>::put(
  const KEY& key,
  const VALUE& value)
{
  typename Map<KEY, VALUE>::Iterator foundIt = find(key);
  if (foundIt == end())
  {
     list.push_back(typename Map<KEY, VALUE>::Element(key, value));
     foundIt = find(key);  // TODO: A better way.
  }
  else
  {
     foundIt->second = value;
  }

  return (foundIt);
}

template<typename KEY, typename VALUE>
typename Map<KEY, VALUE>::Iterator Map<KEY, VALUE>::erase(
   const KEY& key)
{
   typename Map<KEY, VALUE>::Iterator findIt = find(key);
   if (findIt != end())
   {
      list.erase(findIt);
   }
}

template<typename KEY, typename VALUE>
void Map<KEY, VALUE>::erase(
   const typename Map<KEY, VALUE>::Iterator& iterator)
{
   list.erase(iterator);
}

template<typename KEY, typename VALUE>
VALUE& Map<KEY, VALUE>::operator[](
  const KEY& key)
{
  typename Map<KEY, VALUE>::Iterator foundIt = find(key);
  if (foundIt == end())
  {
     list.push_back(typename Map<KEY, VALUE>::Element(key, VALUE()));
     foundIt = find(key);  // TODO: A better way.
  }

  return (foundIt->second);
}

template<typename KEY, typename VALUE>
void Map<KEY, VALUE>::clear()
{
  list.clear();
}

template<typename KEY, typename VALUE>
typename Map<KEY, VALUE>::Iterator Map<KEY, VALUE>::begin() const
{
   return (list.begin());
}

template<typename KEY, typename VALUE>
typename Map<KEY, VALUE>::Iterator Map<KEY, VALUE>::end() const
{
   return (list.end());
}

// Assignment operator.
template<typename KEY, typename VALUE>
Map<KEY, VALUE>& Map<KEY, VALUE>::operator=(
   const Map<KEY, VALUE>& rhs)
{
   if (this != &rhs)
   {
      list = rhs.list;
   }

   return (*this);
}

// Comparison operator.
template<typename KEY, typename VALUE>
bool Map<KEY, VALUE>::operator==(
   const Map<KEY, VALUE>& rhs) const
{
   return (list == rhs.list);
}
