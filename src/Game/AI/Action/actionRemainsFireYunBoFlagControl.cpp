#include "Game/AI/Action/actionRemainsFireYunBoFlagControl.h"

namespace uking::action {

RemainsFireYunBoFlagControl::RemainsFireYunBoFlagControl(const InitArg& arg)
    : ksys::act::ai::Action(arg) {}

RemainsFireYunBoFlagControl::~RemainsFireYunBoFlagControl() = default;

bool RemainsFireYunBoFlagControl::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

void RemainsFireYunBoFlagControl::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Action::enter_(params);
}

void RemainsFireYunBoFlagControl::leave_() {
    ksys::act::ai::Action::leave_();
}

void RemainsFireYunBoFlagControl::loadParams_() {
    getMapUnitParam(&mRemainsFireYunBoFlagType_m, "RemainsFireYunBoFlagType");
}

void RemainsFireYunBoFlagControl::calc_() {
    ksys::act::ai::Action::calc_();
}

}  // namespace uking::action
