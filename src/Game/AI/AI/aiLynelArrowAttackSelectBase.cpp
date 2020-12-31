#include "Game/AI/AI/aiLynelArrowAttackSelectBase.h"

namespace uking::ai {

LynelArrowAttackSelectBase::LynelArrowAttackSelectBase(const InitArg& arg)
    : ksys::act::ai::Ai(arg) {}

LynelArrowAttackSelectBase::~LynelArrowAttackSelectBase() = default;

bool LynelArrowAttackSelectBase::init_(sead::Heap* heap) {
    return ksys::act::ai::Ai::init_(heap);
}

void LynelArrowAttackSelectBase::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Ai::enter_(params);
}

void LynelArrowAttackSelectBase::leave_() {
    ksys::act::ai::Ai::leave_();
}

void LynelArrowAttackSelectBase::loadParams_() {
    getAITreeVariable(&mLynelAIFlags_a, "LynelAIFlags");
}

}  // namespace uking::ai
