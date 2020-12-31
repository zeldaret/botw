#include "Game/AI/AI/aiTargetPlayerPos.h"

namespace uking::ai {

TargetPlayerPos::TargetPlayerPos(const InitArg& arg) : TargetPosAI(arg) {}

TargetPlayerPos::~TargetPlayerPos() = default;

bool TargetPlayerPos::init_(sead::Heap* heap) {
    return TargetPosAI::init_(heap);
}

void TargetPlayerPos::enter_(ksys::act::ai::InlineParamPack* params) {
    TargetPosAI::enter_(params);
}

void TargetPlayerPos::leave_() {
    TargetPosAI::leave_();
}

void TargetPlayerPos::loadParams_() {
    TargetPosAI::loadParams_();
}

}  // namespace uking::ai
