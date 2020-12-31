#include "Game/AI/AI/aiAssassinBossIronBallAttack.h"

namespace uking::ai {

AssassinBossIronBallAttack::AssassinBossIronBallAttack(const InitArg& arg)
    : ksys::act::ai::Ai(arg) {}

AssassinBossIronBallAttack::~AssassinBossIronBallAttack() = default;

bool AssassinBossIronBallAttack::init_(sead::Heap* heap) {
    return ksys::act::ai::Ai::init_(heap);
}

void AssassinBossIronBallAttack::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Ai::enter_(params);
}

void AssassinBossIronBallAttack::leave_() {
    ksys::act::ai::Ai::leave_();
}

void AssassinBossIronBallAttack::loadParams_() {
    getStaticParam(&mIronBallNum_s, "IronBallNum");
    getStaticParam(&mIronBallPartsName_s, "IronBallPartsName");
}

}  // namespace uking::ai
