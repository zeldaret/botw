#include "Game/AI/Action/actionBattleHover.h"

namespace uking::action {

BattleHover::BattleHover(const InitArg& arg) : Hover(arg) {}

BattleHover::~BattleHover() = default;

bool BattleHover::init_(sead::Heap* heap) {
    return Hover::init_(heap);
}

void BattleHover::enter_(ksys::act::ai::InlineParamPack* params) {
    Hover::enter_(params);
}

void BattleHover::leave_() {
    Hover::leave_();
}

void BattleHover::loadParams_() {
    Hover::loadParams_();
    getStaticParam(&mRotSpeed_s, "RotSpeed");
    getDynamicParam(&mTargetPos_d, "TargetPos");
}

void BattleHover::calc_() {
    Hover::calc_();
}

}  // namespace uking::action
