#pragma once

template <typename T1, typename T2>
struct Pair
{
public:

   Pair() {}

   Pair(T1 first, T2 second) : first(first), second(second) {}

   bool operator==(const Pair& rhs) const {return ((this->first == rhs.first) && (this->second == rhs.second));}

   bool operator!=(const Pair& rhs) const {return (!(*this == rhs));}

   T1 first;

   T2 second;
};
