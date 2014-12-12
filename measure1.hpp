#include <boost/variant.hpp>

namespace musicxml {

/**
 * @brief Class corresponding to the %measure1 schema type.
 *
 * @nosubgrouping
 */
class measure1 : public ::xml_schema::type {
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

  using variant_type = boost::variant<
    attributes_type, note_type, backup_type, forward_type, direction_type,
    harmony_type, figured_bass_type, print_type, sound_type, barline_type,
    grouping_type, link_type, bookmark_type>;
  using variant_sequence = ::std::vector<variant_type>;
  using variant_iterator = variant_sequence::iterator;
  using variant_const_iterator = variant_sequence::const_iterator;

  const variant_sequence &variant() const;
  variant_sequence &variant();
  void variant(const variant_sequence &);

  /**
   * @name number
   *
   * @brief Accessor and modifier functions for the %number
   * required attribute.
   */
  //@{

  /**
   * @brief Attribute type.
   */
  typedef ::xml_schema::token number_type;

  /**
   * @brief Attribute traits type.
   */
  typedef ::xsd::cxx::tree::traits<number_type, char> number_traits;

  /**
   * @brief Return a read-only (constant) reference to the attribute.
   *
   * @return A constant reference to the attribute.
   */
  const number_type &number() const;

  /**
   * @brief Return a read-write reference to the attribute.
   *
   * @return A reference to the attribute.
   */
  number_type &number();

  /**
   * @brief Set the attribute value.
   *
   * @param x A new value to set.
   *
   * This function makes a copy of its argument and sets it as
   * the new value of the attribute.
   */
  void number(const number_type &x);

  /**
   * @brief Set the attribute value without copying.
   *
   * @param p A new value to use.
   *
   * This function will try to use the passed value directly
   * instead of making a copy.
   */
  void number(::std::unique_ptr<number_type> p);

  //@}

  /**
   * @name implicit
   *
   * @brief Accessor and modifier functions for the %implicit
   * optional attribute.
   */
  //@{

  /**
   * @brief Attribute type.
   */
  typedef ::musicxml::yes_no implicit_type;

  /**
   * @brief Attribute optional container type.
   */
  typedef ::xsd::cxx::tree::optional<implicit_type> implicit_optional;

  /**
   * @brief Attribute traits type.
   */
  typedef ::xsd::cxx::tree::traits<implicit_type, char> implicit_traits;

  /**
   * @brief Return a read-only (constant) reference to the attribute
   * container.
   *
   * @return A constant reference to the optional container.
   */
  const implicit_optional &implicit() const;

  /**
   * @brief Return a read-write reference to the attribute container.
   *
   * @return A reference to the optional container.
   */
  implicit_optional &implicit();

  /**
   * @brief Set the attribute value.
   *
   * @param x A new value to set.
   *
   * This function makes a copy of its argument and sets it as
   * the new value of the attribute.
   */
  void implicit(const implicit_type &x);

  /**
   * @brief Set the attribute value.
   *
   * @param x An optional container with the new value to set.
   *
   * If the value is present in @a x then this function makes a copy
   * of this value and sets it as the new value of the attribute.
   * Otherwise the attribute container is set the 'not present' state.
   */
  void implicit(const implicit_optional &x);

  /**
   * @brief Set the attribute value without copying.
   *
   * @param p A new value to use.
   *
   * This function will try to use the passed value directly instead
   * of making a copy.
   */
  void implicit(::std::unique_ptr<implicit_type> p);

  //@}

  /**
   * @name non-controlling
   *
   * @brief Accessor and modifier functions for the %non-controlling
   * optional attribute.
   */
  //@{

  /**
   * @brief Attribute type.
   */
  typedef ::musicxml::yes_no non_controlling_type;

  /**
   * @brief Attribute optional container type.
   */
  typedef ::xsd::cxx::tree::optional<non_controlling_type>
    non_controlling_optional;

  /**
   * @brief Attribute traits type.
   */
  typedef ::xsd::cxx::tree::traits<non_controlling_type, char>
    non_controlling_traits;

  /**
   * @brief Return a read-only (constant) reference to the attribute
   * container.
   *
   * @return A constant reference to the optional container.
   */
  const non_controlling_optional &non_controlling() const;

  /**
   * @brief Return a read-write reference to the attribute container.
   *
   * @return A reference to the optional container.
   */
  non_controlling_optional &non_controlling();

