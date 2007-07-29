/* main.c source file
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

// 500 spam; remove file "cmds" first
#define POS "/home/dz/data/corpora/spam/spamassassin_corpus/spam"
// 2500 ham; remove file "cmds" first
#define NEG "/home/dz/data/corpora/spam/spamassassin_corpus/easy_ham"

#include <wdm.hpp>
#include <boost/tokenizer.hpp>

int
main(int argc, char** argv)
{
  ll::wdm<std::string, int, ll::wdm_label_file_property<std::string> > w;

  // read spam
  ll::directory_iterator it_end;
  ll::directory_iterator it(POS);
  ll::wdm_insert_files<ll::wdm_email_tokenizer<boost::tokenizer<> > >
    (w, it, it_end, ll::wdm_label_file_property_creator<std::string>("pos"));

  // read ham
  
}

