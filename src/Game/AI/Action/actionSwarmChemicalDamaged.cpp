#include "Game/AI/Action/actionSwarmChemicalDamaged.h"

namespace uking::action {

SwarmChemicalDamaged::SwarmChemicalDamaged(const InitArg& arg) : SwarmDamaged(arg) {}

SwarmChemicalDamaged::~SwarmChemicalDamaged() = default;

bool SwarmChemicalDamaged::init_(sead::Heap* heap) {
    return SwarmDamaged::init_(heap);
}

void SwarmChemicalDamaged::enter_(ksys::act::ai::InlineParamPack* params) {
    SwarmDamaged::enter_(params);
}

void SwarmChemicalDamaged::leave_() {
    SwarmDamaged::leave_();
}

void SwarmChemicalDamaged::loadParams_() {
    SwarmDamaged::loadParams_();
    getStaticParam(&mResetChemicalTimer_s, "ResetChemicalTimer");
    getStaticParam(&mIsResetAllObject_s, "IsResetAllObject");
}

void SwarmChemicalDamaged::calc_() {
    SwarmDamaged::calc_();
}

}  // namespace uking::action
