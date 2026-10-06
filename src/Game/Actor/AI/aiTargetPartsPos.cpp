#include "Game/Actor/AI/aiTargetPartsPos.h"

namespace uking::ai {

TargetPartsPos::TargetPartsPos(const InitArg& arg) : TargetActorPos(arg) {}

TargetPartsPos::~TargetPartsPos() = default;

bool TargetPartsPos::init_(sead::Heap* heap) {
    return TargetActorPos::init_(heap);
}

void TargetPartsPos::enter_(ksys::act::ai::InlineParamPack* params) {
    TargetActorPos::enter_(params);
}

void TargetPartsPos::leave_() {
    TargetActorPos::leave_();
}

void TargetPartsPos::loadParams_() {
    TargetActorPos::loadParams_();
    getStaticParam(&mPartsName_s, "PartsName");
}

}  // namespace uking::ai
