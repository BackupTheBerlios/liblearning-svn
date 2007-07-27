/* edit_distance.hpp source file
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

#ifndef EDIT_DISTANCE_HPP
#define EDIT_DISTANCE_HPP

template<typename C>
size_t
edit_distance(const C& c1, const C& c2)
{
  size_t l = c1.size();
  size_t* ldata[2];
  ldata[0] = new size_t[l + 1];
  ldata[1] = new size_t[l + 1];
  for (size_t t = 0; t <= l; ++t)
    ldata[0][t] = t;
  int last = 0;
  int current = 1;
  for (size_t st = 0; st < c2.size(); ++st)
  {
    ldata[current][0] = st + 1;
    for (size_t x = 0; x < l; ++x)
      if (c1[x] == c2[st])
        ldata[current][x + 1] = ldata[last][x];
      else
      {
        size_t v = ldata[last][x + 1];
        if (ldata[last][x] < v)
           v = ldata[last][x];
        if (ldata[current][x] < v)
           v = ldata[current][x];
        ldata[current][x + 1] = v + 1;
      }
    if (last) {
      last = 0;
      current = 1;
    } else {
      last = 1;
      current = 0;
    }
  }
  size_t r = ldata[last][l];
  delete[] ldata[0];
  delete[] ldata[1];
  return r;
}

template<typename C, typename Func>
size_t
edit_distance(const C& c1, const C& c2, Func f)
{
  size_t l = c1.size();
  size_t* ldata[2];
  ldata[0] = new size_t[l + 1];
  ldata[1] = new size_t[l + 1];
  for (size_t t = 0; t <= l; ++t)
    ldata[0][t] = t;
  int last = 0;
  int current = 1;
  for (size_t st = 0; st < c2.size(); ++st)
  {
    ldata[current][0] = st + 1;
    for (size_t x = 0; x < l; ++x)
      if (f(c1[x]) == f(c2[st]))
        ldata[current][x + 1] = ldata[last][x];
      else
      {
        size_t v = ldata[last][x + 1];
        if (ldata[last][x] < v)
           v = ldata[last][x];
        if (ldata[current][x] < v)
           v = ldata[current][x];
        ldata[current][x + 1] = v + 1;
      }
    if (last) {
      last = 0;
      current = 1;
    } else {
      last = 1;
      current = 0;
    }
  }
  size_t r = ldata[last][l];
  delete[] ldata[0];
  delete[] ldata[1];
  return r;
}

#endif
