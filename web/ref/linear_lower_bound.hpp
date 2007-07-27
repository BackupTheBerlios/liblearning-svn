#ifndef LINEAR_LOWER_BOUND_HPP
#define LINEAR_LOWER_BOUND_HPP

#include <algorithm>
#include <functional>

class  linear_lower_bound
{
public: 
  /* @mem Returns the first iterator i in [beg, end) such that
     for every iterator j in [beg, i), *j < val.
  */
  template<typename It, typename T>
  It
  operator()(It beg, It end, const T& val) const
  { return std::find_if(beg, end, std::bind2nd(std::greater_equal<T>(), val)); }

  /* @mem Returns the first iterator i in [beg, end) such that
     for every iterator j in [beg, i), f(*j, val) is true.
  */
  template<typename It, typename T, typename F>
  It
  operator()(It beg, It end, const T& val, F f) const
  { 
    for (; beg != end && f(*beg, val); ++beg);
    return beg;
  }
};

#endif
