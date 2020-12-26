#include "Game/AI/Action/actionSetOwnedHorseAS.h"

namespace uking::action {

SetOwnedHorseAS::SetOwnedHorseAS(const InitArg& arg) : ksys::act::ai::Action(arg) {}

SetOwnedHorseAS::~SetOwnedHorseAS() = default;

bool SetOwnedHorseAS::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

void SetOwnedHorseAS::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Action::enter_(params);
}

void SetOwnedHorseAS::leave_() {
    ksys::act::ai::Action::leave_();
}

void SetOwnedHorseAS::loadParams_() {
    getDynamicParam(&mASName_d, "ASName");
}

void SetOwnedHorseAS::calc_() {
    ksys::act::ai::Action::calc_();
}

}  // namespace uking::action
