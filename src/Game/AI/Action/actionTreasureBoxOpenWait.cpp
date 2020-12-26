#include "Game/AI/Action/actionTreasureBoxOpenWait.h"

namespace uking::action {

TreasureBoxOpenWait::TreasureBoxOpenWait(const InitArg& arg) : ksys::act::ai::Action(arg) {}

TreasureBoxOpenWait::~TreasureBoxOpenWait() = default;

bool TreasureBoxOpenWait::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

void TreasureBoxOpenWait::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Action::enter_(params);
}

void TreasureBoxOpenWait::leave_() {
    ksys::act::ai::Action::leave_();
}

void TreasureBoxOpenWait::loadParams_() {
    getStaticParam(&mTargetIdx_s, "TargetIdx");
    getStaticParam(&mSeqBankIdx_s, "SeqBankIdx");
    getStaticParam(&mIsIgnoreSame_s, "IsIgnoreSame");
    getStaticParam(&mASName_s, "ASName");
    getStaticParam(&mASName_PreOpen_s, "ASName_PreOpen");
    getAITreeVariable(&mIsOpenTreasureBox_a, "IsOpenTreasureBox");
}

void TreasureBoxOpenWait::calc_() {
    ksys::act::ai::Action::calc_();
}

}  // namespace uking::action
