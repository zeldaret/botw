#include "Game/AI/Action/actionAlarmLynelTag.h"

namespace uking::action {

AlarmLynelTag::AlarmLynelTag(const InitArg& arg) : ksys::act::ai::Action(arg) {}

AlarmLynelTag::~AlarmLynelTag() = default;

bool AlarmLynelTag::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

void AlarmLynelTag::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Action::enter_(params);
}

void AlarmLynelTag::leave_() {
    ksys::act::ai::Action::leave_();
}

void AlarmLynelTag::loadParams_() {
    getMapUnitParam(&mAlarmPoint_m, "AlarmPoint");
}

void AlarmLynelTag::calc_() {
    ksys::act::ai::Action::calc_();
}

}  // namespace uking::action
