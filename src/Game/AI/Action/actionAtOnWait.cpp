#include "Game/AI/Action/actionAtOnWait.h"

namespace uking::action {

AtOnWait::AtOnWait(const InitArg& arg) : ksys::act::ai::Action(arg) {}

bool AtOnWait::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

void AtOnWait::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Action::enter_(params);
}

void AtOnWait::leave_() {
    ksys::act::ai::Action::leave_();
}

void AtOnWait::loadParams_() {
    getStaticParam(&mAtkAttrType_s, "AtkAttrType");
}

void AtOnWait::calc_() {
    ksys::act::ai::Action::calc_();
}

}  // namespace uking::action
