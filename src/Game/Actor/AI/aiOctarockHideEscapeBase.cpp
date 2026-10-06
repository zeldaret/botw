#include "Game/Actor/AI/aiOctarockHideEscapeBase.h"

namespace uking::ai {

OctarockHideEscapeBase::OctarockHideEscapeBase(const InitArg& arg) : ksys::act::ai::Ai(arg) {}

OctarockHideEscapeBase::~OctarockHideEscapeBase() = default;

bool OctarockHideEscapeBase::init_(sead::Heap* heap) {
    return ksys::act::ai::Ai::init_(heap);
}

void OctarockHideEscapeBase::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Ai::enter_(params);
}

void OctarockHideEscapeBase::leave_() {
    ksys::act::ai::Ai::leave_();
}

void OctarockHideEscapeBase::loadParams_() {
    getDynamicParam(&mTargetPos_d, "TargetPos");
}

}  // namespace uking::ai
