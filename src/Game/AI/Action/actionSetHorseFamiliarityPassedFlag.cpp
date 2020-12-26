#include "Game/AI/Action/actionSetHorseFamiliarityPassedFlag.h"

namespace uking::action {

SetHorseFamiliarityPassedFlag::SetHorseFamiliarityPassedFlag(const InitArg& arg)
    : ksys::act::ai::Action(arg) {}

SetHorseFamiliarityPassedFlag::~SetHorseFamiliarityPassedFlag() = default;

bool SetHorseFamiliarityPassedFlag::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

void SetHorseFamiliarityPassedFlag::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Action::enter_(params);
}

void SetHorseFamiliarityPassedFlag::leave_() {
    ksys::act::ai::Action::leave_();
}

void SetHorseFamiliarityPassedFlag::loadParams_() {}

void SetHorseFamiliarityPassedFlag::calc_() {
    ksys::act::ai::Action::calc_();
}

}  // namespace uking::action