  /**
   * @brief Set the attribute value.
   *
   * @param x A new value to set.
   *
   * This function makes a copy of its argument and sets it as
   * the new value of the attribute.
   */
  void non_controlling(const non_controlling_type &x);

  /**
   * @brief Set the attribute value.
   *
   * @param x An optional container with the new value to set.
   *
   * If the value is present in @a x then this function makes a copy
   * of this value and sets it as the new value of the attribute.
   * Otherwise the attribute container is set the 'not present' state.
   */
  void non_controlling(const non_controlling_optional &x);

  /**
   * @brief Set the attribute value without copying.
   *
   * @param p A new value to use.
   *
   * This function will try to use the passed value directly instead
   * of making a copy.
   */
  void non_controlling(::std::unique_ptr<non_controlling_type> p);

  //@}

  /**
   * @name width
   *
   * @brief Accessor and modifier functions for the %width
   * optional attribute.
   */
  //@{

  /**
   * @brief Attribute type.
   */
  typedef ::musicxml::tenths width_type;

  /**
   * @brief Attribute optional container type.
   */
  typedef ::xsd::cxx::tree::optional<width_type> width_optional;

  /**
   * @brief Attribute traits type.
   */
  typedef ::xsd::cxx::tree::traits<width_type, char> width_traits;

  /**
   * @brief Return a read-only (constant) reference to the attribute
   * container.
   *
   * @return A constant reference to the optional container.
   */
  const width_optional &width() const;

  /**
   * @brief Return a read-write reference to the attribute container.
   *
   * @return A reference to the optional container.
   */
  width_optional &width();

  /**
   * @brief Set the attribute value.
   *
   * @param x A new value to set.
   *
   * This function makes a copy of its argument and sets it as
   * the new value of the attribute.
   */
  void width(const width_type &x);

  /**
   * @brief Set the attribute value.
   *
   * @param x An optional container with the new value to set.
   *
   * If the value is present in @a x then this function makes a copy
   * of this value and sets it as the new value of the attribute.
   * Otherwise the attribute container is set the 'not present' state.
   */
  void width(const width_optional &x);

  /**
   * @brief Set the attribute value without copying.
   *
   * @param p A new value to use.
   *
   * This function will try to use the passed value directly instead
   * of making a copy.
   */
  void width(::std::unique_ptr<width_type> p);

  //@}

  /**
   * @name Constructors
   */
  //@{

  /**
   * @brief Create an instance from the ultimate base and
   * initializers for required elements and attributes.
   */
  measure1(const number_type &);

  /**
   * @brief Create an instance from a DOM element.
   *
   * @param e A DOM element to extract the data from.
   * @param f Flags to create the new instance with.
   * @param c A pointer to the object that will contain the new
   * instance.
   */
  measure1(const ::xercesc::DOMElement &e, ::xml_schema::flags f = 0,
           ::xml_schema::container *c = nullptr);

  /**
   * @brief Copy constructor.
   *
   * @param x An instance to make a copy of.
   * @param f Flags to create the copy with.
   * @param c A pointer to the object that will contain the copy.
   *
   * For polymorphic object models use the @c _clone function instead.
   */
  measure1(const measure1 &x, ::xml_schema::flags f = 0,
           ::xml_schema::container *c = nullptr);

  /**
   * @brief Copy the instance polymorphically.
   *
   * @param f Flags to create the copy with.
   * @param c A pointer to the object that will contain the copy.
   * @return A pointer to the dynamically allocated copy.
   *
   * This function ensures that the dynamic type of the instance is
   * used for copying and should be used for polymorphic object
   * models instead of the copy constructor.
   */
  virtual measure1 *_clone(::xml_schema::flags f = 0,
                           ::xml_schema::container *c = nullptr) const override;

  /**
   * @brief Copy assignment operator.
   *
   * @param x An instance to make a copy of.
   * @return A reference to itself.
   *
   * For polymorphic object models use the @c _clone function instead.
   */
  measure1 &operator=(const measure1 &x);

  //@}

  /**
   * @brief Destructor.
   */
  virtual ~measure1();

  // Implementation.
  //

  //@cond

protected:
  void parse(::xsd::cxx::xml::dom::parser<char> &, ::xml_schema::flags);

protected:
  variant_sequence variant_;

  ::xsd::cxx::tree::one<number_type> number_;
  implicit_optional implicit_;
  non_controlling_optional non_controlling_;
  width_optional width_;

  //@endcond
};

void operator<<(::xercesc::DOMElement &e, const measure1 &i);
}
