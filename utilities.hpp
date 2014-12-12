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

}

