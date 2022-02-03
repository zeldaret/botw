#include "KingSystem/Physics/RigidBody/Shape/physShapeParamObj.h"
#include "KingSystem/Physics/RigidBody/Shape/Box/physBoxShape.h"
#include "KingSystem/Physics/RigidBody/Shape/Capsule/physCapsuleShape.h"
#include "KingSystem/Physics/RigidBody/Shape/CharacterPrism/physCharacterPrismShape.h"
#include "KingSystem/Physics/RigidBody/Shape/Cylinder/physCylinderShape.h"
#include "KingSystem/Physics/RigidBody/Shape/Polytope/physPolytopeShape.h"
#include "KingSystem/Physics/RigidBody/Shape/Sphere/physSphereShape.h"
#include "KingSystem/Physics/RigidBody/Shape/physShape.h"

namespace ksys::phys {

ShapeParamObj::ShapeParamObj()
    : shape_type(sead::SafeString::cEmptyString, "shape_type", this), radius(1.0, "radius", this),
      convex_radius(0.05, "convex_radius", this),
      translate_0(sead::Vector3f::zero, "translate_0", this),
      translate_1(sead::Vector3f::zero, "translate_1", this),
      rotate(sead::Vector3f::zero, "rotate", this), vertex_num(0, "vertex_num", this),
      material(sead::SafeString::cEmptyString, "material", this),
      sub_material(sead::SafeString::cEmptyString, "sub_material", this),
      wall_code({"None"}, "wall_code", this), floor_code({"None"}, "floor_code", this),
      item_code_disable_stick(false, "item_code_disable_stick", this) {}

ShapeParamObj::~ShapeParamObj() {
    vertices.freeBuffer();
}

bool ShapeParamObj::parse(const agl::utl::ResParameterObj& res_obj, sead::Heap* heap) {
    vertices.freeBuffer();

    applyResParameterObj(res_obj);

    const int num_vertices = vertex_num.ref();
    if (num_vertices > 0) {
        vertices.allocBufferAssert(num_vertices, heap);
        for (int i = 0; i < num_vertices; ++i) {
            sead::FormatFixedSafeString<32> name("vertex_%d", i);
            vertices[i].init(sead::Vector3f::zero, name, "頂点", this);
        }

        applyResParameterObj(res_obj);
    }

    return true;
}

ShapeType ShapeParamObj::getShapeType() const {
    if (*shape_type == "sphere")
        return ShapeType::Sphere;
    if (*shape_type == "capsule")
        return ShapeType::Capsule;
    if (*shape_type == "cylinder")
        return ShapeType::Cylinder;
    if (*shape_type == "box")
        return ShapeType::Box;
    if (*shape_type == "polytope")
        return ShapeType::Polytope;
    if (*shape_type == "character_prism")
        return ShapeType::CharacterPrism;

    return ShapeType::Unknown;
}

void ShapeParamObj::getCommon(CommonShapeParam* param) const {
    param->material = materialFromText(*material);
    param->sub_material = sub_material->cstr();
    param->floor_code = floorCodeFromText(*floor_code);
    param->wall_code = wallCodeFromText(*wall_code);
    param->item_code_disable_stick = *item_code_disable_stick;
}

void ShapeParamObj::getSphere(SphereShapeParam* param) const {
    param->radius = *radius;
    param->translate = *translate_0;
    getCommon(&param->common);
}

void ShapeParamObj::getCapsule(CapsuleShapeParam* param) const {
    param->radius = *radius;
    param->vertex_a = *translate_0;
    param->vertex_b = *translate_1;
    getCommon(&param->common);
}

void ShapeParamObj::getCylinder(CylinderShapeParam* param) const {
    param->radius = *radius;
    param->convex_radius = *convex_radius;
    param->vertex_a = *translate_0;
    param->vertex_b = *translate_1;
    getCommon(&param->common);
}

void ShapeParamObj::getBox(BoxShapeParam* param) const {
    param->translate = *translate_0;
    param->extents = *translate_1;
    param->rotate = *rotate;
    param->convex_radius = *convex_radius;
    getCommon(&param->common);
}

void ShapeParamObj::getPolytope(PolytopeShapeParam* param) const {
    param->vertex_num = *vertex_num;
    getCommon(&param->common);
}

void ShapeParamObj::getCharacterPrism(CharacterPrismShapeParam* param) const {
    param->radius = *radius;
    param->translate_0 = *translate_0;
    param->translate_1 = *translate_1;
    getCommon(&param->common);
}

}  // namespace ksys::phys
