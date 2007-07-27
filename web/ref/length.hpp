#ifndef LENGTH_HPP
#define LENGTH_HPP

#include <cmath>
#include <bits/dot_product.hpp>

template<int N>
class length
{
public:
  template<typename T>
  static T
  compute(const T* t)
  { return static_cast<T>(sqrt(dot_product<N>::compute(t, t))); }
};

template<>
class length<1>
{
public:
  template<typename T>
  static T
  compute(const T* t)
  { return *t; }
};

template<>
class length<0>
{
public:
  template<typename T>
  static T
  compute(const T* t)
  { return 0; }
};

#endif
