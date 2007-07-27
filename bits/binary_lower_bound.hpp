/* binary_lower_bound.hpp source file
 * 
 * Copyright 2007 Daniel Etzold
 * detzold@gmx.net
 * Distributed under the terms of the GNU General Public License.
 *
 * This file is part of liblearning.
 *
 * liblearning is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * liblearning is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with liblearning; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301  USA
 */

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
