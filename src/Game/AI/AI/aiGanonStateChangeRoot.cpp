#include "Game/AI/AI/aiGanonStateChangeRoot.h"

namespace uking::ai {

GanonStateChangeRoot::GanonStateChangeRoot(const InitArg& arg) : ksys::act::ai::Ai(arg) {}

GanonStateChangeRoot::~GanonStateChangeRoot() = default;

bool GanonStateChangeRoot::init_(sead::Heap* heap) {
    return ksys::act::ai::Ai::init_(heap);
}

void GanonStateChangeRoot::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Ai::enter_(params);
}

void GanonStateChangeRoot::leave_() {
    ksys::act::ai::Ai::leave_();
}

void GanonStateChangeRoot::loadParams_() {
    getDynamicParam(&mTargetPos_d, "TargetPos");
}

}  // namespace uking::ai
