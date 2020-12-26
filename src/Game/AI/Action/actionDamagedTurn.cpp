#include "Game/AI/Action/actionDamagedTurn.h"

namespace uking::action {

DamagedTurn::DamagedTurn(const InitArg& arg) : ksys::act::ai::Action(arg) {}

DamagedTurn::~DamagedTurn() = default;

bool DamagedTurn::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

void DamagedTurn::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Action::enter_(params);
}

void DamagedTurn::leave_() {
    ksys::act::ai::Action::leave_();
}

void DamagedTurn::loadParams_() {
    getStaticParam(&mRotSpeed_s, "RotSpeed");
    getStaticParam(&mRotRatio_s, "RotRatio");
    getStaticParam(&mPosReduceRatio_s, "PosReduceRatio");
    getStaticParam(&mASName_s, "ASName");
}

void DamagedTurn::calc_() {
    ksys::act::ai::Action::calc_();
}

}  // namespace uking::action
