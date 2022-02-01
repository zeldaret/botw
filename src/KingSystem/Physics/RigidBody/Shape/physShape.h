#pragma once

#include <prim/seadRuntimeTypeInfo.h>
#include <prim/seadSafeString.h>
#include "KingSystem/Physics/System/physDefines.h"
#include "KingSystem/Physics/System/physMaterialMask.h"

class hkpShape;

namespace ksys::phys {

enum class ShapeType {
    Sphere = 0,
    Capsule = 1,
    Box = 2,
    Cylinder = 3,
    Polytope = 4,
    CharacterPrism = 6,
    BoxWater = 7,
    Unknown = -1,
};

class Shape {
    SEAD_RTTI_BASE(Shape)

public:
    Shape() = default;
    virtual ShapeType getType() const = 0;
    virtual float getVolume() const = 0;
    virtual ~Shape() = default;
    virtual hkpShape* getHavokShape() = 0;
    virtual const hkpShape* getHavokShape() const = 0;
    virtual const hkpShape* updateHavokShape() = 0;
    /// @param scale New scale (relative to the current scale)
    virtual void setScale(float scale) = 0;
};

struct CommonShapeParam {
    MaterialMask getMaterialMask(bool flag = false) const {
        return {material, sub_material, floor_code, wall_code, flag};
    }

    Material material;
    const char* sub_material = sead::SafeString::cEmptyString.cstr();
    FloorCode floor_code;
    WallCode wall_code;
    bool item_code_disable_stick = false;
};

}  // namespace ksys::phys
