#ifndef BINARY_LOWER_BOUND_HPP
#define BINARY_LOWER_BOUND_HPP

#include <algorithm>

/* @class binary_lower_bound

   @description
   Searches a sorted sequence in O(\log n) steps.
*/
class binary_lower_bound
{
public:
  /* @mem Returns the furthermost iterator <tt>i</tt> such that for every
     iterator <tt>j</tt> in <tt>[beg, i)</tt>, <tt>*j &lt; val</tt>. Uses
     <tt>operator&lt;</tt> for comparison.
  */
  template<typename It, typename T>
  It
  operator()(It beg, It end, const T& val) const
  { return std::lower_bound(beg, end, val); }

  /* @mem Returns the furthermost iterator <tt>i</tt> such that for every
     iterator <tt>j</tt> in <tt>[beg, i)</tt>, <tt>comp(*j, val)</tt>
     is true.
  */
  template<typename It, typename T, typename StrictWeakOrdering>
  It 
  operator()(It beg, It end, const T& val, StrictWeakOrdering comp) const
  { return std::lower_bound(beg, end, val, comp); }
};

#endif
