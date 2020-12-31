#include "Game/AI/AI/aiOctarockEscape.h"

namespace uking::ai {

OctarockEscape::OctarockEscape(const InitArg& arg) : ksys::act::ai::Ai(arg) {}

OctarockEscape::~OctarockEscape() = default;

bool OctarockEscape::init_(sead::Heap* heap) {
    return ksys::act::ai::Ai::init_(heap);
}

void OctarockEscape::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Ai::enter_(params);
}

void OctarockEscape::leave_() {
    ksys::act::ai::Ai::leave_();
}

void OctarockEscape::loadParams_() {
    getDynamicParam(&mTargetPos_d, "TargetPos");
}

}  // namespace uking::ai
