#include "Game/AI/Action/actionPreJumpAttack.h"

namespace uking::action {

PreJumpAttack::PreJumpAttack(const InitArg& arg) : PreAttack(arg) {}

PreJumpAttack::~PreJumpAttack() = default;

bool PreJumpAttack::init_(sead::Heap* heap) {
    return PreAttack::init_(heap);
}

void PreJumpAttack::enter_(ksys::act::ai::InlineParamPack* params) {
    PreAttack::enter_(params);
}

void PreJumpAttack::leave_() {
    PreAttack::leave_();
}

void PreJumpAttack::loadParams_() {
    PreAttack::loadParams_();
}

void PreJumpAttack::calc_() {
    PreAttack::calc_();
}

}  // namespace uking::action
