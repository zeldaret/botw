#include "Game/AI/Action/actionKorokTargetMove.h"
#include <math/seadMatrixCalcCommon.hpp>
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/Physics/RigidBody/physRigidBody.h"
#include "KingSystem/System/VFR.h"

namespace uking::action {

KorokTargetMove::KorokTargetMove(const InitArg& arg) : ksys::act::ai::Action(arg) {}

KorokTargetMove::~KorokTargetMove() = default;

bool KorokTargetMove::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

void KorokTargetMove::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Action::enter_(params);
}

void KorokTargetMove::leave_() {
    ksys::act::ai::Action::leave_();
}

void KorokTargetMove::loadParams_() {
    getDynamicParam(&mSpeed_d, "Speed");
    getDynamicParam(&mIsBezier_d, "IsBezier");
    getDynamicParam(&mTargetPos_d, "TargetPos");
    getMapUnitParam(&mIsTargetWarp_m, "IsTargetWarp");
}

void KorokTargetMove::calc_() {
    auto* actor = mActor;
    auto* body = actor->getMainBody();
    if (*mIsBezier_d || *mIsTargetWarp_m) {
        body->setPosition(*mTargetPos_d);
        setFinished();
        return;
    }

    sead::Matrix34f mtx = actor->getMtx();
    sead::Vector3f pos(mtx(0, 3), mtx(1, 3), mtx(2, 3));

    ksys::VFR::chaseVec(&pos, *mTargetPos_d, *mSpeed_d);
    body->changePosition(pos, ksys::phys::KeepAngularVelocity{true});

    sead::Vector3f t = pos - *mTargetPos_d;
    if (t.length() < *mSpeed_d) {
        setFinished();
    }
}

}  // namespace uking::action
