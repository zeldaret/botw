#include "Game/AI/AI/aiRupeeRabbitNormal.h"

namespace uking::ai {

RupeeRabbitNormal::RupeeRabbitNormal(const InitArg& arg) : PreyNormal(arg) {}

RupeeRabbitNormal::~RupeeRabbitNormal() = default;

bool RupeeRabbitNormal::init_(sead::Heap* heap) {
    return PreyNormal::init_(heap);
}

void RupeeRabbitNormal::enter_(ksys::act::ai::InlineParamPack* params) {
    PreyNormal::enter_(params);
}

void RupeeRabbitNormal::leave_() {
    PreyNormal::leave_();
}

void RupeeRabbitNormal::loadParams_() {
    PreyNormal::loadParams_();
    getMapUnitParam(&mDeleteEndNushiTime_m, "DeleteEndNushiTime");
}

}  // namespace uking::ai
