#include "Game/AI/Action/actionBowArrowShoot.h"

namespace uking::action {

BowArrowShoot::BowArrowShoot(const InitArg& arg) : BindAction(arg) {}

BowArrowShoot::~BowArrowShoot() = default;

bool BowArrowShoot::init_(sead::Heap* heap) {
    return BindAction::init_(heap);
}

void BowArrowShoot::enter_(ksys::act::ai::InlineParamPack* params) {
    BindAction::enter_(params);
}

void BowArrowShoot::leave_() {
    BindAction::leave_();
}

void BowArrowShoot::loadParams_() {}

void BowArrowShoot::calc_() {
    BindAction::calc_();
}

}  // namespace uking::action
