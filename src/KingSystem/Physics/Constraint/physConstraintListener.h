#pragma once

#include <Havok/Physics2012/Dynamics/Constraint/hkpConstraintListener.h>

namespace ksys::phys {

// TODO
class ConstraintListener : public hkpConstraintListener {
    virtual ~ConstraintListener() = default;
};

};  // namespace ksys::phys
