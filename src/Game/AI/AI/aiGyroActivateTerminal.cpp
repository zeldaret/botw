#include "Game/AI/AI/aiGyroActivateTerminal.h"

namespace uking::ai {

GyroActivateTerminal::GyroActivateTerminal(const InitArg& arg) : ksys::act::ai::Ai(arg) {}

GyroActivateTerminal::~GyroActivateTerminal() = default;

bool GyroActivateTerminal::init_(sead::Heap* heap) {
    return ksys::act::ai::Ai::init_(heap);
}

void GyroActivateTerminal::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Ai::enter_(params);
}

void GyroActivateTerminal::leave_() {
    ksys::act::ai::Ai::leave_();
}

void GyroActivateTerminal::loadParams_() {}

}  // namespace uking::ai
