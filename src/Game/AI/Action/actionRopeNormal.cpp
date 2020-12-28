#include "Game/AI/Action/actionRopeNormal.h"

namespace uking::action {

RopeNormal::RopeNormal(const InitArg& arg) : ksys::act::ai::Action(arg) {}

bool RopeNormal::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

void RopeNormal::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Action::enter_(params);
}

void RopeNormal::leave_() {
    ksys::act::ai::Action::leave_();
}

void RopeNormal::loadParams_() {}

void RopeNormal::calc_() {
    ksys::act::ai::Action::calc_();
}

}  // namespace uking::action
