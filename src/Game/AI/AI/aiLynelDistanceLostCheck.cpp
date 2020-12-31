#include "Game/AI/AI/aiLynelDistanceLostCheck.h"

namespace uking::ai {

LynelDistanceLostCheck::LynelDistanceLostCheck(const InitArg& arg) : DistanceLostCheck(arg) {}

LynelDistanceLostCheck::~LynelDistanceLostCheck() = default;

bool LynelDistanceLostCheck::init_(sead::Heap* heap) {
    return DistanceLostCheck::init_(heap);
}

void LynelDistanceLostCheck::enter_(ksys::act::ai::InlineParamPack* params) {
    DistanceLostCheck::enter_(params);
}

void LynelDistanceLostCheck::leave_() {
    DistanceLostCheck::leave_();
}

void LynelDistanceLostCheck::loadParams_() {
    DistanceLostCheck::loadParams_();
    getAITreeVariable(&mLynelAIFlags_a, "LynelAIFlags");
}

}  // namespace uking::ai
