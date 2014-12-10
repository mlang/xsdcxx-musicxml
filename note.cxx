#include "musicxml.hxx"
#include <xsd/cxx/xml/dom/serialization-source.hxx>

namespace musicxml {

note::note() : note_base{} {}

note::note(const note &x, ::xml_schema::flags f, ::xml_schema::container *c)
: note_base{x, f, c} {}

note::note(const ::xercesc::DOMElement &e, ::xml_schema::flags f,
           ::xml_schema::container *c)
: note_base{e, f, c} {}

note *note::_clone(::xml_schema::flags f, ::xml_schema::container *c) const {
  return new class note(*this, f, c);
}

void operator<<(::xercesc::DOMElement &e, const note &i) {
  e << static_cast<const ::xml_schema::type &>(i);

  if (i.grace()) {
    ::xsd::cxx::xml::dom::create_element("grace", e) << *i.grace();
  } else if (i.cue()) {
    ::xsd::cxx::xml::dom::create_element("cue", e) << *i.cue();
  }

  if (i.chord()) {
    ::xsd::cxx::xml::dom::create_element("chord", e) << *i.chord();
  }

  if (i.pitch()) {
    ::xsd::cxx::xml::dom::create_element("pitch", e) << *i.pitch();
  } else if (i.unpitched()) {
    ::xsd::cxx::xml::dom::create_element("unpitched", e) << *i.unpitched();
  } else if (i.rest()) {
    ::xsd::cxx::xml::dom::create_element("rest", e) << *i.rest();
  }

  if (i.duration()) {
    ::xsd::cxx::xml::dom::create_element("duration", e) << *i.duration();
  }

  for (const auto &elem : i.tie()) {
    ::xsd::cxx::xml::dom::create_element("tie", e) << elem;
  }

  if (i.instrument()) {
    ::xsd::cxx::xml::dom::create_element("instrument", e) << *i.instrument();
  }

  if (i.footnote()) {
    ::xsd::cxx::xml::dom::create_element("footnote", e) << *i.footnote();
  }

  if (i.level()) {
    ::xsd::cxx::xml::dom::create_element("level", e) << *i.level();
  }

  if (i.voice()) {
    ::xsd::cxx::xml::dom::create_element("voice", e) << *i.voice();
  }

  if (i.type()) {
    ::xsd::cxx::xml::dom::create_element("type", e) << *i.type();
  }

  for (const auto &elem : i.dot()) {
    ::xsd::cxx::xml::dom::create_element("dot", e) << elem;
  }

  if (i.accidental()) {
    ::xsd::cxx::xml::dom::create_element("accidental", e) << *i.accidental();
  }

  if (i.time_modification()) {
    ::xsd::cxx::xml::dom::create_element("time-modification", e)
      << *i.time_modification();
  }

  if (i.stem()) {
    ::xsd::cxx::xml::dom::create_element("stem", e) << *i.stem();
  }

  if (i.notehead()) {
    ::xsd::cxx::xml::dom::create_element("notehead", e) << *i.notehead();
  }

  if (i.notehead_text()) {
    ::xsd::cxx::xml::dom::create_element("notehead-text", e)
      << *i.notehead_text();
  }

  if (i.staff()) {
    ::xsd::cxx::xml::dom::create_element("staff", e) << *i.staff();
  }

  for (const auto &elem : i.beam()) {
    ::xsd::cxx::xml::dom::create_element("beam", e) << elem;
  }

  for (const auto &elem : i.notations()) {
    ::xsd::cxx::xml::dom::create_element("notations", e) << elem;
  }

  for (const auto &elem : i.lyric()) {
    ::xsd::cxx::xml::dom::create_element("lyric", e) << elem;
  }

  if (i.play()) {
    ::xsd::cxx::xml::dom::create_element("play", e) << *i.play();
  }

  if (i.default_x()) {
    ::xsd::cxx::xml::dom::create_attribute("default-x", e) << *i.default_x();
  }

  if (i.default_y()) {
    ::xsd::cxx::xml::dom::create_attribute("default-y", e) << *i.default_y();
  }

  if (i.relative_x()) {
    ::xsd::cxx::xml::dom::create_attribute("relative-x", e) << *i.relative_x();
  }

  if (i.relative_y()) {
    ::xsd::cxx::xml::dom::create_attribute("relative-y", e) << *i.relative_y();
  }

  if (i.font_family()) {
    ::xsd::cxx::xml::dom::create_attribute("font-family", e)
      << *i.font_family();
  }

  if (i.font_style()) {
    ::xsd::cxx::xml::dom::create_attribute("font-style", e) << *i.font_style();
  }

  if (i.font_size()) {
    ::xsd::cxx::xml::dom::create_attribute("font-size", e) << *i.font_size();
  }

  if (i.font_weight()) {
    ::xsd::cxx::xml::dom::create_attribute("font-weight", e)
      << *i.font_weight();
  }

  if (i.color()) {
    ::xsd::cxx::xml::dom::create_attribute("color", e) << *i.color();
  }

  if (i.print_object()) {
    ::xsd::cxx::xml::dom::create_attribute("print-object", e)
      << *i.print_object();
  }

  if (i.print_dot()) {
    ::xsd::cxx::xml::dom::create_attribute("print-dot", e) << *i.print_dot();
  }

  if (i.print_spacing()) {
    ::xsd::cxx::xml::dom::create_attribute("print-spacing", e)
      << *i.print_spacing();
  }

  if (i.print_lyric()) {
    ::xsd::cxx::xml::dom::create_attribute("print-lyric", e)
      << *i.print_lyric();
  }

  if (i.dynamics()) {
    ::xsd::cxx::xml::dom::create_attribute("dynamics", e) << *i.dynamics();
  }

  if (i.end_dynamics()) {
    ::xsd::cxx::xml::dom::create_attribute("end-dynamics", e)
      << *i.end_dynamics();
  }

  if (i.attack()) {
    ::xsd::cxx::xml::dom::create_attribute("attack", e) << *i.attack();
  }

  if (i.release()) {
    ::xsd::cxx::xml::dom::create_attribute("release", e) << *i.release();
  }

  if (i.time_only()) {
    ::xsd::cxx::xml::dom::create_attribute("time-only", e) << *i.time_only();
  }

  if (i.pizzicato()) {
    ::xsd::cxx::xml::dom::create_attribute("pizzicato", e) << *i.pizzicato();
  }
}
}
