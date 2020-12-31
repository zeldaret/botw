#include "Game/AI/AI/aiLynelRodeo.h"

namespace uking::ai {

LynelRodeo::LynelRodeo(const InitArg& arg) : ksys::act::ai::Ai(arg) {}

LynelRodeo::~LynelRodeo() = default;

bool LynelRodeo::init_(sead::Heap* heap) {
    return ksys::act::ai::Ai::init_(heap);
}

void LynelRodeo::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Ai::enter_(params);
}

void LynelRodeo::leave_() {
    ksys::act::ai::Ai::leave_();
}

void LynelRodeo::loadParams_() {
    getAITreeVariable(&mLynelRodeoAttackHitNum_a, "LynelRodeoAttackHitNum");
}

}  // namespace uking::ai
