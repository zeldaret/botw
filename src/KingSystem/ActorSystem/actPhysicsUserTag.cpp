#include "KingSystem/ActorSystem/actPhysicsUserTag.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/ActorSystem/actBaseProcAccessor.h"
#include "KingSystem/ActorSystem/actBaseProcMgr.h"

namespace ksys::act {

PhysicsUserTag::PhysicsUserTag(Actor* actor) : mActor(actor) {}

PhysicsUserTag::~PhysicsUserTag() = default;

Actor* PhysicsUserTag::getActor(BaseProcAccessor* accessor, Actor* other_actor) const {
    if (mActor != nullptr) {
        if (mActor != other_actor && !BaseProcMgr::instance()->isAccessingProcSafe(mActor, nullptr))
            return mActor;
        if (!acquireProc(accessor, mActor, "act::PhysicsUserTag"))
            return nullptr;
    }
    return mActor;
}

bool PhysicsUserTag::acquireActor(BaseProcAccessor* accessor) const {
    return accessor->acquire(mActor);
}

const sead::SafeString& PhysicsUserTag::getName() const {
    return mActor->getName();
}

const sead::SafeString& PhysicsUserTag::getName(phys::RigidBody* rigid_body) const {
    return getName();
}

}  // namespace ksys::act
