#include "Game/AI/Action/actionNPCGiveReward.h"

namespace uking::action {

NPCGiveReward::NPCGiveReward(const InitArg& arg) : ksys::act::ai::Action(arg) {}

NPCGiveReward::~NPCGiveReward() = default;

bool NPCGiveReward::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

void NPCGiveReward::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Action::enter_(params);
}

void NPCGiveReward::leave_() {
    ksys::act::ai::Action::leave_();
}

void NPCGiveReward::loadParams_() {}

void NPCGiveReward::calc_() {
    ksys::act::ai::Action::calc_();
}

}  // namespace uking::action
