#pragma once

#include <prim/seadRuntimeTypeInfo.h>

namespace ksys::phys {

class Constraint {
    SEAD_RTTI_BASE(Constraint)

public:
    // FIXME: types
    Constraint();
    virtual ~Constraint();

    /// No-op if instance is null.
    static void destroy(Constraint* instance);
};

}  // namespace ksys::phys
