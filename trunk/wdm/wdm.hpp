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

template<typename FeatureType, typename T, typename Property = null>
class wdm
{
public:
  typedef wdm<FeatureType, T, Property> wdm_type;
  typedef Property property_type;
  typedef FeatureType feature_type;
  typedef T value_type;
  typedef size_t size_type;
  typedef std::pair<size_type, T> pair_type;
  typedef std::vector<pair_type> token_list_type;

  typedef typename std::vector<token_list_type>::iterator iterator;
  typedef typename std::vector<token_list_type>::const_iterator const_iterator;

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
    __p.push_back(p);
  }

  iterator
  begin()
  { return __v.begin(); }

  const_iterator
  begin() const
  { return __v.begin(); }

  iterator
  end()
  { return __v.end(); }

  const_iterator
  end() const
  { return __v.end(); }

  const property_type&
  property(const iterator& i) const
  { return __p[i - __v.begin()]; }

  const property_type&
  property(const const_iterator& i) const
  { return __p[i - __v.begin()]; }

  const feature_type&
  feature(size_type n) const
  { return __k[n]; }

private:
  std::vector<token_list_type> __v;
  std::vector<property_type> __p;
  ll::key_id_map<feature_type> __k;
};

}
#endif

