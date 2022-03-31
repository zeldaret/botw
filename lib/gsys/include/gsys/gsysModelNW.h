#pragma once

#include <gsys/gsysModelUnit.h>

namespace gsys {

// XXX: bad name. This doesn't reflect the fact that ModelNW is a ModelUnit, not a Model.
// TODO
class ModelNW : public ModelUnit,
                public nn::g3d::ICalculateWorldCallback,
                public sead::hostio::Node {
    SEAD_RTTI_OVERRIDE(ModelNW, ModelUnit)
};

}  // namespace gsys
