// Copyright (c) 2005-2014 Code Synthesis Tools CC
//
// This program was generated by CodeSynthesis XSD, an XML Schema to
// C++ data binding compiler.
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
// In addition, as a special exception, Code Synthesis Tools CC gives
// permission to link this program with the Xerces-C++ library (or with
// modified versions of Xerces-C++ that use the same license as Xerces-C++),
// and distribute linked combinations including the two. You must obey
// the GNU General Public License version 2 in all respects for all of
// the code used other than Xerces-C++. If you modify this copy of the
// program, you may extend this exception to your version of the program,
// but you are not obligated to do so. If you do not wish to do so, delete
// this exception statement from your version.
//
// Furthermore, Code Synthesis Tools CC makes a special exception for
// the Free/Libre and Open Source Software (FLOSS) which is described
// in the accompanying FLOSSE file.
//

// Begin prologue.
//
//
// End prologue.

#include <xsd/cxx/pre.hxx>

#include "xml.hxx"

namespace namespace_ {
// lang
//

lang::lang(const char *s) : ::xml_schema::string(s) {}

lang::lang(const ::std::string &s) : ::xml_schema::string(s) {}

lang::lang(const lang &o, ::xml_schema::flags f, ::xml_schema::container *c)
: ::xml_schema::string(o, f, c) {}

// space
//

space::space(value v) : ::xml_schema::ncname(_xsd_space_literals_[v]) {}

space::space(const char *v) : ::xml_schema::ncname(v) {}

space::space(const ::std::string &v) : ::xml_schema::ncname(v) {}

space::space(const ::xml_schema::ncname &v) : ::xml_schema::ncname(v) {}

space::space(const space &v, ::xml_schema::flags f, ::xml_schema::container *c)
: ::xml_schema::ncname(v, f, c) {}

space &space::operator=(value v) {
  static_cast<::xml_schema::ncname &>(*this) =
    ::xml_schema::ncname(_xsd_space_literals_[v]);

  return *this;
}

// lang_member
//

lang_member::lang_member(value v)
: ::xml_schema::string(_xsd_lang_member_literals_[v]) {}

lang_member::lang_member(const char *v) : ::xml_schema::string(v) {}

lang_member::lang_member(const ::std::string &v) : ::xml_schema::string(v) {}

lang_member::lang_member(const ::xml_schema::string &v)
: ::xml_schema::string(v) {}

lang_member::lang_member(const lang_member &v, ::xml_schema::flags f,
                         ::xml_schema::container *c)
: ::xml_schema::string(v, f, c) {}

lang_member &lang_member::operator=(value v) {
  static_cast<::xml_schema::string &>(*this) =
    ::xml_schema::string(_xsd_lang_member_literals_[v]);

  return *this;
}
} // namespace namespace_

#include <xsd/cxx/xml/dom/parsing-source.hxx>

