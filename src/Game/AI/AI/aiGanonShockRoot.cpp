#include "Game/AI/AI/aiGanonShockRoot.h"

namespace uking::ai {

GanonShockRoot::GanonShockRoot(const InitArg& arg) : ksys::act::ai::Ai(arg) {}

GanonShockRoot::~GanonShockRoot() = default;

bool GanonShockRoot::init_(sead::Heap* heap) {
    return ksys::act::ai::Ai::init_(heap);
}

void GanonShockRoot::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Ai::enter_(params);
}

void GanonShockRoot::leave_() {
    ksys::act::ai::Ai::leave_();
}

void GanonShockRoot::loadParams_() {
    getStaticParam(&mIsDoRecoverAction_s, "IsDoRecoverAction");
    getStaticParam(&mIsGuardJust_s, "IsGuardJust");
}

}  // namespace uking::ai
