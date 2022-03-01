#include "KingSystem/Physics/RigidBody/Shape/Polytope/physPolytopeRigidBody.h"
#include "KingSystem/Physics/RigidBody/Shape/Polytope/physPolytopeShape.h"
#include "KingSystem/Utils/SafeDelete.h"

namespace ksys::phys {

PolytopeRigidBody* PolytopeRigidBody::make(RigidBodyInstanceParam* param, sead::Heap* heap) {
    return createPolytope(param, heap);
}

PolytopeRigidBody::PolytopeRigidBody(hkpRigidBody* hk_body, PolytopeShape* shape,
                                     ContactLayerType layer_type, const sead::SafeString& name,
                                     bool set_flag_10, sead::Heap* heap)
    : RigidBodyFromShape(hk_body, layer_type, name, set_flag_10, heap), mShape(shape) {}

PolytopeRigidBody::~PolytopeRigidBody() {
    if (hasFlag(RigidBody::Flag::_10) && mShape) {
        util::safeDelete(mShape);
    }
}

bool PolytopeRigidBody::setVertex(int vertex_idx, const sead::Vector3f& vertex) {
    return mShape->setVertex(vertex_idx, vertex);
}

u16 PolytopeRigidBody::getNumVertices() const {
    return mShape->getNumVertices();
}

const sead::Vector3f& PolytopeRigidBody::getVertex(int vertex_idx) const {
    return mShape->getVertex(vertex_idx);
}

void PolytopeRigidBody::setMaterialMask(const MaterialMask& mask) {
    mShape->setMaterialMask(mask);
}

const MaterialMask& PolytopeRigidBody::getMaterialMask() const {
    return mShape->getMaterialMask();
}

float PolytopeRigidBody::getVolume() {
    return mShape->getVolume();
}

void PolytopeRigidBody::setVolume(float volume) {
    mShape->setVolume(volume);
}

Shape* PolytopeRigidBody::getShape_() {
    return mShape;
}

const Shape* PolytopeRigidBody::getShape_() const {
    return mShape;
}

u32 PolytopeRigidBody::getCollisionMasks(RigidBody::CollisionMasks* masks, const u32* unk,
                                         const sead::Vector3f& contact_point) {
    masks->ignored_layers = ~mContactMask.getDirect();
    masks->collision_filter_info = getCollisionFilterInfo();
    masks->material_mask = getMaterialMask().getRawData();
    return 0;
}

}  // namespace ksys::phys
