#pragma once

#include <math/seadVector.h>
#include "KingSystem/Physics/RigidBody/Shape/physShape.h"

namespace ksys::phys {

struct CharacterPrismShapeParam {
    float radius;
    sead::Vector3f translate_0;
    sead::Vector3f translate_1;
    CommonShapeParam common;
};

}  // namespace ksys::phys
