/* file_reader.hpp source file
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

#ifndef FILE_READER_HPP
#define FILE_READER_HPP

#include <fstream>
#include <string>

template<typename U, typename V>
class file_reader
{
public:
  typedef U first_argument_type;
  typedef V second_argument_type;
  typedef void result_type;

  file_reader()
  { }

  result_type
  operator()(const U& filename, const V& func) const
  {
    char buf[4096];
    std::string data;
    std::ifstream i(filename.c_str());
    while (i.is_open() && !i.fail() && !i.eof())
    {
      i.read(buf, sizeof(buf));
      data.append(buf, i.gcount());
    }
    i.close();
    func(data);
  }
};

#endif
