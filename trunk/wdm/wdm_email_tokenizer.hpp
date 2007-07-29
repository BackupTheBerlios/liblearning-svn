/* wdm_email_tokenizer.hpp source file
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

#ifndef LL_WDM_EMAIL_TOKENIZER_HPP
#define LL_WDM_EMAIL_TOKENIZER_HPP

#include <string>
#include <boost/algorithm/string/case_conv.hpp>
#include <emails/extract_text_parts.hpp>

namespace ll
{

template<typename Seq>
void
_split_email(const Seq& mail, Seq& header, Seq& body)
{
  typename Seq::size_type n = mail.find("\n\n");
  if (n != Seq::npos)
  {
    header = mail.substr(0, n);
    if (n + 2 < mail.size())
      body = mail.substr(n + 2);
  }
  else if ((n = mail.find("\r\n\r\n")) != Seq::npos)
  {
    header = mail.substr(0, n);
    if (n + 4 < mail.size())
      body = mail.substr(n + 4);
  }
}

// we need a redesign here
template<typename Seq>
void
_parse(const Seq& s, Seq& dst)
{
  std::string header;
  std::string body;
  dst = "";
  _split_email(s, header, body);
  ll::extract_text_parts(header, body, dst);
}

// XXX non copyable
template<typename Tokenizer>
class wdm_email_tokenizer
{
public:
  typedef Tokenizer tokenizer_type;

  template<typename Seq>
  wdm_email_tokenizer(const Seq& s)
  {
    _parse(s, __r);
    boost::algorithm::to_lower(__r);
    __tok = new Tokenizer(__r);
  }

  ~wdm_email_tokenizer()
  { delete __tok; }

  typename Tokenizer::iterator
  begin()
  { return __tok->begin(); }

  typename Tokenizer::iterator
  end()
  { return __tok->end(); }

private:
  std::string __r;
  Tokenizer* __tok;
};

}

#endif
