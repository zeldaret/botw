#include "Game/AI/AI/aiWolfLinkBattleRoot.h"

namespace uking::ai {

WolfLinkBattleRoot::WolfLinkBattleRoot(const InitArg& arg) : ksys::act::ai::Ai(arg) {}

WolfLinkBattleRoot::~WolfLinkBattleRoot() = default;

bool WolfLinkBattleRoot::init_(sead::Heap* heap) {
    return ksys::act::ai::Ai::init_(heap);
}

void WolfLinkBattleRoot::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Ai::enter_(params);
}

void WolfLinkBattleRoot::leave_() {
    ksys::act::ai::Ai::leave_();
}

void WolfLinkBattleRoot::loadParams_() {
    getStaticParam(&mAttackIntiationRange_s, "AttackIntiationRange");
    getStaticParam(&mChanceToBarkOnAttackFail_s, "ChanceToBarkOnAttackFail");
    getStaticParam(&mUseChainAttack_s, "UseChainAttack");
    getDynamicParam(&mKeepTargetRange_d, "KeepTargetRange");
}

}  // namespace uking::ai
