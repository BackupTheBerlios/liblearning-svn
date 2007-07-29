/* wdm.hpp source file
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

#ifndef LL_WDM_HPP
#define LL_WDM_HPP

#include <key_id_map.hpp>
#include <vector>
#include <map>
#include <null.hpp>

namespace ll
{

template<typename TokenType, typename T, typename Property = null>
class wdm
{
public:
  typedef Property property_type;
  typedef TokenType token_type;
  typedef T value_type;
  typedef size_t size_type;
  typedef std::vector<std::pair<size_type, T> > token_list_type;

  wdm()
  { }

  template<typename It>
  void
  push_back(It beg, It end)
  { push_back(beg, end, null()); }

  template<typename It>
  void
  push_back(It beg, It end, const Property& p)
  {
    std::map<size_type, size_type> m;
    token_list_type tl;
    for (; beg != end; ++beg)
      m[__k(*beg)]++;
    for (std::map<size_type, size_type>::iterator i = m.begin();
        i != m.end(); ++i)
      tl.push_back(std::make_pair(i->first, i->second));
    __v.push_back(tl);
  }

private:
  std::vector<token_list_type> __v;
  ll::key_id_map<TokenType> __k;
};

}
#endif

