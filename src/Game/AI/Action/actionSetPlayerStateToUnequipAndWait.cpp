#include "Game/AI/Action/actionSetPlayerStateToUnequipAndWait.h"

namespace uking::action {

SetPlayerStateToUnequipAndWait::SetPlayerStateToUnequipAndWait(const InitArg& arg)
    : ksys::act::ai::Action(arg) {}

SetPlayerStateToUnequipAndWait::~SetPlayerStateToUnequipAndWait() = default;

bool SetPlayerStateToUnequipAndWait::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

void SetPlayerStateToUnequipAndWait::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Action::enter_(params);
}

void SetPlayerStateToUnequipAndWait::leave_() {
    ksys::act::ai::Action::leave_();
}

void SetPlayerStateToUnequipAndWait::loadParams_() {}

void SetPlayerStateToUnequipAndWait::calc_() {
    ksys::act::ai::Action::calc_();
}

}  // namespace uking::action
