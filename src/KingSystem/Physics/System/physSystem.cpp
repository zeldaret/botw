#include "KingSystem/Physics/System/physSystem.h"
#include "KingSystem/Physics/Cloth/physClothResource.h"
#include "KingSystem/Physics/Ragdoll/physRagdollControllerKeyList.h"
#include "KingSystem/Physics/Ragdoll/physRagdollResource.h"
#include "KingSystem/Physics/RigidBody/TeraMesh/physTeraMeshRigidBodyResource.h"
#include "KingSystem/Physics/RigidBody/physRigidBodyResource.h"
#include "KingSystem/Physics/StaticCompound/physStaticCompound.h"
#include "KingSystem/Physics/SupportBone/physSupportBoneResource.h"
#include "KingSystem/Physics/System/physContactListener.h"
#include "KingSystem/Physics/System/physContactMgr.h"
#include "KingSystem/Physics/System/physContactPointInfo.h"
#include "KingSystem/Physics/System/physEntityGroupFilter.h"
#include "KingSystem/Physics/System/physGroupFilter.h"
#include "KingSystem/Physics/System/physLayerContactPointInfo.h"
#include "KingSystem/Physics/System/physMaterialTable.h"
#include "KingSystem/Physics/System/physRayCastRequestMgr.h"
#include "KingSystem/Physics/System/physSensorGroupFilter.h"
#include "KingSystem/Physics/System/physSystemData.h"
#include "KingSystem/Resource/resEntryFactory.h"
#include "KingSystem/Resource/resSystem.h"

namespace ksys::phys {

SEAD_SINGLETON_DISPOSER_IMPL(System)

bool System::isPaused() const {
    return mPaused;
}

void System::initSystemData(sead::Heap* heap) {
    res::registerEntryFactory(new (heap) res::EntryFactory<RigidBodyResource>(1.0, 0x400), "hkrb");
    res::registerEntryFactory(new (heap) res::EntryFactory<RagdollResource>(1.0, 0x400), "hkrg");
    res::registerEntryFactory(new (heap) res::EntryFactory<SupportBoneResource>(1.0, 0x100000),
                              "bphyssb");
    res::registerEntryFactory(new (heap) res::EntryFactory<ClothResource>(2.0, 0x2800), "hkcl");
    res::registerEntryFactory(new (heap) res::EntryFactory<StaticCompound>(1.3, 0x40000), "hksc");
    res::registerEntryFactory(new (heap) res::EntryFactory<TeraMeshRigidBodyResource>(1.0, 0x800),
                              "hktmrb");
    res::registerEntryFactory(new (heap) res::EntryFactory<RagdollControllerKeyList>(1.0, 0x4000),
                              "brgcon");

    mEntityGroupFilter = EntityGroupFilter::make(FirstEntity, LastEntity, heap);
    mSensorGroupFilter = SensorGroupFilter::make(LastSensor, heap);
    mGroupFilters.pushBack(mEntityGroupFilter);
    mGroupFilters.pushBack(mSensorGroupFilter);

    mContactMgr = new (heap) ContactMgr;
    if (mContactMgr)
        mContactMgr->init(heap);

    mMaterialTable = new (heap) MaterialTable;

    mSystemData = new (heap) SystemData;
    mSystemData->load(mPhysicsSystemHeap, mEntityGroupFilter, mSensorGroupFilter, mMaterialTable,
                      mContactMgr);
}

void System::removeSystemGroupHandler(SystemGroupHandler* handler) {
    mGroupFilters[static_cast<s32>(handler->getLayerType())]->removeSystemGroupHandler(handler);
}

ContactPointInfo* System::allocContactPointInfo(sead::Heap* heap, int num,
                                                const sead::SafeString& name, int a, int b,
                                                int c) const {
    return mContactMgr->makeContactPointInfo(heap, num, name, a, b, c);
}

void System::freeContactPointInfo(ContactPointInfo* info) const {
    mContactMgr->freeContactPointInfo(info);
}

CollisionInfo* System::allocCollisionInfo(sead::Heap* heap, const sead::SafeString& name) const {
    return mContactMgr->makeCollisionInfo(heap, name);
}

void System::freeCollisionInfo(CollisionInfo* info) const {
    mContactMgr->freeCollisionInfo(info);
}

ContactLayerCollisionInfoGroup*
System::makeContactLayerCollisionInfoGroup(sead::Heap* heap, ContactLayer layer, int capacity,
                                           const sead::SafeString& name) {
    return mContactMgr->makeContactLayerCollisionInfoGroup(heap, layer, capacity, name);
}

void System::freeContactLayerCollisionInfoGroup(ContactLayerCollisionInfoGroup* group) {
    mContactMgr->freeContactLayerCollisionInfoGroup(group);
}

GroupFilter* System::getGroupFilter(ContactLayerType type) const {
    return mGroupFilters[static_cast<s32>(type)];
}

RayCastForRequest* System::allocRayCastRequest(SystemGroupHandler* group_handler,
                                               GroundHit ground_hit) {
    return mRayCastRequestMgr->allocRequest(group_handler, ground_hit);
}

SystemGroupHandler* System::addSystemGroupHandler(ContactLayerType layer_type, int free_list_idx) {
    return getGroupFilter(layer_type)->addSystemGroupHandler(free_list_idx);
}

LayerContactPointInfo* System::allocLayerContactPointInfo(sead::Heap* heap, int num, int num2,
                                                          const sead::SafeString& name, int a,
                                                          int b, int c) const {
    return mContactMgr->makeLayerContactPointInfo(heap, num, num2, name, a, b, c);
}

void System::freeLayerContactPointInfo(LayerContactPointInfo* info) const {
    mContactListeners[static_cast<s32>(info->getLayerType())]->removeLayerPairsForContactPointInfo(
        info);
    mContactMgr->freeContactPointInfo(info);
}

void System::registerContactPointInfo(ContactPointInfo* info) const {
    mContactMgr->registerContactPointInfo(info);
}

void System::registerContactPointLayerPair(LayerContactPointInfo* info, ContactLayer layer1,
                                           ContactLayer layer2, bool enabled) {
    mContactListeners[static_cast<s32>(info->getLayerType())]->addLayerPairForContactPointInfo(
        info, layer1, layer2, enabled);
}

ContactLayerCollisionInfo* System::trackLayerPair(ContactLayer layer_a, ContactLayer layer_b) {
    return mContactListeners[static_cast<s32>(getContactLayerType(layer_a))]->trackLayerPair(
        layer_a, layer_b);
}

RagdollControllerKeyList* System::getRagdollCtrlKeyList() const {
    if (!mSystemData)
        return nullptr;
    return mSystemData->getRagdollCtrlKeyList();
}

}  // namespace ksys::phys
