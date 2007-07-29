/* wdm_insert_files.hpp source file
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

#ifndef WDM_INSERT_FILES_HPP
#define WDM_INSERT_FILES_HPP

#include <fstream>
#include <string>
#include <stdexcept>
#include <strings.hpp>

namespace ll
{

template<typename Tokenizer, typename WDM, typename It>
void
wdm_insert_files(WDM& wdm, It beg, It end)
{
  char buf[4096];
  std::string s;

  for (; beg != end; ++beg)
  {
    std::ifstream is(c_str(*beg));
    if (!is.is_open() || is.fail())
      throw std::runtime_error(std::string("could not open file ") +
        *beg);
    do {
      is.read(buf, sizeof(buf));
      s.append(buf, is.gcount());
    } while (is.gcount());
    Tokenizer tok(s);
    wdm.push_back(tok.begin(), tok.end());
    s.assign("");
  }
}

template<typename Tokenizer, typename WDM, typename It, typename PropCreator>
void
wdm_insert_files(WDM& wdm, It beg, It end, PropCreator p)
{
  char buf[4096];
  std::string s;

  for (; beg != end; ++beg)
  {
    std::ifstream is(c_str(*beg));
    if (!is.is_open() || is.fail())
      throw std::runtime_error(std::string("could not open file ") +
        *beg);
    do
    {
      is.read(buf, sizeof(buf));
      s.append(buf, is.gcount());
    } while (is.gcount());
    Tokenizer tok(s);
    wdm.push_back(tok.begin(), tok.end(), p(*beg, s));
    s.assign("");
  }
}

}
#endif

