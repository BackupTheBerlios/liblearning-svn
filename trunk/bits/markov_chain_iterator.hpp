/* markov_chain_iterator.hpp source file
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

#ifndef MARKOV_CHAIN_ITERATOR_HPP
#define MARKOV_CHAIN_ITERATPR_HPP

#include <loop_unroll.hpp>

/* @class markov_chain_iterator
   @description Iterator to iterate over the states of a Markov chain.
   @1 P @2 The class of the Markov chain. @3
   @1 Order @2 The order of the Markov chain. @3
*/
template<typename P, int Order>
class markov_chain_iterator
{
public:
  typedef typename P::size_type size_type;
  typedef typename P::symbol symbol;
  typedef symbol& reference;
  typedef const symbol& const_reference;
  typedef markov_chain_iterator<P, Order> iterator;
  typedef const symbol* const_symbol_iterator;

  template<typename It>
  markov_chain_iterator(const P* p, It it, size_type n) 
    : __p(p), __n(n) 
  {
    copy_n<Order>::assign(it, &__s[0]);
    _next_symbol();
  }

  /* @mem Creates an end iterator. */
  markov_chain_iterator() 
    : __n(static_cast<size_type>(-1)) 
  { }

  /* @mem Steps forward to the next state. */
  iterator&
  operator++()
  {
    if (__n != static_cast<size_type>(-1))
    {
      copy_n<Order - 1>::assign(&__s[1], &__s[0]);
      __s[Order - 1] = __cs;
      __n = __p->_hash(&__s[0], Order);
      _next_symbol();
    }
    return *this;
  }

  /* @mem Checks whether both iterators are in the same state. */
  bool
  operator==(const iterator& i) const
  { return (__n == i.__n); }

  /* @mem Checks whether the iterators are in different states. */
  bool
  operator!=(const iterator& i) const
  { return !operator==(i); }

  /*! @mem Returns the next symbol. */
  const_reference
  operator*() const
  { return __cs; }

  /*! @mem Assigns the given iterator to the current one. */
  iterator&
  operator=(const iterator& i)
  {
    __n = i.__n;
    __p = i.__p;
    _copy_n(&i.__s[0], Order, &__s[0]);
    __cs = i.__cs;
    return *this;
  }

  // Returns an iterator pointing to the first symbol of the current state.
  const_symbol_iterator
  begin() const
  { return &__s[0]; }

  // Returns an end iterator.
  const_symbol_iterator
  end() const
  { return &__s[Order]; }

private:
  void
  _next_symbol()
  {
    if (!__p->_symbol(__n, __cs))
      __n = static_cast<size_type>(-1); // end iterator
  }

  size_type __n;
  const P* __p;
  symbol __s[Order];
  symbol __cs;
};

#endif
