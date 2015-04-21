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

#include "musicxml.hpp"

#include <xsd/cxx/xml/dom/serialization-source.hxx>
#include <xsd/cxx/tree/error-handler.hxx>
#include <xsd/cxx/tree/exceptions.hxx>
#include <xsd/cxx/xml/dom/bits/error-handler-proxy.hxx>

#include <istream>

#include <xercesc/dom/DOM.hpp>
#include <xercesc/framework/MemBufInputSource.hpp>
#include <xercesc/framework/Wrapper4InputSource.hpp>
#include <xercesc/framework/XMLGrammarPoolImpl.hpp>
#include <xercesc/util/XMLUniDefs.hpp> // chLatin_*

#include <xsd/cxx/xml/sax/std-input-source.hxx>
#include <xsd/cxx/xml/dom/bits/error-handler-proxy.hxx>

#include "grammar-input-stream.hpp"
#include <musicxml-dtd.hpp>
#include <musicxml-schema.hpp>

using std::istream;
using std::ostream;
using std::unique_ptr;
using xercesc::chLatin_L;
using xercesc::chLatin_S;
using xercesc::chNull;
using xercesc::DOMConfiguration;
using xercesc::DOMDocument;
using xercesc::DOMDocumentType;
using xercesc::DOMElement;
using xercesc::DOMImplementation;
using xercesc::DOMImplementationLS;
using xercesc::DOMImplementationRegistry;
using xercesc::DOMLSInput;
using xercesc::DOMLSOutput;
using xercesc::DOMLSParser;
using xercesc::DOMLSResourceResolver;
using xercesc::DOMLSSerializer;
using xercesc::MemBufInputSource;
using xercesc::MemoryManager;
using xercesc::Wrapper4InputSource;
using xercesc::XMLGrammarPool;
using xercesc::XMLGrammarPoolImpl;
using xercesc::XMLPlatformUtils;
using xercesc::XMLUni;

namespace xml = xsd::cxx::xml;
namespace tree = xsd::cxx::tree;

namespace {

struct embedded_resource_resolver: DOMLSResourceResolver {
  DOMLSInput* resolveResource( XMLCh const * const /* resourceType */
                             , XMLCh const * const /* namespaceUri */
                             , XMLCh const * const publicId
                             , XMLCh const * const /* systemId */
                             , XMLCh const * const /* baseURI */
                             )
  {
    std::string public_id(xml::transcode<char>(publicId));
    if (musicxml::dtd.find(public_id) != musicxml::dtd.end()) {
      auto const &pair = musicxml::dtd.at(public_id);
      auto source = new MemBufInputSource(pair.first, pair.second,
                                          public_id.c_str());
      return new Wrapper4InputSource(source);
    }
    return nullptr;
  }
};

}

static const XMLCh ls_id[] = {chLatin_L, chLatin_S, chNull};

static std::unique_ptr<DOMDocument>
dom_document(std::istream &is, const std::string &id, bool validate) {
  MemoryManager *mm(XMLPlatformUtils::fgMemoryManager);
  std::unique_ptr<XMLGrammarPool> gp(new XMLGrammarPoolImpl(mm));
  grammar_input_stream gis(musicxml_schema, sizeof(musicxml_schema));
  gp->deserializeGrammars(&gis);
  gp->lockPool();

  DOMImplementation *dom {
    DOMImplementationRegistry::getDOMImplementation(ls_id)
  };

  std::unique_ptr<DOMLSParser> parser {
    dom->createLSParser(DOMImplementationLS::MODE_SYNCHRONOUS, nullptr, mm, gp.get())
  };

  DOMConfiguration *conf { parser->getDomConfig() };

  embedded_resource_resolver resolver;
  conf->setParameter(XMLUni::fgDOMResourceResolver, &resolver);
  // Discard comment nodes in the document.
  conf->setParameter(XMLUni::fgDOMComments, false);

  // Enable datatype normalization.
  conf->setParameter(XMLUni::fgDOMDatatypeNormalization, true);

  // Do not create EntityReference nodes in the DOM tree. No
  // EntityReference nodes will be created, only the nodes
  // corresponding to their fully expanded substitution text
  // will be created.
  conf->setParameter(XMLUni::fgDOMEntities, false);

  // Perform namespace processing.
  conf->setParameter(XMLUni::fgDOMNamespaces, true);

  // Do not include ignorable whitespace in the DOM tree.
  conf->setParameter(XMLUni::fgDOMElementContentWhitespace, false);

  // Enable/Disable validation.
  conf->setParameter(XMLUni::fgDOMValidate, validate);
  conf->setParameter(XMLUni::fgXercesSchema, validate);
  conf->setParameter(XMLUni::fgXercesSchemaFullChecking, false);

  // Use the loaded grammar during parsing and disable loading schemas via other
  // means (e.g., schemaLocation).
  conf->setParameter(XMLUni::fgXercesUseCachedGrammarInParse, true);
  conf->setParameter(XMLUni::fgXercesLoadSchema, false);

// Xerces-C++ 3.1.0 is the first version with working multi import
// support.
#if _XERCES_VERSION >= 30100
  conf->setParameter(XMLUni::fgXercesHandleMultipleImports, true);
#endif

  // We will release the DOM document ourselves.
  conf->setParameter(XMLUni::fgXercesUserAdoptsDOMDocument, true);

  // Set error handler.
  tree::error_handler<char> eh;
  xml::dom::bits::error_handler_proxy<char> ehp { eh };
  conf->setParameter(XMLUni::fgDOMErrorHandler, &ehp);

  // Prepare input stream.
  xml::sax::std_input_source isrc { is, id };
  Wrapper4InputSource wrap { &isrc, false };

  std::unique_ptr<DOMDocument> doc { parser->parse(&wrap) };

  eh.throw_if_failed<tree::parsing<char>>();

  return doc;
}

