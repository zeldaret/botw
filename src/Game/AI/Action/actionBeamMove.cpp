#include "Game/AI/Action/actionBeamMove.h"

namespace uking::action {

BeamMove::BeamMove(const InitArg& arg) : ksys::act::ai::Action(arg) {}

BeamMove::~BeamMove() = default;

bool BeamMove::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

void BeamMove::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Action::enter_(params);
}

void BeamMove::leave_() {
    ksys::act::ai::Action::leave_();
}

void BeamMove::loadParams_() {
    getStaticParam(&mAtMinDamage_s, "AtMinDamage");
    getStaticParam(&mShieldDamage_s, "ShieldDamage");
    getStaticParam(&mForceExplodeFrame_s, "ForceExplodeFrame");
    getAITreeVariable(&mIsReflectThrownBullet_a, "IsReflectThrownBullet");
}

void BeamMove::calc_() {
    ksys::act::ai::Action::calc_();
}

}  // namespace uking::action
