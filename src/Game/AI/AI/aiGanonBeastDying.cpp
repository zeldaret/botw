#include "Game/AI/AI/aiGanonBeastDying.h"

namespace uking::ai {

GanonBeastDying::GanonBeastDying(const InitArg& arg) : GanonBeastWait(arg) {}

GanonBeastDying::~GanonBeastDying() = default;

bool GanonBeastDying::init_(sead::Heap* heap) {
    return GanonBeastWait::init_(heap);
}

void GanonBeastDying::enter_(ksys::act::ai::InlineParamPack* params) {
    GanonBeastWait::enter_(params);
}

void GanonBeastDying::leave_() {
    GanonBeastWait::leave_();
}

void GanonBeastDying::loadParams_() {
    GanonBeastWait::loadParams_();
}

}  // namespace uking::ai
