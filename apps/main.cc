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


#include <vector>
#include <ext/hash_map>
#include <key_id_map.hpp>
#include <hashing.hpp>
#include <cmath>
#include <ext/hash_set>

template<typename FeatureType, typename LabelType>
class bayes
{
public:
  typedef size_t size_type;
  typedef FeatureType feature_type;
  typedef LabelType label_type;

  bayes()
    : __n(0)
  { }

  template<typename WDM>
  void
  build(const WDM& wdm)
  {
    for (typename WDM::const_iterator i = wdm.begin(); i != wdm.end(); ++i)
    {
      size_type n = __lmap(wdm.property(i).label());
      if (n >= __label_cnt.size())
      {
        __label_cnt.resize(n + 1);
        __feature_cnt.resize(n + 1);
      }
      __label_cnt[n]++;
      __n++;
      for (typename WDM::token_list_type::const_iterator j = i->begin();
          j != i->end(); ++j)
      {
        size_type p = __feature_map(wdm.feature(j->first));
        if (p >= __feature_cnt[n].size())
          __feature_cnt[n].resize(p + 1);
        __feature_cnt[n][p]++;
      }
    }
    for (unsigned i = 0; i < __lmap.size(); ++i)
      __feature_cnt[i].resize(__feature_map.size());
    _build();
  }

  template<typename It, typename Conv>
  const label_type&
  classify(It beg, It end, Conv c) const
  {
    size_type max = 0;
    double pmax = 0.0;
    for (size_type i = 0; i < __feature_cnt.size(); ++i)
    {
      double p = _classify(beg, end, i, c);
      if (p >= pmax)
      {
        pmax = p;
        max = i;
      }
    }
    return __lmap[max];
  }

private:
  void
  _build()
  {
    for (size_type i = 0; i < __feature_cnt.size(); ++i)
      for (size_type j = 0; j < __feature_cnt[i].size(); ++j)
        __feature_cnt[i][j] /= __label_cnt[i];
  }

  template<typename It, typename Conv>
  double
  _classify(It beg, It end, size_type l, Conv c) const
  {
    __gnu_cxx::hash_set<feature_type> fs;
    for (; beg != end; ++beg)
      fs.insert(c(*beg));
    double s = 0;
    for (unsigned i = 0; i < __feature_map.size(); ++i)
    {
      double pr = 0;
      if (fs.find(__feature_map[i]) == fs.end())
        pr = 1.0 - __feature_cnt[l][i];
      else
        pr = __feature_cnt[l][i];
      if (pr < 0.0001) pr = 0.0001;
      s += log(pr);
    }
    return exp(s) * (double) __label_cnt[l] / (double) __n;
  }

  typedef std::vector<double> weights_t;

  size_type __n;
  ll::key_id_map<label_type> __lmap;
  ll::key_id_map<feature_type> __feature_map;

  std::vector<size_type> __label_cnt;
  std::vector<weights_t> __feature_cnt;
};


template<typename WDM>
class select_feature
{
public:
  select_feature(const WDM& wdm)
    : __wdm(wdm)
  { }

  const typename WDM::feature_type&
  operator()(const typename WDM::pair_type& t) const
  {
    return __wdm.feature(t.first);
  }

private:
  const WDM& __wdm;
};

int
main(int argc, char** argv)
{
  ll::wdm<std::string, int, ll::wdm_label_file_property<std::string> > w;

  std::cout << "reading spam ...\n";
  // read spam
  ll::directory_iterator it_end;
  ll::directory_iterator it_pos(POS);
  ll::wdm_insert_files<ll::wdm_email_tokenizer<boost::tokenizer<> > >
    (w, it_pos, it_end, 
     ll::wdm_label_file_property_creator<std::string>("pos"));

  std::cout << "reading ham ...\n";
  // read ham
  ll::directory_iterator it_neg(NEG);
  ll::wdm_insert_files<ll::wdm_email_tokenizer<boost::tokenizer<> > >
    (w, it_neg, it_end, 
     ll::wdm_label_file_property_creator<std::string>("neg"));

  std::cout << "build model ...\n";
  bayes<std::string, std::string> b;
  b.build(w);

  double neg_c = 0;
  double pos_c = 0;
  double pos_n = 0;
  double neg_n = 0;
  select_feature<ll::wdm<std::string, int, ll::wdm_label_file_property<std::string> > > s(w);
  for (ll::wdm<std::string, int, ll::wdm_label_file_property<std::string> >::iterator i = w.begin(); i != w.end(); ++i)
  {
    std::string l = b.classify(i->begin(), i->end(), s);
    std::cout << w.property(i).label() << " " << l << " ";
    if (w.property(i).label() == "pos")
    {
      if (l == "pos") pos_c++;
      pos_n++;
    }
    else
    {
      if (l == "neg") neg_c++;
      neg_n++;
    }
    std::cout << pos_c / pos_n << " " << neg_c / neg_n << "\n";
  }
}

