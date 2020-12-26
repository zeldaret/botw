#include "Game/AI/Action/actionMarkPosition.h"

namespace uking::action {

MarkPosition::MarkPosition(const InitArg& arg) : ksys::act::ai::Action(arg) {}

MarkPosition::~MarkPosition() = default;

bool MarkPosition::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

void MarkPosition::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Action::enter_(params);
}

void MarkPosition::leave_() {
    ksys::act::ai::Action::leave_();
}

void MarkPosition::loadParams_() {
    getDynamicParam(&mPositionX_d, "PositionX");
    getDynamicParam(&mPositionY_d, "PositionY");
    getDynamicParam(&mPositionZ_d, "PositionZ");
}

void MarkPosition::calc_() {
    ksys::act::ai::Action::calc_();
}

}  // namespace uking::action
