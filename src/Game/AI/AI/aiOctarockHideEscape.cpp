#include "Game/AI/AI/aiOctarockHideEscape.h"

namespace uking::ai {

OctarockHideEscape::OctarockHideEscape(const InitArg& arg) : OctarockEscape(arg) {}

OctarockHideEscape::~OctarockHideEscape() = default;

bool OctarockHideEscape::init_(sead::Heap* heap) {
    return OctarockEscape::init_(heap);
}

void OctarockHideEscape::enter_(ksys::act::ai::InlineParamPack* params) {
    OctarockEscape::enter_(params);
}

void OctarockHideEscape::leave_() {
    OctarockEscape::leave_();
}

void OctarockHideEscape::loadParams_() {
    OctarockEscape::loadParams_();
    getStaticParam(&mEscapeDist_s, "EscapeDist");
}

}  // namespace uking::ai
