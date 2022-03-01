#include "KingSystem/Physics/RigidBody/Shape/List/physListShapeRigidBody.h"
#include "KingSystem/Physics/RigidBody/Shape/List/physListShape.h"
#include "KingSystem/Utils/SafeDelete.h"

namespace ksys::phys {

ListShapeRigidBody* ListShapeRigidBody::make(RigidBodyInstanceParam* param, sead::Heap* heap) {
    return createList(param, heap);
}

ListShapeRigidBody::ListShapeRigidBody(hkpRigidBody* hk_body, ListShape* shape,
                                       ContactLayerType layer_type, const sead::SafeString& name,
                                       bool set_flag_10, sead::Heap* heap)
    : RigidBodyFromShape(hk_body, layer_type, name, set_flag_10, heap), mShape(shape) {}

ListShapeRigidBody::~ListShapeRigidBody() {
    if (hasFlag(RigidBody::Flag::_10) && mShape) {
        util::safeDelete(mShape);
    }
}

Shape* ListShapeRigidBody::replaceWithNewSphere(int index, const SphereShapeParam& param,
                                                sead::Heap* heap) {
    return mShape->replaceWithNewSphere(index, param, heap);
}

Shape* ListShapeRigidBody::replaceWithNewCapsule(int index, const CapsuleShapeParam& param,
                                                 sead::Heap* heap) {
    return mShape->replaceWithNewCapsule(index, param, heap);
}

Shape* ListShapeRigidBody::replaceWithNewCylinder(int index, const CylinderShapeParam& param,
                                                  sead::Heap* heap) {
    return mShape->replaceWithNewCylinder(index, param, heap);
}

Shape* ListShapeRigidBody::replaceWithNewBox(int index, const BoxShapeParam& param,
                                             sead::Heap* heap) {
    return mShape->replaceWithNewBox(index, param, heap);
}

Shape* ListShapeRigidBody::replaceWithNewPolytope(int index, const PolytopeShapeParam& param,
                                                  sead::Heap* heap) {
    return mShape->replaceWithNewPolytope(index, param, heap);
}

Shape* ListShapeRigidBody::replaceWithNewCharacterPrism(int index,
                                                        const CharacterPrismShapeParam& param,
                                                        sead::Heap* heap) {
    return mShape->replaceWithNewCharacterPrism(index, param, heap);
}

void ListShapeRigidBody::setMaterialMask(const MaterialMask& mask, int index) {
    mShape->setMaterialMask(mask, index);
}

const MaterialMask& ListShapeRigidBody::getMaterialMask(int index) const {
    return mShape->getMaterialMask(index);
}

float ListShapeRigidBody::getVolume() {
    return mShape->getVolume();
}

Shape* ListShapeRigidBody::getShape_() {
    return mShape;
}

const Shape* ListShapeRigidBody::getShape_() const {
    return mShape;
}

u32 ListShapeRigidBody::getCollisionMasks(RigidBody::CollisionMasks* masks, const u32* unk,
                                          const sead::Vector3f& contact_point) {
    masks->ignored_layers = ~mContactMask;
    masks->collision_filter_info = getCollisionFilterInfo();
    masks->material_mask = getMaterialMask(unk != nullptr ? int(*unk) : 0).getRawData();
    return 0;
}

}  // namespace ksys::phys
