#include "Game/AI/AI/aiStoneBall_BRoot.h"

namespace uking::ai {

StoneBall_BRoot::StoneBall_BRoot(const InitArg& arg) : ksys::act::ai::Ai(arg) {}

StoneBall_BRoot::~StoneBall_BRoot() = default;

bool StoneBall_BRoot::init_(sead::Heap* heap) {
    return ksys::act::ai::Ai::init_(heap);
}

void StoneBall_BRoot::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Ai::enter_(params);
}

void StoneBall_BRoot::leave_() {
    ksys::act::ai::Ai::leave_();
}

void StoneBall_BRoot::loadParams_() {
    getStaticParam(&mWeaponImpulseAmplifyPower_s, "WeaponImpulseAmplifyPower");
    getStaticParam(&mBombImpulseAmplifyPower_s, "BombImpulseAmplifyPower");
    getStaticParam(&mDoubleBombImpulseAmplifyPower_s, "DoubleBombImpulseAmplifyPower");
}

}  // namespace uking::ai
