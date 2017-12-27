#pragma once

#include "List.hpp"

template <typename T>
class LinkedList : public List<T>
{

public:

   LinkedList();

   virtual ~LinkedList();

   bool operator==(
      const LinkedList<T>& rhs);

   // Note: If you don't define this, it seems the default constructor is called, before calling
   //       List<T>::operator()=.  TODO: Research this and  understand why.
   virtual List<T>& operator=(
      const LinkedList<T>& rhs);

   virtual int length() const;

   virtual bool contains(
      const T& value) const;

   virtual const T* item(
      const int& index) const;

   virtual bool add(
      const T& value);

   virtual void remove(
      const T& value);

   virtual typename List<T>::Iterator erase(
      const typename List<T>::Iterator& iterator);
      
   virtual void clear();

private:

   int indexOf(
     const T& value) const;

   typedef struct Node
   {
      T item;
      Node *next;
      Node *prev;

      inline Node(const T& item) : next(NULL), prev(NULL), item(item) {}
   };

   int len;
  
   Node* startNode;
  
   Node* endNode;   

public:

   class Iterator : public List<T>::BaseIterator
   {
   public:

       Iterator(LinkedList<T>::Node* node) : node(node) {}
       virtual ~Iterator() {}
       virtual void  operator++(int) {node = (node->next == NULL) ? NULL : node->next;}
       virtual T& operator*() const {return (node->item);}
       virtual typename List<T>::BaseIterator* clone() const {return new Iterator(*this);}

   protected:

       virtual bool equal(const typename List<T>::BaseIterator& other) const
       {
          // Casting is safe since types have been checked by _Super::operator==
          const Iterator& castOther = static_cast<const Iterator&>(other);
          return (this->node == castOther.node);
       }

   private:
   
       LinkedList<T>::Node* node;
   };

   virtual typename List<T>::Iterator begin() const;

   virtual typename List<T>::Iterator end() const;
};


// Constructor.
template<class T>
LinkedList<T>::LinkedList():
   len(0),
   startNode(NULL),
   endNode(NULL)
{
}

// Destructor.
template<class T>
LinkedList<T>::~LinkedList()
{
  clear();
}

// Comparison operator.
template<class T>
bool LinkedList<T>::operator==(
   const LinkedList<T>& rhs)
{
   return (List<T>::operator==(rhs));
}

// Assignment operator.
template<class T>
List<T>& LinkedList<T>::operator=(
   const LinkedList<T>& rhs)
{
   return (List<T>::operator=(rhs));
}

// Get size
template<class T>
int LinkedList<T>::length() const
{
  return (len);
}

template<class T>
bool LinkedList<T>::contains(
  const T& value) const
{
  return (indexOf(value) != List<T>::NOT_FOUND);
}

template<class T>
const T* LinkedList<T>::item(
  const int& index) const
{
   T* foundIt = NULL;
   
   if (index < length())
   {   
      Node *tmp = startNode;
      
      for (int i = 0; ((i < length()) && (tmp != NULL)); i++)
      {
         if (i == index)
         {
            foundIt = &(tmp->item);
            break;
         }
         else
         {
            tmp = tmp->next;
         }
      }
   }

   return (foundIt);
}

template<class T>
bool LinkedList<T>::add(
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
  
   len++; // Increase size counter
}

template<class T>
void LinkedList<T>::remove(
  const T& value)
{
   Node* tmp = startNode;
   
   while (tmp != NULL)
   {
      if (tmp->item == value)
      {
         if (tmp->prev != NULL)
         {
            tmp->prev->next = tmp->next;
         }
         else
         {
            startNode = tmp->next;
         }

         if (tmp->next != NULL)
         {
            tmp->next->prev = tmp->prev; 
         }
         else
         {
            endNode = tmp->prev;
         }

         len--; // Decrease counter

         delete (tmp);

         break;
      }

      tmp = tmp->next;
   }
}

template<class T>
typename List<T>::Iterator LinkedList<T>::erase(
   const typename List<T>::Iterator& iterator)
{
   Serial.println("LinkedList<T>::erase is not implemented.");
}

template<class T>
void LinkedList<T>::clear()
{
  Node* tmp = startNode;
  while (startNode != NULL)
  {
    tmp = startNode;
    startNode = startNode->next;
    delete tmp; // Delete item
    len--; // Decrease counter
  }
  
  endNode = NULL;
}

template<class T>
int LinkedList<T>::indexOf(
  const T& value) const
{
   int index = List<T>::NOT_FOUND;
   
   Node *tmp = startNode;

   for (int i = 0; (tmp != NULL); i++)
   {
      if (tmp->item == value)
      {
         index = i;
         break;
      }
      else
      {
        tmp = tmp->next;
      }
   }

   return (index);
}

template<class T>
typename List<T>::Iterator LinkedList<T>::begin() const
{
   return (typename List<T>::Iterator(new typename LinkedList<T>::Iterator(startNode)));
}

template<class T>
typename List<T>::Iterator LinkedList<T>::end() const
{
   return (typename List<T>::Iterator(new typename LinkedList<T>::Iterator(NULL)));
}
