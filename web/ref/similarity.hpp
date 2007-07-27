/* similarity.hpp source file
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

#ifndef SIMILARITY_HPP
#define SIMILARITY_HPP

template<typename It, typename Sim>
std::pair<double, size_t>
all_pairs_similarity(It beg, It end, Sim sim)
{
  double r = 0;
  size_t n = 0;
  for (; beg != end; ++beg)
  {
    It i = beg;
    for (++i; i != end; ++i, ++n)
      r += sim(*beg, *i);
  }
  return std::make_pair(r, n);
}

template<typename It, typename Sim>
std::pair<double, size_t>
all_pairs_similarity_if(It beg, It end, Sim sim)
{
  double r = 0;
  size_t n = 0;
  for (; beg != end; ++beg)
  {
    It i = beg;
    for (++i; i != end; ++i)
    {
      std::pair<double, bool> p = sim(*beg, *i);
      if (p.second)
      {
        r += p.first;
        n++;
      }
    }
  }
  return std::make_pair(r, n);
}

#endif