template <>
musicxml::score_partwise
musicxml::parse<musicxml::score_partwise>(std::istream &is,
                                          const std::string &id) {
  xml::auto_initializer xerces_platform { true, false };

  std::unique_ptr<DOMDocument> doc { dom_document(is, id, true) };
  DOMElement *root { doc->getDocumentElement() };

  std::string const ns { xml::transcode<char>(root->getNamespaceURI()) };
  std::string const name { xml::transcode<char>(root->getLocalName()) };

  if (ns == "") {
    if (name == "score-timewise") {
      return musicxml::convert(musicxml::score_timewise{*root});
    } else if (name == "score-partwise") {
      return musicxml::score_partwise{*root};
    }
  }

  throw tree::unexpected_element<char>(name, ns,
                                       "score-partwise|score-timewise", "");
}

template <>
musicxml::score_timewise
musicxml::parse<musicxml::score_timewise>(std::istream &is,
                                          const std::string &id) {
  xml::auto_initializer xerces_platform { true, false };

  std::unique_ptr<DOMDocument> doc { dom_document(is, id, true) };
  DOMElement *root { doc->getDocumentElement() };

  std::string const ns { xml::transcode<char>(root->getNamespaceURI()) };
  std::string const name { xml::transcode<char>(root->getLocalName()) };

  if (ns == "") {
    if (name == "score-partwise") {
      return musicxml::convert(musicxml::score_partwise{*root});
    } else if (name == "score-timewise") {
      return musicxml::score_timewise{*root};
    }
  }

  throw tree::unexpected_element<char>(name, ns,
                                       "score-partwise|score-timewise", "");
}

musicxml::score_timewise::measure_sequence
musicxml::convert(musicxml::score_partwise::part_sequence const &ps) {
  musicxml::score_timewise::measure_sequence ms;

  if (ps.empty()) return ms;

  for (unsigned i = 0; i < ps.front().measure().size(); ++i) {
    const musicxml::score_partwise::part_type::measure_type &pwm =
      ps.front().measure()[i];
    musicxml::score_timewise::measure_type twm{pwm.number()};
    twm.implicit(pwm.implicit());
    twm.non_controlling(pwm.non_controlling());
    twm.width(pwm.width());

    for (const auto &pwp : ps) {
      musicxml::score_timewise::measure_type::part_type twp{pwp.id()};

      twp.music_data(pwp.measure()[i].music_data());

      twm.part().push_back(twp);
    }

    ms.push_back(twm);
  }

  return ms;
}

musicxml::score_partwise::part_sequence
musicxml::convert(musicxml::score_timewise::measure_sequence const &ms) {
  musicxml::score_partwise::part_sequence ps;

  if (ms.empty()) return ps;

  for (unsigned i = 0; i < ms.front().part().size(); ++i) {
    const musicxml::score_timewise::measure_type::part_type &twp =
      ms.front().part()[i];
    musicxml::score_partwise::part_type pwp{twp.id()};

    for (const auto &twm : ms) {
      musicxml::score_partwise::part_type::measure_type pwm{twm.number()};

      pwm.implicit(twm.implicit());
      pwm.non_controlling(twm.non_controlling());
      pwm.width(twm.width());

      pwm.music_data(twm.part()[i].music_data());

      pwp.measure().push_back(pwm);
    }

    ps.push_back(pwp);
  }

  return ps;
}

