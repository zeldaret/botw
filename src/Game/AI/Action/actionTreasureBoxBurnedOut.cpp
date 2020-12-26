#include "Game/AI/Action/actionTreasureBoxBurnedOut.h"

namespace uking::action {

TreasureBoxBurnedOut::TreasureBoxBurnedOut(const InitArg& arg) : ksys::act::ai::Action(arg) {}

TreasureBoxBurnedOut::~TreasureBoxBurnedOut() = default;

bool TreasureBoxBurnedOut::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

void TreasureBoxBurnedOut::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Action::enter_(params);
}

void TreasureBoxBurnedOut::leave_() {
    ksys::act::ai::Action::leave_();
}

void TreasureBoxBurnedOut::loadParams_() {
    getAITreeVariable(&mIsOpenTreasureBox_a, "IsOpenTreasureBox");
    getAITreeVariable(&mDropActorName_a, "DropActorName");
    getAITreeVariable(&mSharpWeaponAddParam_a, "SharpWeaponAddParam");
}

void TreasureBoxBurnedOut::calc_() {
    ksys::act::ai::Action::calc_();
}

}  // namespace uking::action
