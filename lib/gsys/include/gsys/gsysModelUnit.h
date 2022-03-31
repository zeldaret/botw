#pragma once

#include <hostio/seadHostIONode.h>
#include <nn/g3d/World.h>
#include <prim/seadRuntimeTypeInfo.h>

namespace gsys {

// TODO
class ModelUnit {
    SEAD_RTTI_BASE(ModelUnit)
public:
    ModelUnit();
    virtual ~ModelUnit();
};

}  // namespace gsys
