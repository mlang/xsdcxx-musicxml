// Copyright (c) 2014 Mario Lang
//
// This program is free software; you can redistribute it and/or modify
// it under the terms of the GNU General Public License version 2 as
// published by the Free Software Foundation.
//
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with this program; if not, write to the Free Software
// Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA 02110-1301 USA
//
// In addition, as a special exception,
// permission to link this program with the Xerces-C++ library (or with
// modified versions of Xerces-C++ that use the same license as Xerces-C++),
// and distribute linked combinations including the two. You must obey
// the GNU General Public License version 2 in all respects for all of
// the code used other than Xerces-C++. If you modify this copy of the
// program, you may extend this exception to your version of the program,
// but you are not obligated to do so. If you do not wish to do so, delete
// this exception statement from your version.

#include <string>
#include <fstream>
#include <iostream>

#include <memory>
#include <string>
#include <fstream>
#include <iostream>
#include <stdexcept>

#include <xercesc/dom/DOM.hpp>

#include <xsd/cxx/xml/string.hxx> // xml::transcode

#include "dom-parse.hpp"

namespace musicxml {

score_timewise convert(score_partwise const &);
score_partwise convert(score_timewise const &);

template <class Score> Score parse(std::istream &, const std::string &id);

template <>
inline score_partwise parse<score_partwise>(std::istream &is,
                                            const std::string &id) {
  using namespace std;
  using namespace xercesc;
  namespace xml = xsd::cxx::xml;

  unique_ptr<DOMDocument> doc{dom::parse(is, id, true)};

  DOMElement *root(doc->getDocumentElement());

  std::string ns(xml::transcode<char>(root->getNamespaceURI()));
  std::string name(xml::transcode<char>(root->getLocalName()));

  if (ns == "") {
    if (name == "score-timewise") {
      return convert(score_timewise(*root));
    } else if (name == "score-partwise") { return score_partwise(*root); }
  }

  throw ::xsd::cxx::tree::unexpected_element<char>(
    name, ns, "score-partwise|score-timewise", "");
}

template <>
inline score_timewise parse<score_timewise>(std::istream &is,
                                            const std::string &id) {
  using namespace std;
  using namespace xercesc;
  namespace xml = xsd::cxx::xml;

  unique_ptr<DOMDocument> doc{dom::parse(is, id, true)};

  DOMElement *root(doc->getDocumentElement());

  std::string ns(xml::transcode<char>(root->getNamespaceURI()));
  std::string name(xml::transcode<char>(root->getLocalName()));

  if (ns == "") {
    if (name == "score-partwise") {
      return convert(score_partwise(*root));
    } else if (name == "score-timewise") { return score_timewise(*root); }
  }

  throw ::xsd::cxx::tree::unexpected_element<char>(
    name, ns, "score-partwise|score-timewise", "");
}

score_timewise::measure_sequence convert(score_partwise::part_sequence const &);
score_partwise::part_sequence convert(score_timewise::measure_sequence const &);

inline void serialize(::std::ostream &os, score_partwise const &s) {
  score_partwise_(os, s);
}

inline void serialize(::std::ostream &os, score_timewise const &s) {
  score_timewise_(os, s);
}
}
