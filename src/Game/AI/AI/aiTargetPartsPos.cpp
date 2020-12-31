#include "Game/AI/AI/aiTargetPartsPos.h"

namespace uking::ai {

TargetPartsPos::TargetPartsPos(const InitArg& arg) : TargetPosAI(arg) {}

TargetPartsPos::~TargetPartsPos() = default;

bool TargetPartsPos::init_(sead::Heap* heap) {
    return TargetPosAI::init_(heap);
}

void TargetPartsPos::enter_(ksys::act::ai::InlineParamPack* params) {
    TargetPosAI::enter_(params);
}

void TargetPartsPos::leave_() {
    TargetPosAI::leave_();
}

void TargetPartsPos::loadParams_() {
    TargetPosAI::loadParams_();
    getStaticParam(&mPartsName_s, "PartsName");
}

}  // namespace uking::ai
