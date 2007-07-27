/* bounded_stream_iterator.hpp source file
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

#ifndef BOUNDED_STREAM_ITERATOR
#define BOUNDED_STREAM_ITERATOR

#include <string>
#include <iostream>

/* @class bounded_stream_iterator

   @1 String @2 Type used internally to store a block.  @3 std::string

   @description
   This class is used similar to an iterator. It traverses an input
   stream and searches for blocks which have a given prefix and suffix
   and returns the content between them.
   
   @example
#include <iostream>
#include <sstream>
#include <bounded_stream_iterator.hpp>

int main(int argc, char** argv)
{
  std::stringstream ss("Hello <b>World</b>, <b>nice</b> day!");
  bounded_stream_iterator<> iend;
  bounded_stream_iterator<> i("<b>", "</b>", &ss);
  for (; i != iend; ++i)
  {
    std::cout << *i << std::endl;
  }
}

   @exdescription
   Should print the following two lines:<br>
   <pre>World</pre>
   <pre>nice</pre>

*/
template<typename String = std::string>
class bounded_stream_iterator
{
public:
  /* @mem The type <tt>String</tt>. */
  typedef String value_type;
  /* @mem A constant reference to <tt>String</tt>. */
  typedef const String& const_reference;
  /* @mem The type of this iterator. */
  typedef bounded_stream_iterator iterator;

  /* @mem Constructs an end iterator. */
  bounded_stream_iterator()
    : __is(0)
  { }

  /* @mem Constructs an iterator for the given stream <tt>is</tt>
     which extracts all data between the prefix <tt>prf</tt> and the
     suffix <tt>sfx</tt>.
  */
  bounded_stream_iterator(const String& prf,
                  const String& sfx, 
                  std::istream* is)
    : __beg(prf), __end(sfx), __is(is)
  { operator++(); }

  /* @mem Moves the iterator one step forward to the next block .*/
  iterator&
  operator++()
  {
    if (!__is)
      return *this;
    _next();
    return *this;
  }

  /* @mem Checks the address of the stream for equality. */
  bool
  operator==(const iterator& i) const
  { return __is == i.__is; }

  /* @mem Checks the address of the stream for inequality. */
  bool
  operator!=(const iterator& i) const
  { return !operator==(i); }

  /* @mem Returns a const reference to the data block to which the
     iterator currently points to.
  */
  const_reference
  operator*() const
  { return __ret; }

private:
  void
  _next()
  {
    typename String::size_type p = 0;
    // XXX set offset where to start the search
    while ((p = __buf.find(__beg)) == String::npos)
    {
      if (!_read_data())
        return;
    }
    __buf.erase(0, p + __beg.size());
    _end();
  }

  void
  _end()
  {
    typename String::size_type p = 0;
    // XXX set offset where to start the search
    while ((p = __buf.find(__end)) == String::npos)
    {
      if (!_read_data())
        return;
    }
    __ret = __buf.substr(0, p);
    __buf.erase(0, p + __end.size());
  }

  bool
  _read_data()
  {
    char buf[4096];
    if (!__is->eof() && !__is->fail())
    {
      __is->read(buf, sizeof(buf));
      __buf.append(buf, __is->gcount());
      return true;
    }
    __is = 0;
    return false;
  }

  String __end;
  String __beg;
  std::istream* __is;
  String __ret;
  String __buf;
};

#endif
