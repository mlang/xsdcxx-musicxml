namespace {
class serialization_visitor : public boost::static_visitor<void> {
  ::xercesc::DOMElement &e;

public:
  serialization_visitor(::xercesc::DOMElement &e) : e(e) {}

  void operator()(const ::musicxml::note &x) const {
    ::xsd::cxx::xml::dom::create_element("note", e) << x;
  }
  void operator()(const ::musicxml::backup &x) const {
    ::xsd::cxx::xml::dom::create_element("backup", e) << x;
  }
  void operator()(const ::musicxml::forward &x) const {
    ::xsd::cxx::xml::dom::create_element("forward", e) << x;
  }
  void operator()(const ::musicxml::direction &x) const {
    ::xsd::cxx::xml::dom::create_element("direction", e) << x;
  }
  void operator()(const ::musicxml::attributes &x) const {
    ::xsd::cxx::xml::dom::create_element("attributes", e) << x;
  }
  void operator()(const ::musicxml::harmony &x) const {
    ::xsd::cxx::xml::dom::create_element("harmony", e) << x;
  }
  void operator()(const ::musicxml::figured_bass &x) const {
    ::xsd::cxx::xml::dom::create_element("figured-bass", e) << x;
  }
  void operator()(const ::musicxml::print &x) const {
    ::xsd::cxx::xml::dom::create_element("print", e) << x;
  }
  void operator()(const ::musicxml::sound &x) const {
    ::xsd::cxx::xml::dom::create_element("sound", e) << x;
  }
  void operator()(const ::musicxml::barline &x) const {
    ::xsd::cxx::xml::dom::create_element("barline", e) << x;
  }
  void operator()(const ::musicxml::grouping &x) const {
    ::xsd::cxx::xml::dom::create_element("grouping", e) << x;
  }
  void operator()(const ::musicxml::link &x) const {
    ::xsd::cxx::xml::dom::create_element("link", e) << x;
  }
  void operator()(const ::musicxml::bookmark &x) const {
    ::xsd::cxx::xml::dom::create_element("bookmark", e) << x;
  }
};
}
