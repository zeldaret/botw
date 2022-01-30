#pragma once

#include <basis/seadTypes.h>
#include "KingSystem/Physics/RigidBody/Shape/physShape.h"

namespace ksys::phys {

struct PolytopeShapeParam {
    u16 vertex_num;
    CommonShapeParam common;
};

}  // namespace ksys::phys
