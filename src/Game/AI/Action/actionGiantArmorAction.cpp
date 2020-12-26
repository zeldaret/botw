#include "Game/AI/Action/actionGiantArmorAction.h"

namespace uking::action {

GiantArmorAction::GiantArmorAction(const InitArg& arg) : ActionWithPosAngReduce(arg) {}

GiantArmorAction::~GiantArmorAction() = default;

bool GiantArmorAction::init_(sead::Heap* heap) {
    return ActionWithPosAngReduce::init_(heap);
}

void GiantArmorAction::enter_(ksys::act::ai::InlineParamPack* params) {
    ActionWithPosAngReduce::enter_(params);
}

void GiantArmorAction::leave_() {
    ActionWithPosAngReduce::leave_();
}

void GiantArmorAction::loadParams_() {
    ActionWithPosAngReduce::loadParams_();
    getStaticParam(&mUseRestart_s, "UseRestart");
    getStaticParam(&mStartAS_s, "StartAS");
    getStaticParam(&mLoopAS_s, "LoopAS");
    getStaticParam(&mEndAS_s, "EndAS");
}

void GiantArmorAction::calc_() {
    ActionWithPosAngReduce::calc_();
}

}  // namespace uking::action
