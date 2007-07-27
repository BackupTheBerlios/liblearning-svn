/* mbox_iterator.hpp source file
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

#ifndef MBOX_ITERATOR_HPP
#define MBOX_ITERATOR_HPP

#include <iostream>
#include <string>

template<typename String = std::string>
class mbox_iterator
{
public:
  typedef String value_type;
  typedef const String& const_reference;

  /* @mem Creates an end iterator. */
  mbox_iterator()
    : __is(0), __pos(0), __next_pos(0)
  { }

  mbox_iterator(std::istream* is)
    : __is(is), __pos(0), __next_pos(0)
  { _next(); }

  mbox_iterator&
  operator++()
  {
    _next();
    return *this;
  }

  const_reference
  header() const
  { return __h; }

  const_reference
  body() const
  { return __b; }

  const_reference
  envelop() const
  { return __from; }

  off_t
  pos() const
  { return __pos; }

  bool
  operator==(const mbox_iterator& i) const
  { return (__is == i.__is); }

  bool operator!=(const mbox_iterator& i) const
  { return !operator==(i); }

private:
  void
  _getline(std::istream& is, std::string& s)
  {
    s = "";
    char buf[4096];
    int p = 0;
    while (true)
    {
      char c;
      is.get(c);
      if (is.eof())
        break;
      buf[p++] = c;
      if (p == sizeof(buf))
      {
        s.append(buf, p);
        p = 0;
      }
      if (c == '\n')
      {
        s.append(buf, p);
        break;
      }
    }
  }

  void
  _next()
  {
    std::string s;
    bool h = true;

    if (!__is)
      return;
    if (__is->eof() || __is->fail())
    {
      __is = 0;
      return;
    }
    __h = __b = "";
    while (__is->good() && !__is->fail() && !__is->eof())
    {
      off_t p = __is->tellg();
      _getline(*__is, s);
      if (s.substr(0, 5) == "From ")
      {
        __from = __next_from, __next_from = s;
        __pos = __next_pos, __next_pos = p;
        if (!__h.empty())
          return;
        continue;
      }
      if (h && (s.empty() || !s.empty() && (s[0] == '\r' || s[0] == '\n')))
      {
        __h.append(s);
        h = false;
        continue;
      }
      if (h)
        __h.append(s);
      else
        __b.append(s);
    }
    __from = __next_from;
    __pos = __next_pos;
  }

  std::istream* __is;
  String __h;
  String __b;
  String __from;
  String __next_from;
  off_t __pos;
  off_t __next_pos;
};

#endif
