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

#ifndef CLASSIFICATION_HPP
#define CLASSIFICATION_HPP

#include <string>
#include <cctype>
#include <boost/algorithm/string/classification.hpp>

template<typename Char = std::string::value_type>
struct is_consonant
{
  template<typename Pred>
  bool
  __is(Char c, Pred p) const
  { return p(c); }

  bool
  operator()(const Char& c) const
  { return __is(::tolower(c), boost::is_any_of("bcdfghjklmnpqrstvwxyz")); }
};


#endif
