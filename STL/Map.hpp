template <typename KEY, typename VALUE>
class Map
{

public:

   typedef struct Element
   {
      KEY key;
      VALUE value;

      Element() {}

      Element(const KEY& key, const VALUE& value) : key(key), value(value) {}

      bool operator==(const Element& rhs) {return ((this->key == rhs.key) && (this->value == rhs.value));}
   };

   typedef typename List<Element>::Iterator Iterator;

   virtual bool isSet(const KEY& key) const = 0;

   virtual unsigned int length() const = 0;

   virtual const Iterator find(
      const KEY& key) const = 0;

   virtual const Element* item(
      const int& index) const = 0;

   virtual const Iterator put(
      const KEY& key,
      const VALUE& value) = 0;
      
   virtual int erase(
      const KEY& key) = 0;

   virtual Iterator erase(
      const Iterator& iterator) = 0;
      
   virtual VALUE& operator[](
      const KEY& key) = 0;

   virtual void clear() = 0;

   virtual Iterator begin() const = 0;

   virtual Iterator end() const = 0;
};
