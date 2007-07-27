/* external_sorted_sequence_iterator.hpp source file
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

#ifndef EXTERNAL_SORTED_SEQUENCE_ITERATOR_HPP
#define EXTERNAL_SORTED_SEQUENCE_ITERATOR_HPP

template<typename P>
class external_sorted_sequence_iterator
{
public:
  typedef typename P::value_type value_type;
  typedef typename P::const_reference const_reference;
  typedef typename P::size_type size_type;
  typedef typename P::pointer pointer;

  external_sorted_sequence_iterator(P* p, size_type pos = 0)
    : __p(p), __n(pos)
  { 
    if (!pos)
      __init();
  }

  external_sorted_sequence_iterator&
  operator++()
  {
    __next();
    return *this;
  }

  const_reference
  operator*() const
  { return __values[__min]; }

  pointer
  operator->()
  { return &__values[__min]; }

  bool
  operator==(const external_sorted_sequence_iterator& i) const
  { return (__p == i.__p && __n == i.__n); }

  bool
  operator!=(const external_sorted_sequence_iterator& i) const
  { return !operator==(i); }

private:
  void
  __init()
  {
    for (typename P::file_iterator i = __p->fbegin();
      i != __p->fend(); ++i)
    {
      __is.push_back(new std::ifstream(i->c_str(), std::ios::binary));
      __ia.push_back(new boost::archive::binary_iarchive(*__is.back()));
    }
    __values.resize(__is.size());
    for (size_type i = 0; i < __values.size();)
      i = __get_next(i);
    __min = __get_min();
  }

  size_type
  __get_next(size_type i)
  {
    try
    {
      *__ia[i] >> __values[i];
      return (i + 1);
    }
    catch (const boost::archive::archive_exception& e)
    {
      delete __ia[i];
      delete __is[i];
      __ia.erase(__ia.begin() + i);
      __is.erase(__is.begin() + i);
      __values.erase(__values.begin() + i);
    }
    return i;
  }

  size_type
  __get_min() const
  {
    size_type m = 0;
    for (size_type i = 1; i < __values.size(); ++i)
      if (__values[i] < __values[m])
        m = i;
    return m;
  }

  void
  __next()
  {
    __n++;
    __get_next(__min);
    if (!__is.empty())
       __min = __get_min(); // XXX efficiency
  }

  P* __p;
  std::vector<std::ifstream*> __is;
  std::vector<boost::archive::binary_iarchive*> __ia;
  std::vector<value_type> __values;
  size_type __min;
  size_type __n;
};

#endif
