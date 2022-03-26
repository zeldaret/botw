#include "KingSystem/Physics/Ragdoll/physRagdollControllerMgr.h"
#include <prim/seadScopedLock.h>
#include "KingSystem/Physics/Ragdoll/physRagdollController.h"
#include "KingSystem/Physics/System/physSystem.h"

namespace ksys::phys {

RagdollControllerMgr::RagdollControllerMgr() = default;

RagdollControllerMgr::~RagdollControllerMgr() {
    mControllers.freeBuffer();
}

void RagdollControllerMgr::init(sead::Heap* heap) {
    mControllers.alloc(0x400, heap);
}

bool RagdollControllerMgr::addController(RagdollController* controller) {
    return mControllers.push(controller);
}

void RagdollControllerMgr::removeController(RagdollController* controller) {
    auto lock = sead::makeScopedLock(mCS);
    mControllers.erase(controller);
}

void RagdollControllerMgr::calc() {
    ScopedWorldLock world_lock{ContactLayerType::Entity};
    auto lock = sead::makeScopedLock(mCS);

    RagdollController* first_processed = nullptr;

    while (auto* ctrl = mControllers.pop()) {
        mControllers.push(ctrl);

        // If we have processed the entire buffer and wrapped around, stop.
        if (first_processed == ctrl)
            break;

        ctrl->update();

        if (first_processed == nullptr)
            first_processed = ctrl;
    }
}

void RagdollControllerMgr::calc1() {}

}  // namespace ksys::phys
