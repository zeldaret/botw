#include "Game/AI/Action/actionExplode.h"

namespace uking::action {

Explode::Explode(const InitArg& arg) : ksys::act::ai::Action(arg) {}

Explode::~Explode() = default;

bool Explode::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

void Explode::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Action::enter_(params);
}

void Explode::leave_() {
    ksys::act::ai::Action::leave_();
}

void Explode::loadParams_() {
    getStaticParam(&mSizeUpTime_s, "SizeUpTime");
    getStaticParam(&mExplodeTime_s, "ExplodeTime");
    getStaticParam(&mAttackIntensity_s, "AttackIntensity");
    getStaticParam(&mUseDefaultEffect_s, "UseDefaultEffect");
    getStaticParam(&mIsDelete_s, "IsDelete");
    getStaticParam(&mIsDamageGuarantee_s, "IsDamageGuarantee");
    getStaticParam(&mIsVanish_s, "IsVanish");
}

void Explode::calc_() {
    ksys::act::ai::Action::calc_();
}

}  // namespace uking::action
