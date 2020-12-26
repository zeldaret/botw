#include "Game/AI/Action/actionTurnWithAS.h"

namespace uking::action {

TurnWithAS::TurnWithAS(const InitArg& arg) : TurnBase(arg) {}

TurnWithAS::~TurnWithAS() = default;

bool TurnWithAS::init_(sead::Heap* heap) {
    return TurnBase::init_(heap);
}

void TurnWithAS::enter_(ksys::act::ai::InlineParamPack* params) {
    TurnBase::enter_(params);
}

void TurnWithAS::leave_() {
    TurnBase::leave_();
}

void TurnWithAS::loadParams_() {
    TurnBase::loadParams_();
    getStaticParam(&mASName_s, "ASName");
}

void TurnWithAS::calc_() {
    TurnBase::calc_();
}

}  // namespace uking::action
