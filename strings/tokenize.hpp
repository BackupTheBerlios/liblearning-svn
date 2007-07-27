/* tokenize.hpp source file
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

#ifndef TOKENIZE_HPP
#define TOKENIZE_HPP

#include <identity.hpp>
#include <boost/tokenizer.hpp>
#include <string>

template<typename Tokenizer = boost::tokenizer<>,
         typename Str = std::string,
         typename Converter = identity<Str> >
class tokenize
{
public:
  template<typename Ins>
  void
  operator()(const Str& s, Ins ins) const
  {
    Tokenizer t(s);
    Converter c;
    for (typename Tokenizer::iterator i = t.begin(); i != t.end(); ++i)
      *ins = c(*i);
  }
};

#endif
