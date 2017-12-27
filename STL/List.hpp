#pragma once

// https://www.codeproject.com/Articles/92671/How-to-write-abstract-iterators-in-Cplusplus

template<typename A, typename B> bool compareType(A a, B b) {return false;}
template<typename A> bool compareType(A a, A b) {return true;}

template <typename T>
class List
{

public:

   class BaseIterator
   {
   public:

       BaseIterator() {}
       virtual ~BaseIterator() {}
       virtual void  operator++(int) {}
       virtual T& operator*() const {/*return T();*/}
       virtual BaseIterator* clone() const {/*return new BaseIterator(*this);*/}
       
       // The == operator is non-virtual. It checks that the derived objects have compatible types, then calls the
       // virtual comparison function equal.
       bool operator==(const BaseIterator& other) const {return (compareType(*this, other) && equal(other));}

   protected:

      virtual bool equal(const BaseIterator& other) const {return true;}
   };

   class Iterator
   {
   public:

       Iterator(BaseIterator* iterator) : iterator(iterator) {}
       Iterator(const Iterator& other) : iterator(other.iterator->clone()) {}
       virtual ~Iterator() {delete(iterator);}
       void  operator++(int) {(*iterator)++;}
       T& operator*() const {return (*(*iterator));}
       T* operator->() {return (&(*(*iterator)));}
       T const* operator->() const {return (&(*(*iterator)));}
       bool operator==(const Iterator& rhs) const {return((iterator == rhs.iterator) || (*iterator == *(rhs.iterator)));}
       bool operator!=(const Iterator& rhs) const {return (!(*this == rhs));}

       Iterator& operator=(const Iterator& rhs) {if (this != &rhs) iterator = (rhs.iterator->clone()); return (*this);}

   private:

       BaseIterator* iterator;
   };

   static const int NOT_FOUND;

   virtual List<T>& operator=(
      const List<T>& copyObject);

   virtual int length() const = 0;

   virtual bool contains(
      const T& value) const = 0;

   virtual const T* item(
      const int& index) const = 0;

   virtual bool add(
      const T& value) = 0;

   virtual void remove(
      const T& value) = 0;

   virtual Iterator erase(
    const Iterator& iterator) = 0;
      
   virtual void clear() = 0;

   virtual Iterator begin() const = 0;

   virtual Iterator end() const = 0;

   void operator=(
      const List<T>& copyObject);

   bool operator==(
      const List<T>& rhs);
};

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
         add(*it);
      }
   }

   return (*this);
}

template <typename T>
const int List<T>::NOT_FOUND = -1;

// Assignment operator.
template<class T>
void List<T>::operator=(
   const List<T>& copyObject)
{
   if (this != &copyObject)
   {
      clear();

      for (typename List<T>::Iterator it = copyObject.begin(); it != copyObject.end(); it++)
      {
         add(*it);
      }
   }
}

// Comparison operator.
template<class T>
bool List<T>::operator==(
   const List<T>& rhs)
{
   bool equal = false;

   if (this->length() == rhs.length())
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

