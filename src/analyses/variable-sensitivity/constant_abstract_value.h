/*******************************************************************\

 Module: analyses variable-sensitivity

 Author: Thomas Kiley, thomas.kiley@diffblue.com

\*******************************************************************/

/// \file
/// An abstraction of a single value that just stores a constant.

#ifndef CPROVER_ANALYSES_VARIABLE_SENSITIVITY_CONSTANT_ABSTRACT_VALUE_H
#define CPROVER_ANALYSES_VARIABLE_SENSITIVITY_CONSTANT_ABSTRACT_VALUE_H

#include <iosfwd>

#include <analyses/variable-sensitivity/abstract_value_object.h>
#include <util/std_expr.h>

class constant_abstract_valuet : public abstract_value_objectt
{
public:
  explicit constant_abstract_valuet(const typet &t);
  explicit constant_abstract_valuet(const exprt &t);
  constant_abstract_valuet(const typet &t, bool tp, bool bttm);
  constant_abstract_valuet(
    const exprt &e,
    const abstract_environmentt &environment,
    const namespacet &ns);

  ~constant_abstract_valuet() override = default;

  index_range_implementation_ptrt
  index_range_implementation(const namespacet &ns) const override;

  value_range_implementation_ptrt value_range_implementation() const override;

  exprt to_constant() const override;
  constant_interval_exprt to_interval() const override;

  void output(
    std::ostream &out,
    const class ai_baset &ai,
    const class namespacet &ns) const override;

  void get_statistics(
    abstract_object_statisticst &statistics,
    abstract_object_visitedt &visited,
    const abstract_environmentt &env,
    const namespacet &ns) const override;

  size_t internal_hash() const override
  {
    return std::hash<std::string>{}(value.pretty());
  }

  bool internal_equality(const abstract_object_pointert &other) const override
  {
    auto cast_other =
      std::dynamic_pointer_cast<const constant_abstract_valuet>(other);
    return cast_other && value == cast_other->value;
  }

protected:
  CLONE

  /// Attempts to do a constant/constant merge if both are constants,
  /// otherwise falls back to the parent merge
  ///
  /// \param other: the abstract object to merge with
  ///
  /// \return Returns the result of the merge
  abstract_object_pointert merge(abstract_object_pointert other) const override;

private:
  /// Merges another abstract value into this one
  ///
  /// \param other: the abstract object to merge with
  ///
  /// \return Returns a new abstract object that is the result of the merge
  ///         unless the merge is the same as this abstract object, in which
  ///         case it returns this.
  abstract_object_pointert
  merge_constant_constant(const abstract_value_pointert &other) const;

  exprt value;
};

#endif // CPROVER_ANALYSES_VARIABLE_SENSITIVITY_CONSTANT_ABSTRACT_VALUE_H
