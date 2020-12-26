#include "Game/AI/Action/actionAtAndBodyOnWait.h"

namespace uking::action {

AtAndBodyOnWait::AtAndBodyOnWait(const InitArg& arg) : AtOnWait(arg) {}

AtAndBodyOnWait::~AtAndBodyOnWait() = default;

bool AtAndBodyOnWait::init_(sead::Heap* heap) {
    return AtOnWait::init_(heap);
}

void AtAndBodyOnWait::enter_(ksys::act::ai::InlineParamPack* params) {
    AtOnWait::enter_(params);
}

void AtAndBodyOnWait::leave_() {
    AtOnWait::leave_();
}

void AtAndBodyOnWait::loadParams_() {
    AtOnWait::loadParams_();
    getStaticParam(&mBodyName_s, "BodyName");
}

void AtAndBodyOnWait::calc_() {
    AtOnWait::calc_();
}

}  // namespace uking::action
