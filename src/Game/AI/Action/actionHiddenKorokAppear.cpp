#include "Game/AI/Action/actionHiddenKorokAppear.h"

namespace uking::action {

HiddenKorokAppear::HiddenKorokAppear(const InitArg& arg) : ksys::act::ai::Action(arg) {}

HiddenKorokAppear::~HiddenKorokAppear() = default;

bool HiddenKorokAppear::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

void HiddenKorokAppear::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Action::enter_(params);
}

void HiddenKorokAppear::leave_() {
    ksys::act::ai::Action::leave_();
}

void HiddenKorokAppear::loadParams_() {}

void HiddenKorokAppear::calc_() {
    ksys::act::ai::Action::calc_();
}

}  // namespace uking::action
