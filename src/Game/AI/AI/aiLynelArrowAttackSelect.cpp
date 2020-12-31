#include "Game/AI/AI/aiLynelArrowAttackSelect.h"

namespace uking::ai {

LynelArrowAttackSelect::LynelArrowAttackSelect(const InitArg& arg)
    : LynelArrowAttackSelectBase(arg) {}

LynelArrowAttackSelect::~LynelArrowAttackSelect() = default;

bool LynelArrowAttackSelect::init_(sead::Heap* heap) {
    return LynelArrowAttackSelectBase::init_(heap);
}

void LynelArrowAttackSelect::enter_(ksys::act::ai::InlineParamPack* params) {
    LynelArrowAttackSelectBase::enter_(params);
}

void LynelArrowAttackSelect::leave_() {
    LynelArrowAttackSelectBase::leave_();
}

void LynelArrowAttackSelect::loadParams_() {
    LynelArrowAttackSelectBase::loadParams_();
}

}  // namespace uking::ai
