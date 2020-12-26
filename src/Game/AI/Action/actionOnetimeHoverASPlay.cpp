#include "Game/AI/Action/actionOnetimeHoverASPlay.h"

namespace uking::action {

OnetimeHoverASPlay::OnetimeHoverASPlay(const InitArg& arg) : HoverBase(arg) {}

OnetimeHoverASPlay::~OnetimeHoverASPlay() = default;

bool OnetimeHoverASPlay::init_(sead::Heap* heap) {
    return HoverBase::init_(heap);
}

void OnetimeHoverASPlay::enter_(ksys::act::ai::InlineParamPack* params) {
    HoverBase::enter_(params);
}

void OnetimeHoverASPlay::leave_() {
    HoverBase::leave_();
}

void OnetimeHoverASPlay::loadParams_() {
    HoverBase::loadParams_();
    getStaticParam(&mIsIgnoreSameAS_s, "IsIgnoreSameAS");
    getStaticParam(&mASName_s, "ASName");
}

void OnetimeHoverASPlay::calc_() {
    HoverBase::calc_();
}

}  // namespace uking::action
