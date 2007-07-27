/* parse_header.hpp source file
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

#ifndef PARSE_HEADER_HPP
#define PARSE_HEADER_HPP

#include <boost/algorithm/string/trim.hpp>
#include <boost/tokenizer.hpp>
#include <emails/decode_header_field.hpp>

template<typename String, typename Ins>
void parse_header(const String& s, Ins ins, bool lc_key = true) {
	boost::char_delimiters_separator<char> tf(false, "\n", "\n");
	boost::tokenizer<> t(s, tf);
	String lastline;
	for (typename boost::tokenizer<>::iterator i = t.begin();
			i != t.end(); ++i) {
		if (!i->empty()) {
			String tmp(*i);
			boost::algorithm::trim_right(tmp);
			if (isspace(tmp[0])) {
				boost::algorithm::trim_left(tmp);
				lastline += " " + tmp;
			} else {
				if (!lastline.empty())
					decode_header_field(lastline, ins, lc_key);
				lastline = tmp;
			}
		}
	}
	if (!lastline.empty())
		decode_header_field(lastline, ins, lc_key);
}

#endif

