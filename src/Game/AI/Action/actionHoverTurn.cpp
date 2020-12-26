#include "Game/AI/Action/actionHoverTurn.h"

namespace uking::action {

HoverTurn::HoverTurn(const InitArg& arg) : TurnBase(arg) {}

HoverTurn::~HoverTurn() = default;

bool HoverTurn::init_(sead::Heap* heap) {
    return TurnBase::init_(heap);
}

void HoverTurn::enter_(ksys::act::ai::InlineParamPack* params) {
    TurnBase::enter_(params);
}

void HoverTurn::leave_() {
    TurnBase::leave_();
}

void HoverTurn::loadParams_() {
    TurnBase::loadParams_();
    getStaticParam(&mIsIgnoreSameAS_s, "IsIgnoreSameAS");
    getStaticParam(&mASKeyName_s, "ASKeyName");
}

void HoverTurn::calc_() {
    TurnBase::calc_();
}

}  // namespace uking::action
