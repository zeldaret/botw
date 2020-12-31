#include "Game/AI/AI/aiGanonBeastWait.h"

namespace uking::ai {

GanonBeastWait::GanonBeastWait(const InitArg& arg) : ksys::act::ai::Ai(arg) {}

GanonBeastWait::~GanonBeastWait() = default;

bool GanonBeastWait::init_(sead::Heap* heap) {
    return ksys::act::ai::Ai::init_(heap);
}

void GanonBeastWait::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Ai::enter_(params);
}

void GanonBeastWait::leave_() {
    ksys::act::ai::Ai::leave_();
}

void GanonBeastWait::loadParams_() {
    getAITreeVariable(&mIsWeakPointAppearMode_a, "IsWeakPointAppearMode");
}

}  // namespace uking::ai
