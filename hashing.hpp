/* hashing.hpp source file
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

#ifndef HASHER_HPP
#define HASHER_HPP

#include <ext/hash_map>
#include <string>

namespace __gnu_cxx
{
  template<>
  struct hash<std::string>
  {
    size_t
    operator()(const std::string& s) const
    { return __gnu_cxx::hash<const char*>()(s.c_str()); }
  };
};

template<typename T>
inline T __hash(const char* s, size_t n)
{
  T r = T();
  for (; *s && n; ++s, --n)
    r = r * 5 + *s;
  return r;
}

template<typename T>
inline T __hash(const char* s)
{
  T r = T();
  for (; *s; ++s)
    r = r * 5 + *s;
  return r;
}

template<typename T>
struct hash_range
{
  template<typename It>
  T
  operator()(It beg, It end) const
  {
    T r = T();
    for (; beg != end; ++beg)
      r = r * 5 + *beg;
    return r;
  }
};

template<typename T, typename Seq>
struct hash { };

template<typename T>
struct hash<T, std::string>
{
  T
  operator()(const std::string& s, size_t off = 0) const
  { return __hash<T>(s.c_str() + off); }
};

template<typename T, typename Seq>
struct hash_n { };

template<typename T>
class hash_n<T, std::string>
{
public:
  hash_n(size_t n)
    : __n(n)
  { }

  T
  operator()(const std::string& s, size_t off = 0) const
  { return __hash<T>(s.c_str() + off, __n); }

private:
  size_t __n;
};

#endif
