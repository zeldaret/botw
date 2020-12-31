#include "Game/AI/AI/aiGanonGrudgeNormal.h"

namespace uking::ai {

GanonGrudgeNormal::GanonGrudgeNormal(const InitArg& arg) : EnemyNormal(arg) {}

GanonGrudgeNormal::~GanonGrudgeNormal() = default;

bool GanonGrudgeNormal::init_(sead::Heap* heap) {
    return EnemyNormal::init_(heap);
}

void GanonGrudgeNormal::enter_(ksys::act::ai::InlineParamPack* params) {
    EnemyNormal::enter_(params);
}

void GanonGrudgeNormal::leave_() {
    EnemyNormal::leave_();
}

void GanonGrudgeNormal::loadParams_() {
    EnemyNormal::loadParams_();
}

}  // namespace uking::ai
