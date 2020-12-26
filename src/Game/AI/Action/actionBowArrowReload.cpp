#include "Game/AI/Action/actionBowArrowReload.h"

namespace uking::action {

BowArrowReload::BowArrowReload(const InitArg& arg) : BindAction(arg) {}

BowArrowReload::~BowArrowReload() = default;

bool BowArrowReload::init_(sead::Heap* heap) {
    return BindAction::init_(heap);
}

void BowArrowReload::enter_(ksys::act::ai::InlineParamPack* params) {
    BindAction::enter_(params);
}

void BowArrowReload::leave_() {
    BindAction::leave_();
}

void BowArrowReload::loadParams_() {}

void BowArrowReload::calc_() {
    BindAction::calc_();
}

}  // namespace uking::action
