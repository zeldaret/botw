#pragma once

#include <agl/utl/aglParameter.h>
#include <agl/utl/aglParameterObj.h>
#include <container/seadBuffer.h>
#include <prim/seadSafeString.h>
#include "KingSystem/Physics/physDefines.h"

namespace ksys::phys {

enum class ShapeType;

struct BoxShapeParam;
struct CapsuleShapeParam;
struct CharacterPrismShapeParam;
struct CommonShapeParam;
struct CylinderShapeParam;
struct PolytopeShapeParam;
struct SphereShapeParam;

struct ShapeParamObj : agl::utl::ParameterObj {
    ShapeParamObj();
    ~ShapeParamObj() override;
    ShapeParamObj(const ShapeParamObj&) = delete;
    auto operator=(const ShapeParamObj&) = delete;

    bool parse(const agl::utl::ResParameterObj& res_obj, sead::Heap* heap);

    ShapeType getShapeType() const;
    void getCommon(CommonShapeParam* param) const;
    void getSphere(SphereShapeParam* param) const;
    void getCapsule(CapsuleShapeParam* param) const;
    void getCylinder(CylinderShapeParam* param) const;
    void getBox(BoxShapeParam* param) const;
    void getPolytope(PolytopeShapeParam* param) const;
    void getCharacterPrism(CharacterPrismShapeParam* param) const;

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
