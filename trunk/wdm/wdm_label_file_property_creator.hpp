/* wdm_label_file_property_creator.hpp source file
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

#ifndef LL_WDM_LABEL_FILE_PROPERTY_CREATOR_HPP
#define LL_WDM_LABEL_FILE_PROPERTY_CREATOR_HPP

#include <string>
#include <wdm/wdm_label_file_property.hpp>

namespace ll
{

template<typename T>
class wdm_label_file_property_creator
{
public:
  wdm_label_file_property_creator(const T& label)
    : __label(label)
  { }

  wdm_label_file_property<T>
  operator()(const std::string& fname, const std::string& content) const
  { return wdm_label_file_property<T>(__label, fname); }

  wdm_label_file_property<T>
  operator()(const std::string& fname) const
  { return wdm_label_file_property<T>(__label, fname); }

private:
  T __label;
};

}
#endif

