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
