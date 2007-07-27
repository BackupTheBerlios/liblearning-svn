/* extract_text_parts.hpp source file
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

#ifndef EXTRACT_TEXT_PARTS_HPP
#define EXTRACT_TEXT_PARTS_HPP

#ifdef USE_EXT
#include <ext/hash_map>
#include <hasher.hpp>
#else
#include <map>
#endif
#include <sstream>
#include <map_inserter.hpp>
#include <emails/parse_header.hpp>
#include <mbox_iterator.hpp>
#include <boost/algorithm/string/find.hpp>
#include <boost/regex.hpp>
#include <boost/algorithm/string/split.hpp>

template<typename String>
String
__get_boundary(const String& s)
{
  boost::cmatch m;
  boost::regex expr("^.*?boundary[[:space:]]*=[[:space:]]*\"(.*)\"", 
    boost::regex::perl|boost::regex::icase);
  if (boost::regex_match(s.c_str(), m, expr))
    return m[1];
  return "";
}

template<typename Str1, typename Str2>
void
__parse_part(const Str1& s, Str2& dst, int max_depth, int depth)
{
  if (!s.size())
    return;
  std::stringstream str;
  str << s;
  mbox_iterator<Str2> it(&str);
  mbox_iterator<Str2> it_end;
  for (; it != it_end; ++it)
    extract_text_parts(it.header(), it.body(), dst, max_depth, depth);
}

template<typename String>
void
extract_text_parts(const String& header, const String& body, String& dst,
  int max_depth = 7, int depth = 1)
{
  if (depth > max_depth)
    return;
  namespace __ba = boost::algorithm;
#ifdef USE_EXT
  __gnu_cxx::hash_map<String, String> h;
  typename __gnu_cxx::hash_map<String, String>::iterator it;
#else
  std::map<String, String> h;
  typename std::map<String, String>::iterator it;
#endif
  parse_header(header, map_inserter(h));
  if ((it = h.find("content-type")) == h.end())
    return;
  if (__ba::ifind_first(it->second, "text/plain"))
    dst.append(body);
  else if (__ba::ifind_first(it->second, "multipart/"))
  {
    String s(__get_boundary(it->second));
    if (s.empty())
      return;
    typedef __ba::split_iterator<typename String::const_iterator> It;
    It it_end;
    It it = __ba::make_split_iterator(body,
      __ba::first_finder(s, __ba::is_equal()));
    for (; it != it_end; ++it)
      __parse_part(boost::trim_left_copy(*it), dst, max_depth, depth);
  }
}

#endif
