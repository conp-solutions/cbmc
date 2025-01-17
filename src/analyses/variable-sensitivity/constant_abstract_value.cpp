/*******************************************************************\

 Module: analyses variable-sensitivity

 Author: Thomas Kiley, thomas.kiley@diffblue.com

\*******************************************************************/

#include <langapi/language_util.h>
#include <util/namespace.h>
#include <util/std_expr.h>
#include <util/type.h>

#include "abstract_environment.h"
#include "constant_abstract_value.h"

static index_range_implementation_ptrt
make_constant_index_range(const exprt &val);

class constant_index_ranget : public single_value_index_ranget
{
public:
  explicit constant_index_ranget(const exprt &val)
    : single_value_index_ranget(val)
  {
  }

  index_range_implementation_ptrt reset() const override
  {
    return make_constant_index_range(value);
  }
};

static index_range_implementation_ptrt
make_constant_index_range(const exprt &val)
{
  return util_make_unique<constant_index_ranget>(val);
}

constant_abstract_valuet::constant_abstract_valuet(const typet &t)
  : abstract_value_objectt(t), value()
{
}

constant_abstract_valuet::constant_abstract_valuet(const exprt &e)
  : abstract_value_objectt(e.type(), false, false), value(e)
{
}

constant_abstract_valuet::constant_abstract_valuet(
  const typet &t,
  bool tp,
  bool bttm)
  : abstract_value_objectt(t, tp, bttm), value()
{
}

constant_abstract_valuet::constant_abstract_valuet(
  const exprt &e,
  const abstract_environmentt &environment,
  const namespacet &ns)
  : abstract_value_objectt(e.type(), false, false), value(e)
{
}

index_range_implementation_ptrt
constant_abstract_valuet::index_range_implementation(const namespacet &ns) const
{
  exprt val = to_constant();
  if(!val.is_constant())
    return make_indeterminate_index_range();

  return make_constant_index_range(val);
}

value_range_implementation_ptrt
constant_abstract_valuet::value_range_implementation() const
{
  return make_single_value_range(shared_from_this());
}

exprt constant_abstract_valuet::to_constant() const
{
  if(!is_top() && !is_bottom())
  {
    return this->value;
  }
  else
  {
    return abstract_objectt::to_constant();
  }
}

constant_interval_exprt constant_abstract_valuet::to_interval() const
{
  return constant_interval_exprt(value, value);
}

void constant_abstract_valuet::output(
  std::ostream &out,
  const ai_baset &ai,
  const namespacet &ns) const
{
  if(!is_top() && !is_bottom())
  {
    out << from_expr(to_constant_expr(value));
  }
  else
  {
    abstract_objectt::output(out, ai, ns);
  }
}

abstract_object_pointert
constant_abstract_valuet::merge(abstract_object_pointert other) const
{
  auto cast_other =
    std::dynamic_pointer_cast<const abstract_value_objectt>(other);
  if(cast_other)
    return merge_constant_constant(cast_other);

  return abstract_objectt::merge(other);
}

abstract_object_pointert constant_abstract_valuet::merge_constant_constant(
  const abstract_value_pointert &other) const
{
  auto other_expr = other->to_constant();
  if(is_bottom() && other_expr.is_constant())
    return std::make_shared<constant_abstract_valuet>(other_expr);

  if(value == other_expr) // Can we actually merge these value
    return shared_from_this();

  return abstract_objectt::merge(other);
}

void constant_abstract_valuet::get_statistics(
  abstract_object_statisticst &statistics,
  abstract_object_visitedt &visited,
  const abstract_environmentt &env,
  const namespacet &ns) const
{
  abstract_objectt::get_statistics(statistics, visited, env, ns);
  ++statistics.number_of_constants;
  statistics.objects_memory_usage += memory_sizet::from_bytes(sizeof(*this));
}
