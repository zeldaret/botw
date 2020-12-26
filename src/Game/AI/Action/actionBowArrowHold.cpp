#include "Game/AI/Action/actionBowArrowHold.h"

namespace uking::action {

BowArrowHold::BowArrowHold(const InitArg& arg) : BindAction(arg) {}

BowArrowHold::~BowArrowHold() = default;

bool BowArrowHold::init_(sead::Heap* heap) {
    return BindAction::init_(heap);
}

void BowArrowHold::enter_(ksys::act::ai::InlineParamPack* params) {
    BindAction::enter_(params);
}

void BowArrowHold::leave_() {
    BindAction::leave_();
}

void BowArrowHold::loadParams_() {}

void BowArrowHold::calc_() {
    BindAction::calc_();
}

}  // namespace uking::action
