#include "Game/AI/AI/aiZoraHeroRelicBattleRoot.h"

namespace uking::ai {

ZoraHeroRelicBattleRoot::ZoraHeroRelicBattleRoot(const InitArg& arg) : ksys::act::ai::Ai(arg) {}

ZoraHeroRelicBattleRoot::~ZoraHeroRelicBattleRoot() = default;

bool ZoraHeroRelicBattleRoot::init_(sead::Heap* heap) {
    return ksys::act::ai::Ai::init_(heap);
}

void ZoraHeroRelicBattleRoot::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Ai::enter_(params);
}

void ZoraHeroRelicBattleRoot::leave_() {
    ksys::act::ai::Ai::leave_();
}

void ZoraHeroRelicBattleRoot::loadParams_() {
    getAITreeVariable(&mZoraHeroShowMsgUnit_a, "ZoraHeroShowMsgUnit");
}

}  // namespace uking::ai
