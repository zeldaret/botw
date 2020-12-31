#include "Game/AI/AI/aiRemainsWaterRoot.h"

namespace uking::ai {

RemainsWaterRoot::RemainsWaterRoot(const InitArg& arg) : RemainsRoot(arg) {}

RemainsWaterRoot::~RemainsWaterRoot() = default;

bool RemainsWaterRoot::init_(sead::Heap* heap) {
    return RemainsRoot::init_(heap);
}

void RemainsWaterRoot::enter_(ksys::act::ai::InlineParamPack* params) {
    RemainsRoot::enter_(params);
}

void RemainsWaterRoot::leave_() {
    RemainsRoot::leave_();
}

void RemainsWaterRoot::loadParams_() {
    RemainsRoot::loadParams_();
    getAITreeVariable(&mRemainsWaterBattleInfo_a, "RemainsWaterBattleInfo");
}

}  // namespace uking::ai
