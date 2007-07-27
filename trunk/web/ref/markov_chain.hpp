/* markov_chain.hpp source file
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

#ifndef MARKOV_CHAIN_HPP
#define MARKOV_CHAIN_HPP

#include <bits/markov_chain_iterator.hpp>
#include <bits/binary_lower_bound.hpp>
#include <identity.hpp>

#include <vector>
#include <algorithm>
#include <stdexcept>

template<int Order, typename Symbol, 
         typename Mapping, typename SearchAlgorithm>
class markov_chain;

template<int I, typename T, typename U, typename V, typename W>
T&
operator<<(T& t, const markov_chain<I, U, V, W>& mc)
{ return mc._stream(t); }

/* @class markov_chain

   @description
   This class is an implementation of a Markov chain of order
   <tt>Order</tt> for which the transition matrix is build from
   a sequence of symbols given at time of construction.
   Once a Markov chain has been created it can be used for random walks
   using the iterator interface starting at a given state of the chain.
   At each iteration the next state is chosen according to the
   probabilities observed from the sequence of symbols given at the time
   of construction.
   <p>
   For a Markov chain of order <i>k</i> each state of the Markov chain
   is composed of <i>k</i> symbols. For example, if a Markov chain of
   order 2 over the sequence "ABABC" is created we have the states "AB",
   "BA" and "BC". If the current state of the Makrov chain is "AB"
   the next symbol is either "A" or "C" both with probability 0.5. Thus,
   the next state is either "BA" or "BC". Since from state "BC" no
   further transitions could be observed no further steps are possible.
   Such an <i>end</i> state can be checked with the end iterator
   provided by the interface of this implementation.
   </p>
   <p>Complexities: for an <i>k</i>th order Markov chain the space
   complexity is O(|\Sigma|^{k+1}), where |\Sigma| is the number of
   symbols. The time needed to compute the next state is O(\log |\Sigma|).
   </p>

   @1 Order @2 The order of the markov chain. @3 
   @1 Symbol @2 Type of the symbols. @3
   @1 Mapping @2 For n symbols this mapping must assign each symbol a \
      unique number in the interval [0,n). Hence, if symbols are \
      integers in [0,n) the default identity mapping can be used. \
      @3 identity<Symbol>
   @1 SearchAlgorithm @2 The search algorithm to search for the next \
      state. @3 binary_lower_bound

   @see markov_chain_iterator

   @example
#include <iostream>
#include <markov_chain.hpp>

void ex1() 
{
  typedef markov_chain<2, int> mc_t;
  typedef mc_t::iterator iterator;

  int I[] = {0,1,2,0,1,2,0,1,2,2,1};
  mc_t mc(&I[0], &I[11], 3);
  mc_t::iterator i = mc.begin(&I[0]);

  std::cout << I[0] << I[1] << std::endl;
  for (int n = 0; i != mc.end() && n < 100; ++i, ++n)
  {
    std::cout << *i << std::flush;
  }
  std::cout << std::endl << "current state: <";
  iterator::const_symbol_iterator si = i.begin();
  for (; si != i.end(); ++si)
  {
    std::cout << *si;
  }
  std::cout << ">" << std::endl;
}

void ex2()
{
  typedef markov_chain<2, char> mc_t;
  typedef mc_t::iterator iterator;

  char* c = "HELLO, THIS IS A TESTSTRING";
  mc_t mc(&c[0], &c[strlen(c)], 256);
  iterator i = mc.begin(&c[0]);

  std::cout << c[0] << c[1] << std::endl;
  for (int n = 0; i != mc.end() && n < 100; ++i, ++n)
  {
    std::cout << *i << std::flush;
  }
  std::cout << std::endl << "current state: <";
  iterator::const_symbol_iterator si = i.begin();
  for (; si != i.end(); ++si)
  {
    std::cout << *si;
  }
  std::cout << ">" << std::endl;
}

int main(int argc, char** argv)
{
  srand(102);
  ex1();
  ex2();
}

   @exdescription
   In the first example a Markov chain over integers is created. In the
   second example a Markov chain over the ASCII alphabet is created.
   The output of the examples should be similar to the following one.<br>
   <pre>
01
221
current state: <21>
HE
LLO, THIS IS A THIS IS IS IS IS A THIS A TESTSTRING
current state: <NG>
</pre>

*/

template<int Order, typename Symbol, 
         typename Mapping = identity<Symbol>,
         typename SearchAlgorithm = binary_lower_bound>
class markov_chain
{
public:
  /* @mem The type of the mapping object. */
  typedef Mapping mapping;
  /* @mem An unsigned integral type. */
  typedef size_t size_type;
  /* @mem The type of the symbols. */
  typedef Symbol symbol;
  /* @mem Random walk iterator. */
  typedef markov_chain_iterator<
    markov_chain<Order, Symbol, Mapping>, Order> iterator;

  /* @mem Constructor. Creates a markov chain from the observed
     symbols of the given range. */
  template<typename It>
  markov_chain(It beg, It end, size_type n_symbols, bool fin = true)
    : __n_symbols(n_symbols), __n_states(0)
  {
    insert(beg, end);
    if (fin)
      finalize();
  }

  markov_chain(size_type n_symbols)
    : __n_symbols(n_symbols), __n_states(0)
  { }

  /* @mem Returns a random walk iterator starting at the given initial state.
     @note The state of the Markov chain is stored in the iterator. Hence,
     several iterators can be created and do not interact.
  */
  template<typename It>
  iterator
  begin(It it) 
  { return iterator(this, it, _hash(it, Order)); }

  /* @mem Returns an end iterator. */
  iterator
  end() 
  { return iterator(); }

