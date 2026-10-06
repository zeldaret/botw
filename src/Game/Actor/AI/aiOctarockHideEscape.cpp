#include "Game/Actor/AI/aiOctarockHideEscape.h"

namespace uking::ai {

OctarockHideEscape::OctarockHideEscape(const InitArg& arg) : OctarockHideEscapeBase(arg) {}

OctarockHideEscape::~OctarockHideEscape() = default;

bool OctarockHideEscape::init_(sead::Heap* heap) {
    return OctarockHideEscapeBase::init_(heap);
}

void OctarockHideEscape::enter_(ksys::act::ai::InlineParamPack* params) {
    OctarockHideEscapeBase::enter_(params);
}

void OctarockHideEscape::leave_() {
    OctarockHideEscapeBase::leave_();
}

void OctarockHideEscape::loadParams_() {
    OctarockHideEscapeBase::loadParams_();
    getStaticParam(&mEscapeDist_s, "EscapeDist");
}

}  // namespace uking::ai
