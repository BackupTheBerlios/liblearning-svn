/* counter.hpp source file
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

#ifndef COUNTER_HPP
#define COUNTER_HPP

#include <numeric>

template<typename T = unsigned>
class counter
{
public:
  typedef size_t size_type;
  typedef T value_type;
  typedef T& reference;
  typedef T& const_reference;
  typedef T* pointer;

  counter(size_type n)
  { __v.resize(n); }

  reference
  operator[](size_type n)
  { return __v[n]; }

  const_reference
  operator[](size_type n) const
  { return __v[n]; }

  value_type
  sum() const
  { return std::accumulate(__v.begin(), __v.end(), T()); }

private:
  std::vector<T> __v;
};

#endif
