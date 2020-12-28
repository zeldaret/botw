#include "Game/AI/Action/actionNPCTravelerRest.h"

namespace uking::action {

NPCTravelerRest::NPCTravelerRest(const InitArg& arg) : ksys::act::ai::Action(arg) {}

NPCTravelerRest::~NPCTravelerRest() = default;

void NPCTravelerRest::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Action::enter_(params);
}

void NPCTravelerRest::leave_() {
    ksys::act::ai::Action::leave_();
}

void NPCTravelerRest::loadParams_() {
    getDynamicParam(&mIsWarpHorse_d, "IsWarpHorse");
}

void NPCTravelerRest::calc_() {
    ksys::act::ai::Action::calc_();
}

}  // namespace uking::action
