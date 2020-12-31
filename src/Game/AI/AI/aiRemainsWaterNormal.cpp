#include "Game/AI/AI/aiRemainsWaterNormal.h"

namespace uking::ai {

RemainsWaterNormal::RemainsWaterNormal(const InitArg& arg) : ksys::act::ai::Ai(arg) {}

RemainsWaterNormal::~RemainsWaterNormal() = default;

bool RemainsWaterNormal::init_(sead::Heap* heap) {
    return ksys::act::ai::Ai::init_(heap);
}

void RemainsWaterNormal::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Ai::enter_(params);
}

void RemainsWaterNormal::leave_() {
    ksys::act::ai::Ai::leave_();
}

void RemainsWaterNormal::loadParams_() {
    getStaticParam(&mInsideAreaWidth_s, "InsideAreaWidth");
    getStaticParam(&mInsideAreaCenter_s, "InsideAreaCenter");
    getStaticParam(&mInsideAreaWidth02_s, "InsideAreaWidth02");
    getStaticParam(&mInsideAreaCenter02_s, "InsideAreaCenter02");
}

}  // namespace uking::ai
