#include "Game/AI/Action/actionExpandSensorSlowly.h"

namespace uking::action {

ExpandSensorSlowly::ExpandSensorSlowly(const InitArg& arg) : ksys::act::ai::Action(arg) {}

ExpandSensorSlowly::~ExpandSensorSlowly() = default;

bool ExpandSensorSlowly::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

void ExpandSensorSlowly::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Action::enter_(params);
}

void ExpandSensorSlowly::leave_() {
    ksys::act::ai::Action::leave_();
}

void ExpandSensorSlowly::loadParams_() {
    getStaticParam(&mAtkAttrType_s, "AtkAttrType");
    getStaticParam(&mAtkType_s, "AtkType");
    getStaticParam(&mOffLength_s, "OffLength");
    getStaticParam(&mOnLength_s, "OnLength");
    getStaticParam(&mAtExpandStep_s, "AtExpandStep");
}

void ExpandSensorSlowly::calc_() {
    ksys::act::ai::Action::calc_();
}

}  // namespace uking::action
