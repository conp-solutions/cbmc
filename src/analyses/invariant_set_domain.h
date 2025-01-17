/*******************************************************************\

Module: Value Set

Author: Daniel Kroening, kroening@kroening.com

\*******************************************************************/

/// \file
/// Value Set

#ifndef CPROVER_ANALYSES_INVARIANT_SET_DOMAIN_H
#define CPROVER_ANALYSES_INVARIANT_SET_DOMAIN_H

#include <util/threeval.h>

#include "ai.h"
#include "invariant_set.h"

class invariant_set_domaint:public ai_domain_baset
{
public:
  invariant_set_domaint(
    value_setst &value_sets,
    inv_object_storet &object_store,
    const namespacet &ns)
    : has_values(false), invariant_set(value_sets, object_store, ns)
  {
  }

  tvt has_values;
  invariant_sett invariant_set;

  // overloading

  bool merge(const invariant_set_domaint &other, trace_ptrt, trace_ptrt)
  {
    bool changed=invariant_set.make_union(other.invariant_set) ||
                 has_values.is_false();
    has_values=tvt::unknown();

    return changed;
  }

  void output(
    std::ostream &out,
    const ai_baset &,
    const namespacet &) const final override
  {
    if(has_values.is_known())
      out << has_values.to_string() << '\n';
    else
      invariant_set.output(out);
  }

  virtual void transform(
    const irep_idt &function_from,
    trace_ptrt trace_from,
    const irep_idt &function_to,
    trace_ptrt trace_to,
    ai_baset &ai,
    const namespacet &ns) final override;

  void make_top() final override
  {
    invariant_set.make_true();
    has_values=tvt(true);
  }

  void make_bottom() final override
  {
    invariant_set.make_false();
    has_values=tvt(false);
  }

  void make_entry() final override
  {
    invariant_set.make_true();
    has_values=tvt(true);
  }

  bool is_top() const override final
  {
    return has_values.is_true();
  }

  bool is_bottom() const override final
  {
    return has_values.is_false();
  }
};

#endif // CPROVER_ANALYSES_INVARIANT_SET_DOMAIN_H
