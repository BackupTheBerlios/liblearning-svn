/* check_symbols.hpp source file
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

#ifndef CHECK_SYMBOLS_HPP
#define CHECK_SYMBOLS_HPP

#include <algorithm>

template<typename String>
class check_symbols
{
public:
  check_symbols(const String& t)
    : __t(t)
  { }

  template<typename T>
  bool
  operator()(const T& t) const
  { return (std::find_if(__t.begin(), __t.end(), t) != __t.end()); }

private:
  String __t;
};

#endif
