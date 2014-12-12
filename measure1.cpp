#include "musicxml.hpp"
#include <xsd/cxx/xml/dom/serialization-source.hxx>
#include "music_data_serialization_visitor.hpp"
#include <xsd/cxx/xml/dom/parsing-source.hxx>

namespace musicxml {

const measure1::number_type &measure1::number() const {
  return this->number_.get();
}

measure1::number_type &measure1::number() { return this->number_.get(); }

void measure1::number(const number_type &x) { this->number_.set(x); }

void measure1::number(::std::unique_ptr<number_type> x) {
  this->number_.set(std::move(x));
}

const measure1::implicit_optional &measure1::implicit() const {
  return this->implicit_;
}

measure1::implicit_optional &measure1::implicit() { return this->implicit_; }

void measure1::implicit(const implicit_type &x) { this->implicit_.set(x); }

void measure1::implicit(const implicit_optional &x) { this->implicit_ = x; }

void measure1::implicit(::std::unique_ptr<implicit_type> x) {
  this->implicit_.set(std::move(x));
}

const measure1::non_controlling_optional &measure1::non_controlling() const {
  return this->non_controlling_;
}

measure1::non_controlling_optional &measure1::non_controlling() {
  return this->non_controlling_;
}

void measure1::non_controlling(const non_controlling_type &x) {
  this->non_controlling_.set(x);
}

void measure1::non_controlling(const non_controlling_optional &x) {
  this->non_controlling_ = x;
}

void measure1::non_controlling(::std::unique_ptr<non_controlling_type> x) {
  this->non_controlling_.set(std::move(x));
}

const measure1::width_optional &measure1::width() const { return this->width_; }

measure1::width_optional &measure1::width() { return this->width_; }

void measure1::width(const width_type &x) { this->width_.set(x); }

void measure1::width(const width_optional &x) { this->width_ = x; }

void measure1::width(::std::unique_ptr<width_type> x) {
  this->width_.set(std::move(x));
}

const measure1::music_data_sequence &measure1::music_data() const {
  return this->music_data_;
}

measure1::music_data_sequence &measure1::music_data() {
  return this->music_data_;
}

void measure1::music_data(const music_data_sequence &s) {
  this->music_data_ = s;
}

measure1::measure1(const number_type &number)
: ::xml_schema::type()
, number_(number, this)
, implicit_(this)
, non_controlling_(this)
, width_(this) {}

measure1::measure1(const measure1 &x, ::xml_schema::flags f,
                   ::xml_schema::container *c)
: ::xml_schema::type(x, f, c)
, music_data_(x.music_data_)
, number_(x.number_, f, this)
, implicit_(x.implicit_, f, this)
, non_controlling_(x.non_controlling_, f, this)
, width_(x.width_, f, this) {}

measure1::measure1(const ::xercesc::DOMElement &e, ::xml_schema::flags f,
                   ::xml_schema::container *c)
: ::xml_schema::type(e, f | ::xml_schema::flags::base, c)
, number_(this)
, implicit_(this)
, non_controlling_(this)
, width_(this) {
  if ((f & ::xml_schema::flags::base) == 0) {
    ::xsd::cxx::xml::dom::parser<char> p(e, true, false, true);
    this->parse(p, f);
  }
}

void measure1::parse(::xsd::cxx::xml::dom::parser<char> &p,
                     ::xml_schema::flags f) {
  for (; p.more_content(); p.next_content(false)) {
    const ::xercesc::DOMElement &i(p.cur_element());
    const ::xsd::cxx::xml::qualified_name<char> n(
      ::xsd::cxx::xml::dom::name<char>(i));

    if (n.name() == "note" && n.namespace_().empty()) {
      this->music_data_.push_back(note_type(i, f, this));
    } else if (n.name() == "backup" && n.namespace_().empty()) {
      this->music_data_.push_back(backup_type(i, f, this));
    } else if (n.name() == "forward" && n.namespace_().empty()) {
      this->music_data_.push_back(forward_type(i, f, this));
    } else if (n.name() == "direction" && n.namespace_().empty()) {
      this->music_data_.push_back(direction_type(i, f, this));
    } else if (n.name() == "attributes" && n.namespace_().empty()) {
      this->music_data_.push_back(attributes_type(i, f, this));
    } else if (n.name() == "harmony" && n.namespace_().empty()) {
      this->music_data_.push_back(harmony_type(i, f, this));
    } else if (n.name() == "figured-bass" && n.namespace_().empty()) {
      this->music_data_.push_back(figured_bass_type(i, f, this));
    } else if (n.name() == "print" && n.namespace_().empty()) {
      this->music_data_.push_back(print_type(i, f, this));
    } else if (n.name() == "sound" && n.namespace_().empty()) {
      this->music_data_.push_back(sound_type(i, f, this));
    } else if (n.name() == "barline" && n.namespace_().empty()) {
      this->music_data_.push_back(barline_type(i, f, this));
    } else if (n.name() == "grouping" && n.namespace_().empty()) {
      this->music_data_.push_back(grouping_type(i, f, this));
    } else if (n.name() == "link" && n.namespace_().empty()) {
      this->music_data_.push_back(link_type(i, f, this));
    } else if (n.name() == "bookmark" && n.namespace_().empty()) {
      this->music_data_.push_back(bookmark_type(i, f, this));
    } else { break; }
  }

  while (p.more_attributes()) {
    const ::xercesc::DOMAttr &i(p.next_attribute());
    const ::xsd::cxx::xml::qualified_name<char> n(
      ::xsd::cxx::xml::dom::name<char>(i));

    if (n.name() == "number" && n.namespace_().empty()) {
      this->number_.set(number_traits::create(i, f, this));
      continue;
    }

    if (n.name() == "implicit" && n.namespace_().empty()) {
      this->implicit_.set(implicit_traits::create(i, f, this));
      continue;
    }

    if (n.name() == "non-controlling" && n.namespace_().empty()) {
      this->non_controlling_.set(non_controlling_traits::create(i, f, this));
      continue;
    }

    if (n.name() == "width" && n.namespace_().empty()) {
      this->width_.set(width_traits::create(i, f, this));
      continue;
    }
  }

  if (!number_.present()) {
    throw ::xsd::cxx::tree::expected_attribute<char>("number", "");
  }
}

measure1 *measure1::_clone(::xml_schema::flags f,
                           ::xml_schema::container *c) const {
  return new class measure1(*this, f, c);
}

measure1 &measure1::operator=(const measure1 &x) {
  if (this != &x) {
    static_cast<::xml_schema::type &>(*this) = x;
    this->music_data_ = x.music_data_;
    this->number_ = x.number_;
    this->implicit_ = x.implicit_;
    this->non_controlling_ = x.non_controlling_;
    this->width_ = x.width_;
  }

  return *this;
}

measure1::~measure1() {}
} // namespace musicxml

namespace musicxml {
void operator<<(::xercesc::DOMElement &e, const measure1 &i) {
  e << static_cast<const ::xml_schema::type &>(i);

  serialization_visitor v(e);
  std::for_each(i.music_data().begin(), i.music_data().end(),
                boost::apply_visitor(v));

  // number
  //
  {
    ::xercesc::DOMAttr &a(::xsd::cxx::xml::dom::create_attribute("number", e));

    a << i.number();
  }

  // implicit
  //
  if (i.implicit()) {
    ::xercesc::DOMAttr &a(
      ::xsd::cxx::xml::dom::create_attribute("implicit", e));

    a << *i.implicit();
  }

  // non-controlling
  //
  if (i.non_controlling()) {
    ::xercesc::DOMAttr &a(
      ::xsd::cxx::xml::dom::create_attribute("non-controlling", e));

    a << *i.non_controlling();
  }

  // width
  //
  if (i.width()) {
    ::xercesc::DOMAttr &a(::xsd::cxx::xml::dom::create_attribute("width", e));

    a << *i.width();
  }
}
} // namespace musicxml
