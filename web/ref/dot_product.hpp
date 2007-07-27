#ifndef DOT_PRODUCT
#define DOT_PRODUCT

template<int N>
class dot_product
{
public:
  template<typename T>
  static T
  compute(const T* a, const T* b)
  { return *a * *b + dot_product<N - 1>::compute(a + 1, b + 1); }
};

template<>
class dot_product<0>
{
public:
  template<typename T>
  static T
  compute(const T* a, const T* b)
  { return 0; }
};

#endif
