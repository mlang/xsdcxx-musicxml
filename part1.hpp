#include "music_data.hpp"

namespace musicxml {
/**
 * @brief Class corresponding to the %part1 schema type.
 *
 * @nosubgrouping
 */
class part1 : public ::xml_schema::type {
public:
  typedef ::musicxml::note note_type;
  typedef ::xsd::cxx::tree::traits<note_type, char> note_traits;

  typedef ::musicxml::backup backup_type;
  typedef ::xsd::cxx::tree::traits<backup_type, char> backup_traits;

  typedef ::musicxml::forward forward_type;
  typedef ::xsd::cxx::tree::traits<forward_type, char> forward_traits;

  typedef ::musicxml::direction direction_type;
  typedef ::xsd::cxx::tree::traits<direction_type, char> direction_traits;

  typedef ::musicxml::attributes attributes_type;
  typedef ::xsd::cxx::tree::traits<attributes_type, char> attributes_traits;

  typedef ::musicxml::harmony harmony_type;
  typedef ::xsd::cxx::tree::traits<harmony_type, char> harmony_traits;

  typedef ::musicxml::figured_bass figured_bass_type;
  typedef ::xsd::cxx::tree::traits<figured_bass_type, char> figured_bass_traits;

  typedef ::musicxml::print print_type;
  typedef ::xsd::cxx::tree::traits<print_type, char> print_traits;

  typedef ::musicxml::sound sound_type;
  typedef ::xsd::cxx::tree::traits<sound_type, char> sound_traits;

  typedef ::musicxml::barline barline_type;
  typedef ::xsd::cxx::tree::traits<barline_type, char> barline_traits;

  typedef ::musicxml::grouping grouping_type;
  typedef ::xsd::cxx::tree::traits<grouping_type, char> grouping_traits;

  typedef ::musicxml::link link_type;
  typedef ::xsd::cxx::tree::traits<link_type, char> link_traits;

  typedef ::musicxml::bookmark bookmark_type;
  typedef ::xsd::cxx::tree::traits<bookmark_type, char> bookmark_traits;

  typedef ::xml_schema::idref id_type;
  typedef ::xsd::cxx::tree::traits<id_type, char> id_traits;

  using music_data_type = ::musicxml::music_data;
  using music_data_sequence = ::std::vector<music_data_type>;
  using music_data_iterator = music_data_sequence::iterator;
  using music_data_const_iterator = music_data_sequence::const_iterator;

  const music_data_sequence &music_data() const;
  music_data_sequence &music_data();
  void music_data(const music_data_sequence &);

  const id_type &id() const;
  id_type &id();
  void id(const id_type &x);
  void id(::std::unique_ptr<id_type> p);

  part1(const id_type &);
  part1(const ::xercesc::DOMElement &e, ::xml_schema::flags f = 0,
        ::xml_schema::container *c = nullptr);
  part1(const part1 &x, ::xml_schema::flags f = 0,
        ::xml_schema::container *c = nullptr);
  virtual part1 *_clone(::xml_schema::flags f = 0,
                        ::xml_schema::container *c = nullptr) const override;
  part1 &operator=(const part1 &x);

  virtual ~part1();

protected:
  void parse(::xsd::cxx::xml::dom::parser<char> &, ::xml_schema::flags);

protected:
  music_data_sequence music_data_;

  ::xsd::cxx::tree::one<id_type> id_;
};

void operator<<(::xercesc::DOMElement &e, const part1 &i);
}
