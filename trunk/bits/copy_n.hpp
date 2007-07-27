/* copy_n.hpp source file
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

#ifndef COPY_N_HPP
#define COPY_N_HPP

/* @class copy_n
   @description Copies <tt>N</tt> elments without using loops.
   For small <tt>N</tt> this method also
   known as loop unroll may improve performance at run time.

   @1 N @2 Number of elements to copy. @3

   @example
int n[] = {1, 2, 3};
copy_n<2>::assign(&n[1], &n[0]);

   @exdescription
   Copies the element 2 from the second to the first position and the
   element 3 from the third to the second position.

   @see pow
*/
template<int N>
class copy_n
{
public:
  /* @mem Assigns the value at <tt>dst</tt> to <tt>src</tt>. */
  template<typename T, typename U>
  static void
  assign(const T* src, U* dst)
  {
    *dst = *src;
    copy_n<N - 1>::assign(src + 1, dst + 1);
  }
};

template<>
class copy_n<1>
{
public:
  template<typename T, typename U>
  static void
  assign(const T* src, U* dst)
  { *dst = *src; }
};

template<>
class copy_n<0>
{
public:
  template<typename T, typename U>
  static void
  assign(const T* src, U* dst)
  { }
};

#endif
