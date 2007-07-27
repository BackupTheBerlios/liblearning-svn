/* duplicate_ostream.hpp source file
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

#ifndef DUPLICATE_OSTREAM_HPP
#define DUPLICATE_OSTREAM_HPP

#include <iostream>

class duplicate_ostream
{
public:
  duplicate_ostream(std::ostream& os1, std::ostream& os2)
    : __os1(os1), __os2(os2)
  { }

  template<typename T>
  duplicate_ostream&
  operator<<(const T& t)
  {
    __os1 << t;
    __os2 << t;
    return *this;
  }

private:
  std::ostream& __os1;
  std::ostream& __os2;
};

#endif
