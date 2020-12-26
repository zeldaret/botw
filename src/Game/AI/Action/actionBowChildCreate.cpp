#include "Game/AI/Action/actionBowChildCreate.h"

namespace uking::action {

BowChildCreate::BowChildCreate(const InitArg& arg) : ksys::act::ai::Action(arg) {}

BowChildCreate::~BowChildCreate() = default;

bool BowChildCreate::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

void BowChildCreate::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Action::enter_(params);
}

void BowChildCreate::leave_() {
    ksys::act::ai::Action::leave_();
}

void BowChildCreate::loadParams_() {
    getDynamicParam(&mID_d, "ID");
    getDynamicParam(&mParentActor_d, "ParentActor");
}

void BowChildCreate::calc_() {
    ksys::act::ai::Action::calc_();
}

}  // namespace uking::action
