#pragma once

#include <stddef.h>

template <typename T>
class List
{

public:

   List();

   virtual ~List();

   virtual unsigned int size() const;

   virtual void push_back(
      const T& value);

   virtual void remove(
      const T& value);
      
   virtual void clear();

   bool operator==(
      const List<T>& rhs) const;

   virtual List<T>& operator=(
      const List<T>& rhs);

private:

   typedef struct Node
   {
      T item;
      Node *next;
      Node *prev;

      inline Node(const T& item) : next(NULL), prev(NULL), item(item) {}

      inline bool operator==(const Node& rhs) {return (item == rhs.item) && (next == rhs.next) && (prev = rhs.prev);}
   };

   unsigned int listSize;
  
   Node* startNode;
  
   Node* endNode;   

public:

   class Iterator
   {
      friend class List;

   public:

       Iterator(List<T>::Node* node) : node(node) {}
       virtual ~Iterator() {}
       virtual void  operator++(int) {node = (node->next == NULL) ? NULL : node->next;}
       virtual T& operator*() const {return (node->item);}
       virtual T* operator->() {return (&(node->item));}
       virtual T const* operator->() const {return (&(node->item));}
       virtual bool operator==(const Iterator& rhs) const {return(node == rhs.node);}
       virtual bool operator!=(const Iterator& rhs) const {return (!(*this == rhs));}
       virtual Iterator& operator=(const Iterator& rhs) {if (rhs != *this) node = rhs.node; return (*this);}

   private:
   
       List<T>::Node* node;
   };

   virtual const Iterator find(
      const T& value) const;

   virtual Iterator erase(
      const Iterator& iterator);

   virtual Iterator begin() const;

   virtual Iterator end() const;
};


// Constructor.
template<class T>
List<T>::List():
   listSize(0),
   startNode(NULL),
   endNode(NULL)
{
}

// Destructor.
template<class T>
List<T>::~List()
{
  clear();
}

// Get size
template<class T>
unsigned int List<T>::size() const
{
  return (listSize);
}

template<class T>
void List<T>::push_back(
  const T& value)
{
   Node* tmp = new Node(value);

   if (endNode == NULL) // list is empty
   {
     startNode = tmp;
     endNode = tmp;
   }
   else // insert at the end
   {
      tmp->prev = endNode;
      endNode->next = tmp;
      endNode = tmp;
   }
  
   listSize++; // Increase size counter
}

template<class T>
void List<T>::remove(
  const T& value)
{
   List<T>::Iterator foundIt = find(value);
   
   if (foundIt != end())
   {
      erase(foundIt);
   }
}

template<class T>
void List<T>::clear()
{
  Node* tmp = startNode;
  while (startNode != NULL)
  {
    tmp = startNode;
    startNode = startNode->next;
    delete tmp; // Delete item
    listSize--; // Decrease counter
  }
  
  endNode = NULL;
}

// Assignment operator.
template<class T>
List<T>& List<T>::operator=(
   const List<T>& copyObject)
{
   if (this != &copyObject)
   {
      clear();

      for (typename List<T>::Iterator it = copyObject.begin(); it != copyObject.end(); it++)
      {
         push_back(*it);
      }
   }

   return (*this);
}

// Comparison operator.
template<class T>
bool List<T>::operator==(
   const List<T>& rhs) const
{
   bool equal = false;

   if (this->size() == rhs.size())
   {
      equal = true;

      typename List<T>::Iterator it = this->begin();
      typename List<T>::Iterator ot = rhs.begin();

      for (; it != this->end(); it++, ot++)
      {
         if (*it != *ot)
         {
            equal = false;
            break;
         }
      }
   }

   return (equal);
}

template<typename T>
const typename List<T>::Iterator List<T>::find(
   const T& value) const
{
   typename List<T>::Iterator foundIt = end();

   for (typename List<T>::Iterator it = begin(); it != end(); it++)
   {
      if (*it == value)
      {
         foundIt = it;
         break;
      }
   }

   return (foundIt);
}

template<class T>
typename List<T>::Iterator List<T>::erase(
   const typename List<T>::Iterator& iterator)
{
   typename List<T>::Iterator nextIt = end();

   if (iterator != end())
   {
      List<T>::Node* node = iterator.node;

      if (node->prev != NULL)
      {
         node->prev->next = node->next;
      }
      else
      {
         startNode = node->next;
      }

      if (node->next != NULL)
      {
         node->next->prev = node->prev;
         nextIt = Iterator(node->next);
      }
      else
      {
         endNode = node->prev;
      }

      listSize--; // Decrease counter

      delete (node);
   }

   return (nextIt);
}

template<class T>
typename List<T>::Iterator List<T>::begin() const
{
   return (List<T>::Iterator(startNode));
}

template<class T>
typename List<T>::Iterator List<T>::end() const
{
   return (typename List<T>::Iterator(NULL));
}
