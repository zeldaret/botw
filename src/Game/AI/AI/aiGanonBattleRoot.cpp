#include "Game/AI/AI/aiGanonBattleRoot.h"

namespace uking::ai {

GanonBattleRoot::GanonBattleRoot(const InitArg& arg) : ksys::act::ai::Ai(arg) {}

GanonBattleRoot::~GanonBattleRoot() = default;

bool GanonBattleRoot::init_(sead::Heap* heap) {
    return ksys::act::ai::Ai::init_(heap);
}

void GanonBattleRoot::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Ai::enter_(params);
}

void GanonBattleRoot::leave_() {
    ksys::act::ai::Ai::leave_();
}

void GanonBattleRoot::loadParams_() {}

}  // namespace uking::ai
