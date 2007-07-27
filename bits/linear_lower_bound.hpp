/* linear_lower_bound.hpp source file
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
