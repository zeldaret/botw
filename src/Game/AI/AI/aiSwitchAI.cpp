#include "Game/AI/AI/aiSwitchAI.h"

namespace uking::ai {

SwitchAI::SwitchAI(const InitArg& arg) : ksys::act::ai::Ai(arg) {}

SwitchAI::~SwitchAI() = default;

bool SwitchAI::init_(sead::Heap* heap) {
    return ksys::act::ai::Ai::init_(heap);
}

void SwitchAI::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Ai::enter_(params);
}

void SwitchAI::leave_() {
    ksys::act::ai::Ai::leave_();
}

void SwitchAI::loadParams_() {}

}  // namespace uking::ai