namespace namespace_ {
// lang
//

lang::lang(const ::xercesc::DOMElement &e, ::xml_schema::flags f,
           ::xml_schema::container *c)
: ::xml_schema::string(e, f, c) {}

lang::lang(const ::xercesc::DOMAttr &a, ::xml_schema::flags f,
           ::xml_schema::container *c)
: ::xml_schema::string(a, f, c) {}

lang::lang(const ::std::string &s, const ::xercesc::DOMElement *e,
           ::xml_schema::flags f, ::xml_schema::container *c)
: ::xml_schema::string(s, e, f, c) {}

lang *lang::_clone(::xml_schema::flags f, ::xml_schema::container *c) const {
  return new class lang(*this, f, c);
}

// space
//

space::space(const ::xercesc::DOMElement &e, ::xml_schema::flags f,
             ::xml_schema::container *c)
: ::xml_schema::ncname(e, f, c) {
  _xsd_space_convert();
}

space::space(const ::xercesc::DOMAttr &a, ::xml_schema::flags f,
             ::xml_schema::container *c)
: ::xml_schema::ncname(a, f, c) {
  _xsd_space_convert();
}

space::space(const ::std::string &s, const ::xercesc::DOMElement *e,
             ::xml_schema::flags f, ::xml_schema::container *c)
: ::xml_schema::ncname(s, e, f, c) {
  _xsd_space_convert();
}

space *space::_clone(::xml_schema::flags f, ::xml_schema::container *c) const {
  return new class space(*this, f, c);
}

space::value space::_xsd_space_convert() const {
  ::xsd::cxx::tree::enum_comparator<char> c(_xsd_space_literals_);
  const value *i(
    ::std::lower_bound(_xsd_space_indexes_, _xsd_space_indexes_ + 2, *this, c));

  if (i == _xsd_space_indexes_ + 2 || _xsd_space_literals_[*i] != *this) {
    throw ::xsd::cxx::tree::unexpected_enumerator<char>(*this);
  }

  return *i;
}

const char *const space::_xsd_space_literals_[2] = {"default", "preserve"};

const space::value space::_xsd_space_indexes_[2] = {
  ::namespace_::space::default_, ::namespace_::space::preserve};

// lang_member
//

lang_member::lang_member(const ::xercesc::DOMElement &e, ::xml_schema::flags f,
                         ::xml_schema::container *c)
: ::xml_schema::string(e, f, c) {
  _xsd_lang_member_convert();
}

lang_member::lang_member(const ::xercesc::DOMAttr &a, ::xml_schema::flags f,
                         ::xml_schema::container *c)
: ::xml_schema::string(a, f, c) {
  _xsd_lang_member_convert();
}

lang_member::lang_member(const ::std::string &s, const ::xercesc::DOMElement *e,
                         ::xml_schema::flags f, ::xml_schema::container *c)
: ::xml_schema::string(s, e, f, c) {
  _xsd_lang_member_convert();
}

lang_member *lang_member::_clone(::xml_schema::flags f,
                                 ::xml_schema::container *c) const {
  return new class lang_member(*this, f, c);
}

lang_member::value lang_member::_xsd_lang_member_convert() const {
  ::xsd::cxx::tree::enum_comparator<char> c(_xsd_lang_member_literals_);
  const value *i(::std::lower_bound(_xsd_lang_member_indexes_,
                                    _xsd_lang_member_indexes_ + 1, *this, c));

  if (i == _xsd_lang_member_indexes_ + 1 ||
      _xsd_lang_member_literals_[*i] != *this) {
    throw ::xsd::cxx::tree::unexpected_enumerator<char>(*this);
  }

  return *i;
}

const char *const lang_member::_xsd_lang_member_literals_[1] = {""};

const lang_member::value lang_member::_xsd_lang_member_indexes_[1] = {
  ::namespace_::lang_member::empty};
} // namespace namespace_

#include <ostream>

namespace namespace_ {
::std::ostream &operator<<(::std::ostream &o, const lang &i) {
  return o << static_cast<const ::xml_schema::string &>(i);
}

::std::ostream &operator<<(::std::ostream &o, space::value i) {
  return o << space::_xsd_space_literals_[i];
}

::std::ostream &operator<<(::std::ostream &o, const space &i) {
  return o << static_cast<const ::xml_schema::ncname &>(i);
}

::std::ostream &operator<<(::std::ostream &o, lang_member::value i) {
  return o << lang_member::_xsd_lang_member_literals_[i];
}

::std::ostream &operator<<(::std::ostream &o, const lang_member &i) {
  return o << static_cast<const ::xml_schema::string &>(i);
}
} // namespace namespace_

#include <istream>
#include <xsd/cxx/xml/sax/std-input-source.hxx>
#include <xsd/cxx/tree/error-handler.hxx>

namespace namespace_ {} // namespace namespace_

#include <ostream>
#include <xsd/cxx/tree/error-handler.hxx>
#include <xsd/cxx/xml/dom/serialization-source.hxx>

namespace namespace_ {
void operator<<(::xercesc::DOMElement &e, const lang &i) {
  e << static_cast<const ::xml_schema::string &>(i);
}

void operator<<(::xercesc::DOMAttr &a, const lang &i) {
  a << static_cast<const ::xml_schema::string &>(i);
}

void operator<<(::xml_schema::list_stream &l, const lang &i) {
  l << static_cast<const ::xml_schema::string &>(i);
}

void operator<<(::xercesc::DOMElement &e, const space &i) {
  e << static_cast<const ::xml_schema::ncname &>(i);
}

void operator<<(::xercesc::DOMAttr &a, const space &i) {
  a << static_cast<const ::xml_schema::ncname &>(i);
}

void operator<<(::xml_schema::list_stream &l, const space &i) {
  l << static_cast<const ::xml_schema::ncname &>(i);
}

void operator<<(::xercesc::DOMElement &e, const lang_member &i) {
  e << static_cast<const ::xml_schema::string &>(i);
}

void operator<<(::xercesc::DOMAttr &a, const lang_member &i) {
  a << static_cast<const ::xml_schema::string &>(i);
}

void operator<<(::xml_schema::list_stream &l, const lang_member &i) {
  l << static_cast<const ::xml_schema::string &>(i);
}
} // namespace namespace_

#include <xsd/cxx/post.hxx>

// Begin epilogue.
//
//
// End epilogue.
