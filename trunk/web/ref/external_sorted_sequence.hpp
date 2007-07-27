/* external_sorted_sequence.hpp source file
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

#ifndef EXTERNAL_SORTED_SEQUENCE_HPP
#define EXTERNAL_SORTED_SEQUENCE_HPP

#include <vector>
#include <list>
#include <string>
#include <fstream>

#include <boost/archive/binary_oarchive.hpp>
#include <boost/archive/binary_iarchive.hpp>
#include <boost/serialization/vector.hpp>
#include <boost/serialization/utility.hpp>

#include <bits/external_sorted_sequence_iterator.hpp>

template<typename T>
class external_sorted_sequence
{
public:
  typedef size_t size_type;
  typedef T value_type;
  typedef T& reference;
  typedef const T& const_reference;
  typedef T* pointer;
  typedef 
    external_sorted_sequence_iterator<external_sorted_sequence> iterator;
  typedef typename std::list<std::string>::iterator file_iterator;

  external_sorted_sequence(size_type max_elements,
    const std::string& prf, const std::string& sfx = "")
    : __max(max_elements), __siz(0), __cnt(0), __prf(prf), __sfx(sfx),
      __fcnt(0)
  { }

  size_type
  size() const
  { return __siz; }

  void
  push_back(const value_type& t)
  {
    if (++__cnt > __max)
      __flush();
    __values.push_back(t);
    __siz++;
  }

  iterator
  begin()
  {
    __flush();
    return iterator(this);
  }

  iterator
  end()
  { return iterator(this, size()); }

  file_iterator
  fbegin()
  { return __files.begin(); }

  file_iterator
  fend()
  { return __files.end(); }

  void
  erase()
  {
    for (file_iterator i = fbegin(); i != fend(); ++i)
      ::unlink(i->c_str());
    __files.clear();
  }

private:
  void
  __flush()
  {
    if (__values.empty())
      return;
    char buf[4096];
    snprintf(buf, sizeof(buf), "%s%05d%s", __prf.c_str(), __fcnt++,
      __sfx.c_str());
    __files.push_back(buf);
    __values.sort();
    std::ofstream os(buf);
    boost::archive::binary_oarchive oa(os);
    for (typename std::list<T>::const_iterator i = __values.begin();
        i != __values.end(); ++i)
      oa << *i;
    __values.clear();
    __cnt = 0;
  }

  size_type __max;
  size_type __siz;
  size_type __cnt;
  std::string __prf;
  std::string __sfx;
  std::list<T> __values;
  size_type __fcnt;
  std::list<std::string> __files;
};

#endif
