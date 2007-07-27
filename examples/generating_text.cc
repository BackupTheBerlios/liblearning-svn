/* generate_text.cc source file
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

#include <iostream>
#include <directory_iterator.hpp>
#include <file_reader.hpp>
#include <markov_chain.hpp>

/* This class takes a reference to a Markov chain.
 * Each time the operator() is called the Markov chain is updated
 * with the given text.
 */
template<typename T>
class markov_creator
{
public:
  markov_creator(T& mc)
    : __mc(mc)
  { }

  template<typename Str>
  void
  operator()(const Str& s) const
  { __mc.insert(s.begin(), s.end()); }

private:
  T& __mc;
};

int main(int argc, char** argv)
{
  // we have to use unsigned, otherwise letters like the german 'ä'
  // are interpreted as negative values which results in very big
  // values when internally being casted to unsigned integral types.

  typedef markov_chain<2, char, identity<unsigned char> > mc_t;

  // create an iterator to traverse the content of a directory
  directory_iterator dir_it("./data/generating_text",
    directory_iterator::regular);
  directory_iterator dir_end;

  // create a Markov model with 256 possible symbols
  mc_t mc_model(256);

  markov_creator<mc_t> mc(mc_model);

  // read the content of each file of the directory and update the
  // Markov chain
  std::for_each(dir_it, dir_end,
    std::bind2nd(file_reader<directory_iterator::value_type,
    markov_creator<mc_t> >(), mc));

  // build the Markov chain
  mc_model.finalize();

  // start at the state "bei"
  const char* initial = "bei";

  // generate symbol by symbol
  for (mc_t::iterator i = mc_model.begin(initial);
      i != mc_model.end(); ++i)
  {
    std::cout << *i << std::flush;
  }
}

