#include "Game/AI/AI/aiTornadoRoot.h"

namespace uking::ai {

TornadoRoot::TornadoRoot(const InitArg& arg) : ksys::act::ai::Ai(arg) {}

TornadoRoot::~TornadoRoot() = default;

bool TornadoRoot::init_(sead::Heap* heap) {
    return ksys::act::ai::Ai::init_(heap);
}

void TornadoRoot::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Ai::enter_(params);
}

void TornadoRoot::leave_() {
    ksys::act::ai::Ai::leave_();
}

void TornadoRoot::loadParams_() {
    getStaticParam(&mIsHitOnlyPlayer_s, "IsHitOnlyPlayer");
    getMapUnitParam(&mAtMinDamage_m, "AtMinDamage");
    getMapUnitParam(&mAttackPower_m, "AttackPower");
}

}  // namespace uking::ai
