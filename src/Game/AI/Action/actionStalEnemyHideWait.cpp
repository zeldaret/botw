#include "Game/AI/Action/actionStalEnemyHideWait.h"

namespace uking::action {

StalEnemyHideWait::StalEnemyHideWait(const InitArg& arg) : ActionWithPosAngReduce(arg) {}

StalEnemyHideWait::~StalEnemyHideWait() = default;

bool StalEnemyHideWait::init_(sead::Heap* heap) {
    return ActionWithPosAngReduce::init_(heap);
}

void StalEnemyHideWait::enter_(ksys::act::ai::InlineParamPack* params) {
    ActionWithPosAngReduce::enter_(params);
}

void StalEnemyHideWait::leave_() {
    ActionWithPosAngReduce::leave_();
}

void StalEnemyHideWait::loadParams_() {
    ActionWithPosAngReduce::loadParams_();
    getStaticParam(&mASName_s, "ASName");
}

void StalEnemyHideWait::calc_() {
    ActionWithPosAngReduce::calc_();
}

}  // namespace uking::action
