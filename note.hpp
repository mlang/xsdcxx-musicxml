namespace musicxml {
class note : public note_base {
public:
  /**
   * @brief Create an instance from the ultimate base and
   * initializers for required elements and attributes.
   */
  note(const pitch_type &, const duration_type &);
  note(const unpitched_type &, const duration_type &);
  note(const rest_type &, const duration_type &);

  /**
   * @brief Create an instance from a DOM element.
   *
   * @param e A DOM element to extract the data from.
   * @param f Flags to create the new instance with.
   * @param c A pointer to the object that will contain the new
   * instance.
   */
  note(const ::xercesc::DOMElement &e, ::xml_schema::flags f = 0,
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
  note(const note &x, ::xml_schema::flags f = 0,
       ::xml_schema::container *c = nullptr);

  using note_base::grace;

  /**
   * @brief Set the element value.
   *
   * @param x A new value to set.
   *
   * This function makes a copy of its argument and sets it as
   * the new value of the element.
   */
  void grace (const grace_type& x);

  /**
   * @brief Set the element value.
   *
   * @param x An optional container with the new value to set.
   *
   * If the value is present in @a x then this function makes a copy
   * of this value and sets it as the new value of the element.
   * Otherwise the element container is set the 'not present' state.
   */
  void grace (const grace_optional& x);

  /**
   * @brief Set the element value without copying.
   *
   * @param p A new value to use.
   *
   * This function will try to use the passed value directly instead
   * of making a copy.
   */
  void grace (::std::unique_ptr< grace_type > p);

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
  virtual note *_clone(::xml_schema::flags f = 0,
                       ::xml_schema::container *c = nullptr) const override;
};

void operator<<(::xercesc::DOMElement &e, const note &i);
}
