#include "Game/AI/AI/aiTargetLastDamagedPos.h"

namespace uking::ai {

TargetLastDamagedPos::TargetLastDamagedPos(const InitArg& arg) : TargetPosAI(arg) {}

TargetLastDamagedPos::~TargetLastDamagedPos() = default;

bool TargetLastDamagedPos::init_(sead::Heap* heap) {
    return TargetPosAI::init_(heap);
}

void TargetLastDamagedPos::enter_(ksys::act::ai::InlineParamPack* params) {
    TargetPosAI::enter_(params);
}

void TargetLastDamagedPos::leave_() {
    TargetPosAI::leave_();
}

void TargetLastDamagedPos::loadParams_() {
    TargetPosAI::loadParams_();
}

}  // namespace uking::ai
