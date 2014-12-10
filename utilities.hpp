#include <string>
#include <fstream>
#include <iostream>

#include <memory>
#include <string>
#include <fstream>
#include <iostream>
#include <stdexcept>

#include <xercesc/dom/DOM.hpp>

#include <xsd/cxx/xml/string.hxx>       // xml::transcode

#include "dom-parse.hpp"

namespace musicxml {

template<class Score> Score document (std::istream& is, const std::string& id);

template<>
inline score_partwise document<score_partwise>(std::istream& is, const std::string& id)
{
  using namespace std;
  using namespace xercesc;
  namespace xml = xsd::cxx::xml;

  unique_ptr<DOMDocument> doc { parse (is, id, true) };

  DOMElement* root (doc->getDocumentElement ());

  std::string ns (xml::transcode<char> (root->getNamespaceURI ()));
  std::string name (xml::transcode<char> (root->getLocalName ()));

  if (ns == "") {
    if (name == "score-timewise") {
      throw std::runtime_error("MusicXML format conversion unimplemeneted.");
    } else if (name == "score-partwise") {
      return *root;
    }
  }
  throw std::runtime_error("Unknown root element '" + name + "'");
}

template<>
inline score_timewise document<score_timewise>(std::istream& is, const std::string& id)
{
  using namespace std;
  using namespace xercesc;
  namespace xml = xsd::cxx::xml;

  unique_ptr<DOMDocument> doc { parse (is, id, true) };

  DOMElement* root (doc->getDocumentElement ());

  std::string ns (xml::transcode<char> (root->getNamespaceURI ()));
  std::string name (xml::transcode<char> (root->getLocalName ()));

  if (ns == "") {
    if (name == "score-partwise") {
      throw std::runtime_error("MusicXML format conversion unimplemeneted.");
    } else if (name == "score-timewise") {
      return *root;
    }
  }
  throw std::runtime_error("Unknown root element '" + name + "'");
}

#define DEFINE_PUSH_BACK(child) \
inline void push_back(score_partwise::part_type::measure_type &measure,     \
               child const &c)                         \
{                                                                              \
  measure.child().push_back(c);                                  \
  measure.content_order().push_back({ \
    std::remove_reference<decltype(measure)>::type::child##_id, \
    measure.child().size() - 1 \
  }); \
} \
inline void push_back(score_timewise::measure_type::part_type &part,     \
               child const &c)                         \
{                                                                              \
  part.child().push_back(c);                                  \
  part.content_order().push_back({ \
    std::remove_reference<decltype(part)>::type::child##_id, \
    part.child().size() - 1 \
  }); \
}

DEFINE_PUSH_BACK(attributes)
DEFINE_PUSH_BACK(backup)
DEFINE_PUSH_BACK(barline)
DEFINE_PUSH_BACK(direction)
DEFINE_PUSH_BACK(figured_bass)
DEFINE_PUSH_BACK(forward)
DEFINE_PUSH_BACK(grouping)
DEFINE_PUSH_BACK(harmony)
DEFINE_PUSH_BACK(link)
DEFINE_PUSH_BACK(note)
DEFINE_PUSH_BACK(print)
DEFINE_PUSH_BACK(sound)

#undef DEFINE_PUSH_BACK
}

