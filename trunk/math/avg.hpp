/* avg.hpp source file
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

#ifndef AVG_HPP
#define AVG_HPP

template<typename T = double>
class avg
{
public:
  typedef T value_type;

  avg()
    : __acc(T()), __n(T()), __min(T()), __max(T()),
      __alpha(T())
  { }

  avg&
  operator+=(const T& t)
  { 
    __acc += t;
    if (__n == 0)
      __min = __max = t;
    else
      if (t < __min)
        __min = t;
      else if (__max < t)
        __max = t;
    ++__n;
    __alpha += t * t;
    return *this;
  }

  // XXX precision
  T
  standard_deviation() const
  {
    if (__n > 1)
    {
      T x = (__alpha - 2.0 * operator*() * __acc + __n * 
        operator*() * operator*()) / (__n - 1.0);
      if (x > 0.0)
        return sqrt(x);
    }
    return T();
  }

  T
  operator*() const
  { return (__n > 0 ? __acc / __n : 0); }

  const T&
  size() const
  { return __n; }

  const T&
  min() const
  { return __min; }

  const T&
  max() const
  { return __max; }

private:
  T __acc;
  T __n;
  T __min;
  T __max;
  T __alpha;
};

#endif
