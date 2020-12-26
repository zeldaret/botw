#include "Game/AI/Action/actionBackToRailFromLava.h"

namespace uking::action {

BackToRailFromLava::BackToRailFromLava(const InitArg& arg) : ksys::act::ai::Action(arg) {}

BackToRailFromLava::~BackToRailFromLava() = default;

bool BackToRailFromLava::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

void BackToRailFromLava::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Action::enter_(params);
}

void BackToRailFromLava::leave_() {
    ksys::act::ai::Action::leave_();
}

void BackToRailFromLava::loadParams_() {}

void BackToRailFromLava::calc_() {
    ksys::act::ai::Action::calc_();
}

}  // namespace uking::action
