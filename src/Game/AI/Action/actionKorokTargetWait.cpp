#include "Game/AI/Action/actionKorokTargetWait.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/Physics/RigidBody/physRigidBody.h"

namespace uking::action {

KorokTargetWait::KorokTargetWait(const InitArg& arg) : ksys::act::ai::Action(arg) {}

KorokTargetWait::~KorokTargetWait() = default;

bool KorokTargetWait::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

void KorokTargetWait::enter_(ksys::act::ai::InlineParamPack* params) {
    mTime = 0;
}

void KorokTargetWait::leave_() {
    ksys::act::ai::Action::leave_();
}

void KorokTargetWait::loadParams_() {
    getStaticParam(&mSpeedDecreRate_s, "SpeedDecreRate");
    getDynamicParam(&mDynStopTime_d, "DynStopTime");
}

void KorokTargetWait::calc_() {
    mActor->getMainBody()->setLinearVelocity(sead::Vector3f::zero);
    if (mTime >= *mDynStopTime_d) {
        mFlags.set(ksys::act::ai::Action::Flag::Changeable);
        setFinished();
    } else {
        mTime += 1.0;
    }
}

}  // namespace uking::action
