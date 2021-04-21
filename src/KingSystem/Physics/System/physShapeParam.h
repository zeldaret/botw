#pragma once

#include <agl/Utils/aglParameter.h>
#include <agl/Utils/aglParameterObj.h>
#include <container/seadBuffer.h>
#include <prim/seadSafeString.h>
#include "KingSystem/Physics/System/physDefines.h"
#include "KingSystem/Utils/Types.h"

namespace ksys::phys {

struct CommonShapeParam {
    Material material;
    const char* sub_material;
    FloorCode floor_code;
    WallCode wall_code;
    bool item_code_disable_stick;
};

struct SphereParam {
    sead::Vector3f translate;
    float radius;
    CommonShapeParam common;
};
KSYS_CHECK_SIZE_NX150(SphereParam, 0x30);

struct CapsuleParam {
    sead::Vector3f translate_0;
    sead::Vector3f translate_1;
    float radius;
    CommonShapeParam common;
};
KSYS_CHECK_SIZE_NX150(CapsuleParam, 0x40);

struct CylinderParam {
    sead::Vector3f translate_0;
    float radius;
    sead::Vector3f translate_1;
    float convex_radius;
    CommonShapeParam common;
};
KSYS_CHECK_SIZE_NX150(CylinderParam, 0x40);

struct BoxParam {
    sead::Vector3f translate_1;
    sead::Vector3f translate_0;
    sead::Vector3f rotate;
    float convex_radius;
    CommonShapeParam common;
};
KSYS_CHECK_SIZE_NX150(BoxParam, 0x48);

struct PolytopeParam {
    u16 vertex_num;
    CommonShapeParam common;
};
KSYS_CHECK_SIZE_NX150(PolytopeParam, 0x28);

struct CharacterPrismParam {
    float radius;
    sead::Vector3f translate_0;
    sead::Vector3f translate_1;
    CommonShapeParam common;
};
KSYS_CHECK_SIZE_NX150(CharacterPrismParam, 0x40);

struct ShapeParam : agl::utl::ParameterObj {
    enum class Shape {
        Sphere = 0,
        Capsule = 1,
        Box = 2,
        Cylinder = 3,
        Polytope = 4,
        CharacterPrism = 6,
        Unknown = -1,
    };

    ShapeParam();
    ~ShapeParam() override;
    ShapeParam(const ShapeParam&) = delete;
    auto operator=(const ShapeParam&) = delete;

    bool parse(const agl::utl::ResParameterObj& res_obj, sead::Heap* heap);

    Shape getShape() const;
    void getCommon(CommonShapeParam* param) const;
    void getSphere(SphereParam* param) const;
    void getCapsule(CapsuleParam* param) const;
    void getCylinder(CylinderParam* param) const;
    void getBox(BoxParam* param) const;
    void getPolytope(PolytopeParam* param) const;
    void getCharacterPrism(CharacterPrismParam* param) const;

    agl::utl::Parameter<sead::FixedSafeString<32>> shape_type;
    agl::utl::Parameter<float> radius;
    agl::utl::Parameter<float> convex_radius;
    agl::utl::Parameter<sead::Vector3f> translate_0;
    agl::utl::Parameter<sead::Vector3f> translate_1;
    agl::utl::Parameter<sead::Vector3f> rotate;
    agl::utl::Parameter<int> vertex_num;
    sead::Buffer<agl::utl::Parameter<sead::Vector3f>> vertices;
    agl::utl::Parameter<sead::FixedSafeString<32>> material;
    agl::utl::Parameter<sead::FixedSafeString<32>> sub_material;
    agl::utl::Parameter<sead::FixedSafeString<32>> wall_code;
    agl::utl::Parameter<sead::FixedSafeString<32>> floor_code;
    agl::utl::Parameter<bool> item_code_disable_stick;
};

}  // namespace ksys::phys
