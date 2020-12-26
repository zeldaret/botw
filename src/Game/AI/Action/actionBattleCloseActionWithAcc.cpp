#include "Game/AI/Action/actionBattleCloseActionWithAcc.h"

namespace uking::action {

BattleCloseActionWithAcc::BattleCloseActionWithAcc(const InitArg& arg) : BattleCloseAction(arg) {}

BattleCloseActionWithAcc::~BattleCloseActionWithAcc() = default;

bool BattleCloseActionWithAcc::init_(sead::Heap* heap) {
    return BattleCloseAction::init_(heap);
}

void BattleCloseActionWithAcc::enter_(ksys::act::ai::InlineParamPack* params) {
    BattleCloseAction::enter_(params);
}

void BattleCloseActionWithAcc::leave_() {
    BattleCloseAction::leave_();
}

void BattleCloseActionWithAcc::loadParams_() {
    BattleCloseAction::loadParams_();
    getStaticParam(&mAccRatio_s, "AccRatio");
}

void BattleCloseActionWithAcc::calc_() {
    BattleCloseAction::calc_();
}

}  // namespace uking::action
