#include "Game/AI/Action/actionMoonMove.h"

namespace uking::action {

MoonMove::MoonMove(const InitArg& arg) : ksys::act::ai::Action(arg) {}

MoonMove::~MoonMove() = default;

bool MoonMove::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

void MoonMove::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Action::enter_(params);
}

void MoonMove::leave_() {
    ksys::act::ai::Action::leave_();
}

void MoonMove::loadParams_() {}

void MoonMove::calc_() {
    ksys::act::ai::Action::calc_();
}

}  // namespace uking::action
