#include "Game/AI/Action/actionThrownDown.h"

namespace uking::action {

ThrownDown::ThrownDown(const InitArg& arg) : Ragdoll(arg) {}

ThrownDown::~ThrownDown() = default;

bool ThrownDown::init_(sead::Heap* heap) {
    return Ragdoll::init_(heap);
}

void ThrownDown::enter_(ksys::act::ai::InlineParamPack* params) {
    Ragdoll::enter_(params);
}

void ThrownDown::leave_() {
    Ragdoll::leave_();
}

void ThrownDown::loadParams_() {
    Ragdoll::loadParams_();
    getDynamicParam(&mSetupSpeed_d, "SetupSpeed");
}

void ThrownDown::calc_() {
    Ragdoll::calc_();
}

}  // namespace uking::action
