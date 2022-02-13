#pragma once

#include <prim/seadRuntimeTypeInfo.h>
#include <prim/seadSafeString.h>
#include "KingSystem/Physics/physDefines.h"
#include "KingSystem/Physics/physMaterialMask.h"

class hkpShape;

namespace ksys::phys {

enum class ShapeType {
    Sphere = 0,
    Capsule = 1,
    Box = 2,
    Cylinder = 3,
    Polytope = 4,
    List = 5,
    CharacterPrism = 6,
    BoxWater = 7,
    CylinderWater = 8,
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

    /// Update the underlying Havok shape if necessary. This may recreate the Havok shape.
    /// @return a pointer to the new underlying Havok shape if it was recreated, null otherwise
    virtual const hkpShape* updateHavokShape() = 0;

    /// @param scale New scale (relative to the current scale)
    virtual void setScale(float scale) = 0;

    const hkpShape* getHavokShapeConst() const { return getHavokShape(); }
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
