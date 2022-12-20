#include "KingSystem/Physics/Ragdoll/physRagdollInstanceMgr.h"
#include <prim/seadScopedLock.h>
#include "KingSystem/Physics/Ragdoll/physRagdollInstance.h"
#include "KingSystem/Physics/System/physSystem.h"

namespace ksys::phys {

RagdollInstanceMgr::RagdollInstanceMgr() = default;

RagdollInstanceMgr::~RagdollInstanceMgr() {
    mInstances.freeBuffer();
}

void RagdollInstanceMgr::init(sead::Heap* heap) {
    mInstances.alloc(0x400, heap);
}

bool RagdollInstanceMgr::addInstance(RagdollInstance* instance) {
    return mInstances.push(instance);
}

void RagdollInstanceMgr::removeInstance(RagdollInstance* instance) {
    auto lock = sead::makeScopedLock(mCS);
    mInstances.erase(instance);
}

void RagdollInstanceMgr::calc() {
    ScopedWorldLock world_lock{ContactLayerType::Entity};
    auto lock = sead::makeScopedLock(mCS);

    RagdollInstance* first_processed = nullptr;

    while (auto* instance = mInstances.pop()) {
        mInstances.push(instance);

        // If we have processed the entire buffer and wrapped around, stop.
        if (first_processed == instance)
            break;

        instance->update();

        if (first_processed == nullptr)
            first_processed = instance;
    }
}

void RagdollInstanceMgr::calc1() {}

}  // namespace ksys::phys