  void
  finalize()
  { _transform(); }

  template<typename It>
  void
  insert(It beg, It end)
  { _insert(beg, end); }

  size_type
  size() const
  { return __n_states; }

  // XXX replace with a mapping
  template<typename M>
  void
  fill_matrix(M& m) const
  {
    size_type n = dz::pow<Order>::compute(__n_symbols);
    size_type o = n / __n_symbols;
    size_type c = 0;
    std::vector<size_type> p(n);
    
    for (size_type i = 0; i < n; ++i)
      if (__state_vec[i])
        p[i] = c++;

    for (size_type i = 0; i < n; ++i)
    {
      for (typename row::const_iterator j = __v[i].begin(); 
        j != __v[i].end(); ++j)
      {
        size_type next_state = _next_state(i, j->second, o);
        m[p[i]][p[next_state]] = j->first - 
          ((j == __v[i].begin()) ? 0 : (j - 1)->first);
        m[p[i]][p[next_state]] /= __v[i].back().first;
      }
    }
  }

  template<typename M>
  void
  fill_complete_matrix(M& m) const
  {
    size_type n = dz::pow<Order>::compute(__n_symbols);
    size_type o = n / __n_symbols;

    for (size_type i = 0; i < n; ++i)
    {
      for (typename row::const_iterator j = __v[i].begin(); 
        j != __v[i].end(); ++j)
      {
        size_type next_state = _next_state(i, j->second, o);
        m[i][next_state] = j->first - 
          ((j == __v[i].begin()) ? 0 : (j - 1)->first);
        m[i][next_state] /= __v[i].back().first;
      }
    }
  }

  size_type
  capacity() const
  { return __v.size(); }

private:
  friend class markov_chain_iterator<
    markov_chain<Order, Symbol, Mapping>, Order>;

  template<int I, typename T, typename U, typename V, typename W>
  friend T& operator<<(T& t, const markov_chain<I, U, V, W>& mc);

  template<typename T>
  T&
  _stream(T& t) const
  {
    size_type n = dz::pow<Order>::compute(__n_symbols);
    for (size_type i = 0; i < n; ++i)
    {
      if (__state_vec[i])
      {
        t << i << ": ";
        size_type p = 0;
        for (typename row::const_iterator j = __v[i].begin();
          j != __v[i].end(); ++j)
        {
          t << static_cast<size_type>(__mapping(j->second)) 
            << ":" << j->first - p << " ";
          p = j->first;
        }
        t << "/" << __v[i].back().first << std::endl;
      }
    }
    return t;
  }

  size_type
  _next_state(size_type current_state, const symbol& s, size_type n) const
  {
    size_type first_state = current_state / n;
    size_type next = 
      (current_state - first_state * n) * __n_symbols + 
      static_cast<size_type>(__mapping(s));
    return next;
  }

  struct __compare1st
  {
    template<typename T, typename U>
    bool
    operator()(const T& t, const U& u) const
    { return t.first < u; }
  };

  bool
  _symbol(size_type p, symbol& s) const
  {
    if (__v[p].empty())
      return false;
    size_type n = 1 + rand() % __v[p].back().first;
    s = __search(__v[p].begin(), __v[p].end(), n, __compare1st())->second;
    return true;
  }

  // XXX problem if first range has less than Order symbols
  template<typename It>
  void
  _insert(It beg, It end)
  {
    if (__v.empty())
      _init(beg, end);
    size_type h = _hash(&__s[0], Order);
    for (; beg != end; ++beg)
    {
      size_type m = static_cast<size_type>(__mapping(*beg));
      if (m >= __n_symbols)
        throw std::out_of_range("invalid symbol mapping");
      copy_n<Order - 1>::assign(&__s[1], &__s[0]);
      if (__v[h].size() <= m)
        __v[h].resize(m + 1);
      __v[h][m].second = __s[Order - 1] = *beg;
      __v[h][m].first++;
      _count_state((h = _hash(&__s[0], Order)));
    }
  }

  template<typename It>
  void
  _init(It& beg, It end)
  {
    for (size_type i = 0; i < Order && beg != end; ++i, ++beg)
      __s[i] = *beg;
    size_type rows = dz::pow<Order>::compute(__n_symbols);
    __v.resize(rows);
    __state_vec.resize(rows, false);
    _count_state(_hash(&__s[0], Order));
  }

  void
  _count_state(size_type n)
  {
    if (!__state_vec[n])
    {
      __state_vec[n].flip();
      __n_states++;
    }
  }

  void
  _transform()
  {
    for (typename rows::iterator i = __v.begin(); i != __v.end(); ++i)
      if (!i->empty())
        _transform_row(*i);
  }

  template<typename C>
  void
  _transform_row(C& c)
  {
    size_type n = 0;
    for (typename C::iterator i = c.begin(); i != c.end();)
      if (i->first == 0)
      {
        *i = c.back();
        c.pop_back();
      } else
        n = i->first = i->first + n, ++i;
  }

  template<typename It>
  size_type
  _hash(It beg, size_type n) const
  {
    size_type r = 0;
    for (; n; ++beg, --n)
      r = r * __n_symbols + static_cast<size_type>(__mapping(*beg));
    return r;
  }

  typedef std::pair<size_type, Symbol> entry;
  typedef std::vector<entry> row;
  typedef std::vector<row> rows;
  typedef std::vector<bool> state_vec;

  Mapping __mapping;
  size_type __n_symbols;
  rows __v;
  Symbol __s[Order];
  SearchAlgorithm __search;
  size_type __n_states;
  state_vec __state_vec;
};

#endif
