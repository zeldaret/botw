#include "Game/AI/Action/actionSetTreasureBoxOpenAndClose.h"

namespace uking::action {

SetTreasureBoxOpenAndClose::SetTreasureBoxOpenAndClose(const InitArg& arg)
    : ksys::act::ai::Action(arg) {}

SetTreasureBoxOpenAndClose::~SetTreasureBoxOpenAndClose() = default;

bool SetTreasureBoxOpenAndClose::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

void SetTreasureBoxOpenAndClose::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Action::enter_(params);
}

void SetTreasureBoxOpenAndClose::leave_() {
    ksys::act::ai::Action::leave_();
}

void SetTreasureBoxOpenAndClose::loadParams_() {
    getDynamicParam(&mIsSetOpen_d, "IsSetOpen");
    getAITreeVariable(&mIsOpenTreasureBox_a, "IsOpenTreasureBox");
}

void SetTreasureBoxOpenAndClose::calc_() {
    ksys::act::ai::Action::calc_();
}

}  // namespace uking::action
