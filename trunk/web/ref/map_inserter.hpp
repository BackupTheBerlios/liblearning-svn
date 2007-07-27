/* map_inserter.hpp source file
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

#ifndef MAP_INSERTER_HPP
#define MAP_INSERTER_HPP

template<typename C>
class map_insert_iterator_proxy {
public:
	map_insert_iterator_proxy(C& c) : _c(c) { }

	template<typename T, typename U>
	void operator=(const std::pair<T, U>& v) {
		_c.insert(v);
	}
protected:
	C& _c;
};

template<typename C>
class map_insert_iterator {
public:
	map_insert_iterator(C& c) : _c(c) { }

	map_insert_iterator_proxy<C> operator*() {
		return map_insert_iterator_proxy<C>(_c);
	}
protected:
	C& _c;
};

template<typename C>
map_insert_iterator<C> map_inserter(C& c) {
	return map_insert_iterator<C>(c);
}

#endif
