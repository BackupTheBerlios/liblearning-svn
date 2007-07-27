/* directory_iterator.hpp source file
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

#ifndef DIRECTORY_ITERATOR
#define DIRECTORY_ITERATOR

#include <boost/filesystem/operations.hpp>
#include <boost/filesystem/path.hpp>

/* @class directory_iterator
*/
class directory_iterator
{
public:
  typedef std::string value_type;

  const static int dir = 1;
  const static int regular = 2;

  directory_iterator()
    : __t(0)
  { }
  
  template<typename String>
  directory_iterator(const String& path, int type = dir | regular)
    : __t(type)
  { boost::filesystem::path p = 
      boost::filesystem::system_complete(
        boost::filesystem::path(path, boost::filesystem::native));
    __dir = boost::filesystem::directory_iterator(p);
  }

  directory_iterator&
  operator++()
  {
    for (++__dir; __dir != __end; ++__dir)
    {
      if ((boost::filesystem::is_directory(*__dir) && (__t & dir)) ||
          (!boost::filesystem::is_directory(*__dir) && (__t & regular)))
        break;
    }
    return *this;
  }

  std::string
  operator*() const
  { return __dir->native_file_string(); }

  bool
  operator==(const directory_iterator& i) const
  { return __dir == i.__dir; }

  bool operator!=(const directory_iterator& i) const
  { return !operator==(i); }

private:
  boost::filesystem::directory_iterator __dir;
  boost::filesystem::directory_iterator __end;
  int __t;
};

#endif