musicxml::score_timewise musicxml::convert(musicxml::score_partwise const &pw) {
  musicxml::score_timewise tw{pw.part_list()};

  tw.work(pw.work());
  tw.movement_number(pw.movement_number());
  tw.movement_title(pw.movement_title());
  tw.identification(pw.identification());
  tw.defaults(pw.defaults());
  tw.credit(pw.credit());
  tw.version(pw.version());

  tw.measure(convert(pw.part()));

  return tw;
}

musicxml::score_partwise musicxml::convert(musicxml::score_timewise const &tw) {
  musicxml::score_partwise pw{tw.part_list()};

  pw.work(tw.work());
  pw.movement_number(tw.movement_number());
  pw.movement_title(tw.movement_title());
  pw.identification(tw.identification());
  pw.defaults(tw.defaults());
  pw.credit(tw.credit());
  pw.version(tw.version());

  pw.part(convert(tw.measure()));

  return pw;
}

void musicxml::serialize(std::ostream &os, musicxml::score_partwise const &s) {
  xml::auto_initializer xerces_platform(true, false);

  DOMImplementation *dom {
    DOMImplementationRegistry::getDOMImplementation(ls_id)
  };

  xml::string score_type("score-partwise");
  xml::string dtd_public("-//Recordare//DTD MusicXML " + s.version() +
                         " Partwise//EN");
  xml::string dtd_system("http://www.musicxml.org/dtds/partwise.dtd");

  std::unique_ptr<DOMDocument> doc {
    dom->createDocument (
      nullptr, score_type.c_str(),
      dom->createDocumentType(score_type.c_str(), dtd_public.c_str(),
                              dtd_system.c_str())
    )
  };

  musicxml::score_partwise_(*doc, s);

  tree::error_handler<char> eh;
  xml::dom::bits::error_handler_proxy<char> ehp(eh);

  xml::dom::ostream_format_target oft { os };

  std::unique_ptr<DOMLSSerializer> writer { dom->createLSSerializer() };

  DOMConfiguration *conf { writer->getDomConfig() };

  conf->setParameter(XMLUni::fgDOMErrorHandler, &ehp);
  conf->setParameter(XMLUni::fgDOMWRTDiscardDefaultContent, true);
  conf->setParameter(XMLUni::fgDOMWRTFormatPrettyPrint, true);

  std::unique_ptr<DOMLSOutput> output { dom->createLSOutput() };
  output->setEncoding(xml::string("UTF-8").c_str());
  output->setByteStream(&oft);

  writer->write(doc.get(), output.get());

  eh.throw_if_failed<xsd::cxx::tree::serialization<char>>();
}

void musicxml::serialize(std::ostream &os, musicxml::score_timewise const &s) {
  xml::auto_initializer xerces_platform { true, false };

  DOMImplementation *dom {
    DOMImplementationRegistry::getDOMImplementation(ls_id)
  };

  xml::string score_type("score-timewise");
  xml::string dtd_public("-//Recordare//DTD MusicXML " + s.version() +
                         " Timewise//EN");
  xml::string dtd_system("http://www.musicxml.org/dtds/timewise.dtd");

  std::unique_ptr<DOMDocument> doc {
    dom->createDocument (
      nullptr, score_type.c_str(),
      dom->createDocumentType(score_type.c_str(), dtd_public.c_str(),
                              dtd_system.c_str())
    )
  };

  musicxml::score_timewise_(*doc, s);

  xsd::cxx::tree::error_handler<char> eh;
  xml::dom::bits::error_handler_proxy<char> ehp { eh };

  xml::dom::ostream_format_target oft { os };

  std::unique_ptr<DOMLSSerializer> writer { dom->createLSSerializer() };

  DOMConfiguration *conf { writer->getDomConfig() };

  conf->setParameter(XMLUni::fgDOMErrorHandler, &ehp);
  conf->setParameter(XMLUni::fgDOMWRTDiscardDefaultContent, true);
  conf->setParameter(XMLUni::fgDOMWRTFormatPrettyPrint, true);

  std::unique_ptr<DOMLSOutput> output { dom->createLSOutput() };
  output->setEncoding(xml::string("UTF-8").c_str());
  output->setByteStream(&oft);

  writer->write(doc.get(), output.get());

  eh.throw_if_failed<xsd::cxx::tree::serialization<char>>();
}
