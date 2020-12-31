#include "Game/AI/AI/aiGanonBeastStairState.h"

namespace uking::ai {

GanonBeastStairState::GanonBeastStairState(const InitArg& arg) : ksys::act::ai::Ai(arg) {}

GanonBeastStairState::~GanonBeastStairState() = default;

bool GanonBeastStairState::init_(sead::Heap* heap) {
    return ksys::act::ai::Ai::init_(heap);
}

void GanonBeastStairState::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Ai::enter_(params);
}

void GanonBeastStairState::leave_() {
    ksys::act::ai::Ai::leave_();
}

void GanonBeastStairState::loadParams_() {}

}  // namespace uking::ai
