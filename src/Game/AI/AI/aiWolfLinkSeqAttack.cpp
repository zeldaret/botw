#include "Game/AI/AI/aiWolfLinkSeqAttack.h"

namespace uking::ai {

WolfLinkSeqAttack::WolfLinkSeqAttack(const InitArg& arg) : ksys::act::ai::Ai(arg) {}

WolfLinkSeqAttack::~WolfLinkSeqAttack() = default;

bool WolfLinkSeqAttack::init_(sead::Heap* heap) {
    return ksys::act::ai::Ai::init_(heap);
}

void WolfLinkSeqAttack::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Ai::enter_(params);
}

void WolfLinkSeqAttack::leave_() {
    ksys::act::ai::Ai::leave_();
}

void WolfLinkSeqAttack::loadParams_() {
    getStaticParam(&mDistBeginAttackAnimation_s, "DistBeginAttackAnimation");
    getStaticParam(&mAngleReqBeginAttackAnimationMin_s, "AngleReqBeginAttackAnimationMin");
    getStaticParam(&mAngleReqBeginAttackAnimationMax_s, "AngleReqBeginAttackAnimationMax");
    getStaticParam(&mPlayOnMissAI_s, "PlayOnMissAI");
    getStaticParam(&mChargeChainAttackOnHit_s, "ChargeChainAttackOnHit");
}

}  // namespace uking::ai
