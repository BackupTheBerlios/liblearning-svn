/* key_id_map.hpp source file
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

#ifndef KEY_ID_MAP_HPP
#define KEY_ID_MAP_HPP

#include <map>

template<typename T, typename C = std::map<T, size_t> >
class key_id_map
{
public:
  typedef size_t size_type;
  typedef T value_type;
  typedef const T& const_reference;

  key_id_map(size_type off = 0)
    : __off(off)
  { }

  size_type
  operator()(const T& t)
  {
    typename C::iterator i = __c.find(t);
    if (i == __c.end())
    {
      i = __c.insert(std::make_pair(t, __c.size() + __off)).first;
      __rev.push_back(&i->first);
    }
    return i->second;
  }

  const_reference
  operator[](size_type n) const
  { return *__rev[n - __off]; }

private:
  C __c;
  std::vector<const T*> __rev;
  size_type __off;
};

#endif
