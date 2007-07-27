#ifndef COSINE_HPP
#define COSINE_HPP

#include <bits/dot_product.hpp>
#include <bist/length.hpp>

template<int N>
class cosine
{
public:
  template<typename T>
  static T
  compute(const T* a, const T* b)
  {
    return dot_product<N>::compute(a, b) / (length<N>::compute(a) *
      length<N>::compute(b));
  }
};

#endif
