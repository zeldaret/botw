#include "KingSystem/Physics/System/physSystem.h"
#include "KingSystem/Physics/Cloth/physClothResource.h"
#include "KingSystem/Physics/Ragdoll/physRagdollControllerKeyList.h"
#include "KingSystem/Physics/Ragdoll/physRagdollResource.h"
#include "KingSystem/Physics/RigidBody/TeraMesh/physTeraMeshRigidBodyResource.h"
#include "KingSystem/Physics/RigidBody/physRigidBodyResource.h"
#include "KingSystem/Physics/StaticCompound/physStaticCompound.h"
#include "KingSystem/Physics/SupportBone/physSupportBoneResource.h"
#include "KingSystem/Physics/System/physContactMgr.h"
#include "KingSystem/Physics/System/physContactPointInfo.h"
#include "KingSystem/Physics/System/physEntityGroupFilter.h"
#include "KingSystem/Physics/System/physMaterialTable.h"
#include "KingSystem/Physics/System/physSensorGroupFilter.h"
#include "KingSystem/Physics/System/physSystemData.h"
#include "KingSystem/Resource/resEntryFactory.h"
#include "KingSystem/Resource/resSystem.h"

namespace ksys::phys {

SEAD_SINGLETON_DISPOSER_IMPL(System)

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

ContactPointInfo* System::allocContactPointInfo(sead::Heap* heap, int num,
                                                const sead::SafeString& name, int a, int b,
                                                int c) const {
    return mContactMgr->makeContactPointInfo(heap, num, name, a, b, c);
}

void System::freeContactPointInfo(ContactPointInfo* info) const {
    mContactMgr->freeContactPointInfo(info);
}

LayerContactPointInfo* System::allocLayerContactPointInfo(sead::Heap* heap, int num, int num2,
                                                          const sead::SafeString& name, int a,
                                                          int b, int c) const {
    return mContactMgr->makeLayerContactPointInfo(heap, num, num2, name, a, b, c);
}

void System::registerContactPointInfo(ContactPointInfo* info) const {
    mContactMgr->registerContactPointInfo(info);
}

}  // namespace ksys::phys
