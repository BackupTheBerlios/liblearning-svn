/* decode_header_field.hpp source file
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

#ifndef DECODE_HEADER_FIELD_HPP
#define DECODE_HEADER_FIELD_HPP

#include <boost/algorithm/string/case_conv.hpp>
#include <boost/algorithm/string/trim.hpp>

template<typename String, typename Ins>
void decode_header_field(String s, Ins ins, bool lc_key = true) {
	typename String::size_type p = s.find(":");
	if (p != String::npos) {
		String k = s.substr(0, p);
		boost::algorithm::trim_right(k);
		String v;
		if (p + 1 < s.size())
			v = s.substr(p + 1);
		boost::algorithm::trim(v);
		if (lc_key)
			boost::to_lower(k);
		*ins = std::make_pair(k, v);
	}
}

#endif
